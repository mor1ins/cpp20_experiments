#include <functional>

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