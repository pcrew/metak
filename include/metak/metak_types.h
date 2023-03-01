/**
 * @file
 * Copyright 2018 - present, Dmitry Lotakov
 *
 * This source code is licensed under the BSD-3-Clause license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <sys/types.h>

namespace metak {

using u8 = u_int8_t;
using s8 = int8_t;

using u16 = u_int16_t;
using s16 = int16_t;

using u32 = u_int32_t;
using s32 = int32_t;

using u64 = u_int64_t;
using s64 = int64_t;

using f32  = float;
using f64  = double;
using f128 = long double;

template <typename T, typename S>
using lesser_type_of = std::conditional_t<sizeof(T) < sizeof(S), T, S>;

template <typename T, typename S>
using wider_type_of = std::conditional_t<sizeof(S) < sizeof(T), T, S>;

}  // namespace metak
