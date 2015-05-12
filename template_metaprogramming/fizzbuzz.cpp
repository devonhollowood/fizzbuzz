#include <stdio.h>

// struct representing a string. This is the basis of everything.
template <char... Cs>
struct string {
    constexpr static char value[] = {Cs..., '\0'};
};

template <char... Cs>
constexpr char string<Cs...>::value[];

// Use this to append a character to a string.
template <typename S, char C>
struct string_append;

template <char... Cs, char C>
struct string_append<string<Cs...>, C> {
    using result = string<Cs..., C>;
};

// Use this to concatenate two strings
template <typename S1, typename S2>
struct string_concat;

template <char... Cs1, char... Cs2>
struct string_concat<string<Cs1...>, string<Cs2...>>{
    using result = string<Cs1..., Cs2...>;
};

// This is a helper struct for itoa.
// 'B' is whether the number is less than 10
// 'N' is the number
template <bool B, size_t N>
struct itoa_helper;

/* recursive case */
template <bool B, size_t N>
struct itoa_helper {
    using result = typename string_append<
            typename itoa_helper<N/10<10, N/10>::result,
            '0' + N%10
        >::result;
};

/* base case */
template <size_t N>
struct itoa_helper<true, N> {
    using result = string<'0' + N>;
};

// Use this to convert a size_t to a string
template <size_t N>
struct itoa {
    using result = typename itoa_helper<N<10, N>::result;
};

// Use this to either get the string "Fizz" (if 'B' is true), or ""
template <bool B>
struct Fizz {
    using result = string<>;
};

template<>
struct Fizz<true> {
    using result = string<'F', 'i', 'z', 'z'>;
};

// Use this to either get the string "Buzz" (if 'B' is true), or ""
template <bool B>
struct Buzz {
    using result = string<>;
};

template<>
struct Buzz<true> {
    using result = string<'B', 'u', 'z', 'z'>;
};

// Use this to ready a number for printing.
// 'N' is the number
// 'S' is the string produced by (
//     string_concat<typename Fizz<N%3==0>::result,
//                   typename Buzz<N%5==0>::result>::result
//     )
template <size_t N, typename S>
struct ready;

template <size_t N, char C, char... Cs>
struct ready<N, string<C, Cs...>>{
    using result = string<C, Cs...>;
};

template <size_t N>
struct ready<N, string<>> {
    using result = typename itoa<N>::result;
};

// Use this to get the FizzBuzz result for N
template <size_t N>
struct FizzBuzz{
    using result = typename ready<
        N,
        typename string_concat<typename Fizz<N%3==0>::result,
                      typename Buzz<N%5==0>::result
        >::result
    >::result;
};

// Helper struct for FizzBuzzPrinter
// 'N' is the current number
// 'Remaining' is how many numbers we have left
/* recursive case */
template <size_t N, size_t Remaining>
struct FizzBuzzPrinter_helper{
    using result = typename string_concat<
        typename string_concat<
            typename FizzBuzz<N>::result,
            string<'\n'>
        >::result,
        typename FizzBuzzPrinter_helper<N+1, Remaining-1>::result
    >::result;
};

/* base case */
template <size_t N>
struct FizzBuzzPrinter_helper<N,0>{
    using result = typename FizzBuzz<N>::result;
};

// Use this to print out the FizzBuzz results from 1 to N
template <size_t N>
struct FizzBuzzPrinter {
    using result = typename FizzBuzzPrinter_helper<1, N-1>::result;
};

int main() {
    printf("%s\n", FizzBuzzPrinter<100>::result::value);
}
