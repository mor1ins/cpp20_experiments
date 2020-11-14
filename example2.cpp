template<typename ...Args>
consteval int sum(Args&&... args) {
    return (args + ... );
}

//
//int main() {
//    constexpr int a = 1;
//
//    volatile int result = sum(a, 2, 3, 4, 5, 6, 7, 8, 9, 10);
//    return 0;
//}