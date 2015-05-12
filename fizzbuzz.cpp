#include <array>
#include <iostream>

template <char... Cs>
struct compile_time_string {
    constexpr static char value[] = {Cs..., '\0'};
};

template <char... Cs>
constexpr char compile_time_string<Cs...>::value[];

int main() {
    std::cout << compile_time_string<'h', 'e', 'l', 'l', 'o'>::value << std::endl;
}
