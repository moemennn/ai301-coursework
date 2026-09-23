# Unit 1 — Issue Selection

Path: `beat-1-sandbox/unit-1/selection.md`

Record of the issue carried into Unit 2, and of the evaluation runs that produced
`eval-run.txt`. This file is graded at the path above; a copy kept anywhere else in
the repository is not read.

Complete every labelled field below. Each is graded on its own; content placed under the
wrong label is not graded.

---

## Selected issue

**Issue link**

"https://github.com/codepath/pathreview-ai301-fa26-s3/issues/67"

**Verdict output**

**The verdict must record `accept` for this issue.** Choose an issue your own skill
accepts. If your skill rejects every candidate you try, that is a signal about your
rubric rather than about the issues: revise it and re-run — retries are unlimited and a
partial re-run costs about $0.20 — or run the skill on different candidates. Output
recording `reject` for the issue you chose earns no credit for this field.

```

#67 — Review creation does not verify profile ownership — second: also a security issue (missing authorization check on POST /reviews) and backend/API work you said interests you, but it's tier-2 with no effort estimate, and the body is truncated mid-example, so it's a bigger and slightly less pinned-down piece of work than #72.
- Active: pass. Low Contention: pass — no assignee, zero comments, no linked PR. Actionable: pass — names the endpoint, core/services/review_service.py, the ignored argument, and the correct pattern to copy (get_review()/list_reviews() scoping via Profile.user_id).

  {
    "item": "https://github.com/codepath/pathreview-ai301-fa26-s3/issues/67",
    "checks": [
      {"name": "Active", "grade": "pass", "evidence": "Latest default-branch commit 2026-09-16, within the last 180 days."},
      {"name": "Low Contention", "grade": "pass", "evidence": "assignees: [], 0 comments, timeline shows only two labeling events; repo has 0 PRs so nothing is linked."},
      {"name": "Actionable", "grade": "pass", "evidence": "\"core/services/review_service.py ignores that argument... inconsistent with get_review() and list_reviews(), which already scope review reads through Profile.user_id\" — names the file and the pattern to follow, though the body is truncated mid-example."}
    ],
    "verdict": "accept"
  }

```

---

## Eval iterations

Quote source text directly in each field below. Paraphrase does not satisfy them.

**Run history**

agreement: 16/20 scored items  (bar: 18/20: below the bar)
agreement: 18/20 scored items  (bar: 18/20: PASS)

**Issue analysis**

issue-09

My rubric's decision was reject, while the gold label was accept. The run showed failed: Low Contention. My original Low Contention check treated an assignee as enough evidence to reject the issue. I revised the check so that an assignee alone does not fail it, and instead looked for clear evidence that someone was actively working on the issue. After that change, issue-09 was graded accept, matching the gold label.

**Check rationale**

Pass if there is no clear evidence that someone is actively working on the issue. An assignee alone does not cause a fail; fail if the assignee or another commenter states they are working on it, or if there is an active PR linked to the issue.

I changed this check because the original version was too strict and rejected issues simply because they had an assignee. The current wording focuses on whether work is actually in progress, which better matches my goal of avoiding duplicate work while still considering issues that may have an assignee for triage or other reasons.

**Trade-offs**

This change means I may accept an issue where someone is actually working on it but has not clearly said so or linked a PR. I accepted that trade-off because issue-09 showed that rejecting every assigned issue was too strict. After re-running issue-09 with --only, it changed from reject to accept.

---

## Selection rationale

Graded on whether all three are answered, in your own words. Not on how good the
reasoning is, and not on length — a short honest answer to each earns the full marks.
This is also the basis for the claim comment you write in Unit 2.

**Selection rationale**

[Answer all three:

1. The issue's fit to your interests and to the time available.
This issue fits my interests because it involves cybersecurity and backend logic, which are both areas I want to learn more about. The problem is also fairly focused: it is about making sure a user can only create a review for a profile they own. That feels challenging enough to learn from without being too large for the time available.
2. What the verdict identified correctly, and what you weighed that the rubric could
   not.
My verdict correctly identified that the issue is available to work on and has a specific problem with a clear place in the codebase to investigate. The issue points to the review creation flow and explains how the current behavior differs from the existing ownership checks used when reading reviews. I also weighed my personal interest in security and authorization bugs, which my rubric cannot fully capture.
3. The anticipated difficulty in claiming it.
I expect the issue to be fairly straightforward to claim because it currently has no assignee and no linked branch or pull request. The main difficulty will probably be understanding the existing review and profile ownership logic well enough to add the check without breaking the current behavior.

---

Related paths: `eval-run.txt` in this directory; your skill's files in
`tools/issue-select/`.
