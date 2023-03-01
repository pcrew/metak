/**
 * @file
 * Copyright 2018 - present, Dmitry Lotakov
 *
 * This source code is licensed under the BSD-3-Clause license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <functional>
#include <optional>
#include <string>
#include <array>

#include <metak/metak_array_view.h>

namespace metak {

template <auto val>
struct c_value_t {
    using value_type = decltype(val);

    constexpr c_value_t() noexcept {};

    constexpr value_type operator()() const { return value; }
    constexpr operator value_type() const { return value; }

    constexpr static auto abs() { return c_value_t<metak::abs(val)>(); }
    constexpr static auto is_odd() { return c_value_t<metak::is_odd(val)>(); }
    constexpr static auto is_even() { return c_value_t<metak::is_even(val)>(); }
    constexpr static auto is_prime() { return c_value_t<metak::is_prime(val)>(); }

    template <auto Exp>
    constexpr static auto pow(c_value_t<Exp>) {
        return c_value_t<metak::pow(val, Exp)>();
    }

private:
    constexpr static auto value{val};
};

template <auto a, auto b>
constexpr auto max(c_value_t<a>(), c_value_t<b>()) {
    return c_value_t<metak::max(a, b)>();
}

template <auto a, auto b>
constexpr auto min(c_value_t<a>(), c_value_t<b>()) {
    return c_value_t<metak::min(a, b)>();
}

template <auto a, auto b>
constexpr auto gcd(c_value_t<a>(), c_value_t<b>()) {
    return c_value_t<metak::gcd(a, b)>();
}

template <auto a, auto b>
constexpr auto lcm(c_value_t<a>(), c_value_t<b>()) {
    return c_value_t<metak::lcm(a, b)>();
}

template <typename T>
constexpr static auto is_c_value_t(T) {
    return false;
}

template <auto val>
constexpr static auto is_c_value_t(c_value_t<val>) {
    return true;
}

template <typename T>
constexpr static auto value(T val) {
    return val;
}

template <auto val>
constexpr static auto value(c_value_t<val>) {
    return val;
}

template <bool val>
using c_bool_t  = c_value_t<val>;
using c_false_t = c_bool_t<false>;
using c_true_t  = c_bool_t<true>;

template <std::size_t val>
using c_size_t = c_value_t<val>;

template <typename T, T... values>
struct c_values_t;

template <auto v_1, auto v_2, typename CommonType = std::common_type_t<decltype(v_1), decltype(v_2)>>
constexpr static auto concat(c_value_t<v_1>, c_value_t<v_2>) {
    return c_values_t<CommonType, static_cast<CommonType>(v_1), static_cast<CommonType>(v_2)>();
}

template <typename T1, T1... vs_1, typename T2, T2... vs_2, typename CommonType = std::common_type_t<T1, T2>>
constexpr static auto concat(c_values_t<T1, vs_1...>, c_values_t<T2, vs_2...>) {
    return c_values_t<CommonType, static_cast<CommonType>(vs_1)..., static_cast<CommonType>(vs_2)...>();
}

template <auto v, typename T, T... vs, typename CommonType = std::common_type_t<T, decltype(v)>>
constexpr static auto concat(c_values_t<T, vs...>, c_value_t<v>) {
    return c_values_t<CommonType, static_cast<CommonType>(vs)..., static_cast<CommonType>(v)>();
}

template <auto v, typename T, T... vs, typename CommonType = std::common_type_t<T, decltype(v)>>
constexpr static auto concat(c_value_t<v>, c_values_t<T, vs...>) {
    return c_values_t<CommonType, static_cast<CommonType>(v), static_cast<CommonType>(vs)...>();
}

template <typename T, T i0, T... is, T j0, T... js>
constexpr static auto merge(c_values_t<T, i0, is...> i, c_values_t<T, j0, js...> j) {
    if constexpr (i0 <= j0) {
        return merge(c_values_t<T, is...>(), c_values_t<T, j0, js...>()).template prepend<i0>();
    } else {
        return merge(c_values_t<T, i0, is...>(), c_values_t<T, js...>()).template prepend<j0>();
    }
}

template <typename T>
constexpr static auto merge(c_values_t<T>, c_values_t<T>) {
    return c_values_t<T>();
}

template <typename T, T i0, T j0>
constexpr static auto merge(c_values_t<T, i0>, c_values_t<T, j0>) {
    return c_values_t<T, metak::min(i0, j0), metak::max(i0, j0)>();
}

template <typename T, T v>
constexpr static auto merge(c_values_t<T, v>, c_values_t<T>) {
    return c_values_t<T, v>();
}

template <typename T, T v>
constexpr static auto merge(c_values_t<T>, c_values_t<T, v>) {
    return c_values_t<T, v>();
}

template <typename T, T v0, T... vs>
constexpr static auto merge(c_values_t<T, v0, vs...>, c_values_t<T>) {
    return c_values_t<T, v0, vs...>();
}

template <typename T, T v0, T... vs>
constexpr static auto merge(c_values_t<T>, c_values_t<T, v0, vs...>) {
    return c_values_t<T, v0, vs...>();
}

template <typename T, T... values>
constexpr static auto sort(c_values_t<T, values...> a) {
    if constexpr (a.size() == 0) {
        return c_values_t<T>();
    } else if constexpr (a.size() == 1) {
        return a;
    } else {
        return merge(sort(a.left_half()), sort(a.right_half()));
    }
}

template <typename T, T... values>
struct c_values_t {
    using value_type = T;

    constexpr c_values_t() = default;
    template <T... other_values>
    constexpr c_values_t(c_values_t<T, other_values...> = c_values_t<T, other_values...>()) {
        *this = c_values_t<T, other_values...>();
    }

    constexpr static auto as_tuple() { return std::make_tuple(values...); }
    constexpr static auto as_array() { return std::array<value_type, sizeof...(values)>{values...}; }
    constexpr static std::optional<std::string> as_string() {
        if constexpr (std::is_same_v<value_type, char>) {
            return std::string{values...};
        } else {
            return std::nullopt;
        }
    }

    constexpr static auto data() { return as_array().data(); }
    constexpr static auto size() { return c_size_t<sizeof...(values)>(); }
    constexpr static auto length() { return size(); }
    constexpr static auto max_size() { return c_size_t<std::numeric_limits<std::size_t>::max()>(); }
    constexpr static auto empty() { return c_bool_t<size() == 0>(); }

    template <std::size_t index>
    constexpr const auto operator[](c_size_t<index>) const {
        return c_value_t<get(c_size_t<index>())>();
    }

    constexpr const auto operator[](std::size_t index) const { return as_array()[index]; }

    template <auto e>
    constexpr static auto prepend() {
        return c_values_t<value_type, static_cast<value_type>(e), values...>();
    }

    template <auto e>
    constexpr static auto append() {
        return c_values_t<value_type, values..., static_cast<value_type>(e)>();
    }

    template <std::size_t n>
    constexpr static auto trunc() {
        if constexpr (n >= size()) {
            return c_values_t<value_type, values...>();
        } else if constexpr (n == 0) {
            return c_values_t<value_type>();
        } else if constexpr (n == 1) {
            return c_values_t<value_type, get(c_size_t<0>())>();
        } else {
            return concat(trunc<n - 1>(), c_value_t<get(c_size_t<n - 1>())>());
        }
    }

    template <std::size_t start, std::size_t n>
    constexpr static auto slice() {
        if constexpr (start >= size()) {
            return c_values_t<value_type>();
        } else if constexpr (start + n > size()) {
            return slice<start, size() - start>();
        } else if constexpr (n == 1) {
            return c_values_t<value_type, get(c_size_t<start>())>();
        } else {
            return concat(c_value_t<get(c_size_t<start>())>(), slice<start + 1, n - 1>());
        }
    }

    template <std::size_t to_remove>
    constexpr static auto remove_prefix() {
        return slice<to_remove, size()>();
    }

    template <std::size_t to_remove>
    constexpr static auto remove_suffix() {
        return trunc<size() - to_remove>();
    }

    template <value_type... others>
    constexpr static auto starts_with(c_values_t<value_type, others...> what) {
        return c_bool_t<trunc<what.size()>() == what>();
    }

    template <value_type... others>
    constexpr static auto ends_with(c_values_t<value_type, others...> what) {
        return c_bool_t<slice<size() - what.size(), what.size()>() == what>();
    }

    template <value_type... others>
    constexpr static auto contains(c_values_t<value_type, others...> what) {
        return c_bool_t<contains_helper<0>(what)>();
    }

    template <value_type... others>
    constexpr static auto find(c_values_t<value_type, others...> what) {
        return c_size_t<find_helper<0>(what)>();
    }

    template <value_type... others>
    constexpr static auto rfind(c_values_t<value_type, others...> what) {
        return c_size_t<rfind_helper<size() - what.size()>(what)>();
    }

    template <typename Fn, std::enable_if_t<std::is_invocable_v<Fn, decltype(values)...>, bool> = true>
    constexpr static auto invoke(Fn &&fn) {
        return std::invoke(fn, values...);
    }

    constexpr static auto left_half() { return trunc<size() / 2>(); }
    constexpr static auto right_half() { return slice<size() / 2, size() - size() / 2>(); }
    constexpr static auto reversed() { return reverse_helper<size() - 1>(); }

    constexpr static auto sorted() { return sort(c_values_t<value_type, values...>()); }

    constexpr static auto front() { return c_value_t<get<0>()>(); }
    constexpr static auto back() { return c_value_t<get<size() - 1>()>(); }

    constexpr static auto min() { return sorted().front(); }
    constexpr static auto max() { return sorted().back(); }

    constexpr static auto sum() { return c_value_t<metak::sum(values...)>(); }
    constexpr static auto prod() { return c_value_t<metak::prod(values...)>(); }
    constexpr static auto sum_of_sqr() { return c_value_t<metak::sum_of_sqr(values...)>(); }
    constexpr static auto gcd() { return c_value_t<metak::gcd(values...)>(); }
    constexpr static auto lcm() { return c_value_t<metak::lcm(values...)>(); }

    /* floating point section */
    constexpr static auto mean() { return static_cast<f64>(metak::mean(values...)); }

private:
    template <std::size_t index, value_type front, value_type... rest>
    struct get_n : get_n<index - 1, rest...> {};

    template <value_type front, value_type... rest>
    struct get_n<0, front, rest...> {
        constexpr static auto value{front};
    };

    template <std::size_t index>
    constexpr static auto get(c_size_t<index> = c_size_t<index>()) {
        return get_n<index, values...>::value;
    }

    template <std::size_t index>
    constexpr static auto reverse_helper() {
        if constexpr (index == 0) {
            return c_values_t<T, get(c_size_t<0>())>();
        } else {
            return concat(c_value_t<get(c_size_t<index>())>(), reverse_helper<index - 1>());
        }
    }

    template <std::size_t index, value_type... others>
    constexpr static auto contains_helper(c_values_t<value_type, others...> seq) {
        if constexpr ((size() - index) < seq.size()) {
            return false;
        } else if constexpr (slice<index, seq.size()>() == seq) {
            return true;
        } else {
            return contains_helper<index + 1>(seq);
        }
    }

    template <std::size_t index, value_type... others>
    constexpr static std::size_t find_helper(c_values_t<value_type, others...> seq) {
        if constexpr ((size() - index) < seq.size()) {
            return std::numeric_limits<std::size_t>::max();
        } else if constexpr (slice<index, seq.size()>() == seq) {
            return index;
        } else {
            return find_helper<index + 1>(seq);
        }
    }

    template <std::size_t index, value_type... others>
    constexpr static std::size_t rfind_helper(c_values_t<value_type, others...> seq) {
        if constexpr (index >= size()) {
            return std::numeric_limits<std::size_t>::max();
        } else if constexpr (slice<index, seq.size()>() == seq) {
            return index;
        } else {
            return rfind_helper<index - 1>(seq);
        }
    }
};

namespace details {

template <std::size_t index, typename T1, T1... vs1, typename T2, T2... vs2>
constexpr auto operator_equal_helper(const c_values_t<T1, vs1...> seq1, const c_values_t<T2, vs2...> seq2) {
    if constexpr (index == seq1.size()) {
        return true;
    } else if constexpr (seq1[c_size_t<index>()] == seq2[c_size_t<index>()]) {
        return operator_equal_helper<index + 1>(seq1, seq2);
    } else {
        return false;
    }
}

}  // namespace details

template <typename T1, T1... vs1, typename T2, T2... vs2>
constexpr auto operator==(const c_values_t<T1, vs1...> seq1, const c_values_t<T2, vs2...> seq2) {
    if constexpr (seq1.size() == seq2.size()) {
        return c_bool_t<details::operator_equal_helper<0>(seq1, seq2)>();
    } else {
        return c_false_t();
    }
}

template <typename T1, T1... vs1, typename T2, T2... vs2>
constexpr auto operator!=(const c_values_t<T1, vs1...> &seq1, const c_values_t<T2, vs2...> seq2) {
    return !(seq1 == seq2);
}

template <std::size_t... values>
using c_values_size_t = c_values_t<std::size_t, values...>;

template <s8... values>
using c_values_s8_t = c_values_t<s8, values...>;

template <u8... values>
using c_values_u8_t = c_values_t<u8, values...>;

template <s16... values>
using c_values_s16_t = c_values_t<s16, values...>;

template <u16... values>
using c_values_u16_t = c_values_t<u16, values...>;

template <s32... values>
using c_values_s32_t = c_values_t<s32, values...>;

template <u32... values>
using c_values_u32_t = c_values_t<u32, values...>;

template <s64... values>
using c_values_s64_t = c_values_t<s64, values...>;

template <u64... values>
using c_values_u64_t = c_values_t<u64, values...>;

namespace details {
template <typename T, std::size_t n, T start, T step>
constexpr static auto make_arithmetic_sequence() {
    if constexpr (n == 1) {
        return c_values_t<T, start>();
    } else if constexpr (n == 2) {
        return c_values_t<T, start, start + step>();
    } else if constexpr (n == 4) {
        return c_values_t<T, start, start + step, start + step * 2, start + step * 3>();
    } else {
        constexpr auto left_half  = n / 2;
        constexpr auto right_half = n - left_half;

        return concat(make_arithmetic_sequence<T, left_half, start, step>(),
                      make_arithmetic_sequence<T, right_half, start + left_half * step, step>());
    }
}

template <typename T, std::size_t n, T start, T step>
constexpr static auto make_geometric_sequence() {
    if constexpr (n == 1) {
        return c_values_t<T, start>();
    } else if constexpr (n == 2) {
        return c_values_t<T, start, start * step>();
    } else if constexpr (n == 4) {
        return c_values_t<T, start, start * step, start * step * step, start * step * step * step>();
    } else {
        constexpr auto left_half  = n / 2;
        constexpr auto right_half = n - left_half;

        return concat(make_geometric_sequence<T, left_half, start, step>(),
                      make_geometric_sequence<T, right_half, start * c_value_t<step>().pow(right_half), step>());
    }
}
}  // namespace details

template <typename T, T... values>
constexpr static auto make_cvalues = c_values_t<T, values...>();

template <typename T, std::size_t n, T start, T step>
constexpr static auto make_geometric_sequence_t = details::make_geometric_sequence<T, n, start, step>;

template <typename T, std::size_t n, T start, T step>
constexpr static auto make_arithmetic_sequence_t = details::make_arithmetic_sequence<T, n, start, step>;

template <typename T, std::size_t n>
constexpr static auto make_zero_values_t = make_arithmetic_sequence_t<T, n, T{0}, T{0}>;

template <typename T, std::size_t n>
constexpr static auto make_ones_values_t = make_arithmetic_sequence_t<T, n, T{1}, T{0}>;

template <typename T, std::size_t n>
constexpr auto c_factorial = c_value_t<make_arithmetic_sequence_t<T, n, T{1}, T{1}>().prod()>();

template <typename T, std::size_t n>
constexpr auto make_index_sequence = make_arithmetic_sequence_t<T, n, T{0}, T{1}>;

}  // namespace metak
