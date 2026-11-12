# Evidence guide: where evidence lives in a PR package

Section names below are the ones an eval bundle uses (Repo facts, Issue, Thread highlights, Plan context, Candidate PR with its Title, Description, Commits, Diff, and Test evidence). In live mode the same evidence comes from the student's working copy and the real repo. Eval mode reads only the bundle text; live mode reads only what is listed under "Live".

## Plan fidelity (harness category: silent-drift)

Covers the checks **Diff matches plan** and **Claims match diff**.

**Where it lives**

- *Eval:* the plan's scope, named files, proposed changes, exclusions, and test plan are in the **Plan context** block (the "Plan:" paragraph, "Files:", "Not in scope:"). Any deviation note appears there too. What actually changed is the **Candidate PR > Diff** (changed file names in the `---`/`+++` headers, changed lines under each `@@`). The claims to check are in **Candidate PR > Description** (and the Title).
- *Live:* the plan is `plan.md` in the working copy, including its deviation notes. The diff is the output of `git diff main...HEAD` (three dots) from the working copy. The claims are in `pr_draft.md` (draft title and description).

**What good looks like**

- Every changed file and every substantive changed line falls inside the plan's named files and proposed changes, or inside a recorded deviation note. The core change the plan promised is present in the diff.
- Silent drift in the "more" direction: the diff touches a file, theme, or behavior the plan excluded or never mentioned, with no deviation note. Silent drift in the "less" direction: a planned step is missing from the diff and nothing says so.
- An honest deviation re-ties a mismatch: the plan (or the description) states what changed and why. A deviation that appears only in the diff is drift.
- Each factual claim in the description ("removes X", "fixes #N", "rendering unchanged", "follows the plan") is true of the diff. A description claiming more or less than the diff delivers is drift, not a comms problem. A description that admits a limitation or partial fix is honest and passes.
- *calib-01 example:* the plan names one file (`themes.gitconfig`) and one step (remove the first shadowed line). The diff changes that file only, removing exactly that line. The description's claims match, so both checks pass.

## Test evidence (harness category: not-tested)

Covers the checks **Observable test evidence** and **Repo checks run**.

**Where it lives**

- *Eval:* the proof is **Candidate PR > Test evidence**. Read it against the **Plan context** test plan, the reproduction steps quoted in the Plan context (and the **Issue** body), and the checks the **Repo facts** block says must run (test suite, linter, formatter, build, or the contribution docs' asks).
- *Live:* the proof is `test_evidence.md` (and any output quoted in `pr_draft.md`). The plan's test plan is in `plan.md`. The reproduction is the student's repro comment on the issue (or the house repro pack). The repo's required checks are in the repo's PR template and `docs/CONTRIBUTING.md`.

**What good looks like**

- An observable result that tells fixed from broken: a named command, its real output, and an expected-after that differs from the reported failure (a before/after pair, or a test that failed before and passes after). The same reproduction the plan and issue used, re-run on the branch, is strong evidence.
- The tests exercise the changed code. Output from unrelated tests, or "tested locally" and "all tests pass" with no command or output, is not evidence.
- Each check the repo requires before submission is shown run with its result, or the description says plainly it was not run and why. Silence on a required check fails. If the repo states no required checks, nothing is owed.
- *calib-01 example:* the evidence shows the strict `configparser` repro before (DuplicateOptionError) and after (`parsed OK`), the `git config --get-all` output showing one remaining value, and a `delta --show-syntax-themes` smoke check. These match the plan's test plan, so Observable test evidence passes. The repo facts name no required suite or linter, so Repo checks run has nothing outstanding.

## Diff quality (harness category: unreviewable)

Covers the check **Reviewable diff**, plus the preferred **Commit hygiene** check.

**Where it lives**

- *Eval:* the unified diff in **Candidate PR > Diff** (every hunk and file header) and the list in **Candidate PR > Commits**.
- *Live:* the output of `git diff main...HEAD` and `git log main..HEAD` run from the working copy.

**What good looks like**

- A reviewer can read the diff as one coherent change: the fix is visible and nothing unrelated rides along.
- Debris tells to look for: debug prints, commented-out code, dead code, stray or generated files, build artifacts, merge leftovers. Unrelated-hunk tells: whitespace or formatting churn, renames, and drive-by edits in files or sections the fix does not need. A few small related touches that serve the same fix are fine.
- Commits are understandable in isolation, with no throwaway or fix-up noise the contributing policy forbids.
- *calib-01 example:* one commit, one hunk, one removed line, no extra files. Reviewable diff passes.

## Standards and comms (harness category: standards-wall)

Covers the checks **Standards followed** and the preferred **Clear title and description**.

**Where it lives**

- *Eval:* the repo's asks are in the **Repo facts** block (PR template sections, contribution instructions, stated policy including any AI-use disclosure rule) and in explicit maintainer direction in **Thread highlights** and the **Issue**. The PR's response to them is in **Candidate PR > Title** and **Description**.
- *Live:* the repo's PR template and `docs/CONTRIBUTING.md`, fetched from the scoped repo, and the issue thread (read with `gh` or the GitHub API). The PR's response to them is the draft title and description in `pr_draft.md`.

**What good looks like**

- Every ask the repo or a maintainer explicitly stated is met: required template sections are filled with real content (not boilerplate or blank headings), required disclosures are present, required links or issue references are included, and explicit maintainer instructions in the thread are engaged with. Nothing the repo has not stated is required.
- The title and description let a maintainer understand the problem and the fix without opening the diff. Judge meaning, not length or formatting.
- Whether the description's claims match the diff is Plan fidelity above, not this family.
- *calib-01 example:* the repo has no PR template and the contribution docs ask only that PRs stay small and reference the issue. The PR is one line and its description cites #2211, so Standards followed passes. There is no stated AI policy, so no disclosure is owed.