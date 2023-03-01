#include <cassert>

#include <vector>
#include <array>

#include <metak/metak.h>

int main() {
    {
        auto arr  = std::array{1, 2, 3, 4, 5};
        auto view = metak::array_view(arr);

        assert(view.empty() == arr.empty());
        assert(view.front() == arr.front());
        assert(view.back() == arr.back());

        auto tail = view.remove_prefix(3);
        assert(tail.empty() == false);
        assert(tail.front() == arr[3]);
        assert(tail.back() == arr[4]);
    }

    {
        auto vec  = std::vector<int>{1, 2, 3, 4, 5};
        auto view = metak::array_view(vec);

        assert(view.empty() == vec.empty());
        assert(view.front() == vec.front());
        assert(view.back() == vec.back());

        auto tail = view.remove_prefix(3);
        assert(tail.empty() == false);
        assert(tail.front() == vec[3]);
        assert(tail.back() == vec[4]);
    }

    return 0;
}
