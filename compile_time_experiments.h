#ifndef CPP20_EXPERIMENTS_COMPILE_TIME_EXPERIMENTS_H
#define CPP20_EXPERIMENTS_COMPILE_TIME_EXPERIMENTS_H

#include <array>
#include <iostream>
#include <ranges>
#include <functional>
#include <tuple>
#include <iostream>
#include <cmath>


///////////////////////////////////////////////////////////////////
////////////////////// FIBONACCI //////////////////////////////////
///////////////////////////////////////////////////////////////////
constexpr int fib(int n) {
    if (n <= 1)
        return n;
    return fib(n-1) + fib(n-2);
}

int fib_example() {
    constexpr int b = 11;
    auto mul2 = [] (auto value) { return value * 2; };
    auto div2 = [] (auto value) { return value / 2; };

    volatile int result = fib((b % 2 == 0) ? div2(b) : mul2(b));

    return 0;
}

///////////////////////////////////////////////////////////////////
//////////////////////////// SUM //////////////////////////////////
///////////////////////////////////////////////////////////////////

template<typename ...Args>
consteval int sum(Args&&... args) {
    return (args + ... );
}


int sum_example() {
    constexpr int a = 1;

    volatile int result = sum(a, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    return 0;
}

///////////////////////////////////////////////////////////////////
////////////// MAP AND CONCATENATION OF STD::ARRAY  ///////////////
///////////////////////////////////////////////////////////////////

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

int map_concat_example() {
    constexpr std::array a{ 1, 2, 3, 4 };
    constexpr std::array b{ 5, 6 };
    volatile auto mapped = map(a, [] (auto value) { return value * 2; });
    volatile auto concated = concat(a, b);

    return 0;
}


///////////////////////////////////////////////////////////////////
///////////////////////////// DIVMOD  /////////////////////////////
///////////////////////////////////////////////////////////////////

template <typename T>
auto divmod(T a, T b) {
    static_assert(std::numeric_limits<T>::is_integer, "Only integer types allowed!");
    return std::make_tuple(a / b, a % b);
}

int divmod_example() {
    auto [div, mod] = divmod(10, 3);
    std::cout << div << " " << mod << std::endl;

    return 0;
}


#endif //CPP20_EXPERIMENTS_COMPILE_TIME_EXPERIMENTS_H
