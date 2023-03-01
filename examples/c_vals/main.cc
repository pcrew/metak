

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cassert>

#include <metak/metak.h>

float __attribute__((noinline)) foo(float a, float b, float c) { return a + b + c; }

int main() {
    {
        constexpr auto a = metak::c_value_t<metak::s32(5)>();
        constexpr auto b = metak::c_value_t<metak::s16(4)>();
        constexpr auto c = metak::c_value_t<metak::s32(-4)>();
        constexpr auto d = metak::c_value_t<metak::s16(-5)>();
        constexpr std::size_t e{100};

        static_assert(metak::is_c_value_t(a) && metak::is_c_value_t(b));
        static_assert(metak::is_c_value_t(e) == false);

        static_assert(a.is_odd() && d.is_odd());
        static_assert(b.is_even() && c.is_even());

        static_assert(a.abs() == a);
        static_assert(b.abs() == b);

        static_assert(c.abs() == b);
        static_assert(d.abs() == a);

        static_assert(a.pow(a) == 3125);
        static_assert(a.pow(b) == 625);
        static_assert(a.pow(c) == 0);
        static_assert(a.pow(d) == 0);

        static_assert(b.pow(a) == 1024);
        static_assert(b.pow(b) == 256);
        static_assert(b.pow(c) == 0);
        static_assert(b.pow(d) == 0);

        static_assert(c.pow(a) == -1024);
        static_assert(c.pow(b) == 256);
        static_assert(c.pow(c) == 0);
        static_assert(c.pow(d) == 0);

        static_assert(d.pow(a) == -3125);
        static_assert(d.pow(b) == 625);
        static_assert(d.pow(c) == 0);
        static_assert(d.pow(d) == 0);

        static_assert(metak::gcd(metak::c_value_t<int(36)>(), metak::c_value_t<(4)>()) == 4);
        static_assert(metak::gcd(metak::c_value_t<int(36)>(), metak::c_value_t<(7)>()) == 1);
        static_assert(metak::lcm(metak::c_value_t<int(36)>(), metak::c_value_t<(4)>()) == 36);
        static_assert(metak::lcm(metak::c_value_t<int(7)>(), metak::c_value_t<(5)>()) == 35);
    }
    {
        constexpr auto a = metak::c_true_t();
        constexpr auto b = metak::c_false_t();

        static_assert(a == true);
        static_assert(b == false);
    }
    {
        constexpr auto a = metak::c_values_t<metak::u32, 1, 2, 3, 4>();

        static_assert(a.size() == 4);
        static_assert(a.max() == 4);
        static_assert(a.min() == 1);
        static_assert(a.front() == 1 && a.back() == 4);
        static_assert(a.sum() == 10);
        static_assert(a.prod() == 24);
        static_assert(a.mean() == static_cast<double>(1 + 2 + 3 + 4) / 4);
        static_assert(a[metak::c_size_t<0>()] == 1);
        static_assert(a[metak::c_size_t<1>()] == 2);
        static_assert(a[metak::c_size_t<2>()] == 3);
        static_assert(a[metak::c_size_t<3>()] == 4);
    }
    {
        constexpr auto a = metak::c_values_t<int, 1, 2, 3, 4, 5>();
        constexpr auto b = metak::c_values_t<int, 6, 7, 8, 9, 10, 11, 12, 13>();
        constexpr auto c = metak::concat(a, b);

        static_assert(a != b);
        static_assert(c.size() == a.size() + b.size());
        static_assert(c.front() == a.front());
        static_assert(c.back() == b.back());
        static_assert(c.sum() == a.sum() + b.sum());
        static_assert(c == metak::make_arithmetic_sequence_t<int, 13, 1, 1>());
    }
    {
        constexpr auto a = metak::c_values_t<int, 4, 5, 6, 7, 8>()
                               .append<9>()
                               .prepend<3>()
                               .prepend<2>()
                               .append<10>()
                               .append<11>()
                               .prepend<1>()
                               .append<12>()
                               .append<13>();

        static_assert(a == metak::make_arithmetic_sequence_t<int, 13, 1, 1>());
    }
    {
        constexpr auto seq = metak::make_geometric_sequence_t<metak::u64, 4, 5, 3>();
        static_assert(seq[metak::c_size_t<0>()] == 5);
        static_assert(seq[metak::c_size_t<1>()] == 15);
        static_assert(seq[metak::c_size_t<2>()] == 45);
        static_assert(seq[metak::c_size_t<3>()] == 135);
    }
    {
        constexpr auto seq = metak::c_values_t<int, 100, 0, 1, 2, -100, 5, 7, 6, 10, 1500>().sorted();
        static_assert(seq[metak::c_size_t<0>()] == -100);
        static_assert(seq[metak::c_size_t<1>()] == 0);
        static_assert(seq[metak::c_size_t<2>()] == 1);
        static_assert(seq[metak::c_size_t<3>()] == 2);
        static_assert(seq[metak::c_size_t<4>()] == 5);
        static_assert(seq[metak::c_size_t<5>()] == 6);
        static_assert(seq[metak::c_size_t<6>()] == 7);
        static_assert(seq[metak::c_size_t<7>()] == 10);
        static_assert(seq[metak::c_size_t<8>()] == 100);
        static_assert(seq[metak::c_size_t<9>()] == 1500);
    }
    {
        constexpr auto seq = metak::c_values_t<int, 100, 0, 1, 2, -100, 5, 7, 6, 10, 1500>().sorted().reversed();
        static_assert(seq[metak::c_size_t<0>()] == 1500);
        static_assert(seq[metak::c_size_t<1>()] == 100);
        static_assert(seq[metak::c_size_t<2>()] == 10);
        static_assert(seq[metak::c_size_t<3>()] == 7);
        static_assert(seq[metak::c_size_t<4>()] == 6);
        static_assert(seq[metak::c_size_t<5>()] == 5);
        static_assert(seq[metak::c_size_t<6>()] == 2);
        static_assert(seq[metak::c_size_t<7>()] == 1);
        static_assert(seq[metak::c_size_t<8>()] == 0);
        static_assert(seq[metak::c_size_t<9>()] == -100);
    }
    {
        constexpr auto seq = metak::c_values_t<int, 100, 0, 1, 2, -100, 5, 7, 6, 10, 1500>().sorted().trunc<5>();
        static_assert(seq.size() == 5);
        static_assert(seq[metak::c_size_t<0>()] == -100);
        static_assert(seq[metak::c_size_t<1>()] == 0);
        static_assert(seq[metak::c_size_t<2>()] == 1);
        static_assert(seq[metak::c_size_t<3>()] == 2);
        static_assert(seq[metak::c_size_t<4>()] == 5);
    }
    {
        constexpr auto seq = metak::c_values_t<int, 100, 0, 1, 2, -100, 5, 7, 6, 10, 1500>().sorted().slice<3, 3>();
        static_assert(seq.size() == 3);
        static_assert(seq[metak::c_size_t<0>()] == 2);
        static_assert(seq[metak::c_size_t<1>()] == 5);
        static_assert(seq[metak::c_size_t<2>()] == 6);
    }
    {
        constexpr auto seq = metak::c_values_t<int, 100, 0, 1, 2, -100, 5, 7, 6, 10, 1500>().reversed();
        static_assert(seq[metak::c_size_t<0>()] == 1500);
        static_assert(seq[metak::c_size_t<1>()] == 10);
        static_assert(seq[metak::c_size_t<2>()] == 6);
        static_assert(seq[metak::c_size_t<3>()] == 7);
        static_assert(seq[metak::c_size_t<4>()] == 5);
        static_assert(seq[metak::c_size_t<5>()] == -100);
        static_assert(seq[metak::c_size_t<6>()] == 2);
        static_assert(seq[metak::c_size_t<7>()] == 1);
        static_assert(seq[metak::c_size_t<8>()] == 0);
        static_assert(seq[metak::c_size_t<9>()] == 100);
    }
    {
        auto seq = metak::c_values_t<int, 100, 50, 1>().sorted().reversed();
        assert(seq.invoke(foo) == 151);
    }

    return 0;
}
