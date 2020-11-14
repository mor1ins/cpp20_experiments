////#include <tuple>
////#include <iostream>
////#include <cmath>
////
////
////std::tuple<int, int> divmod(int a, int b) {
////    return std::make_tuple(a / b, a % b);
////}
////
////
////int main() {
////    std::tuple<int, int> dm = divmod(5, 2);
////    std::cout << std::get<0>(dm) << " " << std::get<1>(dm) << std::endl;
////
////    return 0;
////}
//
//#include <tuple>
//#include <iostream>
//#include <cmath>
//
//
//template <typename T>
//auto divmod(T a, T b) {
//    static_assert(std::numeric_limits<T>::is_integer, "Only integer types allowed!");
//    return std::make_tuple(a / b, a % b);
//}
//
//
//int main() {
//    auto [div, mod] = divmod(10, 3);
//    std::cout << div << " " << mod << std::endl;
//
//    return 0;
//}