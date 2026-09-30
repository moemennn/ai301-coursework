# Evidence guide: where proof lives in a reproduction package

## Environment

Where it lives: In an eval bundle, look in the repro report's environment record and compare it with any version, operating system, dependency, or installation requirements stated in the issue context or repo-facts block. In live mode, compare the student's environment details with the GitHub issue and the repository's installation or setup documentation.

What good looks like: The relevant software or package version, operating system, and installation method are stated. They should match the environment targeted by the issue, or any differences should be clearly called out and should not invalidate the reproduction.

## Steps

Where it lives: In an eval bundle, look in the repro report's reproduction steps, including the starting state, input, command, command-line options, configuration, and actions taken before the behavior occurs. Compare these with the issue context and any setup requirements in the repo-facts block. In live mode, use the student's draft reproduction steps together with the original GitHub issue and repository documentation.

What good looks like: A stranger should be able to follow the steps from the stated starting state to the trigger without guessing important actions. The input and command should match the issue, or any differences should be explained and still test the same behavior.

## Behavior shown

Where it lives: In an eval bundle, look at the repro report's output excerpts and any attached logs, screenshots, stack traces, or other artifacts. Read them against the failure, error message, or incorrect behavior described in the issue context. In live mode, compare the student's captured output or screenshots with the behavior described in the GitHub issue.

What good looks like: The evidence should show the same failure or behavior described by the issue, not a different error that happens earlier or an adjacent problem. If the issue cannot be reproduced, the artifacts should still show that the correct reproduction attempt was made and what actually happened instead.

## Honesty

Where it lives: In an eval bundle, compare the claim comment and the repro report's expected-versus-actual result with the supporting output, logs, screenshots, and other artifacts. In live mode, compare the student's proposed GitHub comment with the evidence they collected during reproduction.

What good looks like: The written claim should say only what the evidence supports. A clear and evidenced "could not reproduce" is acceptable, while claiming the issue was reproduced when the artifacts show a different failure is not.

## Comms

Where it lives: In an eval bundle, look at the claim comment, the issue context, and the repo-facts block for issue templates, contribution guidance, terminology, formatting expectations, or AI-use disclosure requirements. In live mode, compare the student's draft comment with the GitHub issue thread, repository contribution documentation, and any repository-specific communication rules.

What good looks like: The comment should describe the reproduction result specifically and accurately, using the repository's expected terminology and conventions. It should avoid unsupported conclusions or generic boilerplate and include any disclosure or formatting required by the repository.
