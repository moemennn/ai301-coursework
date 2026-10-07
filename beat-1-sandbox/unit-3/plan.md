# Plan — Issue #67: Review creation does not verify profile ownership

- Issue: https://github.com/codepath/pathreview-ai301-fa26-s3/issues/67
- My reproduction (posted 2026-09-30): https://github.com/codepath/pathreview-ai301-fa26-s3/issues/67#issuecomment-5903439889
- Base commit: `2f4e82f52efbcfcc57d65b3fa5348672163ca088`
- Branch (on my fork): `fix/67-review-ownership-check`

## Repro evidence this plan relies on

All quotes below come from my posted reproduction comment.

The setup: Bob is authenticated and sends Alice's profile ID through the real `POST /reviews` route and the unmodified `create_review()`:

> The request is authenticated as Bob and sends Alice's profile ID

Raw output from that run:

```text
alice's profile  = d0ba02ab-223e-4cd2-a050-0f7ec3a94d7a  (owned by alice)

Bob -> POST /reviews {'profile_id': 'd0ba02ab-223e-4cd2-a050-0f7ec3a94d7a'}
2026-09-29 23:15:02 [info     ] review_created                 profile_id=d0ba02ab-223e-4cd2-a050-0f7ec3a94d7a review_id=2105f93c-e81d-4e69-b923-d57756a43330 user_id=d3de3257-bdcb-4be2-81d7-468960e48e0b
status: 200
background process_review scheduled for: [('2105f93c-e81d-4e69-b923-d57756a43330', UUID('d0ba02ab-223e-4cd2-a050-0f7ec3a94d7a'))]

reviews now attached to alice's profile in DB: 1

REPRODUCED: Bob created a review on Alice's profile (expected 403/404).
```

What that output established, as I wrote it in the comment:

> * the request returns HTTP `200`;
> * the returned review contains Alice's `profile_id`;
> * the review is persisted under Alice's profile in the database; and
> * the background `process_review` call is scheduled with Alice's profile ID.

And where I located the gap:

> From reading the current implementation, `create_review()` in `core/services/review_service.py` (lines 16–33) accepts `user_id` but does not use it to verify that the supplied profile belongs to that user before creating the `Review`.

> By comparison, the existing read paths such as `get_review()` and `list_reviews()` scope review access through `Profile.user_id`.

Limits of that evidence, also stated in the comment: it ran on SQLite rather than Postgres. The harness converted the profile ID to `str` before `create_review()` and removed duplicate index declarations so the tables could be created. None of those changes touch an ownership check.

## Diagnosis

`create_review()` never checks that `profile_id` belongs to `user_id`. It builds a `Review(profile_id=profile_id, ...)`, adds it, and commits. The `user_id` argument is accepted and never read. The route doesn't check ownership either. It calls `create_review()` and then schedules `process_review` on `data.profile_id`. So an authenticated user can attach a review to any profile whose UUID they know, and the background pipeline then runs on that profile.

The evidence supports this directly, beyond what code reading suggests. In the run, the `review_created` log line pairs Bob's `user_id` (`d3de3257-…`) with Alice's `profile_id` (`d0ba02ab-…`), and a row was persisted (`reviews now attached to alice's profile in DB: 1`). Nothing between the request and the commit rejected the mismatch.

## Scope

**I will change:**

1. `create_review()` will check ownership before it creates anything. If the profile isn't owned by `user_id`, it returns `None` and writes nothing.
2. `create_review_endpoint()` will turn that `None` into a `404`, before the background task is scheduled.
3. Unit tests for both the owner path and the non-owner path of `create_review()`.

**I will not change:**

- `get_review()`, `list_reviews()` and their routes. They already scope through `Profile.user_id`.
- `process_review()` and the ingestion, agent and RAG pipeline. After the fix it's never reached for a non-owner, because the route returns before `add_task`.
- `profile_service.py`. I reuse `get_profile()` as it is.
- The SQLite-only quirks my repro worked around: the `UUID(as_uuid=False)` bind error and the duplicate `ix_profiles_user_id` index. They're real, but they're harness problems, not this bug, and production uses Postgres with Alembic.
- The 13 `xfail(strict=True)` tests in `test_review_service.py` marked `issue #65: review_service tests misconfigure async mocks`. They belong to #65.
- Any cleanup of cross-owner reviews that may already exist in a database.
- The 404-vs-403 policy for the rest of the API.

## Files I'll touch

| File | Change |
|---|---|
| `core/services/review_service.py` | `create_review()`: owner-scoped lookup via `get_profile()`; return `None` when it misses; docstring and return type updated (`Review \| None`). |
| `api/routes/reviews.py` | `create_review_endpoint()`: raise `404` when `create_review()` returns `None`, before `background_tasks.add_task(...)`. |
| `tests/unit/test_review_service.py` | Two new tests. The six existing `create_review` tests patch `get_profile` so they keep testing what they tested before (see Risks). |

## Approach

**Service.** `core/services/profile_service.py` already has exactly the lookup this needs:

```python
async def get_profile(db, profile_id, user_id) -> Profile | None:
    """
    Get a profile by ID, checking ownership.
    """
    stmt = select(Profile).where((Profile.id == profile_id) & (Profile.user_id == user_id))
```

`create_review()` will call it first:

```python
profile = await get_profile(db, profile_id, user_id)
if profile is None:
    log.warning("review_create_profile_not_owned", profile_id=str(profile_id), user_id=str(user_id))
    return None
# existing Review(...) / add / commit / refresh unchanged
```

Returning `None` matches the service's existing convention: `get_review()` returns `None` for "not found or not yours", and so does `get_profile()`. It also keeps HTTP concerns out of the service layer. `review_service.py` doesn't import `HTTPException` today.

**Route.** In `create_review_endpoint()`, right after the `create_review(...)` call:

```python
if review is None:
    log.warning("review_profile_not_found", profile_id=str(data.profile_id), user_id=str(current_user.id))
    raise HTTPException(status_code=status.HTTP_404_NOT_FOUND, detail="Profile not found")
```

This sits before `background_tasks.add_task(...)`, so nothing is scheduled for a profile the caller doesn't own. The handler already has `except HTTPException: raise`, so the 404 passes through without being turned into a 500.

**Why 404 and not 403.** Every owner-scoped endpoint in this codebase returns 404 for "not found or not yours". `get_review_endpoint` and the profile routes all say `Returns 404 if not found or not owned by current user.` A 403 would also tell a caller that another user's profile ID exists. My repro comment said "a `403` or `404`". I'm choosing 404 for consistency, and I'll raise it as an open question in the plan comment rather than treat it as settled.

## Test plan

**1. Re-run my unit 2 repro, unchanged.** I'll use the same commit-pinned setup and the same `repro_issue_67.py` from my posted comment, run from the repo root on the fix branch:

```bash
python3.12 -m venv .venv
.venv/bin/pip install -e ".[dev]" aiosqlite
.venv/bin/python repro_issue_67.py; echo "exit=$?"
```

| Line in output | Before (quoted from my repro) | Expected after the fix |
|---|---|---|
| `status:` | `200` | `404` |
| `body:` | the created review, with Alice's `profile_id` | `{'detail': 'Profile not found'}` |
| `background process_review scheduled for:` | `[('2105f93c-…', UUID('d0ba02ab-…'))]` | `[]` |
| `reviews now attached to alice's profile in DB:` | `1` | `0` |
| last line / exit status | `REPRODUCED: …` / `1` | `NOT REPRODUCED: request was rejected.` / `0` |

The script's SQLite shim still converts the ID to a string before `create_review()`. The new lookup then receives a string ID, the same type the shim already feeds the `Review` insert, so the shim doesn't need to change.

**2. New unit tests in `tests/unit/test_review_service.py`.** Both should fail on `2f4e82f` and pass after the fix.

- `test_create_review_returns_none_for_profile_not_owned_by_user`: patch `core.services.review_service.get_profile` to return `None`. Assert that the result is `None` and that `db.add` and `db.commit` were never called. On current code this fails, because a `Review` is added and committed.
- `test_create_review_checks_ownership_with_requesting_user`: patch `get_profile` to return a profile. Assert it was awaited with `(db, profile_id, user_id)` and that the `Review` was built with that `profile_id` and `status="pending"`. This is the owner control. On current code it fails because `get_profile` is never called.

I'll run these once on `2f4e82f` before changing the service, to confirm they fail for the right reason. On that commit `review_service` doesn't import `get_profile` yet, so a plain `patch(...)` would fail with an `AttributeError` before any assertion runs. For that pre-fix run I'll patch with `create=True`, so the failure comes from the assertions themselves (a review was added and committed, and `get_profile` was never awaited).

**3. Suite and CI checks** (CONTRIBUTING requires `make check && make test-unit`):

```bash
.venv/bin/pytest tests/unit/test_review_service.py -v   # baseline on 2f4e82f: 6 passed, 13 xfailed
make check && make test-unit
```

Expected after the fix: `test_review_service.py` gives **8 passed, 13 xfailed**. That's the 6 existing tests plus my 2. The xfailed count must stay at 13. If it changes, I've accidentally touched #65's tests.

## Risks and unknowns

- **Existing tests will break unless I adjust them. I've verified this, it isn't a guess.** The six passing `create_review` tests use a session where `execute = AsyncMock()`. I ran that mock through the same calls `get_profile()` makes: `scalars()` returns a coroutine, and `.first()` raises `AttributeError: 'coroutine' object has no attribute 'first'`. That's the same misconfiguration #65 describes. **Mitigation:** in those six tests, patch `core.services.review_service.get_profile` to return a profile, so each test keeps checking what it checked before. I won't change the shared `mock_db_session` fixture. Fixing the fixture would likely flip #65's strict-xfail tests to XPASS and pull #65 into this change.
- **No Postgres run.** All of my evidence is on SQLite. The new query is the same one `get_profile()` already runs for `GET /profiles/{id}` with the same argument types, which reduces the risk, but I haven't run it on Postgres myself. **Validation:** the PR's CI `test-integration` job. If CI doesn't cover this path, I'll say so in the PR rather than claim it.
- **404 vs 403** is a policy choice. I'm following the file's existing convention and asking on the thread. If a maintainer prefers 403, only the route's status code and the expected `status:` line in step 1 change.
- **Circular import.** `review_service` will import from `profile_service`. `profile_service` imports only models and schemas, not `review_service`, so I don't expect a cycle. The first test run will confirm.
- **Another plan is already posted on the thread** (nydhy, 2026-10-06), with a similar direction. Under the course rules this doesn't block mine. My plan is built from my own route-level reproduction, and I'll keep my work on my own branch.

## Deviations

Built on `fix/67-review-ownership-check`, commit `ccae588`, on top of `2f4e82f`. The fix itself went as planned: `create_review()` calls `get_profile()` and returns `None` for a non-owner, and the route returns `404 "Profile not found"` before `add_task`. Nothing in my posted plan comment is now untrue, so I'm not posting a follow-up comment on the issue. These are the places where *how* I did it differed:

1. **How the six existing tests were fixed.** The plan said to patch `get_profile` in each of the six `create_review` tests. I added one `owned_profile` fixture that does that patch and requested it from those six tests instead. The effect is the same, and the diff is smaller: no existing assertions changed, and the shared `mock_db_session` fixture and #65's xfail tests are untouched. The risk I named showed up exactly as predicted. After the service change, before the fixture, all six failed with `AttributeError: 'coroutine' object has no attribute 'first'`.
2. **`create=True` is not in the committed tests.** As planned, I used it only for the pre-fix red run. There both new tests failed on their assertions: the non-owner test with `assert <Review(... status=pending)> is None`, and the owner test with `Expected mock to have been awaited once. Awaited 0 times.` After `get_profile` was imported into `review_service`, I removed it.
3. **Small additions in files the plan already named.** The route checks `if not review:` rather than `is None`, to match `get_review_endpoint` in the same file. I also added one docstring line to `create_review_endpoint` ("Returns 404 if the profile is not found or not owned by current user."), since CONTRIBUTING asks for docstrings and the other owner-scoped routes say this.
4. **`make check && make test-unit` couldn't run as written.** `make` on this machine stops with "You have not agreed to the Xcode license agreements". I ran the Makefile's underlying commands from `.venv` instead:
   - `ruff check .`: All checks passed.
   - `black --check` on the three changed files: unchanged. I didn't run `black .`, because it rewrites unrelated files across the repo.
   - `pytest tests/unit -m unit`: **377 passed, 53 xfailed**. On `main` the same command gives 375 passed, 53 xfailed, so that's my 2 new tests and no change to any xfail.
   - `mypy` as configured: fails on both `main` and my branch before checking any project code, on a numpy stub (`numpy/__init__.pyi:737: error: Type statement is only supported in Python 3.12 and greater`). `pyproject.toml` pins `python_version = "3.11"` and the installed numpy is 2.5.3. With `--python-version 3.12` it gives `Success: no issues found in 76 source files` on both. This is an environment issue, not my change, and I'll mention it in the PR if CI's mypy job behaves differently.
5. **The repro script was re-extracted from my posted comment.** My local copy was gone, so I took `repro_issue_67.py` verbatim from the code block in my repro comment (95 lines) and ran it from the repo root on the fix branch. It printed exactly the "Expected after the fix" column:

   ```text
   status: 404
   body:   {'detail': 'Profile not found'}
   background process_review scheduled for: []

   reviews now attached to alice's profile in DB: 0

   NOT REPRODUCED: request was rejected.
   ```

   It exited with status `0`. Both new warning logs fired: `review_create_profile_not_owned`, then `review_profile_not_found`.

Still open, unchanged from Risks: I haven't run this against Postgres, and 404 vs 403 is still waiting on maintainer input.
