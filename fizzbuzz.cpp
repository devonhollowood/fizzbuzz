#include <iostream>

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

int main() {
    std::cout << itoa<24601>::result::value << std::endl;
}
