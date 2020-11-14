//#include <string>
//#include <array>
//#include <iostream>
//#include <ranges>
//
//
//consteval auto length(int number) {
//    int result = 0;
//    while (number > 0) {
//        result++;
//        number /= 10;
//    }
//    return result == 0 ? 1 : result;
//}
//
//template <typename T, size_t N>
//consteval auto reverse_array(std::array<T, N> arr) {
//    std::array<T, N> result{0};
//    for (int i = 0; i < N; i++) {
//        result[i] = arr[N - i - 1];
//    }
//    return result;
//}
//
//template <size_t N>
//consteval auto int_to_digits(int number) {
//    std::array<int, N> digits{0};
//    for (int i = 0; i < N; i++) {
//        digits[i] = number % 10;
//        number /= 10;
//    }
//    return reverse_array(digits);
//}
//
//template <int Digit>
//struct to_char {
//    char digit = '0' + Digit % 10;
//};
//
//consteval auto int_to_str(int number) {
//    std::array<std::string_view, 10> digits =
//            {"0", "1", "2", "3", "4",
//             "5", "6", "7", "8", "9"};
//
//    return digits[number % 10];
//}
//
//
//template <size_t N>
//consteval auto digits_to_strings(std::array<int, N> digits) {
//    std::array<char, N> result{0};
//    for (int i = 0; i < N; i++) result[i] = '0' + digits[i];
//    return result;
//}
//
//template <int N, int len = length(N)>
//consteval auto int_to_string() {
//    return digits_to_strings(int_to_digits<len>(N));
//}
////
////
//template <size_t N, size_t M, size_t length = N + (N - 1) * M>
//consteval auto
//join(const std::array<char, M> delimiter, const std::array<char, N> sequence) {
//    std::array<char, length> result{0};
//
//    int sequence_index = 0;
//    int delimiter_index = 0;
//    for (int i : std::ranges::views::iota(0, (int)length)) {
//        if (delimiter_index == 0) {
//            result[i] = sequence[sequence_index++];
//            delimiter_index = M;
//        }
//        else {
//            result[i] = delimiter[M - delimiter_index];
//            delimiter_index -= 1;
//        }
//    }
//
//    return result;
//}
//
//template <size_t N, size_t M>
//consteval auto
//concat(const char * first, const char * second) {
//    std::array<char, N + M> result{0};
//    for (int i : std::ranges::views::iota(0, (int)(N + M))) {
//        result[i] = (i < N) ? first[i] : second[i - N];
//    }
//
//    return result;
//}
//
//template <char * Date, size_t N>
//struct compile_time_string_view {
//    std::string_view value {Date, N};
//};
//
//
//int main() {
//    constexpr std::array ints = int_to_string<1076>();
//    constexpr std::array delimiter { ' ', '-', ' ' };
//    constexpr std::array ints_str = join(delimiter, ints);
//
//    for (auto i : ints_str) std::cout << i;
//    std::cout << std::endl;
//
//
////    constexpr std::string_view a = "123";
////    constexpr std::string_view b = "456";
////    constexpr auto c = concat<a.size(), b.size()>(a.data(), b.data());
////
////    const char * str = c._M_elems;
//
//    return 0;
//}