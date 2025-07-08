#include "libasm.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

#define ITERATIONS 10000000

// ANSI Color codes
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

void print_header(const char *title) {
    printf("\n" BOLD CYAN "╔════════════════════════════════════════════════════════════╗\n");
    printf("║                    %-35s     ║\n", title);
    printf("╚════════════════════════════════════════════════════════════╝" RESET "\n");
}

void print_section(const char *section) {
    printf("\n" BOLD YELLOW "┌─ %s " RESET, section);
    for (int i = strlen(section); i < 50; i++) printf("─");
    printf("\n");
}

size_t my_strlen(const char *str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

char *my_strcpy(char *dest, const char *src) {
    char *original_dest = dest;
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';  // Copy the null terminator
    return original_dest;
}

int my_strcmp(const char *s1, const char *s2) {
    while (*s1 && *s2 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

void test_strlen_performance() {
    print_section("STRLEN PERFORMANCE BENCHMARK");
    
    const char test_str[] __attribute__((aligned(16))) = "1234567890123456";
    size_t len;
    clock_t start, end;
    
    printf(BOLD "Test String: " RESET "\"" GREEN "%s" RESET "\" (length: %zu)\n", test_str, strlen(test_str));
    printf(BOLD "Iterations: " RESET MAGENTA "%d" RESET "\n\n", ITERATIONS);

    // Assembly strlen test
    printf("🚀 " BOLD "Assembly ft_strlen" RESET " (4x unrolled, aligned)...\n");
    start = clock();
    for (size_t iter = 0; iter < ITERATIONS; iter++) {
        len = ft_strlen(test_str);
    }
    end = clock();
    double asm_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("   Result: " GREEN "%zu" RESET " | Time: " CYAN "%.6f seconds" RESET "\n\n", len, asm_time);

    // Simple C strlen test
    printf("🔄 " BOLD "Simple C strlen" RESET " (unoptimized -O0)...\n");
    start = clock();
    for (size_t iter = 0; iter < ITERATIONS; iter++) {
        len = my_strlen(test_str);
    }
    end = clock();
    double my_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("   Result: " GREEN "%zu" RESET " | Time: " CYAN "%.6f seconds" RESET "\n\n", len, my_time);

    // libc strlen test
    printf("⚡ " BOLD "libc strlen" RESET " (highly optimized SIMD)...\n");
    start = clock();
    for (size_t iter = 0; iter < ITERATIONS; iter++) {
        len = strlen(test_str);
    }
    end = clock();
    double libc_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("   Result: " GREEN "%zu" RESET " | Time: " CYAN "%.6f seconds" RESET "\n\n", len, libc_time);

    // Performance comparison
    printf(BOLD "📊 PERFORMANCE COMPARISON:" RESET "\n");
    printf("   Assembly vs C:     " YELLOW "%.2fx faster" RESET "\n", my_time / asm_time);
    printf("   Assembly vs libc:  " RED "%.2fx slower" RESET "\n", asm_time / libc_time);
    printf("   libc vs C:         " GREEN "%.2fx faster" RESET "\n", my_time / libc_time);
}

void test_strcpy_functionality() {
    print_section("STRCPY FUNCTIONALITY & PERFORMANCE TEST");
    
    char dest[50] __attribute__((aligned(16)));
    char dest_libc[50] __attribute__((aligned(16)));
    char dest_my[50] __attribute__((aligned(16)));
    const char src[] __attribute__((aligned(16))) = "Hello, Assembly World! 🌍";
    
    printf(BOLD "Source string: " RESET "\"" GREEN "%s" RESET "\" (length: %zu)\n\n", src, strlen(src));

    // Test our strcpy
    char *result = ft_strcpy(dest, src);
    
    // Test libc strcpy for comparison
    strcpy(dest_libc, src);
    
    // Test simple C strcpy
    my_strcpy(dest_my, src);
    
    printf("🔧 " BOLD "Assembly ft_strcpy result:" RESET "\n");
    printf("   Destination: \"" CYAN "%s" RESET "\"\n", dest);
    printf("   Return ptr:  " GREEN "%s" RESET "\n\n", (result == dest) ? "✅ CORRECT" : "❌ WRONG");
    
    printf("📚 " BOLD "libc strcpy result:" RESET "\n");
    printf("   Destination: \"" CYAN "%s" RESET "\"\n\n", dest_libc);
    
    printf("🔄 " BOLD "Simple C strcpy result:" RESET "\n");
    printf("   Destination: \"" CYAN "%s" RESET "\"\n\n", dest_my);
    
    printf(BOLD "🎯 VALIDATION:" RESET "\n");
    printf("   Assembly vs libc:  " GREEN "%s" RESET "\n", (strcmp(dest, dest_libc) == 0) ? "✅ PASS" : "❌ FAIL");
    printf("   Assembly vs C:     " GREEN "%s" RESET "\n", (strcmp(dest, dest_my) == 0) ? "✅ PASS" : "❌ FAIL");
    printf("   Return value:      " GREEN "%s" RESET "\n\n", (result == dest) ? "✅ PASS" : "❌ FAIL");

    // Performance test with smaller iterations for strcpy
    const int STRCPY_ITERATIONS = 1000000;  // 1M iterations for strcpy
    printf(BOLD "⚡ PERFORMANCE COMPARISON (" MAGENTA "%d" RESET BOLD " iterations):" RESET "\n", STRCPY_ITERATIONS);
    
    clock_t start, end;
    
    // Assembly strcpy performance
    start = clock();
    for (int i = 0; i < STRCPY_ITERATIONS; i++) {
        ft_strcpy(dest, src);
    }
    end = clock();
    double asm_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("   🚀 Assembly ft_strcpy: " CYAN "%.6f seconds" RESET "\n", asm_time);
    
    // Simple C strcpy performance
    start = clock();
    for (int i = 0; i < STRCPY_ITERATIONS; i++) {
        my_strcpy(dest_my, src);
    }
    end = clock();
    double my_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("   🔄 Simple C strcpy:   " CYAN "%.6f seconds" RESET "\n", my_time);
    
    // libc strcpy performance
    start = clock();
    for (int i = 0; i < STRCPY_ITERATIONS; i++) {
        strcpy(dest_libc, src);
    }
    end = clock();
    double libc_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("   ⚡ libc strcpy:       " CYAN "%.6f seconds" RESET "\n\n", libc_time);
    
    printf(BOLD "📊 SPEED COMPARISON:" RESET "\n");
    printf("   Assembly vs C:     " YELLOW "%.2fx %s" RESET "\n", 
           my_time > asm_time ? my_time / asm_time : asm_time / my_time,
           my_time > asm_time ? "faster" : "slower");
    printf("   Assembly vs libc:  " RED "%.2fx %s" RESET "\n", 
           asm_time > libc_time ? asm_time / libc_time : libc_time / asm_time,
           asm_time > libc_time ? "slower" : "faster");
    printf("   libc vs C:         " GREEN "%.2fx faster" RESET "\n", my_time / libc_time);
}

void test_strcmp_functionality() {
    print_section("STRCMP FUNCTIONALITY & PERFORMANCE TEST");
    
    // Test cases for strcmp
    struct {
        const char s1[32] __attribute__((aligned(16)));
        const char s2[32] __attribute__((aligned(16)));
        const char *description;
    } test_cases[] = {
        {{"hello"}, {"hello"}, "Equal strings"},
        {{"hello"}, {"world"}, "Different strings (h < w)"},
        {{"world"}, {"hello"}, "Different strings (w > h)"},
        {{"test"}, {"testing"}, "First string is prefix of second"},
        {{"testing"}, {"test"}, "Second string is prefix of first"},
        {{""}, {""}, "Both empty strings"},
        {{"hello"}, {""}, "First string empty"},
        {{""}, {"hello"}, "Second string empty"},
        {{"ABC"}, {"abc"}, "Case sensitivity test"}
    };
    
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    printf(BOLD "🧪 CORRECTNESS TESTS:" RESET "\n\n");
    
    int passed = 0;
    for (int i = 0; i < num_tests; i++) {
        int ft_result = ft_strcmp(test_cases[i].s1, test_cases[i].s2);
        int libc_result = strcmp(test_cases[i].s1, test_cases[i].s2);
        int my_result = my_strcmp(test_cases[i].s1, test_cases[i].s2);
        
        // Normalize results to -1, 0, 1 for comparison
        int ft_norm = (ft_result > 0) ? 1 : (ft_result < 0) ? -1 : 0;
        int libc_norm = (libc_result > 0) ? 1 : (libc_result < 0) ? -1 : 0;
        int my_norm = (my_result > 0) ? 1 : (my_result < 0) ? -1 : 0;
        
        int correct = (ft_norm == libc_norm) && (my_norm == libc_norm);
        
        printf("   %s: " CYAN "\"%s\"" RESET " vs " CYAN "\"%s\"" RESET "\n", 
               test_cases[i].description, test_cases[i].s1, test_cases[i].s2);
        printf("      ft_strcmp: %s%d" RESET " | libc: %s%d" RESET " | my_strcmp: %s%d" RESET " %s\n",
               ft_result > 0 ? GREEN "+" : ft_result < 0 ? RED "" : YELLOW "", ft_result,
               libc_result > 0 ? GREEN "+" : libc_result < 0 ? RED "" : YELLOW "", libc_result,
               my_result > 0 ? GREEN "+" : my_result < 0 ? RED "" : YELLOW "", my_result,
               correct ? GREEN "✅" : RED "❌");
        
        if (correct) passed++;
    }
    
    printf("\n" BOLD "📊 TEST RESULTS: " GREEN "%d/%d PASSED" RESET "\n\n", passed, num_tests);
    
    // Performance test
    printf(BOLD "⚡ PERFORMANCE BENCHMARK:" RESET "\n");
    const char perf_str1[] __attribute__((aligned(16))) = "This is a performance test string for strcmp";
    const char perf_str2[] __attribute__((aligned(16))) = "This is a performance test string for strcmp!"; // Different at the end
    
    clock_t start, end;
    int result;
    
    // Test ft_strcmp
    printf("🚀 " BOLD "Assembly ft_strcmp" RESET "...\n");
    start = clock();
    for (int i = 0; i < ITERATIONS; i++) {
        result = ft_strcmp(perf_str1, perf_str2);
    }
    end = clock();
    double asm_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("   Result: " CYAN "%d" RESET " | Time: " CYAN "%.6f seconds" RESET "\n\n", result, asm_time);
    
    // Test my_strcmp
    printf("🔄 " BOLD "Simple C strcmp" RESET "...\n");
    start = clock();
    for (int i = 0; i < ITERATIONS; i++) {
        result = my_strcmp(perf_str1, perf_str2);
    }
    end = clock();
    double my_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("   Result: " CYAN "%d" RESET " | Time: " CYAN "%.6f seconds" RESET "\n\n", result, my_time);
    
    // Test libc strcmp
    printf("⚡ " BOLD "libc strcmp" RESET "...\n");
    start = clock();
    for (int i = 0; i < ITERATIONS; i++) {
        result = strcmp(perf_str1, perf_str2);
    }
    end = clock();
    double libc_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("   Result: " CYAN "%d" RESET " | Time: " CYAN "%.6f seconds" RESET "\n\n", result, libc_time);
    
    // Performance comparison
    printf(BOLD "📊 PERFORMANCE COMPARISON:" RESET "\n");
    printf("   Assembly vs C:     " YELLOW "%.2fx %s" RESET "\n", 
           my_time / asm_time, asm_time < my_time ? "faster" : "slower");
    printf("   Assembly vs libc:  " YELLOW "%.2fx %s" RESET "\n", 
           libc_time / asm_time, asm_time < libc_time ? "faster" : "slower");
    printf("   libc vs C:         " GREEN "%.2fx faster" RESET "\n", my_time / libc_time);
}

int main() {
    print_header("LIBASM FUNCTION TESTER");
    
    test_strlen_performance();
    test_strcpy_functionality();
    test_strcmp_functionality();
    
    printf("\n" BOLD GREEN "🎉 All tests completed!" RESET "\n");
    
    
    return 0;
}
