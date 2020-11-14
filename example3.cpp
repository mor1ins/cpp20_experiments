#include <array>
// #include <iostream>
#include <ranges>


template <typename T, size_t N, typename Lambda>
consteval auto map(std::array<T, N> container, Lambda lambda) {
    std::array<T, N> result{ 0 };
    for (int i : std::ranges::views::iota(0, (int)N)) {
        result[i] = lambda(container[i]);
    }

    return result;
}


template <typename T, size_t N, size_t M>
consteval auto concat(std::array<T, N> first, std::array<T, M> second) {
    std::array<T, N + M> result{0};
    for (int i : std::ranges::views::iota(0, (int)(N + M))) {
        result[i] = (i < N) ? first[i] : second[i - N];
    }

    return result;
}

//
//int main() {
//    constexpr std::array a{ 1, 2, 3, 4 };
//    constexpr std::array b{ 5, 6 };
//    volatile auto mapped = map(a, [] (auto value) { return value * 2; });
//    volatile auto concated = concat(a, b);
//
//    return 0;
//}