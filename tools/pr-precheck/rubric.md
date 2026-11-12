# Rubric: is this pull request ready to submit?

## Checks

| Check | Evidence | Pass condition | Weight |
|---|---|---|---|
| Diff matches plan | The diff's changed files and behavior changes, read against the plan's scope, proposed changes, exclusions, and any deviation notes. | Every substantive change in the diff falls inside the plan plus its recorded deviation notes, and the plan's core change is present in the diff. A change the plan did not authorize, or a core change the plan promised that is missing, fails unless a deviation note in the plan (or an honest disclosure in the PR description) records it and why. A deviation that exists only in the diff fails. A smaller change than planned passes when the shortfall is disclosed. | required |
| Claims match diff | The PR description's statements about what changed, what was fixed, and how closely it follows the plan, read against the diff. | Every factual claim in the description (what the PR does, "fixes #N", "follows the plan", "no behavior change") is true of the diff. A claim the diff contradicts or does not support fails. Honest disclosure of a limitation, partial fix, or known gap passes. | required |
| Observable test evidence | The test evidence (commands and output quoted in the description or supplied), read against the plan's test plan and the issue's reported failure. | The evidence shows an observable result that distinguishes fixed behavior from the reported failure (a test that failed before and passes after, or repro steps with before/after output). Claims such as "tested locally" or "all good" with no command or output do not count. Evidence that exists but could not pass or fail on the change (tests unrelated to the changed code) fails. | required |
| Repo checks run | The test evidence and description, read against the repo's own checks named in CONTRIBUTING / the PR template / the repo-facts block (test suite, linter, formatter, build). | Each check the repo says must pass before submission is shown as run, with its result. If a check was not run or fails, the description says so and why. Silence on a required repo check fails. | required |
| Reviewable diff | The diff's hunks and file list, read against the plan's scope and the issue. | A reviewer can read the diff as one coherent change. There is no debris (debug prints, commented-out code, stray files, build artifacts, merge leftovers) and no unrelated hunks (drive-by reformatting, renames, or edits to files the fix does not need) that bury the change. A few small related touches that serve the same fix pass. | required |
| Standards followed | The PR title and description, read against the repo's PR template, `docs/CONTRIBUTING.md`, and the issue thread's maintainer requirements (including disclosure asks such as AI-assistance or issue-linking rules). | Every ask the repo or a maintainer has explicitly stated is satisfied: required template sections are filled, required disclosures are present, required links or references are included, and explicit maintainer instructions are honored. Do not require anything the repo has not stated. | required |
| Clear title and description | The PR title and description read against the diff. | A maintainer can tell from the title and description what problem is solved and how, without reading the diff first. Judge whether the meaning is clear, not the length or formatting. | preferred |
| Commit hygiene | The branch's commit messages and commit list. | Commits are understandable in isolation and contain no throwaway messages or fix-up noise that the repo's contributing policy forbids. | preferred |

## Verdict rule

Grade each check `pass`, `fail`, or `unclear`, each on its own pass condition.

**Accept (submit)** when every required check passes.

**Reject (hold)** when any required check fails or is `unclear`. An `unclear` required check counts as a fail.

Preferred checks never change the verdict; report them in their evidence lines.

Grading rules:

1. **Pass:** the evidence reasonably supports the pass condition.
2. **Fail:** the evidence shows a contradiction, a material flaw, or a missing essential element.
3. **Unclear:** essential information is missing or genuinely ambiguous, so the check cannot be graded reliably. Do not use `unclear` merely because more detail would be nice.
4. **Honest shortfall is not a failure.** A PR that does less than the plan, or leaves a known gap, and says so plainly in the description or a plan deviation note can be ready. Hold a PR for hiding a shortfall, not for having one.
5. **Do not double-count.** One flaw fails the check it belongs to; fail another check only if the flaw independently breaks that check's pass condition.

For every failed or unclear required check, the evidence line names the specific fact that decided it.