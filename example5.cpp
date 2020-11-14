//#include <cstdio>
//#include <array>
//#include <vector>
//#include <numeric>
//#include <functional>
//#include <iostream>
//#include <ranges>
//
//
//namespace detail
//{
//    template<unsigned... digits>
//    struct to_chars { static const char value[]; };
//
//    template<unsigned... digits>
//    constexpr char to_chars<digits...>::value[] = {('0' + digits)..., 0};
//
//    template<unsigned rem, unsigned... digits>
//    struct explode : explode<rem / 10, rem % 10, digits...> {};
//
//    template<unsigned... digits>
//    struct explode<0, digits...> : to_chars<digits...> {};
//}
//
//template<unsigned num>
//struct num_to_string : detail::explode<num> {};
//
//
//template <typename T, size_t N, size_t M>
//consteval auto
//concat(const std::array<T, N> first, const std::array<T, M> second) {
//    std::array<T, N + M> result;
//    for (int i : std::ranges::views::iota(0, (int)(N + M))) {
//        result[i] = (i < N) ? first[i] : second[i - N];
//    }
//
//    return result;
//}
//
//template <size_t N, size_t M>
//consteval auto
//concat(const char (&first)[N], const char (&second)[M]) {
//    std::array<char, N + M - 1> result;
//    for (int i : std::ranges::views::iota(0, (int)(N + M - 1))) {
//        result[i] = (i < N - 1) ? first[i] : second[i - N + 1];
//    }
//
//    return result;
//}
//
//
////template <size_t N>
////struct reverse_range {
////    explicit consteval reverse_range() {
////        this->times = std::ranges::views::reverse(std::ranges::views::iota(0, (int)time));
////    }
////
////    std::array<int, N> times;
////};
//
//struct Signal {
//public:
//    consteval
//    explicit
//    Signal(std::size_t time = 0, bool is_pause = false)
//    : time(time), is_pause(is_pause)
//    {}
//
//    consteval Signal operator+(const Signal& other) const {
//        return Signal(this->time + other.time, this->is_pause && other.is_pause);
//    }
//
//    consteval void operator=(const Signal& other) {
//        if (this != &other) { // self-assignment check expected
//            this->time = other.time;
//            this->is_pause = other.is_pause;
//        }
//    }
//
//    consteval Signal operator+(const int other) const {
//        return Signal(this->time + other, this->is_pause);
//    }
//
//    [[nodiscard]] consteval Signal tick() const {
//        return Signal(time > 0 ? time - 1 : 0, is_pause);
//    }
//
//
//    std::size_t time;
//    bool is_pause;
//};
//
//
//struct Pause : Signal {
//    consteval Pause(size_t time) : Signal(time, true) {}
//};
//
//
//struct Vibrate : Signal {
//    consteval Vibrate(size_t time) : Signal(time) {}
//};
//
//
//template<size_t N = 0, typename ...Args>
//struct SignalSequence {
//public:
//    static consteval auto length() {
//        return N > 0 ? N : sizeof...(Args);
//    }
//
////    consteval explicit SignalSequence(SignalSequence<N> sequence) : sequence(sequence.sequence) {}
//    consteval explicit SignalSequence(std::array<Signal, N> sequence) : sequence(sequence) {}
//    consteval explicit SignalSequence(Args... more) : sequence({more...}) {}
//
//    consteval auto sum() const {
//        int sum = 0;
//        for (auto signal: sequence) sum += signal.time;
//        return sum;
//    }
//
//    consteval auto operator+(const auto& other) const {
//        auto sequence = concat(this->sequence, other.sequence);
//        return SignalSequence<sequence.size()>(sequence);
//    }
//
//    std::array<Signal, length()> sequence;
//    std::string_view str = "hehehe";
//};
//
////template<typename ...Args>
////consteval auto sum(Args&&... args) {
////    return std::array<std::string_view, sizeof...(Args)>{ (std::string_view(num_to_string<args>::value), ...) };
////}
//
////template <size_t N>
////struct signals_to_strings {
////    explicit consteval
////    signals_to_strings()
////    : value()
////    {}
////
////    std::array<std::string_view, N> value = sum(1, 2, 3, 4, 5);
////};
//
//
//consteval auto get_reverse_range(auto size) {
//    return std::ranges::views::reverse(std::ranges::views::iota(0, static_cast<int>(size)));
//}
//
//
//int main() {
////    constexpr Signal start(10);
////    constexpr Signal current(start.tick());
////    volatile size_t i = current.get_time();
////    std::cout << i << std::endl;
////
////    constexpr Signal current1(current.tick());
////    i = current1.get_time();
////    std::cout << i << std::endl;
////
////    constexpr Signal current2(current1.tick());
////    i = current2.get_time();
////    std::cout << i << std::endl;
////
////    constexpr Signal current3(current2.tick());
////    i = current3.get_time();
////    std::cout << i << std::endl;
//
//    constexpr SignalSequence first(Vibrate(1), Pause(2));
//    constexpr SignalSequence second(Vibrate(3), Pause(4), Vibrate(5));
//
//    constexpr auto sequence = first + second;
//
//    volatile auto sum = sequence.sum();
//    volatile auto length = sequence.length();
//
//    volatile size_t i = 0;
//    std::cout << "Start" << std::endl;
//    for (Signal signal: sequence.sequence) {
//        i = signal.time;
////        printf("%s\n", concat(num_to_string<12>::value, num_to_string<34>::value));
//        std::cout << "Time: " << signal.time << ", "
//                  << (signal.is_pause ? "Waiting..." : "Vibrating...");
//
//        constexpr auto times = get_reverse_range(sequence.sequence[0].time);
//    }
////    constexpr auto strs = signals_to_strings<sequence.length(), sequence, SignalSequence>().value;
////    for (auto str : strs) std::cout << str << " ";
//    std::cout << std::endl << "End" << std::endl << std::endl;
//
//
//    std::cout << "sum: " << sum << "\n";
//    std::cout << "length: " << length << "\n";
//}
//
//
//
//
////#include <cstdio>
////#include <array>
////#include <vector>
////#include <numeric>
////#include <functional>
////#include <iostream>
////#include <ranges>
////
////template <typename T, size_t N, size_t M>
////consteval auto concat(const std::array<T, N> first, const std::array<T, M> second) {
////    std::array<T, N + M> result;
////    for (int i : std::ranges::views::iota(0, (int)(N + M))) {
////        result[i] = (i < N) ? first[i] : second[i - N];
////    }
////
////    return result;
////}
////
////struct Signal {
////public:
////    consteval explicit Signal(std::size_t time = 0, bool is_pause = false)
////        : time(time), is_pause(is_pause) {}
////
////    consteval Signal operator+(const Signal& other) const {
////        return Signal(this->time + other.time, this->is_pause && other.is_pause);
////    }
////
////    consteval Signal operator+(const int other) const {
////        return Signal(this->time + other, this->is_pause);
////    }
////
////    consteval std::size_t get_time() const {
////        return time;
////    }
////
////private:
////    std::size_t time;
////    bool is_pause;
////};
////
////
//////template<size_t N>
//////struct SignalSequence {
//////public:
//////    constexpr explicit SignalSequence(std::array<Signal, N> sequence) : sequence(sequence) {}
//////
//////    consteval auto get_sequence() const {
//////        return sequence;
//////    }
//////
//////private:
//////    std::array<Signal, N> sequence;
//////};
////
////
////template<size_t N = 0, typename ...Args>
////struct SignalSequence {
////public:
////    static consteval auto length() {
////        return N > 0 ? N : sizeof...(Args);
////    }
////
////    consteval explicit SignalSequence(std::array<Signal, N> sequence) : sequence(sequence) {}
////    consteval explicit SignalSequence(Args... more) : sequence({more...}) {}
////
////    consteval auto sum() const {
////        int sum = 0;
////        for (auto signal: sequence) sum += signal.get_time();
////        return sum;
////    }
////
////    consteval auto get_sequence() const {
////        return sequence;
////    }
////
////    consteval auto operator+(const auto& other) const {
////        auto sequence = concat(this->get_sequence(), other.get_sequence());
////        return SignalSequence<sequence.size()>(sequence);
////    }
////
////private:
////    std::array<Signal, length()> sequence;
////};
////
//////template <std::size_t N = 0>
//////struct NotificationQueue {
//////public:
//////    constexpr NotificationQueue(SignalSequence<N> sequence) : sequence(sequence) {}
//////    constexpr NotificationQueue() : sequence({Signal(0, false, true)}) {}
//////
//////    constexpr NotificationQueue notify(const auto sequence) {
//////        return NotificationQueue(this->sequence + sequence);
//////    }
//////
//////private:
//////    SignalSequence<N == 0 ? 1 : N> sequence;
//////};
////
////
////int main() {
////    constexpr SignalSequence first(Signal(5), Signal(5, true));
////    constexpr SignalSequence second(Signal(5), Signal(5, true), Signal(5));
////
////    constexpr auto sequence = first + second;
////
////    volatile auto sum = sequence.sum();
////    volatile auto length = sequence.length();
////
////
//////    volatile NotificationQueue queue;
//////    volatile NotificationQueue new_queue = queue.notify(first);
////
////    std::cout << "sum: " << sum << "\n";
////    std::cout << "length: " << length << "\n";
////}
//
//
//
//
////
////#include <cstdio>
////#include <array>
////#include <vector>
//////#include <iostream>
////
////
////class Signal {
////public:
////    explicit Signal(std::size_t time, bool is_pause = false) : time(time), is_pause(is_pause) {}
////
////    Signal operator+(const Signal& other) const {
////        return Signal(this->time + other.time, this->is_pause && other.is_pause);
////    }
////
////    auto get_time() const {
////        return time;
////    }
////
////private:
////    std::size_t time;
////    bool is_pause;
////};
////
////template<typename ...Args>
////class SignalSequence {
////public:
////    explicit SignalSequence(Signal first, Args... more) : sequence({first, more...}) {}
////
////    [[nodiscard]] auto sum() const {
////        std::size_t sum = 0;
////
////        for (auto signal: sequence)
////            sum += signal.get_time();
////
////        return sum;
////    }
////
////private:
////    std::vector<Signal> sequence;
////};
////
////int main() {
////    SignalSequence sequence(Signal(5), Signal(5, true), Signal(5));
////    volatile auto sum = sequence.sum();
//////    std::cout << signal.sum() << "\n";
////}