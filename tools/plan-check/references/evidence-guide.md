# Evidence guide: where evidence lives in a plan package

## Diagnosis and grounding

**Where it lives:**

- **Eval package:** Read `## Issue` for the reported problem, expected behavior, and actual behavior. Read `## Repro evidence` for reproduction steps, observed results, control experiments, and supporting artifacts. Compare these with the cause stated in `## Candidate plan`, especially its Diagnosis or Summary. Check `## Thread highlights` for additional claims or competing explanations.
- **Live mode:** Read the GitHub issue description, the student's posted reproduction report, and relevant issue comments. Compare these against the diagnosis in the draft plan.

**What good looks like:**

The stated cause explains the behavior demonstrated by the reproduction evidence without contradicting observations or control experiments. A claim made in an issue comment is not automatically confirmed evidence.

For example, in calib-03, the plan blames pager key bindings, but the slowdown also occurs with paging disabled. The diagnosis therefore contradicts the reproduction evidence and should fail.

## Scope

**Where it lives:**

- **Eval package:** Read the Candidate plan's Scope, Changes, and any In scope or Out of scope statements. Compare proposed modifications with the Issue, Repro evidence, and Repo facts.
- **Live mode:** Examine the draft plan's proposed modifications, identified files or components, and explicit exclusions. Compare these with the GitHub issue's requirements and repository structure.

**What good looks like:**

The plan proposes one coherent, bounded change that directly addresses the evidence-supported problem. It identifies the affected files or components and avoids unrelated refactoring or unnecessary changes.

A plan must not exclude work that the evidence indicates is necessary. In calib-03, excluding syntax highlighting is problematic because the reproduction evidence identifies highlighting as the source of the slowdown.

## Executability

**Where it lives:**

- **Eval package:** Read the Candidate plan's Change, Changes, or implementation description. Compare the named files, functions, components, and proposed actions with the Repo facts and relevant Thread highlights.
- **Live mode:** Review the draft implementation plan and verify its references against the repository's source files, architecture, and contribution documentation.

**What good looks like:**

A developer unfamiliar with the issue could begin implementing the fix without asking the author to make major missing design decisions. The plan identifies where changes belong, what behavior needs modification, and a sufficiently concrete approach for carrying out the work.

For example, calib-01 identifies the push completion callback in `pkg/gui/controllers/sync_controller.go` and specifies adding the branch-commits context to the post-push refresh scope.

By contrast, calib-02 only proposes exploring the editor code to find where undo history lives. It lacks an identified implementation target and concrete approach, making it insufficiently actionable.

## Test plan

**Where it lives:**

- **Eval package:** Read the Candidate plan's Test or Test plan. Compare its steps and expected results with the Issue and Repro evidence, including control cases and artifacts.
- **Live mode:** Read the draft plan's testing instructions alongside the student's reproduction report, logs, screenshots, or other supporting artifacts.

**What good looks like:**

The tests reproduce the original failure and specify an observable result that demonstrates the fix works. They also cover relevant regressions where appropriate.

Repeatable manual tests are acceptable when they decisively verify behavior; an automated test is not mandatory unless repository requirements say otherwise.

For example, calib-01 tests whether the commit changes color immediately after a successful push without leaving the current view. It also checks the main commits panel and force-push behavior.

A statement such as "test that undo works" in calib-02 is insufficient because it does not specify the editor-toggle sequence, expected result, or how success will be distinguished from the existing failure.

## Honesty

**Where it lives:**

- **Eval package:** Examine the Candidate plan's Diagnosis, implementation approach, assumptions, risks, and unresolved questions. Compare claims of certainty against the Repro evidence, Repo facts, and Thread highlights. Review the Candidate plan comment for unsupported promises or exaggerated confidence.
- **Live mode:** Review the draft plan, issue discussion, and reproduction report. During implementation, inspect progress updates, revised plans, and PR comments for documented deviations from the original approach.

**What good looks like:**

The plan distinguishes confirmed findings from hypotheses and acknowledges uncertainties that could affect the implementation. Important unknowns have concrete validation steps before the proposed change depends on them.

For example, a plan may state that a refresh callback is the suspected cause and propose verifying the callback's behavior before modifying it.

A plan fails this check when it presents unsupported assumptions as proven facts or promises a fix without enough evidence to justify its approach.

If implementation reveals a different cause or requires changing the original scope, the author should record the new evidence, explain the deviation, and update the plan rather than silently proceeding.

## Comms

**Where it lives:**

- **Eval package:** Read `## Candidate plan comment` alongside `## Thread highlights` and `## Repo facts`. Check repository contribution policies, issue templates, maintainer requests, and any stated AI-use disclosure requirements.
- **Live mode:** Review the proposed GitHub issue or PR comment against the full issue conversation, repository `CONTRIBUTING.md`, issue or PR templates, and other relevant contributor instructions.

**What good looks like:**

The comment accurately summarizes the evidence-supported diagnosis, proposed change, and verification approach. It responds to relevant maintainer requests and follows repository communication and contribution requirements.

In calib-01, the comment references the reproduced behavior, identifies the targeted refresh fix, and acknowledges the maintainer's limited review bandwidth.

In calib-02, the comment promises a PR soon without presenting a concrete implementation approach or responding meaningfully to the thread's reports that the bug persists.

A comment must not claim a cause is proven when the reproduction evidence contradicts it. If the repository explicitly requires AI-use disclosure, the comment or submission must satisfy that requirement. Do not invent a disclosure requirement when none is stated.

A comment should communicate what is actually known and planned, rather than using enthusiasm or confident promises as substitutes for evidence.