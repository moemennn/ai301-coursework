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
