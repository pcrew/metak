

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cassert>

#include <metak/metak.h>

using namespace metak::literals;

int main() {
    constexpr auto s1 = "hello"_cs;
    constexpr auto s2 = ", "_cs;
    constexpr auto s3 = "World"_cs;
    constexpr auto s  = s1 + s2 + s3;

    static_assert(s1 == "hello"_cs);
    static_assert(s2 == ", "_cs);
    static_assert(s3 == "World"_cs);
    static_assert(s == "hello, World"_cs);

    static_assert(s.remove_prefix<s1.size()>() == s2 + s3);
    static_assert(s.remove_prefix<s1.size() + s2.size()>() == s3);
    static_assert(s.remove_prefix<s1.size() + s2.size() + s3.size()>() == ""_cs);

    static_assert(s.remove_suffix<s3.size()>() == s1 + s2);
    static_assert(s.remove_suffix<s2.size() + s3.size()>() == s1);
    static_assert(s.remove_suffix<s1.size() + s2.size() + s3.size()>() == ""_cs);

    static_assert(s.starts_with(s1));
    static_assert(s.starts_with(s1 + s2));
    static_assert(s.starts_with(s1 + s2 + s3));
    static_assert(!s.starts_with("xxx"_cs));

    static_assert(s.ends_with(s3));
    static_assert(s.ends_with(s2 + s3));
    static_assert(s.ends_with(s1 + s2 + s3));
    static_assert(!s.ends_with("xxx"_cs));

    static_assert(s.slice<1, 4>() == "ello"_cs);
    static_assert(s.slice<2, 4>() == "llo,"_cs);
    static_assert(s.contains("orld"_cs));
    static_assert(s.contains("hello"_cs));
    static_assert(s.contains(" "_cs));
    static_assert(s.contains(""_cs));
    static_assert(!s.contains("  "_cs));
    static_assert(!s.contains("xxx"_cs));

    static_assert(s.find("hello, World"_cs) == 0);
    static_assert(s.find("ello, World"_cs) == 1);
    static_assert(s.find("llo, World"_cs) == 2);
    static_assert(s.find(", "_cs) == 5);
    static_assert(s.find("Wor"_cs) == 7);
    static_assert(s.find("xxx"_cs) == s.max_size());

    static_assert(s.find("l"_cs) == 2);
    static_assert(s.rfind("l"_cs) == 10);
    static_assert(s.rfind("z"_cs) == s.max_size());

    assert(*s.as_string() == "hello, World");

    constexpr auto bye = (s2 + s3).prepend<'e'>().prepend<'y'>().prepend<'b'>();
    static_assert(bye == "bye, World"_cs);

    return 0;
}
