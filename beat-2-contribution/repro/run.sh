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
