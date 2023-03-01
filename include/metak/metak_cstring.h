/**
 * @file
 * Copyright 2018 - present, Dmitry Lotakov
 *
 * This source code is licensed under the BSD-3-Clause license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

namespace metak {

template <char... chars>
struct c_string_t : public c_values_t<char, chars...> {
    constexpr static auto base = c_values_t<char, chars...>();

    // https://github.com/serge-sans-paille/frozen/blob/master/include/frozen/bits/hash_string.h#L9
    constexpr static auto hash() { return hash_helper<0>(c_size_t<5381>()); }

    // https://github.com/serge-sans-paille/frozen/blob/master/include/frozen/bits/hash_string.h#L19
    template <std::size_t seed>
    constexpr static auto hash(c_size_t<seed>) {
        constexpr auto gen = (0x811c9dc5 ^ seed) * static_cast<size_t>(0x01000193);
        return hash_seed_helper<0>(c_size_t<gen>());
    }

private:
    template <std::size_t index, std::size_t gen>
    constexpr static auto hash_helper(c_size_t<gen>) {
        if constexpr (index == base.size()) {
            return c_size_t<gen>();
        } else {
            constexpr auto next = gen * 33 + static_cast<std::size_t>(base[c_size_t<index>()]);
            return hash_helper<index + 1>(c_size_t<next>());
        }
    }

    template <std::size_t index, std::size_t gen>
    constexpr static auto hash_seed_helper(c_size_t<gen>) {
        if constexpr (index == base.size()) {
            return c_size_t<gen / 256>();
        } else {
            constexpr auto next =
                (gen ^ static_cast<size_t>(base[c_size_t<index>()])) * static_cast<size_t>(0x01000193);
            return hash_seed_helper<index + 1>(c_size_t<next>());
        }
    }
};

namespace literals {
template <typename T, T... chars>
constexpr auto operator"" _cs() {
    return c_string_t<chars...>{};
}

}  // namespace literals

template <char... chars_1, char... chars_2>
constexpr auto operator+(const c_string_t<chars_1...> &str1, const c_string_t<chars_2...> &str2) {
    return c_string_t<chars_1..., chars_2...>();
}

}  // namespace metak
