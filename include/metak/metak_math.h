/**
 * @file
 * Copyright 2018 - present, Dmitry Lotakov
 *
 * This source code is licensed under the BSD-3-Clause license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <limits>

namespace metak {

template <typename T>
constexpr auto select(bool cnd, T x, T y) {
    return cnd ? x : y;
}

template <typename T>
constexpr auto trunc(T x) {
    return static_cast<T>(static_cast<s64>(x));
}

template <typename T>
constexpr auto is_even(T x) {
    return x % 2 == 0;
}

template <typename T>
constexpr auto is_odd(T x) {
    return !is_even(x);
}

template <typename T, std::enable_if_t<std::is_unsigned<T>::value, bool> = true>
constexpr auto abs(T x) {
    return x;
}

template <typename T, std::enable_if_t<!std::is_unsigned<T>::value, bool> = true>
constexpr auto abs(T x) {
    return x >= 0 ? x : -x;
}

template <typename T, typename S>
constexpr auto is_close(T x, S y) {
    if constexpr (std::is_floating_point<T>::value && std::is_floating_point<T>::value) {
        using lesser_type = lesser_type_of<T, S>;
        return abs(x - y) <= std::numeric_limits<lesser_type>::epsilon() * abs(x + y) ||
               abs(x - y) < std::numeric_limits<lesser_type>::min();
    } else {
        return x == y;
    }
}

namespace details {
template <typename T, typename Integral>
constexpr auto pow_helper(T val, Integral exponent) -> std::common_type_t<T, Integral> {
    return exponent == 0       ? 1
           : exponent % 2 == 0 ? pow_helper(val * val, exponent / 2)
                               : val * pow_helper(val * val, (exponent - 1) / 2);
}

}  // namespace details

template <typename T, typename Integral>
constexpr auto pow(T val, Integral exponent) -> std::common_type_t<T, Integral> {
    return exponent == 0  ? 1
           : exponent > 0 ? details::pow_helper(val, exponent)
                          : 1 / details::pow_helper(val, -exponent);
}

template <typename T>
constexpr auto factorial(T x) {
    T ret{1};
    for (T i = 2; i <= x; i++) {
        ret *= i;
    }

    return ret;
}

template <typename T>
constexpr auto min(T first) {
    return first;
}

template <typename T, typename... Rest>
constexpr auto min(T first, T second, Rest... rest) {
    return min(first < second ? first : second, rest...);
}

template <typename T>
constexpr auto max(T first) {
    return first;
}

template <typename T, typename... Rest>
constexpr auto max(T first, T second, Rest... rest) {
    return max(first > second ? first : second, rest...);
}

template <typename... Values>
constexpr auto sum(Values... values) {
    return (0 + ... + values);
}

template <typename T>
constexpr auto sum_of_sqr(T first) {
    return first * first;
}

template <typename T, typename... Rest>
constexpr auto sum_of_sqr(T first, Rest... rest) {
    return first * first + sum_of_sqr(rest...);
}

template <typename... Values>
constexpr auto prod(Values... values) {
    return (1 * ... * values);
}

template <typename... Values>
constexpr auto mean(Values... values) {
    return static_cast<f32>(sum(values...)) / sizeof...(values);
}

namespace details {
template <typename T>
constexpr auto is_prime_helper(T x, T divider) {
    return divider * divider > x ? true : x % divider == 0 ? false : is_prime_helper(x, divider + 2);
}

}  // namespace details

template <typename T>
constexpr auto is_prime(T x) {
    return x < 2 ? false : x == 2 ? true : x % 2 == 0 ? false : details::is_prime_helper(x, 3);
}

template <typename T, typename S>
constexpr auto gcd(T x, S y) -> std::common_type_t<T, S> {
    return y > x ? gcd(y, x) : x % y == 0 ? y : gcd(y, x % y);
}

template <typename T, typename... Rest>
constexpr auto gcd(T a, T b, T c, Rest... rest) {
    return gcd(a, gcd(b, c, rest...));
}

template <typename T, typename S>
constexpr auto lcm(T x, S y) -> std::common_type_t<T, S> {
    return x == 0 || y == 0 ? 1 : x * y / gcd(x, y);
}

template <typename T, typename... Rest>
constexpr auto lcm(T a, T b, T c, Rest... rest) {
    return lcm(a, lcm(b, c, rest...));
}

}  // namespace metak
