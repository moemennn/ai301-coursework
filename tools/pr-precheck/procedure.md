# Procedure: how this tool grades a PR package

## Read order

Read in this order. Plan first, then the diff, then the description last, because the description is a claim about the diff and must not shape how you read the diff.

1. **Read the issue first.** Record the reported problem, expected behavior, actual behavior, and any acceptance conditions the reporter or a maintainer stated.

2. **Read the thread highlights.** Record maintainer requests, rejected approaches, and explicit instructions for the PR (disclosure asks, linking rules, testing asks).

3. **Read the repo standards.** Live: the PR template and `docs/CONTRIBUTING.md`. Eval: the repo-facts block. Record every explicit ask: required template sections, required disclosures, required links, and every check that must be run before submitting (tests, linter, formatter, build).

4. **Read the plan, including its deviation notes.** Record the plan's scope, the list of files or components it names, its proposed changes, its exclusions, its test plan, and each deviation note with its stated reason. This is the yardstick for the diff.

5. **Read the diff.** Live: run `git diff main...HEAD` (three dots) from the working copy, and `git log main..HEAD` for commit messages. Eval: the diff in the bundle. List every changed file, and for each one note what it changes in one line. Mark any file the plan does not name, any hunk that looks like debris (debug prints, commented-out code, stray or generated files), and any hunk that looks unrelated (reformatting, renames).

6. **Read the test evidence.** Record each command quoted, the output shown, and what the output claims to demonstrate.

7. **Read the PR title and description last.** Record each factual claim: what changed, what is fixed, issue references, claims of fidelity to the plan, claims about tests run, and any stated limitations or disclosures.

8. **Keep observations separate from claims.** Finish recording what the diff and test output actually show before comparing them with what the description says they show.

## Evidence gathering

Build one evidence record per rubric check: the package part used, the specific fact, and anything missing. Never treat an unsupported claim as a confirmed fact.

1. **Diff matches plan:** Pair the changed-file list (step 5) with the plan's named files and proposed changes. Record (a) changed files or behaviors not in the plan or a deviation note, (b) core planned changes missing from the diff, and (c) for each mismatch, whether a deviation note or a description disclosure covers it.

2. **Claims match diff:** Pair each description claim (step 7) with the diff. Mark each claim supported, unsupported, or contradicted. Record any limitation the description admits.

3. **Observable test evidence:** Pair the test evidence (step 6) with the plan's test plan and the issue's reported failure. Record whether there is a command, real output, and a result that would differ between broken and fixed behavior. Record whether the tests touch the changed code.

4. **Repo checks run:** Take the list of required repo checks from step 3. For each, find in the test evidence or description whether it was run and what the result was. Record "not mentioned" where silent.

5. **Reviewable diff:** Take the debris and unrelated-hunk marks from step 5. Count them, and judge whether they bury the fix. Small related touches that serve the fix are not debris.

6. **Standards followed:** Pair each explicit ask from steps 2 and 3 with the title and description. Record each ask as met, unmet, or not applicable. Record only asks the repo or a maintainer actually stated.

7. **Clear title and description (preferred):** Record whether the title and description say what problem is solved and how.

8. **Commit hygiene (preferred):** Record whether commit messages are understandable and free of noise the contributing policy forbids.

## Check execution

1. **Run the checks in rubric order:** Diff matches plan, Claims match diff, Observable test evidence, Repo checks run, Reviewable diff, Standards followed, Clear title and description, Commit hygiene.

2. **Apply the rubric's pass condition exactly.** Judge the outcome (does the diff fall inside the plan, is the evidence observable), not the write-up's length, formatting, or commit count.

3. **Assign `pass`** only when the evidence record shows the pass condition is met.

4. **Assign `fail`** when the record shows a contradiction, a material flaw, or a clearly missing required element.

5. **Assign `unclear`** only when essential information is absent or genuinely ambiguous, such as a diff that is truncated or a test output that cannot be interpreted. Do not assign `unclear` just because more detail would help, and do not fill gaps with assumptions.

6. **Honest disclosure rule:** when a mismatch between plan and diff (or a missing repo check) is recorded in a deviation note or stated plainly in the description, treat it as disclosed. Disclosed shortfalls do not fail Diff matches plan, Claims match diff, or Repo checks run. Undisclosed ones do.

7. **When evidence for a check is absent from the package** (for example, no test evidence at all), grade it `fail` if the rubric requires that evidence to exist, and `unclear` only if the missing piece is something the package cannot be expected to contain.

8. **Do not double-count.** One flaw fails the check it belongs to. Fail a second check for it only if it independently breaks that check's pass condition.

9. **Record a grade and a one-line evidence statement** (the fact or short quote that decided it) for every check. Once the record is sufficient, grade without rereading the whole package. Revisit a source only when evidence conflicts or is missing from the record.

10. **Grade preferred checks independently.** Record them, but they never override required checks.

## Verdict assembly

1. **Confirm all eight checks have a grade** of `pass`, `fail`, or `unclear` and an evidence line.

2. **Use only the required checks to decide.** Return `accept` if every required check is `pass`. Return `reject` if any required check is `fail` or `unclear`.

3. **Never let a preferred check change the verdict.** Report it in its evidence line only.

4. **Pick the deciding check:** the first failing (or unclear) required check in rubric order. Quote its decisive fact or short passage in the readable summary and make its JSON evidence line name that fact. When several required checks did not pass, list the others briefly in the summary.

5. **State the minimum correction** for each required check that did not pass, in the summary: what to change, disclose, or verify to make it pass.

6. **Output** the readable summary, then the fenced JSON block from SKILL.md with each check's exact rubric name, its grade, and its one-line evidence, and the verdict. Nothing follows the block.

7. **Consistency check before emitting:** an `accept` has no failed or unclear required check, and a `reject` names at least one required check that did not pass.

8. **Report procedure gaps.** If you hit a step this procedure does not cover, say so in the summary and do not invent one.