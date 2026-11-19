# Contribution: OSS possible hash collision

Path: `beat-2-contribution/contribution-story.md`

This file is Assignment 5, and it is graded at the path above; a copy kept anywhere else in
the repository is not read. **Keep every section header below under its exact name** — the
format criteria grade exactly that. Your course repo link is the whole submission: no tool
files and no evidence uploads are part of Assignment 5.

**Contribution Number:** [1]
**Student:** Moemen Ibrahim
**GitHub Username:** moemennn
**Issue:** https://github.com/finos/opengris-scaler/issues/177
**Pull Request:** [GitHub PR link, once opened]

One repository, built across units 5 to 8, telling the whole story of your real
contribution. Fill it as you work, not at the end — the sections below ask for evidence that
is far easier to write down as it happens than to reconstruct in the last weekend.

Contribution Number stays `[1]` unless you make more than one contribution this term; it
just numbers them.

---

## Toolkit

Every story section below, from Why I Chose This Issue through Pull
Request, ends with a Toolkit block: which tool did that phase's work
and how you used it, what it produced, what difficulties or
shortcomings it presented, and what you changed or would change
because of them. Together the blocks are the thread the rubric's
Toolkit points read, and they are the raw material for your unit-9
portfolio, so keep them current as you work rather than
reconstructing them later.

A Toolkit block looks like this (copy it into each story section and
fill it there):

```text
**Toolkit**

- Tool: [which tool did this phase's work, and how you used it]
- What it produced: [described in a sentence or a short excerpt]
- Difficulties: [what fought you or fell short, or "none met"]
- What changed: [the patch, revision, or workaround, what you would
  update, or "nothing"]
```

This section also keeps one short dated entry per week of tool work,
starting below: what you built or changed that week, what broke, and
what you changed because of it. The blocks tell the story where it
happened; these entries are the toolkit's own timeline.

All four entries are graded. Keep every heading below, and fill each
one in the week it belongs to.

**Unit 5: wrote my scout's search strategy, ran two scans, and patched the rubric and strategy from what the first scan got wrong (2026-11-18)**

I wrote a search strategy for issue-scout: 14 `gh search issues` queries, each traced to a sentence of my fit profile, plus point-based ranking filters that send the top 5 to my rubric for grading. Scan 1 showed two problems. My rubric accepted 4 issues whose fix was already merged, because Actionable only read the issue text. It also counted bot-only commits as repo activity. On the strategy side, one org filling slots across sibling repos and a 1,456-comment bounty issue took up all 5 grading slots. I added an "already done on main" fail condition to Actionable, excluded bot-only commits from Active, and changed the strategy to cap per owner, ignore blanket labels, and drop bounty and crowded issues. Scan 2 showed the fixes working: 5 different owners, and the new Actionable condition caught 2 already-fixed issues.

**Unit 6: installed the voice guard, patched my rubric's scope check, and wrote a repo memory file for opengris-scaler (2026-11-18)**

I merged my three voice-guide copies into one guide with an Upstream section for claims, questions, and pings, and hooked the guard into Claude Code, where the wiring test stopped `gh issue comment --help` as it should. Its first real check came 20 minutes after I had already posted my claim, and it stopped on my own claims rule: "I'm aiming to open a PR within about a week" promises a PR before the maintainers have chosen a design. The revised line passed, but the posted comment still has the original, so I now post through Claude Code with `--body-file`, where the hook checks a draft before it goes up. My `CLAUDE.local.md` for opengris-scaler distills CONTRIBUTING.md and one orientation pass over the object storage code, and writing it caught two things I'd have gotten wrong: a stale version-bump path that recent PRs skip (I'll ask about it in my PR), and an AGENTS.md ban on agent `Co-authored-by` trailers, which the file now tells Claude to follow.

**Unit 7: [one line on the tool work]**

[2-4 sentences: the ship-gate and your gate manifest. What it produced
on your real branch, what fought you, what changed because of it.]

**Unit 8: [one line on the tool work]**

[2-4 sentences: the PR-monitor and your playbook. What it read, what it
drafted, what you did with the draft.]

---

## Why I Chose This Issue

I searched with my issue-scout scans across all of GitHub. Scan 1 had nothing usable: 4 of the issues it accepted were already fixed on main, and the fifth was a bounty farm. After patching, scan 2 accepted two issues. The best was a TypeScript task adding unit tests for an auth middleware (scout-off/scout-off-contracts#1893), but it was outside my languages and in a repo with unanswered contributor PRs. I found this issue, finos/opengris-scaler#177, on the AI301 Issue Selection site and graded it with the scout in direct mode. The verdict was **accept**. Active passed: the last 5 default-branch commits were all by humans in the past week. Low Contention passed: no assignee, no linked PR, and only design discussion in the thread. Actionable passed: `setObject()` in `src/cpp/scaler/object_storage/object_manager.cpp` still dedups objects on `std::hash` alone, with no equality check. It fits my profile better than anything the scans found. It's C++, one of my languages, and it's an algorithms problem about hash collisions and equality, which I'm interested in. The fix is small and testable. My claim comment proposes an equality check: when a hash already exists, compare the payload bytes; on a real collision, store the new object separately instead of aliasing it. A test would force a collision. I hope to learn how to work in a real C++ codebase with a Python extension, and how to write tests that prove a collision case is handled.

The scout held up on its own grading: the "already done" check I added after scan 1 caught 2 finished issues in scan 2. Its search is where it fell short. My Python, Java, and C++ queries put nothing in the top 5, because search results have no language field to rank on, and the scans never surfaced this issue. I had to find it by hand. The scout also couldn't read the issue's project-board status, because my `gh` token lacks the `read:project` permission, so that is one thing I had to check by hand on the issue itself. Next I would add a ranking bonus for results found by the language queries, and drop reward-program labels like Stellar Wave that attract crowds of applicants.

Claim comment: https://github.com/finos/opengris-scaler/issues/177#issuecomment-6998745588 (posted 2026-11-18)

**Toolkit**

- Tool: issue-scout, with my search strategy (14 queries plus ranking filters) and my 3-check rubric. I used it for two full scans and one direct-mode grade of this issue.
- What it produced: scan 1 accepted 4 already-fixed issues and rejected 1 bounty farm. Scan 2 accepted 2 and rejected 3, 2 of them as already done. Direct grading of #177 gave **accept**, with evidence for each check and a caveat that the project-board status couldn't be read.
- Difficulties: the original rubric couldn't tell that an issue was already fixed, and it counted bot-only commits as activity. The strategy let one org and a bounty issue fill the top 5, gave no ranking advantage to my languages, and never surfaced the issue I chose.
- What changed: I added an "already done on main" fail condition to Actionable and excluded bot-only commits from Active. I added a per-owner cap, a label-stuffing guard, and bounty and 30-plus-comment drops to the strategy, and confirmed them with scan 2. Still to patch: a bonus for results from the language queries, and a drop for reward-program labels.

---

## Understanding the Issue

**Problem Description**

[In your own words, what is broken or missing?]

**Expected Behavior**

[What should happen?]

**Current Behavior**

[What actually happens?]

**Affected Components**

[Which parts of the codebase are involved?]

**Toolkit**

- Tool:
- What it produced:
- Difficulties:
- What changed:

---

## Reproduction Process

**Environment Setup**

[What a stranger would need to stand this up: your operating system,
the relevant versions (language, runtime, package manager, the project
itself), and how you set the project up. Then the challenges you faced
and how you solved them, or that none came up.]

**Steps to Reproduce**

1. [Step 1]
2. [Step 2]
3. [Observed result]

**Reproduction Evidence**

- **Commit showing reproduction:** [link to commit in your fork]
- **Screenshots/logs:** [if applicable]
- **My findings:** [what you discovered during reproduction; an
  honest, evidenced cannot-reproduce that led you to re-pick or ask
  the maintainer belongs here and costs you nothing]

**Toolkit**

- Tool:
- What it produced:
- Difficulties:
- What changed:

---

## Solution Approach

**Analysis**

[Your analysis of the root cause: what is causing the issue, traced
to the files and functions involved.]

**Proposed Solution**

[High-level description of your fix approach, and what you are
deliberately NOT changing.]

**Implementation Plan**

1. [Modify file X to do Y]
2. [Add or change Z]
3. [Update tests]

[Record deviations here as they happen: what changed mid-build and
why. A recorded deviation is honest work; silent drift is not.]

**Toolkit**

- Tool:
- What it produced:
- Difficulties:
- What changed:

---

## Testing Strategy

[What observable checks prove the fix: your reproduction steps re-run
against the built change (before and after), and the repo's own test
suite or checks with the outcome shown. "Tests pass" with nothing
observable named is not a strategy.]

**Toolkit**

- Tool:
- What it produced:
- Difficulties:
- What changed:

---

## Implementation Notes

[A running log, added to as you work. Date each entry. What you
built, decisions you made when you made them, wrong turns included.]

**[Date]**

[Entry]

**[Date]**

[Entry]

**Toolkit**

- Tool:
- What it produced:
- Difficulties:
- What changed:

---

## Pull Request

**PR Link:** [GitHub PR URL when opened]

**PR Description:** [what the PR says; much of the content above
adapts into it]

**Maintainer Feedback:**

- [Date]: [feedback received, or "none yet"; silence is a normal
  state and costs you nothing]
- [Date]: [how you addressed it]

**Status:** [Awaiting review / Iterating / Merged / Closed. The
status is a fact you record, never a grade: the PR is graded as
opened.]

**Toolkit**

- Tool:
- What it produced:
- Difficulties:
- What changed:

---

## Learnings and Reflections

**Technical Skills Gained**

[What you learned technically, named concretely.]

**Challenges Overcome**

[What was hard and how you solved it; point at the real events, the
Toolkit blocks above are full of them.]

**What I'd Do Differently Next Time**

[Reflection on your process.]

---

## Resources Used

[What actually helped, not a reading list. List things this story
already shows you using: the doc you followed to set the environment
up, the thread that explained the bug, the person who answered you.
One real entry beats ten plausible ones.]

- [Link to documentation that helped]
- [Discussion, issue, or post that helped]
