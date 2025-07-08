#include "libasm.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

#define ITERATIONS 10000000

size_t my_strlen(const char *str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int main() {
    const char test_str[] __attribute__((aligned(16))) = "1234567890123456";

    size_t len;
    clock_t start, end;

    // mi asm strlen
    start = clock();
    for (size_t iter = 0; iter < ITERATIONS; iter++) {
        len = ft_strlen(test_str);
    }
    end = clock();
    double asm_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Assembly ft_strlen result: %zu, time: %f seconds\n", len, asm_time);

    // strlen de iterador SIN optimizar (-O0 en makefile sino f)
    start = clock();
    for (size_t iter = 0; iter < ITERATIONS; iter++) {
        len = my_strlen(test_str);
    }
    end = clock();
    double my_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Iteration ft_strlen result: %zu, time: %f seconds\n", len, my_time);

    // strlen de libc
    start = clock();
    for (size_t iter = 0; iter < ITERATIONS; iter++) {
        len = strlen(test_str);
    }
    end = clock();
    double libc_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("libc strlen result: %zu, time: %f seconds\n", len, libc_time);

    return 0;
}
