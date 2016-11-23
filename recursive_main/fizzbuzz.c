#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char **argv) {
    int n = 0;
    if (argc != 2 || sscanf(argv[1], "%d", &n) != 1 || n < 1) {
        puts("Usage: fizzbuzz <count>");
        exit(1);
    }

    if (n != 1) {
        sprintf(argv[1], "%d", n - 1);
        main(2, argv);
    }

    if (n % 15 == 0) {
        puts("Fizzbuzz");
    } else if (n % 5 == 0) {
        puts("Buzz");
    } else if (n % 3 == 0) {
        puts("Fizz");
    } else {
        printf("%d\n", n);
    }
}
