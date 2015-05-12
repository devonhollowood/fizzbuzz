#include <stdio.h>

template <char... Cs>
struct string {
    constexpr static char value[] = {Cs..., '\0'};
};

template <char... Cs>
constexpr char string<Cs...>::value[];

template <typename S, char C>
struct string_append;

template <char... Cs, char C>
struct string_append<string<Cs...>, C> {
    using result = string<Cs..., C>;
};

template <typename S1, typename S2>
struct string_concat;

template <char... Cs1, char... Cs2>
struct string_concat<string<Cs1...>, string<Cs2...>>{
    using result = string<Cs1..., Cs2...>;
};

template <bool B, size_t N>
struct itoa_helper;

//recursive itoa_helper
template <bool B, size_t N>
struct itoa_helper {
    using result = typename string_append<
            typename itoa_helper<N/10<10, N/10>::result,
            '0' + N%10
        >::result;
};

template <size_t N>
struct itoa_helper<true, N> {
    using result = string<'0' + N>;
};

template <size_t N>
struct itoa {
    using result = typename itoa_helper<N<10, N>::result;
};

template <bool B>
struct Fizz {
    using result = string<>;
};

template<>
struct Fizz<true> {
    using result = string<'F', 'i', 'z', 'z'>;
};

template <bool B>
struct Buzz {
    using result = string<>;
};

template<>
struct Buzz<true> {
    using result = string<'B', 'u', 'z', 'z'>;
};

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

template <size_t N>
struct FizzBuzz{
    using result = typename ready<
        N,
        typename string_concat<typename Fizz<N%3==0>::result,
                      typename Buzz<N%5==0>::result
        >::result
    >::result;
};

template <size_t N, size_t Target>
struct FizzBuzzPrinter_helper{
    using result = typename string_concat<
        typename string_concat<
            typename FizzBuzz<N>::result,
            string<'\n'>
        >::result,
        typename FizzBuzzPrinter_helper<N+1, Target>::result
    >::result;
};

template <size_t N>
struct FizzBuzzPrinter_helper<N,N>{
    using result = typename FizzBuzz<N>::result;
};

template <size_t Target>
struct FizzBuzzPrinter {
    using result = typename FizzBuzzPrinter_helper<1, Target>::result;
};

int main() {
    printf("%s\n", FizzBuzzPrinter<100>::result::value);
}
