/**
 * @file
 * Copyright 2018 - present, Dmitry Lotakov
 *
 * This source code is licensed under the BSD-3-Clause license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

namespace metak {

template <typename T>
struct constants {
    constexpr static auto sqrt_2 = static_cast<T>(1.41421356237309504880168872420969807);
    constexpr static auto sqrt_3 = static_cast<T>(1.73205080756887729352744634150587236);
    constexpr static auto pi     = static_cast<T>(3.14159265358979323846264338327950288);
    constexpr static auto sqr_pi = static_cast<T>(1.77245385090551602729816748334114518);
    constexpr static auto e      = static_cast<T>(2.71828182845904523536028747135266249);
    constexpr static auto log_2  = static_cast<T>(0.69314718055994530941723212145817656);
    constexpr static auto log_10 = static_cast<T>(2.30258509299404568401799145468436420);
};

template <typename T, int p = 1, int q = 1>
constexpr auto c_sqrt_2 = constants<T>::sqrt_2 * p / q;

template <typename T, int p = 1, int q = 1>
constexpr auto c_sqrt_3 = constants<T>::sqrt_3 * p / q;

template <typename T, int p = 1, int q = 1>
constexpr auto c_pi = constants<T>::pi * p / q;

template <typename T, int p = 1, int q = 1>
constexpr auto c_sqr_pi = constants<T>::sqr_pi * p / q;

template <typename T, int p = 1, int q = 1>
constexpr auto c_e = constants<T>::e * p / q;

template <typename T, int p = 1, int q = 1>
constexpr auto c_log_2 = constants<T>::log_2 * p / q;

template <typename T, int p = 1, int q = 1>
constexpr auto c_log_10 = constants<T>::log_10 * p / q;

}  // namespace metak
