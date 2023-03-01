/**
 * @file
 * Copyright 2018 - present, Dmitry Lotakov
 *
 * This source code is licensed under the BSD-3-Clause license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <limits>
#include <cstdint>

namespace metak {

namespace details {

template <typename ToType, typename FromType,
          std::enable_if_t<std::is_signed_v<ToType> && std::is_signed_v<FromType>, bool> = true>
constexpr auto saturate_cast_helper(FromType value) {
    using cast_type       = std::conditional_t<std::is_floating_point_v<FromType>, FromType, intmax_t>;
    constexpr auto max_to = static_cast<cast_type>(std::numeric_limits<ToType>::max());
    constexpr auto min_to = static_cast<cast_type>(std::numeric_limits<ToType>::min());

    return static_cast<cast_type>(value) > max_to   ? std::numeric_limits<ToType>::max()
           : static_cast<cast_type>(value) < min_to ? std::numeric_limits<ToType>::min()
                                                    : static_cast<ToType>(value);
}

template <typename ToType, typename FromType,
          std::enable_if_t<std::is_signed_v<ToType> && std::is_unsigned_v<FromType>, bool> = true>
constexpr auto saturate_cast_helper(FromType value) {
    constexpr auto max_to = static_cast<uintmax_t>(std::numeric_limits<ToType>::max());

    return static_cast<uintmax_t>(value) > max_to ? std::numeric_limits<ToType>::max() : static_cast<ToType>(value);
}

template <typename ToType, typename FromType,
          std::enable_if_t<std::is_unsigned_v<ToType> && std::is_signed_v<FromType>, bool> = true>
constexpr auto saturate_cast_helper(FromType value) {
    using cast_type       = std::conditional_t<std::is_floating_point_v<FromType>, FromType, intmax_t>;
    constexpr auto max_to = static_cast<cast_type>(std::numeric_limits<ToType>::max());

    return value < 0                                ? 0
           : static_cast<cast_type>(value) > max_to ? std::numeric_limits<ToType>::max()
                                                    : static_cast<ToType>(value);
}

template <typename ToType, typename FromType,
          std::enable_if_t<std::is_unsigned_v<ToType> && std::is_unsigned_v<FromType>, bool> = true>
constexpr auto saturate_cast_helper(FromType value) {
    constexpr auto max_to = static_cast<uintmax_t>(std::numeric_limits<ToType>::max());

    return static_cast<uintmax_t>(value) > max_to ? std::numeric_limits<ToType>::max() : static_cast<ToType>(value);
}

}  // namespace details

template <typename ToType, typename FromType>
constexpr auto saturate_cast(FromType value) {
    constexpr auto max_to   = static_cast<f128>(std::numeric_limits<ToType>::max());
    constexpr auto max_from = static_cast<f128>(std::numeric_limits<FromType>::max());
    constexpr auto min_to   = static_cast<f128>(std::numeric_limits<ToType>::lowest());
    constexpr auto min_from = static_cast<f128>(std::numeric_limits<FromType>::lowest());

    if constexpr (std::is_same_v<ToType, FromType>) {
        return value;
    } else if constexpr ((max_to >= max_from) && (min_to <= min_from)) {
        return static_cast<ToType>(value);
    } else {
        return details::saturate_cast_helper<ToType>(value);
    }
}

}  // namespace metak
