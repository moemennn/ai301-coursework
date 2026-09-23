# Rubric: is this a good first issue?

## Checks

| Check          | Evidence                                                                                                                                                                       | Pass condition                                                                                                                                                                                                         | Weight   |
| -------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | -------- |
| Active         | Repo-facts block and recent repository activity. Check the dates of the last 5 default-branch commits and the issue/comment thread for recent maintainer responses.            | Pass if at least one of the last 5 default-branch commits is within the last 180 days or a maintainer has commented on an issue or PR within the last 180 days.                                                        | required |
| Low Contention | Repo-facts block for the assignee and the issue comment thread for anyone claiming, starting, or submitting work on the issue. | Pass if there is no clear evidence that someone is actively working on the issue. An assignee alone does not cause a fail; fail if the assignee or another commenter states they are working on it, or if there is an active PR linked to the issue. | required |
| Actionable     | Issue body, repo-facts block, and comment thread. Look for a specific problem or requested change, expected behavior, and enough context to identify what needs to be changed. | Pass if the issue describes a specific problem or desired change and provides enough information for a newcomer to identify a reasonable starting point without first needing major clarification from the maintainer. | required |

## Verdict rule

Accept only if all three required checks pass. If any required check fails, reject the issue. Treat `unclear` as a fail because I would want enough evidence that the repository is active, nobody else is already working on the issue, and the issue is actionable before choosing it as a first contribution.
