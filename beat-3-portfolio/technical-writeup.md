# Opening a fix for silent data loss on hash collisions in OpenGRIS Scaler's object store

## Overview

OpenGRIS Scaler is a FINOS open source project for running distributed computations, and its C++ object storage server saves memory by storing each distinct payload only once. Issue [#177](https://github.com/finos/opengris-scaler/issues/177) pointed out that it decided two payloads were the same by their 64-bit `std::hash` alone and never compared the bytes, so if two different payloads ever shared a hash, the second was thrown away and its ID returned the first one's data with no error. I reproduced the bug by forcing a collision, then opened a fix in [PR #1106](https://github.com/finos/opengris-scaler/pull/1106): payloads with the same hash now share a bucket and are compared byte by byte, and `ObjectManager` takes its hash function as a constructor argument so tests can force collisions. While checking edge cases, I found that my first version turned a quiet bug in `duplicateObject(id, id)` into a server crash, so I added a guard in its own commit before the fix. The PR is open and waiting for maintainer review. The project's CI hasn't run yet, because it needs a maintainer's approval for a first-time contributor.

## What happened

**Proving the bug (2026-11-18).** The issue puts the odds of a natural collision at 0.00000271% for a million objects, and `std::hash` is a different algorithm in libc++, libstdc++ and MSVC, so there's no colliding pair I could rely on. I forced one instead: I compiled the unmodified `object_manager.cpp` with a header pre-included through `-include` that swaps `std::hash` for a stub that always returns `0x5eed`. A small program stores `"payload-A"` and `"payload-B"` and reads them back. With the real hash it works. With the forced collision, B comes back as A:

```text
=== forced collision: same hash, two different payloads ===
setObject(B) returned        "payload-A"
getObject(B)                 "payload-A"   (expected "payload-B")
size()=2 sizeUnique()=1 totalObjectsSize()=9   (expected 2, 2, 18)
after deleteObject(A): getObject(B) "payload-A"   (expected "payload-B")
RESULT: B's bytes were replaced by A's
```

The accounting stayed consistent with the wrong answer (1 unique object, 9 bytes), so nothing in the server would show that data had been lost. The existing tests missed it because every one of them stores the same `"Hello"` payload.

**Choosing the fix.** The thread discussed a 128-bit hash, detecting the collision and reporting it, and rafa-be's suggestion to keep the hash and compare bytes, the way `std::unordered_set` does. I chose the byte comparison. A wider hash makes a collision rarer but still possible. Detecting one tells you about the problem but still leaves B with nowhere correct to be stored. The core change is in `setObject` and the data model:

```cpp
-    std::map<ObjectID, ObjectHash> objectIDToHash;
-    std::map<ObjectHash, ManagedObject> hashToObject;
+    std::map<ObjectID, ObjectLocation> objectIDToObject;
+    // Payloads with the same hash share a bucket and are told apart by their bytes.
+    std::map<ObjectHash, std::vector<ManagedObject>> hashToObjects;
```

**Tests first (2026-11-19).** I added a constructor, `explicit ObjectManager(PayloadHashFunction)`, in its own refactor commit (`b4998a0`), so a test can pass in a hash that always returns 42. On that commit, before the fix, `TestHashCollisionKeepsPayloadsApart` failed 8 assertions with the same values as my reproduction. After the fix (`6df0ae1`), all 8 `test_object_manager` tests pass. The same reproduction program shows the difference:

| | `getObject(B)` | `sizeUnique()` | `totalObjectsSize()` | exit |
|---|---|---|---|---|
| before (`b4998a0`) | `"payload-A"` | 1 | 9 | 1 |
| after (`6df0ae1`) | `"payload-B"` | 2 | 18 | 0 |

**The change I didn't plan for.** My plan left a known bug out of scope: `duplicateObject(id, id)` deletes the entry and then reads it. On `main` that read returned null and miscounted the bytes, which was wrong but didn't crash. My plan still said to check that case on the old and new code, and on my new code it crashed with a segfault (exit 139), because the entry now held a `shared_ptr`. The server passes a client's two IDs straight through, so any client could have crashed it. I set the fix aside, added a guard and a test that crashes without it, and committed that first (`f83bd6f`), so no commit on the branch can crash the server:

```cpp
+    if (originalObjectID == newObjectID) {
+        // Overriding the object with itself would delete it first.
+        return locationIt->second.payload;
+    }
```

I recorded it as a dated deviation in my plan and explained it in the PR description.

**Getting it through my pre-PR checks (2026-11-20).** Before opening the PR, I ran a check script I wrote for the course. It runs six of the project's own checks, which I listed in my ship manifest, and grades the PR description against my pr-precheck rubric. It stopped me three times. First, the build ran under Rosetta and picked the x86_64 preset. Second, my local `main` was stale, so the diff looked like 24 files. Third, there was a false line in my description:

```text
- Claims match diff [fail]: Description says 'Commits, each with its tests', but test_evidence.md
  section 4 builds the collision tests on top of b4998a0 (commit 1), so commit 1 carries none.
```

I fixed each one, and the next run passed every check: the C++ build and 6 of 6 ctest targets, clang-format, the Python object storage tests, ruff and mypy, and all eight rubric checks. I opened PR #1106 right after. The EasyCLA bot flagged that I hadn't signed the FINOS contributor agreement, so I signed it, and that check now passes.

## Limitations and what's next

- **Every collision is forced.** I've never seen a natural collision go through this code, and I never ran one through the live server. The server tests pass, but with the real hash.
- **Only macOS is tested.** I built and tested with LLVM 21 on macOS only. Linux (libstdc++) and Windows (MSVC) are unverified until a maintainer approves the CI run. The one green check on the PR is the CLA, not a build.
- **No performance measurement.** My claim that the byte comparison is cheap rests on rafa-be's benchmark in the thread (0.7–0.85× the hash's cost up to 500 MB, about 2.4× at 2 GB), not on my own measurement.
- **I built before the design was confirmed.** If the maintainers choose the 128-bit hash, I'll have to rework the branch.

Next, I'd add a test that runs a forced collision through the object storage server end to end, and benchmark the comparison on large payloads myself. In my next contribution, I'd wait for a maintainer to confirm the design, or ask a smaller question first, before writing code.
