/**
 * @file
 * Copyright 2018 - present, Dmitry Lotakov
 *
 * This source code is licensed under the BSD-3-Clause license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <array>
#include <vector>
#include <initializer_list>

namespace metak {

template <typename T>
struct array_view {
    using value_type      = T;
    using reference       = T &;
    using const_reference = const T &;
    using pointer         = T *;
    using const_pointer   = const T *;
    using iterator        = pointer;
    using const_iterator  = const_pointer;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;

    constexpr array_view() noexcept
        : _data{nullptr}
        , _size{0} {}

    template <std::size_t S>
    constexpr array_view(const value_type a[S]) noexcept
        : _data{&a[0]}
        , _size{S} {}

    template <std::size_t S>
    constexpr array_view(const std::array<value_type, S> &arr) noexcept
        : _data{arr.data()}
        , _size{S} {}

    template <typename Allocator>
    constexpr array_view(const std::vector<value_type, Allocator> &vec) noexcept
        : _data{vec.data()}
        , _size{vec.size()} {}

    constexpr array_view(const array_view &other) noexcept            = default;
    constexpr array_view(array_view &&other) noexcept                 = default;
    constexpr array_view &operator=(const array_view &other) noexcept = default;
    constexpr array_view &operator=(array_view &other) noexcept       = default;

    constexpr auto operator[](std::size_t index) const { return _data[index]; }

    constexpr auto data() const noexcept { return _data; }
    constexpr auto size() const noexcept { return _size; }
    constexpr auto length() const noexcept { return size(); }
    constexpr auto max_size() const noexcept { return std::numeric_limits<size_type>::max(); }
    constexpr auto empty() const noexcept { return size() == 0; }

    constexpr auto begin() const noexcept { return data(); }
    constexpr auto end() const noexcept { return data() + size() - 1; }
    constexpr const auto cbegin() const noexcept { return begin(); }
    constexpr const auto cend() const noexcept { return end(); }

    constexpr auto front() const noexcept { return *begin(); }
    constexpr auto back() const noexcept { return *end(); }

    constexpr auto remove_prefix(std::size_t to_remove) noexcept {
        _data += to_remove;
        _size -= to_remove;
        return *this;
    }

    constexpr auto remove_suffix(std::size_t to_remove) noexcept {
        if (to_remove > _size) {
            _size = 0;
        } else {
            _size -= to_remove;
        }

        return *this;
    }

private:
    const_pointer _data;
    size_type _size;
};

}  // namespace metak
