# Unit 2 — Claim and Reproduce

Path: `beat-1-sandbox/unit-2/reproduction.md`

Record of your claim and reproduction on the issue you chose in Unit 1, and of the
evaluation runs that produced `eval-run.txt`. This file is graded at the path above; a copy
kept anywhere else in the repository is not read.

Complete every labelled field below. Each is graded on its own; content placed under the wrong
label is not graded.

---

## Your identity upstream

**GitHub username**

moemennn
---

## Posted upstream

**Claim comment**

https://github.com/codepath/pathreview-ai301-fa26-s3/issues/67#issuecomment-5903098086

Hi! I’d like to claim this issue.

I reviewed the current implementation and confirmed that create_review_endpoint() passes current_user.id into create_review(), but create_review() does not use that value before creating the Review with the supplied profile_id. I also noticed that get_review() and list_reviews() already scope their queries through Profile.user_id.

I plan to reproduce the behavior first, then update review creation to verify that the requested profile belongs to the authenticated user and add coverage for that case.

**Reproduction comment**

https://github.com/codepath/pathreview-ai301-fa26-s3/issues/67#issuecomment-5903439889

# Reproduction Report — Issue #67

## Result

With this SQLite-based test setup, I reproduced the behavior described in issue #67: an authenticated user can create a review associated with a profile owned by another user.

## Environment

* Repository: `codepath/pathreview-ai301-fa26-s3`
* Commit: `2f4e82f52efbcfcc57d65b3fa5348672163ca088`
* OS: macOS 26.6.2 (build 25G83), arm64
* Python: 3.12.4
* SQLAlchemy: 2.1.1 (also: FastAPI 0.142.1, Pydantic 2.13.5, aiosqlite 0.22.1)
* Install method: pip into a venv (`pip install -e ".[dev]" aiosqlite`)
* Database used for reproduction: SQLite (via `aiosqlite`, temporary file DB)
* Production database: Postgres

Postgres and Docker were not available on this machine, so I used a temporary SQLite database for the reproduction.

## Reproduction setup

The test creates two users:

* Alice, who owns a profile
* Bob, who is authenticated for the request

Bob submits Alice's profile ID to `POST /reviews`.

The reproduction uses the real review route and the existing `create_review()` ownership logic, with the following test-only changes:

1. Authentication is overridden so the request is treated as Bob:
   The script mounts the real `api.routes.reviews.router` on a minimal `FastAPI()` app and sets `app.dependency_overrides[get_current_user] = lambda: bob`, where `bob` is the `User` row seeded in the database. `get_db` is not overridden. The real `AsyncSessionLocal` is used, with `DATABASE_URL` pointed at the SQLite file.

2. `process_review` is replaced with a recorder so I can verify that the background task was scheduled without running the full ingestion pipeline:
   `api.routes.reviews.process_review` is monkeypatched to `lambda db, rid, pid: scheduled.append((rid, pid))`. The route still calls `background_tasks.add_task(process_review, db, review.id, data.profile_id)` as written. Only the task body is replaced.

3. Before the value reaches `create_review()`, the profile ID is converted from `uuid.UUID` to `str` because SQLite's `UUID(as_uuid=False)` handling otherwise produces:

   ```text
   'UUID' object has no attribute 'replace'
   ```

   This is done by wrapping `api.routes.reviews.create_review` in a function that calls the original `core.services.review_service.create_review(db, str(profile_id), user_id)`.

4. Duplicate index definitions are removed only in the reproduction harness before creating the SQLite tables because the models define `ix_profiles_user_id` through both `index=True` and an explicit `Index`.

The ownership logic inside `create_review()` is not modified.

## Steps

1. Check out the commit and install dependencies:

   ```bash
   git clone https://github.com/codepath/pathreview-ai301-fa26-s3.git
   cd pathreview-ai301-fa26-s3
   git checkout 2f4e82f52efbcfcc57d65b3fa5348672163ca088

   python3.12 -m venv .venv
   .venv/bin/pip install -e ".[dev]" aiosqlite
   ```

   `aiosqlite` is not a project dependency and is only needed for this harness. No Postgres, Redis, or `.env` is required.

2. Save the script below as `repro_issue_67.py` in the repository root.

3. Run it from the repository root:

   ```bash
   .venv/bin/python repro_issue_67.py
   ```

   It exits with status `1` when the bug reproduces and `0` when the request is rejected. The output shown under "Actual behavior" was captured from this exact command. Fresh UUIDs are generated on every run.

<details>
<summary><code>repro_issue_67.py</code></summary>

```python
"""Repro for issue #67: POST /reviews does not verify profile ownership.

Runs the real reviews router + real create_review() against a throwaway SQLite DB.
Only auth (get_current_user) and the background pipeline are stubbed.
"""

import asyncio
import os
import sys
import tempfile

DB_PATH = os.path.join(tempfile.mkdtemp(), "repro67.db")
os.environ["DATABASE_URL"] = f"sqlite+aiosqlite:///{DB_PATH}"
os.environ["APP_ENV"] = "test"
sys.path.insert(0, os.getcwd())

from fastapi import FastAPI  # noqa: E402
from fastapi.testclient import TestClient  # noqa: E402

import api.routes.reviews as reviews_routes  # noqa: E402
from api.middleware.auth import get_current_user  # noqa: E402
from core.database import AsyncSessionLocal, Base, engine, get_db  # noqa: E402
from core.models import ingested_source, profile, review, user  # noqa: E402,F401
from core.models.profile import Profile  # noqa: E402
from core.models.review import Review  # noqa: E402
from core.models.user import User  # noqa: E402


async def seed():
    # Models declare some indexes twice (index=True + explicit Index); the real app
    # builds its schema via Alembic, so drop the duplicates for this scratch DB only.
    for table in Base.metadata.tables.values():
        seen = set()
        for idx in list(table.indexes):
            if idx.name in seen:
                table.indexes.discard(idx)
            seen.add(idx.name)
    async with engine.begin() as conn:
        await conn.run_sync(Base.metadata.create_all)
    async with AsyncSessionLocal() as s:
        alice = User(email="alice@example.com", hashed_password="x")
        bob = User(email="bob@example.com", hashed_password="x")
        s.add_all([alice, bob])
        await s.flush()
        alice_profile = Profile(user_id=alice.id, github_username="alice")
        s.add(alice_profile)
        await s.commit()
        return alice.id, bob, alice_profile.id


async def reviews_on(profile_id):
    from sqlalchemy import select

    async with AsyncSessionLocal() as s:
        return (await s.execute(select(Review).where(Review.profile_id == profile_id))).scalars().all()


alice_id, bob, alice_profile_id = asyncio.run(seed())
print(f"alice.id         = {alice_id}")
print(f"bob.id           = {bob.id}")
print(f"alice's profile  = {alice_profile_id}  (owned by alice)")

app = FastAPI()
app.include_router(reviews_routes.router)
app.dependency_overrides[get_current_user] = lambda: bob  # authenticated as Bob

# Don't run the ingestion/agent pipeline; just record that it would have been scheduled.
scheduled = []
reviews_routes.process_review = lambda db, rid, pid: scheduled.append((rid, pid))

# SQLite-only shim: UUID(as_uuid=False) columns choke on uuid.UUID binds under SQLite
# (asyncpg on Postgres accepts them). Stringify the id; create_review itself is unchanged.
_real_create_review = reviews_routes.create_review


async def _create_review_sqlite(db, profile_id, user_id):
    return await _real_create_review(db, str(profile_id), user_id)


reviews_routes.create_review = _create_review_sqlite

client = TestClient(app)
print(f"\nBob -> POST /reviews {{'profile_id': '{alice_profile_id}'}}")
resp = client.post("/reviews", json={"profile_id": alice_profile_id})
print(f"status: {resp.status_code}")
print(f"body:   {resp.json()}")
print(f"background process_review scheduled for: {scheduled}")

rows = asyncio.run(reviews_on(alice_profile_id))
print(f"\nreviews now attached to alice's profile in DB: {len(rows)}")

if resp.status_code == 200 and rows:
    print("\nREPRODUCED: Bob created a review on Alice's profile (expected 403/404).")
    sys.exit(1)
print("\nNOT REPRODUCED: request was rejected.")
```

</details>

## Input

The request is authenticated as Bob and sends Alice's profile ID:

```http
POST /reviews
Content-Type: application/json

{
  "profile_id": "d0ba02ab-223e-4cd2-a050-0f7ec3a94d7a"
}
```

## Expected behavior

Because Bob does not own Alice's profile, the request should be rejected with a `403` or `404`.

No review should be created for Alice's profile.

## Actual behavior

The request succeeds.

Raw output:

```text
alice.id         = 5940d8d0-d1be-4bf3-b6bc-fb25471de4d8
bob.id           = d3de3257-bdcb-4be2-81d7-468960e48e0b
alice's profile  = d0ba02ab-223e-4cd2-a050-0f7ec3a94d7a  (owned by alice)

Bob -> POST /reviews {'profile_id': 'd0ba02ab-223e-4cd2-a050-0f7ec3a94d7a'}
2026-09-29 23:15:02 [info     ] review_created                 profile_id=d0ba02ab-223e-4cd2-a050-0f7ec3a94d7a review_id=2105f93c-e81d-4e69-b923-d57756a43330 user_id=d3de3257-bdcb-4be2-81d7-468960e48e0b
status: 200
body:   {'id': '2105f93c-e81d-4e69-b923-d57756a43330', 'profile_id': 'd0ba02ab-223e-4cd2-a050-0f7ec3a94d7a', 'status': 'pending', 'sections': None, 'overall_score': None, 'error_message': None, 'created_at': '2026-09-30T03:15:02.498095', 'updated_at': '2026-09-30T03:15:02.498098'}
background process_review scheduled for: [('2105f93c-e81d-4e69-b923-d57756a43330', UUID('d0ba02ab-223e-4cd2-a050-0f7ec3a94d7a'))]

reviews now attached to alice's profile in DB: 1

REPRODUCED: Bob created a review on Alice's profile (expected 403/404).
```

The output shows:

* the request returns HTTP `200`;
* the returned review contains Alice's `profile_id`;
* the review is persisted under Alice's profile in the database; and
* the background `process_review` call is scheduled with Alice's profile ID.

Note that the `review_created` log line records Bob's `user_id` (`d3de3257-…`) next to Alice's `profile_id` (`d0ba02ab-…`).

The reproduction harness records the scheduling of `process_review`; it does not execute the ingestion pipeline itself.

## Where the ownership check appears to be missing

From reading the current implementation, `create_review()` in `core/services/review_service.py` (lines 16–33) accepts `user_id` but does not use it to verify that the supplied profile belongs to that user before creating the `Review`.

The route (`api/routes/reviews.py`, lines 37–44) passes the authenticated user's ID into `create_review()`, but the ownership check is not performed before the review is created.

By comparison, the existing read paths such as `get_review()` and `list_reviews()` scope review access through `Profile.user_id`.

## SQLite-specific differences

This reproduction differs from a production run in three ways:

### SQLite instead of Postgres

The reproduction uses SQLite because Postgres and Docker were unavailable locally.

### UUID conversion

SQLite fails when the `UUID(as_uuid=False)` column receives a `uuid.UUID` object, so the reproduction harness converts the profile ID to a string before it reaches `create_review()`.

This change is only to avoid the SQLite-specific UUID error. It does not add or remove an ownership check.

Without this conversion, the same request returns `500 {"detail": "Failed to create review"}` under SQLite. The failure comes from the SQLite UUID bind error, not from any ownership check.

### Duplicate indexes

Direct table creation from the models fails because `ix_profiles_user_id` is declared twice.

The reproduction harness removes those duplicate index declarations before creating the SQLite tables.

The application's normal database setup uses Alembic instead.

## Conclusion

With this SQLite-based setup, Bob was able to submit Alice's profile ID to `POST /reviews` and receive a successful response that created a review associated with Alice's profile.

This reproduces the missing ownership validation behavior described in issue #67 under the test setup above.


## Eval iterations

**Run history**

1. Full run, first rubric: **16/20**, category floor unmet. It missed pkg-10 (gold accept, graded reject), pkg-16, pkg-19 and pkg-20 (gold reject, graded accept). With pkg-20 missed, `disclosure` was 0/1. I didn't use `--save-run` on this run. I rebuilt the score by comparing each package's verdict in the grader transcripts against `gold-labels.json`.
2. `--only pkg-10,pkg-16,pkg-19,pkg-20` on the revised rubric: **4/4 agreed**. This was a partial run, so it printed no bar verdict.
3. Full confirming run on the same revised rubric, with `--save-run eval-run.txt`: **19/20**. The committed file reads:
   `categories: clear-accept 7/8  disclosure 1/1  no-evidence 4/4  unfollowable-comms 3/3  wrong-target 4/4`
   `agreement: 19/20 scored items  (bar: 18/20: PASS)`

**Package analysis**

**pkg-09** (sharkdp/fd#2033). The committed run shows:
`pkg-09  accept  reject   NO     failed: Input`

My rubric decided **reject**. The gold label is **accept**: "honest cannot-reproduce: real attempt at the argument-size reordering with marker-order artifacts, names what differed (uniform name lengths, 2 MiB ARG_MAX) and what a triggering setup likely needs".

The rubric read it this way because of how its Input check is worded: "Pass if it matches the issue's triggering conditions, or any differences are justified and still exercise the same behavior." The report is candid about whether its input reaches the trigger: "my padding approach may not achieve that, since fd appears to flush both command buffers at the same file-count boundary on this input (uniform name lengths)." The grader took that candor as proof the trigger was never exercised: "the input never demonstrably exercised the issue's triggering condition, and no justified equivalence is established."

My rubric allows an honest cannot-reproduce in the Output check and in the verdict rule, but not in Input. So an attempt that says its own input might be insufficient fails Input on its own terms, even when every other check passes. The gold label rewards exactly that honesty: the report names what differed and what a triggering setup would likely need. In run 1, the first rubric passed this same package on Input: "limitation explicitly justified".

**Check rationale**

From `rubric.md`, as it reads now:

> | Repo communication requirements | The claim comment read against the repo-facts block, repository contribution guidance, issue templates, and any disclosure requirements. | Pass if the proposed comment satisfies any applicable repository requirements, including required AI-use disclosure, and does not omit information the repository explicitly requires. | required |

In the first rubric this check was "Repo conventions", weighted `preferred`, with the pass condition "Pass if the wording and proposed post respect the repository's relevant conventions and do not conflict with known project guidance." That version failed pkg-20 in two ways. First, it was preferred, and "Preferred checks do not change the final verdict", so it could never hold a package. Second, "relevant conventions" never pointed the grader at disclosure. In run 1 the grader graded pkg-20 accept and flagged only an Evidence problem, never the missing AI disclosure. The gold label says "ghostty's stated AI policy requires disclosing all AI usage and the comments do not disclose".

I revised the check in three ways:
- I made it `required`.
- I narrowed its evidence to the claim comment read against the repo-facts block and contribution guidance.
- I named "required AI-use disclosure" explicitly.

I kept the pass condition conditional ("any applicable repository requirements", "information the repository explicitly requires") and rejected a blanket "must disclose AI use". A blanket rule would fail packages from repos that have no such requirement, like pkg-05 ("conda's stated generative-AI policy is permissive-with-responsibility, no disclosure requirement"). It would also fail pkg-03, where a human-voiced comment satisfies ripgrep's rule without a disclosure line. After the revision, pkg-20 went from accept to reject (`disclosure 1/1`), and pkg-03, pkg-05 and pkg-07 stayed accept.

**Trade-offs**

The revision changed pkg-09's result, from accept in run 1 to reject in run 3. The new verdict rule is "Ready only if every required check passes". The old rule was "Ready if the Input, Command, and Output checks all pass". I also added `Followable steps` and `Target behavior` as required checks and made `Evidence supports claims` required. Together, that gives a clear accept more ways to be held.

pkg-09 wasn't in my `--only` list. Run 2 re-ran only the four packages I was trying to fix, with no already-agreeing canaries, so the flip first showed up on the confirming full run. I haven't re-run pkg-09 alone. With one run on each rubric, I can't tell whether the flip comes from rewording Input ("preserve the condition the issue is testing" became "still exercise the same behavior") or from grader variance. I accept that this rubric will sometimes hold an honest cannot-reproduce whose report admits its input may not reach the trigger. That's the case it will miss. In return it catches pkg-16, pkg-19 and pkg-20, and it still clears the 18/20 bar and every category floor.

Related paths: `eval-run.txt` in this directory; your skill's files in
`tools/repro-check/`.
