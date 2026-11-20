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

The object storage server saves memory by storing each distinct payload only once. It decides two payloads are the same when their 64-bit `std::hash` values match, and it never compares the bytes. So if two different payloads ever get the same hash, the server keeps only the first one, and the second object's ID returns the first object's bytes. A collision is very unlikely, but when one happens the data is wrong and nothing reports an error.

**Expected Behavior**

Every object ID returns exactly the bytes that were stored under it. Identical payloads still share one stored copy. Two different payloads that happen to share a hash are both stored, and `sizeUnique()` and `totalObjectsSize()` count both of them.

**Current Behavior**

When a new payload's hash is already in the table, `setObject` adds one to the existing entry's use count and returns the existing payload (`object_manager.cpp:47-52`). The new payload's bytes are freed. With a forced collision, `getObject(B)` returns `"payload-A"`, and still does after A is deleted. `sizeUnique()` reports 1 object and `totalObjectsSize()` 9 bytes, instead of 2 objects and 18 bytes. Without the forced collision, B round-trips correctly.

**Affected Components**

- `src/cpp/scaler/object_storage/object_manager.h` and `object_manager.cpp`: the `ObjectManager` class, its two maps (`objectIDToHash`, `hashToObject`), and `setObject`, `getObject`, `deleteObject`, `duplicateObject` and `sizeUnique`.
- `src/cpp/scaler/object_storage/object_storage_server.cpp`: the only caller. It handles SET (`:235`), GET (`:251`), DELETE (`:264`), DUPLICATE (`:288`, `:407`) and the totals (`:308-310`). It passes along whatever `ObjectManager` returns, so it serves the wrong bytes without knowing it, but its code doesn't need to change.
- `tests/cpp/object_storage/test_object_manager.cpp`: every test stores the same `"Hello"` payload, so no test has two different payloads, let alone two with the same hash.

**Toolkit**

- Tool: Claude Code, using my `CLAUDE.local.md` notes on the object storage code as its map. It reread the issue thread, traced `ObjectManager` on upstream `main` (`45fd02d`), and checked that no object storage C++ had changed since my repro commit `e7fd9f0`.
- What it produced: the four answers above, with line references, plus two facts I hadn't written down. The issue's file link points to the old path `scaler/object_storage/`; the code now lives under `src/cpp/scaler/object_storage/`. And `std::hash` isn't Murmur everywhere, as the issue says: each standard library uses its own algorithm (libc++ on macOS, libstdc++ on Linux, MSVC on Windows), so the collision odds and any colliding pair depend on the platform.
- Difficulties: no maintainer has answered my claim yet. The thread leans toward the equality check (rafa-be proposed it, and gxuu and I-Need-Sleep-Asap went along with it), but nobody has confirmed the design for this PR.
- What changed: since a known natural collision can't serve as a test input on every platform, the plan passes the hash function into `ObjectManager` so a test can force collisions. It also waits for a maintainer to confirm the design before any code.

---

## Reproduction Process

**Environment Setup**

- **System:** macOS 26.6.2 on Apple Silicon (arm64), with Apple clang 21.0.0 from the Command Line Tools in C++23 mode.
- **Cap'n Proto:** 1.5.0 from Homebrew. The repo pins 1.1.0, but here it's only needed to compile `message.h`, which `object_manager.h` includes for `ObjectID`. `ObjectManager` makes no Cap'n Proto calls.
- **Project:** opengris-scaler `main` at `e7fd9f0` (2026-11-18), with `object_manager.cpp` unmodified.

I didn't use the repo's CMake build. This Mac has two problems:
- **Broken Xcode:** `xcodebuild` fails to load a library, so plain `clang++` errors out. I called the Command Line Tools clang directly instead.
- **No CMake:** `cmake` isn't installed, so I compiled `object_manager.cpp` directly instead of running `./scripts/build.sh`.

Two more problems came up on the way:
- **libc++ not found:** the Command Line Tools clang couldn't find the standard library headers, because its toolchain copy is missing. I passed the SDK's copy with `-isysroot` and `-isystem`.
- **Generated header needed:** `message.h` needs a header generated from the repo's Cap'n Proto schema. I installed `capnp` with Homebrew and generated it with `capnp compile`.

A natural 64-bit collision can't be found on demand: the issue puts the odds at 0.00000271% for 1M objects. So I forced one. I built `main`'s `object_manager.cpp` twice:
- **Control:** with the real `std::hash`.
- **Forced collision:** a header pre-included into that one file swaps `std::hash` for a stub that returns the same value for every payload.

I compared the preprocessed file with and without the header. The only differences are that hash call and the consistent renaming of local variables named `hash`.

**Steps to Reproduce**

1. Clone the repo and check out the commit: `git clone https://github.com/finos/opengris-scaler && git -C opengris-scaler checkout e7fd9f0`.
2. Install Cap'n Proto: `brew install capnp`.
3. Save the three files below into a `repro/` folder.
4. Run `CXXFLAGS="-isysroot $SDK -isystem $SDK/usr/include/c++/v1" bash repro/run.sh /path/to/opengris-scaler`, where `SDK=$(xcrun --show-sdk-path)`. With only the Command Line Tools, use `/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk`.
5. Observed result: with the real hash, B round-trips. With the forced collision, `setObject(B)` returns A's payload and `getObject(B)` returns `"payload-A"`, including after A is deleted. `sizeUnique()` and `totalObjectsSize()` count one 9-byte object instead of two objects and 18 bytes.

<details><summary><code>force_collision.h</code> (pre-included into <code>object_manager.cpp</code> only)</summary>

```cpp
// Pre-included (-include) ONLY into an unmodified object_manager.cpp to simulate a 64-bit hash collision.
// Everything object_manager.cpp includes is pulled in first, so the macro below touches only the body of
// object_manager.cpp: `std::hash<std::string_view>` there becomes `std::repro_colliding_hash<...>`,
// which returns the same value for every payload. Local variables named `hash` are renamed consistently.
#pragma once
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <string_view>

#include "scaler/object_storage/object_manager.h"

namespace std {
template <class T>
struct repro_colliding_hash {
    size_t operator()(T) const noexcept { return 0x5eed; }
};
}  // namespace std

#define hash repro_colliding_hash
```
</details>

<details><summary><code>repro_collision.cpp</code> (the input: two different payloads under two object IDs)</summary>

```cpp
// Stores two DIFFERENT payloads under two object IDs, then reads them back through ObjectManager's public API.
#include <cstdio>
#include <memory>
#include <string>

#include "scaler/object_storage/object_manager.h"
#include "scaler/ymq/buffered_bytes.h"

using scaler::object_storage::ObjectID;
using scaler::object_storage::ObjectManager;

static std::string show(const std::shared_ptr<const scaler::object_storage::ObjectPayload>& payload)
{
    return payload ? "\"" + payload->asString().value_or("<non-string>") + "\"" : "<null>";
}

int main()
{
    ObjectManager manager;
    const ObjectID idA {1, 0, 0, 0};
    const ObjectID idB {2, 0, 0, 0};

    manager.setObject(idA, std::make_unique<scaler::ymq::BufferedBytes>(std::string("payload-A")));
    auto returnedForB = manager.setObject(idB, std::make_unique<scaler::ymq::BufferedBytes>(std::string("payload-B")));

    std::printf("setObject(B) returned        %s\n", show(returnedForB).c_str());
    std::printf("getObject(A)                 %s\n", show(manager.getObject(idA)).c_str());
    std::printf("getObject(B)                 %s   (expected \"payload-B\")\n", show(manager.getObject(idB)).c_str());
    std::printf("size()=%zu sizeUnique()=%zu totalObjectsSize()=%zu   (expected 2, 2, 18)\n",
                manager.size(), manager.sizeUnique(), manager.totalObjectsSize());

    manager.deleteObject(idA);
    std::printf("after deleteObject(A): getObject(B) %s   (expected \"payload-B\")\n",
                show(manager.getObject(idB)).c_str());

    const bool bIsCorrect = manager.getObject(idB) && manager.getObject(idB)->asString() == "payload-B";
    std::printf("RESULT: %s\n", bIsCorrect ? "B round-trips correctly" : "B's bytes were replaced by A's");
    return bIsCorrect ? 0 : 1;
}
```
</details>

<details><summary><code>run.sh</code></summary>

```bash
#!/bin/bash
# Usage: ./run.sh /path/to/opengris-scaler
# Needs: clang++ with C++23, Cap'n Proto (headers + `capnp` compiler).
# On macOS with only Command Line Tools: CXXFLAGS="-isysroot $(xcrun --show-sdk-path)" or the CLT SDK path.
set -euo pipefail
SCALER="$(cd "${1:?path to opengris-scaler clone}" && pwd)"
HERE="$(cd "$(dirname "$0")" && pwd)"
OUT="$HERE/build"
CXX="${CXX:-clang++}"
CAPNP_PREFIX="$(dirname "$(dirname "$(command -v capnp)")")"
mkdir -p "$OUT/protocol"

capnp compile -I"$CAPNP_PREFIX/include" -oc++:"$OUT/protocol" --src-prefix="$SCALER/src/protocol" \
    "$SCALER/src/protocol/object_storage.capnp"

FLAGS=(${CXXFLAGS:-} -std=c++23 -O0 -g -I"$SCALER/src/cpp" -I"$OUT" -I"$CAPNP_PREFIX/include")
LIBS=(-L"$CAPNP_PREFIX/lib" -lcapnp -lkj)
MANAGER="$SCALER/src/cpp/scaler/object_storage/object_manager.cpp"

echo "scaler commit: $(git -C "$SCALER" rev-parse --short HEAD)  object_manager.cpp unmodified: $(git -C "$SCALER" diff --quiet HEAD -- src/cpp/scaler/object_storage && echo yes || echo NO)"

"$CXX" "${FLAGS[@]}" "$HERE/repro_collision.cpp" "$MANAGER" "$OUT/protocol/object_storage.capnp.c++" "${LIBS[@]}" -o "$OUT/control"
"$CXX" "${FLAGS[@]}" -c "$MANAGER" -include "$HERE/force_collision.h" -o "$OUT/object_manager_collide.o"
"$CXX" "${FLAGS[@]}" "$HERE/repro_collision.cpp" "$OUT/object_manager_collide.o" "$OUT/protocol/object_storage.capnp.c++" "${LIBS[@]}" -o "$OUT/collision"

echo; echo "=== control: real std::hash, two different payloads ==="; "$OUT/control" || true
echo; echo "=== forced collision: same hash, two different payloads ==="; "$OUT/collision" || true
```
</details>

**Reproduction Evidence**

- **Commit showing reproduction:** none (the harness isn't in my fork)
- **Screenshots/logs:** the output of `run.sh`, from my run on 2026-11-18:

```text
scaler commit: e7fd9f0  object_manager.cpp unmodified: yes

=== control: real std::hash, two different payloads ===
setObject(B) returned        "payload-B"
getObject(A)                 "payload-A"
getObject(B)                 "payload-B"   (expected "payload-B")
size()=2 sizeUnique()=2 totalObjectsSize()=18   (expected 2, 2, 18)
after deleteObject(A): getObject(B) "payload-B"   (expected "payload-B")
RESULT: B round-trips correctly

=== forced collision: same hash, two different payloads ===
setObject(B) returned        "payload-A"
getObject(A)                 "payload-A"
getObject(B)                 "payload-A"   (expected "payload-B")
size()=2 sizeUnique()=1 totalObjectsSize()=9   (expected 2, 2, 18)
after deleteObject(A): getObject(B) "payload-A"   (expected "payload-B")
RESULT: B's bytes were replaced by A's
```

- **My findings:**
  - The bug is real on `main` today. When two different payloads share a hash, `setObject` finds the existing entry, only increments its use count (`object_manager.cpp:49`), and returns the first payload. The second payload's bytes are freed.
  - From then on, the second object's ID reads the first object's bytes, including after the first object is deleted.
  - The accounting stays consistent: one unique object, 9 bytes. So nothing in the server's totals shows that data was lost.
  - The existing tests in `tests/cpp/object_storage/test_object_manager.cpp` all use the same `"Hello"` payload, so none of them covers this case.
  - Limits: the collision is forced, not natural. I didn't run the object storage server (it calls these same methods at `object_storage_server.cpp:235` and `:251`) or the repo's GTest suite.

**Toolkit**

- Tool: repro-check in live mode. I ran `claude "repro-check: grade my claim comment in claim-draft.md and my repro report in repro-draft.md for issue …"` twice. The voice guard also checked both drafts.
- What it produced:
  - Run 1: **hold**, with 1 of 7 required checks failing. Followable steps failed because only one of the three harness files was in the report: `repro_collision.cpp` was an excerpt and `run.sh` was only described.
  - Run 2: **accept**, with all 7 required checks passing. It checked my line citations against `e7fd9f0` and checked that the report's output matches my run log line for line.
- Difficulties:
  - repro-check only reads; it can't run the harness. It checks a reproduction by comparing the report with the code and the log, not by repeating it.
  - My claim was already posted, so it graded `claim-draft.md` as an edit to the posted comment.
  - It flagged two problems with the posted claim. It breaks my claims rule ("open a PR within about a week"). And it says the 128-bit hash was "the route that @gxuu mentioned", but gxuu actually suggested just checking for collisions.
- What changed:
  - I pasted the full `run.sh` and `repro_collision.cpp` into the report, and changed the command to `bash repro/run.sh` so a copied script runs.
  - I restored the posted comment's Markdown in `claim-draft.md`.
  - Still to do: edit the posted claim with the new timeframe line and correct how it describes gxuu's suggestion.

---

## Solution Approach

**Analysis**

The cause is that `ObjectManager` uses a payload's 64-bit hash as the payload's identity. Every path below is under `src/cpp/scaler/object_storage/`.

- **The data model can't hold a collision.** `object_manager.h:53-54` has two maps: `objectIDToHash` (object ID → hash) and `hashToObject` (hash → one `ManagedObject {useCount, payload}`). With the hash as the key, two different payloads with the same hash can't both be stored.
- **`setObject` never compares bytes.** `computePayloadHash` (`object_manager.cpp:10-13`) hashes the bytes with `std::hash<std::string_view>`. `setObject` (`:19-53`) records the ID's hash (`:29`) and looks it up (`:31`). If the hash is already there, it only adds one to `useCount` (`:49`) and returns the stored payload (`:52`). The new `unique_ptr` goes out of scope, and its bytes are freed.
- **Every read follows the hash.** `getObject` (`:55-64`), `deleteObject` (`:66-89`) and `duplicateObject` (`:91-114`) all go from ID to hash to that one entry. After a collision, they all act on the first payload. `sizeUnique()` (`:126-129`) counts hash keys, so it counts the two objects as one.
- **The server passes the wrong bytes on.** `object_storage_server.cpp` sends `ObjectManager`'s results straight to clients: SET `:235`, GET `:251`, DELETE `:264`, DUPLICATE `:288` and `:407`, and the totals at `:308-310`. From reading that code, a client asking for B would get A's bytes, and nothing would report an error. I haven't run a collision through the server.
- **The reproduction agrees.** Forcing every hash to the same value makes `getObject(B)` return `"payload-A"`, including after A is deleted, with 1 unique object and 9 bytes counted. The control build with the real hash returns `"payload-B"`, with 2 objects and 18 bytes.
- **Why the tests miss it.** Every test in `tests/cpp/object_storage/test_object_manager.cpp` stores the same `"Hello"` payload.
- **`std::hash` differs by platform.** Its algorithm depends on the standard library: libc++ on macOS, libstdc++ on Linux, MSVC on Windows. So a test can't rely on a known pair of colliding payloads, and it has to force the collision.

**Proposed Solution**

This follows rafa-be's suggestion in the thread: keep `std::hash` and add an equality check. It works like `std::unordered_set` does, which gxuu named as the fallback. My claim already asks rafa-be to choose between this and a 128-bit hash, and I won't build until that's answered (step 1 below).

- **One hash, several payloads.** `hashToObject` becomes `std::map<ObjectHash, std::vector<ManagedObject>>`. The vector holds every distinct payload with that hash, and it almost always has one entry.
- **`setObject` compares before sharing.** In the hash's bucket, it looks for an entry with the same size and the same bytes (`std::equal` over `data()`; `Bytes` has no `operator==`). On a match, it adds one to `useCount` and returns that payload, as it does today. With no match, it adds a new entry and adds its size to `totalObjectsBytes`.
- **Each ID knows its exact payload.** `objectIDToHash` becomes a map from ID to a small `{hash, payload}` record. Since it no longer holds only a hash, I'll rename it `objectIDToObject` and update every use. `getObject` returns the record's payload directly. `deleteObject` and `duplicateObject` find the entry in the bucket by comparing payload pointers, not bytes, and remove a bucket once it's empty. `sizeUnique()` counts payloads, not hash keys.
- **The hash function can be passed in.** A new `explicit ObjectManager(PayloadHashFunction)` constructor takes the hash function, where `PayloadHashFunction` is a plain function pointer, `ObjectHash (*)(const ObjectPayload&)`. The default constructor keeps using `computePayloadHash`, so the server keeps working unchanged. Tests pass in a function that returns the same value for every payload, which forces a collision.
- **Cost:** the byte comparison only runs when the hash already exists, which almost always means a real duplicate. In rafa-be's benchmark, comparing took 0.7 to 0.85 times as long as hashing up to 500 MB, and about 2.4 times as long at 2 GB. Storing a payload whose hash isn't in the table costs what it does today.

What I'm deliberately not changing:

- The hash function: no 128-bit hash, no xxHash, no new dependency.
- `ObjectManager`'s public methods: their signatures, return values, and the dedup of identical payloads.
- `object_storage_server.cpp`, the protocol, and the Python code.
- ~~The possible read of freed memory in `duplicateObject(id, id)`: I won't fix it here.~~ Changed during the build (see Deviations). The new ID record turned that read into a server crash, so the PR now guards `duplicateObject(id, id)` in its own commit. `hashIt` from `:94` is used at `:105` after `deleteObject` erases it at `:86`.
- The version number. CONTRIBUTING.md asks for a bump in `scaler/about.py`, which no longer exists, and recent merged PRs haven't bumped `src/scaler/version.txt`. I'll ask in the PR.

**Implementation Plan**

1. Wait for a reply to my claim on #177 (posted 2026-11-19), which already asks rafa-be to choose between the equality check and a 128-bit hash. Write no code until then. If the reply picks the equality check, start at step 2. If it picks the 128-bit hash, rewrite this plan. This plan comment stays a local draft and isn't posted, so I'll ask whether the hash-function constructor is an acceptable way to test collisions in the PR description instead.
2. Add an `upstream` remote and branch from the latest `finos/opengris-scaler` `main` (`45fd02d` or later).
3. In `object_manager.h` and `object_manager.cpp`, add a `PayloadHashFunction` type and the `explicit ObjectManager(PayloadHashFunction)` constructor. The default constructor passes `computePayloadHash`. Nothing else changes yet.
4. In `tests/cpp/object_storage/test_object_manager.cpp`, add tests that build an `ObjectManager` with a hash that always returns the same value:
   - Two different payloads, `"payload-A"` and `"payload-B"`: B reads back as `"payload-B"`. `sizeUnique()` is 2 and `totalObjectsSize()` is 18. B still reads back after A is deleted. A duplicate of B returns B's bytes. Deleting everything brings the totals back to 0.
   - Two identical payloads with the same hash still share one copy: `sizeUnique()` is 1.

   Run `ctest --preset darwin-arm64 -R test_object_manager` and confirm the collision test fails on the unchanged storage code.
5. Change `ObjectManager` as described in Proposed Solution: the bucket and ID-record types in `object_manager.h`, and `setObject`, `getObject`, `deleteObject`, `duplicateObject` and `sizeUnique` in `object_manager.cpp`. Follow the file's existing style. Rerun the new tests and confirm they pass.
6. Verify:
   - Run my ship manifest's checks: the C++ build and `./scripts/test.sh`, clang-format on all C++ files, the Python object storage tests, and ruff and mypy.
   - Rerun my repro harness (`force_collision.h`, `repro_collision.cpp` and `run.sh`, printed in full in my contribution story's Reproduction Process section and saved to a `repro/` folder outside the clone) against the changed `object_manager.cpp`. The forced-collision run should now print `"payload-B"` with 2 objects and 18 bytes, the same as the control. Changed during the build: `repro_collision.cpp` now builds `ObjectManager` with a constant hash through the new constructor, run before (`b4998a0`) and after the fix (see Deviations).
   - Check `duplicateObject(id, id)` on the old and new code.
7. Commit with Conventional Commits, one concern per commit, and no agent `Co-authored-by` trailer:
   - `refactor(object_storage): let ObjectManager take its payload hash function`, for step 3.
   - `fix(object_storage): make duplicating an object onto its own ID a no-op`, with its test. Added during the build.
   - `fix(object_storage): compare payload bytes when hashes match`, with the collision tests.
8. Confirm my FINOS individual CLA is on file, since CONTRIBUTING.md says nothing merges without one.
9. Open the PR from my fork. In its description:
   - Ask about the hash-function constructor and the version bump.
   - Say in one line why I stored both payloads instead of only detecting the collision (gxuu's first suggestion): detecting it alone would leave B with no correct place to be stored.
   - List each deviation below.
   - Say how I used AI tools.

Deviations:

- **2026-11-19, step 1:** I built before rafa-be replied to my claim. The branch is local, and nothing is pushed. If the reply picks the 128-bit hash, I'll rewrite the branch.
- **2026-11-19, `duplicateObject(id, id)` is now in scope:**
  - My plan left this bug out. But with the new `{hash, payload}` record, `duplicateObject(a, a)` crashed with a segfault (exit 139), whether the payload had one owner or two. On `main` it returns null and leaves 0 bytes counted for 1 stored object.
  - A client can trigger it: `processDuplicateRequest` passes the client's two IDs straight through. So my change would have turned silent corruption into a server crash.
  - It's now its own commit: an early return when the two IDs match, with a test that crashes without it.
- **2026-11-19, step 6 harness:**
  - `force_collision.h` renames every token named `hash`, and that now includes the new `ObjectLocation::hash` field, so the forced-collision build no longer compiles.
  - I didn't rename the field to suit the harness. Instead, a copy of `repro_collision.cpp` builds `ObjectManager` with a constant hash (`0x5eed`) through the new constructor; it's a one-line diff, with the same payloads and printouts.
  - I ran it against `b4998a0` (the constructor, with the old storage) and against the fix.
- **2026-11-19, smaller choices:**
  - I also renamed `hashToObject` to `hashToObjects`, since it now holds several payloads per hash.
  - The ID record is named `ObjectLocation`.
  - `sizeUnique()` uses a `uniqueObjectsCount` counter instead of walking the buckets, so it stays constant-time.

**Toolkit**

- Tool: plan-check in live mode. I ran `claude "plan-check: grade my plan in plan.md and draft comment in plan-comment.md for issue https://github.com/finos/opengris-scaler/issues/177"` from my clone, revised, and reran it until it accepted.
- What it produced:
  - Run 1 was **reject**, with 1 of 7 required checks failing. Thread and repository alignment failed because my step 1 said to post the plan comment on #177, and my scope keeps plan comments off the thread.
  - After I revised, the next three runs were all **accept**, with every check passing.
  - It checked every line number against the source. It confirmed `object_manager.cpp` is the same blob on `e7fd9f0` and upstream `45fd02d`, and it checked my cost numbers against rafa-be's benchmark table.
- Difficulties:
  - Run headless with `claude -p`, it couldn't read its own rubric and procedure, because they're outside the clone. It stopped without grading, which is the right behavior, until I passed `--add-dir ~/.claude/skills/plan-check` and allowed its read-only `gh` and `git` calls.
  - It can't run my repro harness, so it graded the forced-collision results as the drafts quote them.
  - My `procedure.md` is written for eval bundles ("Repo facts", "Thread highlights"). It doesn't say where each one comes from in live mode, or what to use when no repro comment is posted.
- What changed:
  - Step 1 now waits for a reply to my posted claim instead of posting the plan. The constructor question moved into the PR description.
  - I fixed my cost claim ("about the same cost as the hash" didn't hold at 2 GB, where comparing took 2.4 times as long). I rename `objectIDToHash`, since it will hold more than a hash, and I named the hash function's type.
  - I no longer claim the PR can't change `duplicateObject(id, id)`. Instead, I'll check it after the change.
  - I marked the server behavior as read from the code, not run. I added the FINOS CLA check, and a PR line on why I chose buckets over gxuu's detect-only option.
  - In the comment, I replaced a self-contradicting sentence ("unmodified … with `std::hash` replaced") with how the collision was actually forced.
  - Still to patch in `procedure.md`: say where each evidence section comes from in live mode.

---

## Testing Strategy

Every output below is pasted in full in `test_evidence.md` in my clone, from runs on 2026-11-19 against branch head `6df0ae1`.

**1. My reproduction, before and after**

- **Before, on today's `main`:** my unchanged Unit 6 harness (`force_collision.h`, `repro_collision.cpp`, `run.sh`), run on a clean worktree of upstream `main` (`45fd02d`). It prints the same failure as on 2026-11-18: with the forced collision, `getObject(B)` returns `"payload-A"`, `sizeUnique()` is 1, and `totalObjectsSize()` is 9. The control with the real hash returns `"payload-B"`, 2, and 18.
- **Same harness on both sides:** `force_collision.h` can't compile against the fix, because its `#define hash` also renames the new `ObjectLocation::hash` field. So a copy of `repro_collision.cpp` sets the constant hash (`0x5eed`) through the new constructor; it's a one-line diff. I ran it on `b4998a0`, which has the constructor but the old storage, and on `6df0ae1`:

  | | `setObject(B)` returns | `getObject(B)` | `sizeUnique()` | `totalObjectsSize()` | after deleting A | exit |
  |---|---|---|---|---|---|---|
  | before (`b4998a0`) | `"payload-A"` | `"payload-A"` | 1 | 9 | `"payload-A"` | 1 |
  | after (`6df0ae1`) | `"payload-B"` | `"payload-B"` | 2 | 18 | `"payload-B"` | 0 |

**2. New tests that fail before the fix and pass after**

All three are in `tests/cpp/object_storage/test_object_manager.cpp`.

- **`TestHashCollisionKeepsPayloadsApart`:** uses a hash that returns 42 for every payload.
  - It checks that A and B keep their own bytes, that a duplicate of B returns B, that B survives deleting A, and that the totals are 2 and 18, then 0 after everything is deleted.
  - Before the fix, 8 assertions failed, with the repro's values (`"payload-A"`, 1, 9).
- **`TestHashCollisionStillSharesIdenticalPayloads`:** two identical payloads under the same hash still share one copy (the same pointer, `sizeUnique()` 1). It passes before and after. It guards against a fix that simply stops deduplicating.
- **`TestDuplicateObjectOntoItself`:** without the guard, the test binary crashed with a segfault (exit 139). With it, the test passes.

**3. `duplicateObject(a, a)` directly**

- **On `main`:** it returns null. With one owner, it counts 0 bytes for 1 stored object.
- **On the fix:** it returns the payload and the counts are unchanged, with one owner or two.

**4. The project's own checks: every row of my ship manifest, as written, in a fresh shell**

| Row | Result |
|---|---|
| C++ build (`./scripts/build.sh`) | exit 0 |
| Rebuild the Python extensions into `.venv` | exit 0 |
| `./scripts/test.sh` | 6 of 6 ctest targets passed, including `test_object_manager` (8 of 8 tests) and `test_object_storage_server` |
| clang-format 21 on every `.cpp`/`.h` file | no output, exit 0 |
| Python object storage tests | 10 passed, including the WebSocket parity test, which sends SET/GET through real C++ server processes |
| ruff, ruff format, mypy | all pass, with no mypy issues in 411 files |

**Not verified**

- **A natural collision:** every collision here is forced.
- **A collision through the running server:** the server tests and the WebSocket parity test go through the server, but with the real hash, so they show the server still works, not that it handles a collision.
- **Linux (libstdc++) and Windows (MSVC):** I only built with LLVM 21 on macOS. CI runs all three.
- **The full Python suite:** it's excluded in my manifest, because on `main` on this Mac, 6 tests time out under load and the run takes about 19 minutes. CI runs it.
- **Performance:** I didn't measure the cost of the byte comparison. The cost claim rests on rafa-be's benchmark.

**Toolkit**

- Tool: my ship manifest's six checks and my Unit 6 repro harness. I ran each manifest row exactly as written, in a fresh shell with no virtual environment, the way the ship-gate runs them. A small script read the commands out of `ship-manifest.md` so I couldn't drift from what the gate will run. The ship-gate itself, with pr-precheck, runs at the PR step.
- What it produced: all six rows pass on `6df0ae1` in about a minute. The repro shows the failure on `main` and on `b4998a0`, and correct output on the fix. Everything is in `test_evidence.md`.
- Difficulties:
  - The harness's `#define hash` trick doesn't survive a new field named `hash`.
  - AddressSanitizer builds hang at run time on this Mac, even for code that's fine, so I couldn't use it for the `duplicateObject` check.
  - My manifest can't run the full Python suite within the gate's budget, so it narrows to the object storage tests.
  - In a zsh loop, `$rev:src` was read as a substitution modifier and mangled my `git show` paths on the first try.
- What changed:
  - I ran the harness through the new constructor, on `b4998a0` before and `6df0ae1` after, so both sides use the same program. I kept the original harness on `main` for continuity with my repro report.
  - I compared plain builds instead of sanitizer builds.
  - I wrote `${rev}`, with braces.

---

## Implementation Notes

**2026-11-19: branch and refactor**

- rafa-be hadn't replied to my claim, which my plan's step 1 waits for. I chose to build on a local branch anyway and record it as a deviation.
- I added `upstream` and branched `fix/177-hash-collision` from upstream `main` at `45fd02d`. `object_manager.cpp` hadn't changed since my repro commit `e7fd9f0`.
- I unset the branch's tracking of `upstream/main`, so a stray `git push` can't target the upstream repo.
- Refactor `b4998a0`: `ObjectManager` takes a `PayloadHashFunction` (`ObjectHash (*)(const ObjectPayload&) noexcept`). The default constructor passes `computePayloadHash`, and `ObjectHash` moved to `public` so the type can be named.
- The object storage tests still passed (2 of 2 ctest targets), and clang-format was clean.
- AGENTS.md wants `_camelCase` private fields, but `ObjectManager`'s fields don't use it. I followed the file, as my plan says, rather than mixing the two styles in one class.

**2026-11-19: tests first, then a scope change**

- I added `TestHashCollisionKeepsPayloadsApart` and `TestHashCollisionStillSharesIdenticalPayloads`. Both pass `collidingHash`, which returns 42 for every payload.
- On the refactor-only code, the collision test failed with the repro's numbers: B read `"payload-A"`, with `sizeUnique()` 1 and 9 bytes instead of 2 and 18. The dedup test passed, as it should today.
- I wrote the fix: a bucket per hash, `hasSameBytes` (`std::equal` over `data()`) in `setObject`, an `ObjectLocation {hash, payload}` per ID, a lookup by pointer in delete and duplicate, and a `uniqueObjectsCount` counter. All 7 tests passed.
- **Wrong turn:**
  - I then ran the `duplicateObject(id, id)` check my plan asked for, comparing the old and new code. On `main` it returns null and leaves 0 bytes counted for 1 object. The new code crashed with a segfault.
  - My first attempt used AddressSanitizer, but every build hung on this Mac, the safe cases too, so I compared plain builds instead.
  - The server passes a client's DUPLICATE IDs straight through, so a client could crash the server.
  - I chose to guard it in this PR, rather than shipping a new crash or blocking on a separate PR first.
- I set the collision work aside with `git stash`, added the guard and `TestDuplicateObjectOntoItself` to the old code, saw the test crash without the guard (exit 139) and pass with it, and committed `f83bd6f`.
- Restoring the stash conflicted, because both commits added tests at the end of the same file. I rebuilt the file from both sides and pointed the guard at the new `ObjectLocation`.
- A typo in my shell command dropped the stash before the resolved file was copied in. Nothing was lost, because the resolved file was already saved.

**2026-11-19: verification and the fix commit**

- All 8 `test_object_manager` tests pass. The guarded `duplicateObject(a, a)` now returns the payload, with the counts unchanged.
- The repro harness's `#define hash` broke on the new `ObjectLocation::hash` field. I ran the one-line constructor variant instead. Before the fix (`b4998a0`) it printed the Unit 6 failure line for line. After the fix, the forced collision prints `"payload-B"`, 2 objects and 18 bytes, the same as the control.
- Every ship manifest row passed:
  - The C++ build and `./scripts/test.sh` (6 of 6).
  - clang-format.
  - The Python object storage tests: 10 passed, one more than before, from a test upstream added.
  - ruff and mypy.
- I committed the fix as `6df0ae1`. The branch is now refactor, guard, fix, with no agent trailer.

**Toolkit**

- Tool: Claude Code built the change on my branch, with `plan.md` as the scope to stay inside and my `CLAUDE.local.md` for the repo's rules (Conventional Commits, no agent trailer, a failing test before the fix). It ran the object storage tests and clang-format after each commit, and the full manifest before the fix commit. It asked me before each decision that wasn't in the plan.
- What it produced:
  - Three commits: `b4998a0` (refactor), `f83bd6f` (guard) and `6df0ae1` (fix), with three new tests. Each test was seen failing before its change.
  - Dated notes, and a Deviations list in the plan.
- Difficulties:
  - **Scope:** the plan's own check after step 5 found that the new per-ID record turned the `duplicateObject(id, id)` read of freed memory into a segfault that a client can trigger. My plan had kept that bug out of the PR. plan-check had warned that "neither fixes nor changes" might not hold, and it didn't.
  - **Commit order:** putting the guard before the fix meant stashing the fix. The stash conflicted in the test file, and a typo in my command dropped the stash before the resolved file was copied in. The resolved file was already saved, so nothing was lost.
  - **Style:** AGENTS.md's `_camelCase` field rule disagrees with how `ObjectManager` names its fields today.
- What changed:
  - The guard got its own commit before the fix, so no commit on the branch can crash the server. The plan, `plan.md` and Deviations record it, and the PR description will list it.
  - New fields follow the file's existing names. The style question isn't mine to settle in this PR.
  - I added AddressSanitizer's hang on this Mac to my notes, so I don't lose time on it again.

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
