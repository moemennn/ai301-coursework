# Unit 3 — Plan and Build

## Posted upstream

**GitHub username**

moemennn

**Plan comment**

https://github.com/codepath/pathreview-ai301-fa26-s3/issues/67#issuecomment-6030489431

Here's my plan for this, based on my reproduction above (https://github.com/codepath/pathreview-ai301-fa26-s3/issues/67#issuecomment-5903439889).

**What the repro showed:** with Bob authenticated and sending Alice's `profile_id` through the real `POST /reviews` route, the request returned `status: 200`, the log line paired Bob's `user_id` with Alice's `profile_id`, `process_review` was scheduled on her profile, and `reviews now attached to alice's profile in DB: 1`. `create_review()` accepts `user_id` but never reads it, and the route doesn't check ownership either.

**Change:**
- In `core/services/review_service.py`, `create_review()` first calls the existing `get_profile(db, profile_id, user_id)` from `profile_service.py`, which already filters on `Profile.user_id`. If that returns `None`, `create_review()` returns `None` without adding or committing anything. That matches how `get_review()` reports "not found or not yours".
- In `api/routes/reviews.py`, `create_review_endpoint()` turns `None` into a `404 "Profile not found"` *before* `background_tasks.add_task(...)`, so nothing gets scheduled for a profile the caller doesn't own.

**Not changing:** `get_review()`/`list_reviews()` (already scoped), `process_review` and the pipeline, or the #65 xfail tests. I'm also leaving alone the two SQLite-only problems my repro had to work around (the UUID bind error and the duplicate `ix_profiles_user_id` index). Those are harness problems, not this bug.

**How I'll verify:**
- I'll re-run the same `repro_issue_67.py` from my repro comment, unchanged. Before the fix it printed `status: 200`, `reviews now attached to alice's profile in DB: 1`, and exit 1. After the fix I expect `status: 404`, `process_review` scheduled for `[]`, `0` reviews on Alice's profile, `NOT REPRODUCED`, and exit 0.
- I'll add two unit tests to `test_review_service.py`. One checks that a non-owner gets `None` with no `db.add`/`commit`. The other checks that an owner still gets a pending review and that `get_profile` is called with the requesting user's ID. Both should fail on `2f4e82f`.
- I'll run `make check && make test-unit`.

**Risks I've already checked:**
- The six existing `create_review` tests mock `db.execute` with a bare `AsyncMock()`. I confirmed that the new lookup makes `.scalars().first()` raise `AttributeError` with that mock. I'll patch `get_profile` in those six tests rather than change the shared fixture, so #65's strict-xfail tests stay untouched.
- I haven't run this against Postgres, only SQLite.

**Open question:** I went with 404 rather than 403 because every other owner-scoped endpoint here says "Returns 404 if not found or not owned by current user", and a 404 doesn't reveal whether another user's profile exists. If 403 is preferred, it's a one-line change.

I'll build this on `fix/67-review-ownership-check` in my fork.

---

## Your branch

**Branch**

`fix/67-review-ownership-check`

(https://github.com/moemennn/pathreview-ai301-fa26-s3/tree/fix/67-review-ownership-check, fix commit `ccae588` on top of `2f4e82f`)

**Evidence**

My Unit 2 reproduction script, `repro_issue_67.py`, re-run unchanged against the built change. I copied it verbatim from the code block in my posted repro comment (https://github.com/codepath/pathreview-ai301-fa26-s3/issues/67#issuecomment-5903439889). It drives the real `POST /reviews` router and the real `create_review()`; the only stand-ins are the auth override, a `process_review` recorder, and the two SQLite shims that comment documents. For each run I checked out the commit, saved the script in the repo root, ran it, and deleted it. Environment: macOS 26.6.2 arm64, Python 3.12.4, SQLAlchemy 2.1.1, SQLite via `aiosqlite`.

Before (commit `2f4e82f`, the commit I reproduced on in Unit 2):

```text
$ git checkout 2f4e82f
$ git log --oneline -1
2f4e82f chore: track five more manifest entries against the tracker
$ .venv/bin/python repro_issue_67.py; echo "exit=$?"
alice.id         = 9e085fb1-7982-4b78-b156-ab07f1ab9e3a
bob.id           = 9808e8fb-e69d-4795-942e-07e1b667aa2e
alice's profile  = 79e3254d-11ec-4e46-9789-fad918d40915  (owned by alice)

Bob -> POST /reviews {'profile_id': '79e3254d-11ec-4e46-9789-fad918d40915'}
2026-10-06 23:55:11 [info     ] review_created                 profile_id=79e3254d-11ec-4e46-9789-fad918d40915 review_id=15b02d8b-eafb-4a99-b64d-8f7444756387 user_id=9808e8fb-e69d-4795-942e-07e1b667aa2e
status: 200
body:   {'id': '15b02d8b-eafb-4a99-b64d-8f7444756387', 'profile_id': '79e3254d-11ec-4e46-9789-fad918d40915', 'status': 'pending', 'sections': None, 'overall_score': None, 'error_message': None, 'created_at': '2026-10-07T03:55:11.646382', 'updated_at': '2026-10-07T03:55:11.646385'}
background process_review scheduled for: [('15b02d8b-eafb-4a99-b64d-8f7444756387', UUID('79e3254d-11ec-4e46-9789-fad918d40915'))]

reviews now attached to alice's profile in DB: 1

REPRODUCED: Bob created a review on Alice's profile (expected 403/404).
exit=1
```

After (commit `ccae588`, branch `fix/67-review-ownership-check`):

```text
$ git checkout ccae588
$ git log --oneline -1
ccae588 fix(reviews): verify profile ownership before creating a review
$ .venv/bin/python repro_issue_67.py; echo "exit=$?"
alice.id         = 8eb63a86-c455-4da0-b878-b68ad4f47d8d
bob.id           = c8276ae8-19f9-4d2d-8b9c-d6f49cafc737
alice's profile  = 0f2d67f2-a286-4c9a-b6b8-39439d9005b0  (owned by alice)

Bob -> POST /reviews {'profile_id': '0f2d67f2-a286-4c9a-b6b8-39439d9005b0'}
2026-10-06 23:55:12 [warning  ] review_create_profile_not_owned profile_id=0f2d67f2-a286-4c9a-b6b8-39439d9005b0 user_id=c8276ae8-19f9-4d2d-8b9c-d6f49cafc737
2026-10-06 23:55:12 [warning  ] review_profile_not_found       profile_id=0f2d67f2-a286-4c9a-b6b8-39439d9005b0 user_id=c8276ae8-19f9-4d2d-8b9c-d6f49cafc737
status: 404
body:   {'detail': 'Profile not found'}
background process_review scheduled for: []

reviews now attached to alice's profile in DB: 0

NOT REPRODUCED: request was rejected.
exit=0
```

The before-run matches what I posted in Unit 2 (`status: 200`, `reviews now attached to alice's profile in DB: 1`, `REPRODUCED`). The after-run prints `status: 404`, `background process_review scheduled for: []`, `reviews now attached to alice's profile in DB: 0`, `NOT REPRODUCED: request was rejected.` and `exit=0`, which is what my plan said to expect.

## Eval iterations

**Run history**

1. Full run: **18/20**. It missed pkg-09 and pkg-14 (both gold accept, graded reject), so the categories line would read `clear-accept 5/7`. I didn't save this run; I rebuilt the score from the per-package verdicts in the grader transcripts.
2. Full re-run with no changes to the rubric, evidence guide or procedure: **17/20**. pkg-09 and pkg-14 were still missed, and pkg-02 (gold accept) flipped to reject. Because nothing changed between runs 1 and 2, this drop came from the grader varying, not from an edit.
3. `--only pkg-03,pkg-09,pkg-12` after revising the rubric: **3/3** agreed. This was a partial run, so it printed no bar verdict.
4. Full confirming run on the same rubric, saved with `--save-run eval-run.txt`: **19/20**. The committed file reads:
   `categories: clear-accept 7/7  scope-creep 4/4  thread-convention 1/2  unbuildable 3/3  wrong-cause 4/4`
   `agreement: 19/20 scored items  (bar: 18/20: PASS)`

**Package analysis**

**pkg-20** (ghostty). The committed run shows `pkg-20  thread-convention  reject  accept   NO     graded accept`. My rubric decided **accept**. The gold label is **reject**: "excellent bounded plan that follows the thread's direction, but the comment contains no AI-use disclosure and ghostty's stated policy requires disclosing all AI usage; every package here is treated as AI-assisted work".

The package's repo facts say: "All AI usage in any form must be disclosed, stating the tool used and the extent of the assistance". The candidate plan comment has no disclosure line. My rubric reads this through the "Thread and repository alignment" check, which ends: "Do not require acknowledgments, disclosures, or formatting conventions that the repository has not specified." Ghostty does specify one, so the check should have failed. But the grader read the policy as conditional on evidence of AI use and passed it: "The AI policy requires disclosure only of AI use, and no AI use by the author is indicated."

My rubric never states the eval set's premise, that every package is AI-assisted work. So the grader treated "no AI use indicated" as "nothing to disclose". Every other check passed on substance, for example "A generation counter with recompute of `prev` on change fixes the stale pointer itself rather than masking the assert." So this one reading decided the verdict.

**Check rationale**

From the `rubric.md` I uploaded, as it reads now:

| Uncertainty and assumptions | The plan's diagnosis, assumptions, unresolved questions, and implementation approach compared against Repro evidence, Repo facts, and Thread highlights. | The plan does not present claims contradicted by evidence as established facts. Reasonable uncertainty about implementation details is acceptable if it does not undermine the proposed approach. Explicit validation steps are necessary only for critical unknowns that determine whether the proposed fix is viable. | required |

In my first rubric (runs 1 and 2) this check's pass condition read: "Important unknowns are acknowledged rather than presented as established facts. Any uncertainty that could change the root cause, implementation, or feasibility is either resolved by evidence or accompanied by a concrete validation step before implementation proceeds."

That wording held both "honestly scoped-down" clear accepts. On pkg-14 the grader failed it because "the debug-log trace is deferred into the PR rather than gating the design". On pkg-09 it graded it unclear because the plan "Assumes backslash-spelled glob patterns will match once candidates are normalized, with no validation step". The gold labels call both plans "arguable on the deferral, ready as scoped".

The old condition demanded a validation step for *any* uncertainty that *could* change the implementation, which almost every real plan has. So I narrowed it in three ways:
- What fails is presenting claims *contradicted by evidence* as facts.
- Uncertainty about implementation details is explicitly acceptable.
- A validation step is required only for "critical unknowns that determine whether the proposed fix is viable".

I rejected keeping the old "before implementation proceeds" gate. It graded a plan's honesty about open details as if it were a defect in the diagnosis. With the new wording, pkg-09 and pkg-14 both moved to accept, and the wrong-cause packages that this check also guards (pkg-01, pkg-07, pkg-11, pkg-16) stayed reject at 4/4.

**Trade-offs**

The same revision changed **pkg-20**'s result. I loosened the rubric as a whole: the alignment check gained "Do not require acknowledgments, disclosures, or formatting conventions that the repository has not specified", and the verdict rule now says "Do not assign `unclear` merely because additional information could be useful". In run 1, pkg-20 was correctly held on Thread alignment as `unclear`: "repo AI_POLICY.md requires all AI use to be disclosed and the comment has no AI-use statement either way". In the final run it passed, and `thread-convention` dropped from 2/2 to 1/2.

My `--only` canaries were pkg-03 (clear-accept) and pkg-12 (scope-creep), both of which held. But I didn't include a thread-convention canary, so the pkg-20 flip only showed up on the confirming full run. The category floor still holds through pkg-04, which stayed reject.

I accept that this rubric will miss a disclosure-required repo when the comment says nothing about AI use either way. The fix I'd make next is one sentence in the alignment check, stating that eval packages are treated as AI-assisted work, followed by an `--only pkg-20,pkg-04,pkg-09` run.
