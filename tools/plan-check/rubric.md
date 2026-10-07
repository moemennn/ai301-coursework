# Rubric: is this plan ready to post and build from?

## Checks

| Check | Evidence | Pass condition | Weight |
|---|---|---|---|
| Evidence-supported diagnosis | The plan's stated or implied cause compared against the Issue, Repro evidence, control results, and Thread highlights. | The diagnosis offers a plausible explanation consistent with observed behavior and does not contradict decisive reproduction or control evidence. The exact internal root cause does not need to be conclusively proven before implementation. A stated hypothesis is acceptable when the proposed approach remains supported by the evidence. | required |
| Correct fix targeting | The plan's proposed changes compared against the Issue, Repro evidence, and evidence-supported diagnosis. | The proposed change has a reasonable causal connection to resolving the observed failure. It does not merely conceal the symptom when the reproduction evidence demonstrates a different underlying cause. The plan need not prove that the fix already works. | required |
| Bounded scope | The plan's scope statement, proposed changes, and exclusions compared against the Issue, Repro evidence, and Repo facts. | The work is limited to one coherent, manageable change addressing the reported problem. Affected files or components are reasonably identifiable, unrelated behavior is left untouched, and necessary work is not explicitly excluded. A small number of related changes is acceptable when they serve the same fix. | required |
| Actionable implementation | The plan's implementation approach, affected components, and proposed changes compared against Repo facts and relevant Thread highlights. | A developer can identify a concrete starting point, the intended behavioral change, and a reasonable implementation direction. Every function, file, or internal detail need not be specified, but the plan must not leave the central solution entirely to future investigation. | required |
| Meaningful verification | The plan's proposed tests compared against the Issue, Repro evidence, observed failure, and expected behavior. | The plan identifies a repeatable manual or automated check with an observable result that distinguishes fixed behavior from the reported failure. Referencing the established reproduction steps is sufficient when the expected post-fix behavior is clear. Additional regression coverage is preferred but not mandatory unless explicitly required by the repository or issue. | required |
| Uncertainty and assumptions | The plan's diagnosis, assumptions, unresolved questions, and implementation approach compared against Repro evidence, Repo facts, and Thread highlights. | The plan does not present claims contradicted by evidence as established facts. Reasonable uncertainty about implementation details is acceptable if it does not undermine the proposed approach. Explicit validation steps are necessary only for critical unknowns that determine whether the proposed fix is viable. | required |
| Thread and repository alignment | The plan's proposed approach and Candidate plan comment compared against Thread highlights, Repo facts, contribution policies, and stated repository conventions. | The plan respects explicit maintainer requirements, repository constraints, and relevant contribution policies. The proposed comment accurately communicates the intended work and does not contradict the evidence or ignore material thread guidance. Do not require acknowledgments, disclosures, or formatting conventions that the repository has not specified. | required |
| Implementation efficiency | The plan's proposed solution compared against the Issue, scope, Repo facts, and documented existing patterns. | The approach avoids clearly unnecessary complexity and unrelated modifications. Reusing existing mechanisms is preferred where appropriate, but the plan need not demonstrate that its approach is the most optimal possible solution. | preferred |

## Verdict rule

Grade each check as `pass`, `fail`, or `unclear`.

**Accept (ready)** when every required check passes.

**Reject (hold)** when at least one required check fails or is unclear.

Apply the following grading rules:

1. **Pass:** The available evidence reasonably supports the check's pass condition. Do not require absolute certainty, completed implementation, or proof beyond what is appropriate for a planning-stage review.
2. **Fail:** The evidence demonstrates a contradiction, a material flaw, or a missing essential element that prevents the plan from satisfying the check.
3. **Unclear:** Essential information is missing or genuinely ambiguous, preventing a reliable assessment. Do not assign `unclear` merely because additional information could be useful or some implementation details remain unspecified.
4. **Preferred checks:** These provide feedback but never independently change the verdict.
5. **Independent evaluation:** Grade each check on its own pass condition. Do not automatically fail multiple checks because of one minor omission unless that omission independently creates a material problem for each check.

For every failed or unclear required check, identify the specific evidence, explain why the check was not satisfied, and state the minimum correction or verification necessary for readiness.

A plan does not need to establish every implementation detail or guarantee success before work begins. It must provide an evidence-consistent explanation, a reasonably targeted and bounded approach, enough direction to begin implementation, and an observable way to verify the result.

**The final verdict must reflect whether the plan is ready to begin work, not whether the implementation is already complete.**