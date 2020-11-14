#ifndef CPP20_EXPERIMENTS_COMPILE_TIME_EXPERIMENTS_H
#define CPP20_EXPERIMENTS_COMPILE_TIME_EXPERIMENTS_H

#include <iostream>
#include <ranges>
#include <tuple>
#include <cmath>
#include <cstdio>
#include <vector>
#include <numeric>
#include <functional>
#include <string>
#include <array>



///////////////////////////////////////////////////////////////////
///////////////////////////// DIVMOD  /////////////////////////////
///////////////////////////////////////////////////////////////////

template <typename T>
auto 
divmod(T a, T b) {
    static_assert(std::numeric_limits<T>::is_integer, "Only integer types allowed!");
    return std::make_tuple(a / b, a % b);
}

inline int 
divmod_example() {
    auto [div, mod] = divmod(10, 3);
    std::cout << div << " " << mod << std::endl;

    return 0;
}

inline int 
divmod_example_without_example() {
    auto [div, mod] = divmod(10, 3);

    volatile auto div1 = div;
    volatile auto mod1 = mod;

    return 0;
}


///////////////////////////////////////////////////////////////////
/////////////////////////// FIBONACCI /////////////////////////////
///////////////////////////////////////////////////////////////////
consteval int 
fib(int n) {
    if (n <= 1)
        return n;
    return fib(n-1) + fib(n-2);
}

inline int 
fib_example() {
    constexpr int b = 15;
    auto mul2 = [] (auto value) { return value * 2; };
    auto div2 = [] (auto value) { return value / 2; };

    volatile int result = fib((b % 2 == 0) ? div2(b) : mul2(b));

    return 0;
}

///////////////////////////////////////////////////////////////////
//////////////////////////// SUM //////////////////////////////////
///////////////////////////////////////////////////////////////////

template<typename ...Args>
consteval int 
sum(Args&&... args) {
    return (args + ... );
}


inline int 
sum_example() {
    constexpr int a = 1;

    volatile int result = sum(a, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    return 0;
}

///////////////////////////////////////////////////////////////////
////////////// MAP AND CONCATENATION OF STD::ARRAY  ///////////////
///////////////////////////////////////////////////////////////////

template <typename T, size_t N, typename Lambda>
consteval auto 
map(std::array<T, N> container, Lambda lambda) {
    std::array<T, N> result{ 0 };
    for (int i : std::ranges::views::iota(0, (int)N)) {
        result[i] = lambda(container[i]);
    }

    return result;
}



// template <size_t N, size_t M>
// consteval auto
// concat(const char * first, const char * second) {
//     std::array<char, N + M> result{0};
//     for (int i : std::ranges::views::iota(0, (int)(N + M))) {
//         result[i] = (i < N) ? first[i] : second[i - N];
//     }

//     return result;
// }


template <typename T, size_t N, size_t M>
consteval auto
concat(const std::array<T, N> first, const std::array<T, M> second) {
    std::array<T, N + M> result;
    for (int i : std::ranges::views::iota(0, (int)(N + M))) {
        result[i] = (i < N) ? first[i] : second[i - N];
    }

    return result;
}

template <size_t N, size_t M>
consteval auto
concat(const char (&first)[N], const char (&second)[M]) {
    std::array<char, N + M - 1> result;
    for (int i : std::ranges::views::iota(0, (int)(N + M - 1))) {
        result[i] = (i < N - 1) ? first[i] : second[i - N + 1];
    }

    return result;
}

inline int 
map_concat_example() {
    constexpr std::array a{ 1, 2, 3, 4 };
    constexpr std::array b{ 5, 6 };
    constexpr auto mapped = map(a, [] (auto value) { return value * 2; });
    constexpr auto concated = concat(a, b);

    std::cout << "mapped: ";
    for (auto el : mapped) std::cout << el << " ";
    std::cout << std::endl;

    std::cout << "concated: ";
    for (auto el : concated) std::cout << el << " ";
    std::cout << std::endl;

    return 0;
}

inline int 
map_concat_example_without_out() {
    constexpr std::array a{ 1, 2, 3, 4 };
    constexpr std::array b{ 5, 6 };
    constexpr auto mapped = map(a, [] (auto value) { return value * 2; });
    constexpr auto concated = concat(a, b);

    volatile int i = 0;
    for (auto el : mapped) i = el;
    for (auto el : concated) i = el;

    return 0;
}


///////////////////////////////////////////////////////////////////
///////////////////// VIBRATION SIGNALS  //////////////////////////
///////////////////////////////////////////////////////////////////

struct Signal {
public:
    consteval explicit
    Signal(std::size_t time = 0, bool is_pause = false)
    : time(time), is_pause(is_pause)
    {}

    consteval Signal 
    operator+(const Signal& other) const {
        return Signal(this->time + other.time, this->is_pause && other.is_pause);
    }

    consteval void 
    operator=(const Signal& other) {
        if (this != &other) { // self-assignment check expected
            this->time = other.time;
            this->is_pause = other.is_pause;
        }
    }

    consteval Signal 
    operator+(const int other) const {
        return Signal(this->time + other, this->is_pause);
    }

    [[nodiscard]] consteval Signal 
    tick() const {
        return Signal(time > 0 ? time - 1 : 0, is_pause);
    }

    std::size_t time;
    bool is_pause;
};


struct Pause : Signal {
    consteval Pause(size_t time) : Signal(time, true) {}
};


struct Vibrate : Signal {
    consteval Vibrate(size_t time) : Signal(time) {}
};


template<size_t N = 0, typename ...Args>
struct SignalSequence {
public:
    static consteval auto 
    length() {
        return N > 0 ? N : sizeof...(Args);
    }

    consteval explicit 
    SignalSequence(std::array<Signal, N> sequence) : sequence(sequence) {}
    consteval explicit 
    SignalSequence(Args... more) : sequence({more...}) {}

    consteval auto 
    sum() const {
        int sum = 0;
        for (auto signal: sequence) sum += signal.time;
        return sum;
    }

    consteval auto operator+(const auto& other) const {
        auto sequence = concat(this->sequence, other.sequence);
        return SignalSequence<sequence.size()>(sequence);
    }

    std::array<Signal, length()> sequence;
};


inline int 
signal_example() {
   constexpr Signal start(10);
   constexpr Signal current(start.tick());
   volatile size_t i = current.time;
   std::cout << i << std::endl;

   constexpr Signal current1(current.tick());
   i = current1.time;
   std::cout << i << std::endl;

   constexpr Signal current2(current1.tick());
   i = current2.time;
   std::cout << i << std::endl;

   constexpr Signal current3(current2.tick());
   i = current3.time;
   std::cout << i << std::endl;

   return 0;
}


inline int 
signal_example_without_out() {
   constexpr Signal start(10);
   constexpr Signal current(start.tick());
   volatile size_t i = current.time;

   constexpr Signal current1(current.tick());
   i = current1.time;

   constexpr Signal current2(current1.tick());
   i = current2.time;

   constexpr Signal current3(current2.tick());
   i = current3.time;

   return 0;
}

inline int 
signal_sequence_example() {
    constexpr SignalSequence first(Vibrate(1), Pause(2));
    constexpr SignalSequence second(Vibrate(3), Pause(4), Vibrate(5));

    constexpr auto sequence = first + second;

    constexpr auto sum = sequence.sum();
    constexpr auto length = sequence.length();

    std::cout << "sum: " << sum << "\n";
    std::cout << "length: " << length << "\n";

    std::cout << "Start" << std::endl;
    for (Signal signal: sequence.sequence) {
        std::cout << "Time: " << signal.time << ", "
                 << (signal.is_pause ? "Waiting..." : "Vibrating...");

        for (int time = signal.time; time >= 0; time--) std::cout << " " << time;
        std::cout << std::endl;
    }

    return 0;
}


inline int 
signal_sequence_example_without_out() {
    constexpr SignalSequence first(Vibrate(1), Pause(2));
    constexpr SignalSequence second(Vibrate(3), Pause(4), Vibrate(5));

    constexpr auto sequence = first + second;

    constexpr auto sum = sequence.sum();
    constexpr auto length = sequence.length();

    volatile size_t i = 0;
    volatile size_t j = 0;
    
    for (Signal signal: sequence.sequence) {
        i = signal.time;
        for (int time = signal.time; time >= 0; time--) j = time;
    }

    return 0;
}



///////////////////////////////////////////////////////////////////
//////////////////////// NUMBER TO STRING /////////////////////////
///////////////////////////////////////////////////////////////////



consteval auto
count_of_digits(int number) {
   int result = 0;
   while (number > 0) {
       result++;
       number /= 10;
   }
   return result == 0 ? 1 : result;
}

template <typename T, size_t N>
consteval auto
reverse_array(std::array<T, N> arr) {
   std::array<T, N> result{0};
   for (int i = 0; i < N; i++) {
       result[i] = arr[N - i - 1];
   }
   return result;
}

template <size_t N>
consteval auto
int_to_digits(int number) {
   std::array<int, N> digits{0};
   for (int i = 0; i < N; i++) {
       digits[i] = number % 10;
       number /= 10;
   }
   return reverse_array(digits);
}

template <int Digit>
struct to_char {
   char digit = '0' + Digit % 10;
};

consteval auto
int_to_str(int number) {
   std::array<std::string_view, 10> digits =
           {"0", "1", "2", "3", "4",
            "5", "6", "7", "8", "9"};

   return digits[number % 10];
}


template <size_t N>
consteval auto
digits_to_strings(std::array<int, N> digits) {
   std::array<char, N> result{0};
   for (int i = 0; i < N; i++) result[i] = '0' + digits[i];
   return result;
}

template <int N, int len = count_of_digits(N)>
consteval auto
int_to_string() {
   return digits_to_strings(int_to_digits<len>(N));
}

template <auto get_delimiter>
consteval auto 
str_to_chars() {
   constexpr std::string_view delim = get_delimiter();
   constexpr auto len = delim.size();
   std::array<char, len> result{0};
   for (int i = 0; i < len; i++) result[i] = delim[i];
   return result;
}


template <size_t N, size_t M, size_t length = N + (N - 1) * M>
consteval auto
join(const std::array<char, M> delimiter, const std::array<char, N> sequence) {
   std::array<char, length> result{0};

   int sequence_index = 0;
   int delimiter_index = 0;
   for (int i : std::ranges::views::iota(0, (int)length)) {
       if (delimiter_index == 0) {
           result[i] = sequence[sequence_index++];
           delimiter_index = M;
       }
       else {
           result[i] = delimiter[M - delimiter_index];
           delimiter_index -= 1;
       }
   }

   return result;
}


template <size_t N>
consteval auto
get_delimiter_impl(const char (&delimiter)[N]) {
   return [delimiter](){ return delimiter;};
}


inline int 
int_to_char_array_example() {
   constexpr std::array ints = int_to_string<1076>();
   constexpr std::array delimiter = str_to_chars<get_delimiter_impl(", ")>();
   constexpr std::array ints_str = join(delimiter, ints);

   for (auto i : ints_str) std::cout << i;
   std::cout << std::endl;

   return 0;
}

inline int 
int_to_char_array_example_without_out() {
   constexpr std::array ints = int_to_string<1076>();
   constexpr std::array delimiter = str_to_chars<get_delimiter_impl(", ")>();
   constexpr std::array ints_str = join(delimiter, ints);

   volatile char i = ' ';
   for (auto c : ints_str) i = c;

   return 0;
}

#endif //CPP20_EXPERIMENTS_COMPILE_TIME_EXPERIMENTS_H


