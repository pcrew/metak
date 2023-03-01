#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <metak/metak.h>

int main() {
    {
        static_assert(metak::saturate_cast<metak::s8>(metak::s16(5)) == 5);
        static_assert(metak::saturate_cast<metak::s8>(metak::s16(127)) == 127);
        static_assert(metak::saturate_cast<metak::s8>(metak::s16(128)) == 127);
        static_assert(metak::saturate_cast<metak::s8>(metak::s16(2000)) == 127);
        static_assert(metak::saturate_cast<metak::s8>(metak::s16(-5)) == -5);
        static_assert(metak::saturate_cast<metak::s8>(metak::s16(-127)) == -127);
        static_assert(metak::saturate_cast<metak::s8>(metak::s16(-128)) == -128);
        static_assert(metak::saturate_cast<metak::s8>(metak::s16(-2000)) == -128);

        static_assert(metak::saturate_cast<metak::u8>(metak::s16(5)) == 5);
        static_assert(metak::saturate_cast<metak::u8>(metak::s16(127)) == 127);
        static_assert(metak::saturate_cast<metak::u8>(metak::s16(128)) == 128);
        static_assert(metak::saturate_cast<metak::u8>(metak::s16(2000)) == 255);
        static_assert(metak::saturate_cast<metak::u8>(metak::s16(-5)) == 0);
        static_assert(metak::saturate_cast<metak::u8>(metak::s16(-127)) == 0);
    }

    {
        static_assert(metak::saturate_cast<metak::u8>(metak::u16(5)) == 5);
        static_assert(metak::saturate_cast<metak::u8>(metak::u16(127)) == 127);
        static_assert(metak::saturate_cast<metak::u8>(metak::u16(128)) == 128);
        static_assert(metak::saturate_cast<metak::u8>(metak::u16(2000)) == 255);
    }

    return 0;
}
