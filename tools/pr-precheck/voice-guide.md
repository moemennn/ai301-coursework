# Voice guide: how I talk upstream

## Who I am in threads

I am a student developer contributing to the repository and still learning the codebase. When I comment on an issue, I am usually reporting what I tested and what I observed rather than claiming I know the root cause.

Readers can expect me to be direct about my setup, reproduction steps, results, and anything I am unsure about.

When I open a pull request, I am asking a maintainer to spend review time on my work. The title and description are where I tell them exactly what the diff does, how I checked it, and what I did not check, so they can decide quickly whether it is ready to review.

## Rules I write by

### Rule: Say what I observed, not what I assume

I describe what my reproduction actually showed. I do not turn a possible explanation into a confirmed cause unless I have evidence for it.

* Wrong: "This happens because the parser is broken."
* Right: "I reproduced the same parser error when running the command with this input."

### Rule: Be specific about the result

I name the command, error, behavior, or important environment detail instead of saying something vague like "it worked" or "I got the issue."

* Wrong: "I tested this and got the same problem."
* Right: "I ran `example-command` with the issue's input and received the same error shown in the issue."

### Rule: Be honest when I cannot reproduce

If my result is different from the issue, I say exactly that. I do not claim a successful reproduction just because I encountered an error.

* Wrong: "Confirmed, I reproduced the issue."
* Right: "I followed the reproduction steps, but I could not reproduce the reported failure. My run completed successfully."

### Rule: Call out meaningful differences

If my environment, input, or command differs from the issue, I mention the difference when it could affect the result instead of hiding it.

* Wrong: "I followed the same setup and reproduced this."
* Right: "I used Python 3.12 instead of 3.11 because 3.11 was not available in my environment; the rest of the reproduction steps were unchanged."

### Rule: Keep conclusions proportional to the evidence

I report what my test demonstrates without claiming that one reproduction proves the issue occurs everywhere or identifies the fix.

* Wrong: "This proves the feature is completely broken."
* Right: "With this setup, I was able to reproduce the behavior described in the issue."

### Rule: The title names the change, not the effort

A PR title is read in a list of other PRs. It follows the repo's Conventional Commits format, says what the code now does, and stays short enough to read at a glance. It doesn't describe how hard the work was, and it doesn't repeat the issue's complaint.

* Wrong: "Fixed the bug from issue #67 (finally!)"
* Right: "fix(api): verify profile ownership before creating a review" (scope from CONTRIBUTING's list: `ingestion`, `rag`, `agent`, `safety`, `api`, `frontend`)

### Rule: The description promises exactly what the diff contains

Every change I list must be in the diff, and every file in the diff must be explained. I don't describe work I planned but didn't do, and I don't leave a changed file for the reviewer to discover.

* Wrong: "Adds ownership checks to the review endpoints." (Only `POST /reviews` changed.)
* Right: "`create_review()` now looks up the profile through `get_profile()` and returns `None` when the caller doesn't own it; `create_review_endpoint()` turns that into a 404 before scheduling `process_review`."

### Rule: A checked box means I ran that exact check

I tick a template checkbox only if I ran the command it names and it passed. If I ran an equivalent instead, or couldn't run it, I leave the box unticked and say what I did run and what it printed.

* Wrong: "- [x] Unit tests pass (`make test-unit`)" (when `make` never ran)
* Right: "- [ ] Unit tests pass (`make test-unit`): `make` is blocked on my machine by the Xcode license prompt, so I ran the same command directly: `.venv/bin/pytest tests/unit -m unit` → 377 passed, 53 xfailed (375 passed, 53 xfailed on `main`)."

### Rule: Tie the PR back to the posted plan, and name any deviation

The reviewer may have read my plan on the issue. I link to it and to my reproduction, and if the build differs from what the plan said, I say what changed and why. I write it plainly, as a fact about the work, not as an apology.

* Wrong: "Sorry, I didn't quite follow my plan for the tests."
* Right: "Deviation from my plan: instead of patching `get_profile` in each of the six existing tests, I added one `owned_profile` fixture they all use. The behavior tested is unchanged, and #65's xfail tests aren't touched."

### Rule: State what I did not verify

A shortfall I disclose is information the reviewer needs. I name what I didn't test and why, without hedging the parts I did test.

* Wrong: "This should probably work in production too."
* Right: "Not verified: I haven't run this against Postgres, only SQLite. The new query is the same one `get_profile()` already runs for `GET /profiles/{id}`."

## Things I never post

* A claim that I reproduced an issue when I actually received a different error.
* A guessed root cause presented as a fact.
* "Definitely," "obviously," or similar language when the evidence does not support that certainty.
* A promise that I will fix something, submit a PR, or investigate further unless I know I can follow through.
* Vague comments such as "same issue," "doesn't work," or "confirmed" without supporting details.
* Environment, input, or command differences that I know could materially affect the reproduction.
* AI-generated claims or conclusions that I have not checked against my own reproduction evidence.
* A ticked checkbox for a check I didn't run as written, or that didn't pass.
* Coverage claims the evidence doesn't show, such as "fully tested," "no regressions," or "works everywhere."
* A change listed in the description that isn't in the diff, or a changed file the description never mentions.
* "Closes #N" when the PR fixes only part of the issue.
* Template sections left as their placeholder comments, or filled with boilerplate that doesn't describe this PR.
