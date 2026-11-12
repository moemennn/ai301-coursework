# Unit 4 — Test and Submit

## Your pull request

**Pull request**

https://github.com/codepath/pathreview-ai301-fa26-s3/pull/282

**Branch**

`fix/67-review-ownership-check`

## Eval iterations

**Run history**

1. One full run, saved with `--save-run eval-run.txt`: **20/20**. The committed file reads:
   `categories: clear-accept 7/7  not-tested 4/4  silent-drift 4/4  standards-wall 2/2  unreviewable 3/3`
   `agreement: 20/20 scored items  (bar: 18/20: PASS)`

That was the only run. Every package agreed with its gold label, so there were no disagreements to revise against, and I made no partial (`--only`) runs.

**Package analysis**

**pkg-20** (ghostty). The committed run shows `pkg-20  standards-wall  reject  reject   yes`. My rubric decided **reject**, and the gold label is **reject**: "excellent bounded fix implementing the maintainer-authored diagnosis with decisive mode-2031 evidence, but the description contains no AI-use disclosure and ghostty's stated policy requires disclosing all AI usage; every package here is treated as AI-assisted work".

My rubric reads it this way because of the "Standards followed" check. Its evidence column names "disclosure asks such as AI-assistance or issue-linking rules", and its pass condition requires that "required disclosures are present". The package's repo facts say "All AI usage in any form must be disclosed, stating the tool used and the extent of the assistance". The grader held the PR on exactly that: "AI_POLICY requires disclosure of all AI usage (tool and extent), and the description contains no AI-disclosure statement."

Everything else about the fix was strong. The grader passed Observable test evidence ("Repro command with before ESC[?997;2n and after ESC[?997;1n under --window-theme=dark with a single theme, matching the issue and test plan"), Reviewable diff, and Repo checks run. So the missing disclosure is what decides it, which is the reason this package sits in the `standards-wall` category.

The grader also failed "Claims match diff" on its own grounds: "Description says 'a second case covers the single-theme scheme flip', but the added second test covers unrelated key .fullscreen returning null". The gold note doesn't mention this, so the reject doesn't depend on it.

**Check rationale**

From the `rubric.md` I uploaded to `tools/pr-precheck/`, as it reads now:

| Repo checks run | The test evidence and description, read against the repo's own checks named in CONTRIBUTING / the PR template / the repo-facts block (test suite, linter, formatter, build). | Each check the repo says must pass before submission is shown as run, with its result. If a check was not run or fails, the description says so and why. Silence on a required repo check fails. | required |

It reads this way because I wanted the check to grade *honesty about* the repo's checks, not a perfect local run. The key sentence is "If a check was not run or fails, the description says so and why. Silence on a required repo check fails."

I rejected the stricter version, "every required repo check passes", because it would hold PRs whose checks are blocked by the contributor's environment rather than by the change. That fits the verdict rule I paired with it: "**Honest shortfall is not a failure.** ... Hold a PR for hiding a shortfall, not for having one."

The check behaved this way on my own PR (#282) in live mode:
- **First run: held.** It failed Repo checks run because my draft was silent on two checks CONTRIBUTING lists, `make format` and the frontend tests, and it claimed a `make check` run with no output shown.
- **Second run: passed.** I ran those checks and pasted their output. The check then passed even though `make typecheck` still failed locally, because the description said why. That run's evidence line reads: "typecheck numpy-stub failure (identical on main), and pending CI are each disclosed with reasons."

**Trade-offs**

Nothing changed between runs, because there was only one run. Here is how I know the scored run is the rubric I'm submitting: the fingerprints in `eval-run.txt` (`rubric.md  sha256:6b83d68003d4e123`, `procedure.md  sha256:611b7d431d3527e0`, `evidence-guide.md  sha256:3312c858322afa11`, `SKILL.md  sha256:e44bcb2a5871f14a`) match my installed files today. The only file I edited after the run is `voice-guide.md`, and eval mode never reads it.

The case I accept this check will miss is a PR that openly says it didn't run a required check. Repo checks run passes that PR, because the shortfall is disclosed. I rely on "Observable test evidence" to catch a PR that discloses away its testing entirely ("Claims such as 'tested locally' or 'all good' with no command or output do not count"). So a PR that skips the linter but says so can still be accepted, and that's a known gap I chose over holding every environment-blocked check.
