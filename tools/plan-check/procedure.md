# Procedure: how this skill grades a plan package

## Read order

1. **Read the issue description first.** Record the reported problem, expected behavior, actual behavior, and any constraints or requirements stated by the reporter.

2. **Read the Repro evidence before the candidate plan.** Identify the reproduction steps, observed results, control experiments, and any evidence that narrows down the root cause. Record what the evidence establishes and what remains uncertain.

3. **Read the Thread highlights.** Record maintainer comments, requested changes, rejected approaches, implementation constraints, and any relevant agreements or disagreements.

4. **Read the Repo facts.** Identify relevant files, components, existing conventions, technical limitations, and contribution requirements.

5. **Read the Candidate plan last.** Extract its proposed diagnosis, implementation approach, affected files, scope boundaries, testing strategy, assumptions, and intended posting comment.

6. **Keep observations separate from claims.** Record what the reproduction evidence actually demonstrates before evaluating what the candidate plan claims. This prevents a plausible explanation from influencing the interpretation of the evidence.

## Evidence gathering

1. **Diagnosis evidence:** Locate the candidate plan's stated root cause. Compare it against the issue's observed behavior, reproduction steps, control results, and relevant thread discussion. Record supporting evidence, contradictions, and unresolved alternatives.

2. **Fix-targeting evidence:** Locate the proposed implementation changes. Compare each change against the evidence-supported cause. Record whether the changes address the underlying failure or only its visible symptoms.

3. **Scope evidence:** Locate the plan's scope statement, target files, proposed modifications, and explicit exclusions. Compare these against the issue requirements and repo facts. Record unnecessary changes, missing necessary changes, and any unclear boundaries.

4. **Implementation evidence:** Extract the specific files, functions, components, and implementation actions identified in the plan. Compare them with the repository information. Record whether a developer could begin the work without making major design decisions independently.

5. **Testing evidence:** Locate the candidate plan's testing strategy. Compare its proposed test steps, inputs, and expected results against the Repro evidence. Record whether the tests would visibly distinguish a successful fix from the existing failure. Identify relevant regression coverage.

6. **Uncertainty evidence:** Locate assumptions, hypotheses, unresolved questions, and statements of confidence. Compare them against the available evidence. Record unsupported certainty and determine whether important unknowns have a concrete validation step.

7. **Repository and thread alignment evidence:** Compare the implementation approach and proposed posting comment against the Thread highlights and Repo facts. Record whether maintainer requests, repository conventions, and explicit restrictions are respected.

8. **Efficiency evidence:** Review the proposed implementation against the issue's scope and documented repository patterns. Record avoidable complexity, unnecessary modifications, or opportunities to reuse existing mechanisms.

9. **Build an evidence record for every rubric check.** For each check, record the relevant package section, the specific supporting or contradicting fact, and any missing information. Do not invent evidence or treat an unsupported claim as a confirmed fact.

## Check execution

1. **Evaluate the checks in rubric order:** Evidence-supported diagnosis, Correct fix targeting, Bounded scope, Actionable implementation, Meaningful verification, Uncertainty and assumptions, Thread and repository alignment, and Implementation efficiency.

2. **Apply the exact pass condition from the rubric.** Grade the actual quality and feasibility of the proposed work rather than its formatting, length, or number of sections.

3. **Assign `pass`** only when the gathered evidence demonstrates that the check's pass condition is satisfied.

4. **Assign `fail`** when the evidence contradicts the pass condition, the plan proposes an approach that cannot address the demonstrated problem, or a required element is clearly absent.

5. **Assign `unclear`** when the available information is insufficient to determine whether the condition passes or fails. Do not fill gaps with assumptions.

6. **For diagnosis and fix targeting, prioritize reproduction evidence over unsupported explanations.** If the plan claims a root cause contradicted by a control experiment, fail the relevant check even if the proposed solution sounds technically reasonable.

7. **For testing, require observable verification.** Accept repeatable manual or automated tests when they directly demonstrate the reported problem is resolved. Do not require a new automated test unless the repository explicitly requires one.

8. **For uncertainty, distinguish acceptable investigation from unsupported certainty.** A plan may acknowledge uncertainty and provide a concrete validation step. Fail if it treats a critical unverified assumption as established fact without a way to validate it before proceeding.

9. **For each check, record its grade and a short explanation referencing the specific evidence.** Once the evidence record is sufficient, grade the check without rereading the entire package. Revisit a source only when evidence conflicts or is missing from the record.

10. **Evaluate preferred checks independently.** Record their grades and explanations, but do not allow them to override required checks.

## Verdict assembly

1. **Collect all eight check grades.** Confirm that every rubric check has a grade of `pass`, `fail`, or `unclear` and a supporting explanation.

2. **Separate required and preferred checks.** Determine the verdict using only required checks.

3. **Return `accept` (ready)** if every required check is graded `pass`.

4. **Return `reject` (hold)** if at least one required check is graded `fail` or `unclear`. Treat `unclear` as insufficient evidence for readiness.

5. **Never use preferred checks to change the verdict.** A failed or unclear preferred check may appear in feedback but cannot independently cause rejection.

6. **Identify the deciding check or checks.** For each required failure or uncertainty, cite the specific section of the package and quote a short relevant passage or reproduce the decisive observation. Explain exactly why the pass condition was not met.

7. **State the minimum correction needed for readiness.** Describe what must be changed, clarified, or verified to satisfy each failed or unclear required check. Do not redesign the entire plan unless the evidence demonstrates that its underlying approach is incorrect.

8. **Produce the final result using the skill's required output format.** Include the binary verdict, each check's exact rubric name and grade, and evidence-based explanations. Do not invent additional verdict categories or rename rubric checks.

9. **Perform a consistency check before finalizing.** Verify that an `accept` verdict has no failed or unclear required checks and that every `reject` verdict identifies at least one required check that did not pass.