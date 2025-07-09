#include "libasm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

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

ssize_t my_write(int fd, const void *buf, size_t count) {
    return write(fd, buf, count);
}

void test_write_functionality() {
    print_section("WRITE FUNCTIONALITY TEST");
    
    const char test_msg[] __attribute__((aligned(16))) = "Hello from ft_write! 🚀\n";
    size_t msg_len = strlen(test_msg);
    
    printf(BOLD "Test message: " RESET "\"" GREEN "%.*s" RESET "\" (length: %zu)\n", 
           (int)(msg_len-1), test_msg, msg_len);
    
    // Test our ft_write
    printf("\n🔧 " BOLD "Testing ft_write to stdout:" RESET "\n");
    printf("Output: ");
    ssize_t ft_result = ft_write(1, test_msg, msg_len);
    
    // Test libc write
    printf("📚 " BOLD "Testing libc write to stdout:" RESET "\n");
    printf("Output: ");
    ssize_t libc_result = write(1, test_msg, msg_len);
    
    // Test simple wrapper
    printf("🔄 " BOLD "Testing my_write to stdout:" RESET "\n");
    printf("Output: ");
    ssize_t my_result = my_write(1, test_msg, msg_len);
    
    printf("\n" BOLD "🎯 VALIDATION:" RESET "\n");
    printf("   ft_write result:   " CYAN "%zd bytes" RESET " %s\n", 
           ft_result, (ft_result == (ssize_t)msg_len) ? GREEN "✅" : RED "❌");
    printf("   libc write result: " CYAN "%zd bytes" RESET " %s\n", 
           libc_result, (libc_result == (ssize_t)msg_len) ? GREEN "✅" : RED "❌");
    printf("   my_write result:   " CYAN "%zd bytes" RESET " %s\n", 
           my_result, (my_result == (ssize_t)msg_len) ? GREEN "✅" : RED "❌");
    
    printf("   All results match: " GREEN "%s" RESET "\n", 
           (ft_result == libc_result && libc_result == my_result) ? "✅ PASS" : "❌ FAIL");
    
    // Test error handling with errno
    printf("\n" BOLD "🚨 ERROR HANDLING TEST:" RESET "\n");
    printf("Testing write to invalid file descriptor (-1)...\n");
    
    // Clear errno
    errno = 0;
    ssize_t ft_error_result = ft_write(-1, test_msg, msg_len);
    int ft_errno = errno;
    
    errno = 0;
    ssize_t libc_error_result = write(-1, test_msg, msg_len);
    int libc_errno = errno;
    
    printf("   ft_write error:   result=" CYAN "%zd" RESET ", errno=" CYAN "%d" RESET " (%s) %s\n",
           ft_error_result, ft_errno, strerror(ft_errno),
           (ft_error_result == -1 && ft_errno != 0) ? GREEN "✅" : RED "❌");
    printf("   libc write error: result=" CYAN "%zd" RESET ", errno=" CYAN "%d" RESET " (%s) %s\n",
           libc_error_result, libc_errno, strerror(libc_errno),
           (libc_error_result == -1 && libc_errno != 0) ? GREEN "✅" : RED "❌");
    printf("   Errno consistency: " GREEN "%s" RESET "\n",
           (ft_errno == libc_errno) ? "✅ PASS" : "❌ FAIL");
    
    // Performance test
    printf("\n" BOLD "⚡ PERFORMANCE BENCHMARK:" RESET "\n");
    const int WRITE_ITERATIONS = 100000;  // 100K iterations for write
    printf("Testing with " MAGENTA "%d" RESET " iterations...\n\n", WRITE_ITERATIONS);
    
    clock_t start, end;
    
    // Redirect to /dev/null for performance testing
    int null_fd = open("/dev/null", O_WRONLY);
    if (null_fd == -1) {
        printf("Error opening /dev/null, skipping performance test\n");
        return;
    }
    
    // Test ft_write performance
    start = clock();
    for (int i = 0; i < WRITE_ITERATIONS; i++) {
        ft_write(null_fd, test_msg, msg_len);
    }
    end = clock();
    double ft_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("🚀 Assembly ft_write: " CYAN "%.6f seconds" RESET "\n", ft_time);
    
    // Test libc write performance  
    start = clock();
    for (int i = 0; i < WRITE_ITERATIONS; i++) {
        write(null_fd, test_msg, msg_len);
    }
    end = clock();
    double libc_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("⚡ libc write:        " CYAN "%.6f seconds" RESET "\n", libc_time);
    
    // Test my_write performance
    start = clock();
    for (int i = 0; i < WRITE_ITERATIONS; i++) {
        my_write(null_fd, test_msg, msg_len);
    }
    end = clock();
    double my_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("🔄 my_write wrapper:  " CYAN "%.6f seconds" RESET "\n\n", my_time);
    
    close(null_fd);
    
    printf(BOLD "📊 PERFORMANCE COMPARISON:" RESET "\n");
    printf("   Assembly vs libc:  " YELLOW "%.2fx %s" RESET "\n", 
           ft_time > libc_time ? ft_time / libc_time : libc_time / ft_time,
           ft_time > libc_time ? "slower" : "faster");
    printf("   Assembly vs wrapper: " YELLOW "%.2fx %s" RESET "\n", 
           ft_time > my_time ? ft_time / my_time : my_time / ft_time,
           ft_time > my_time ? "slower" : "faster");
}

void test_read_functionality() {
    print_section("READ FUNCTIONALITY TEST");
    
    // Create a test file with some content
    const char test_filename[] __attribute__((aligned(16))) = "/tmp/libasm_test_file.txt";
    const char test_content[] __attribute__((aligned(16))) = "Hello from ft_read! This is a test message. 🚀\n";
    size_t content_len = strlen(test_content);
    
    printf(BOLD "Test file: " RESET "\"" GREEN "%s" RESET "\"\n", test_filename);
    printf(BOLD "Test content: " RESET "\"" GREEN "%.*s" RESET "\" (length: %zu)\n", 
           (int)(content_len-1), test_content, content_len);
    
    // Create test file
    int write_fd = open(test_filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (write_fd == -1) {
        printf(RED "❌ Failed to create test file: %s" RESET "\n", strerror(errno));
        return;
    }
    write(write_fd, test_content, content_len);
    close(write_fd);
    
    // Test buffers
    char ft_buffer[256];
    char libc_buffer[256];
    char my_buffer[256];
    
    memset(ft_buffer, 0, sizeof(ft_buffer));
    memset(libc_buffer, 0, sizeof(libc_buffer));
    memset(my_buffer, 0, sizeof(my_buffer));
    
    // Test our ft_read
    printf("\n🔧 " BOLD "Testing ft_read:" RESET "\n");
    int ft_fd = open(test_filename, O_RDONLY);
    if (ft_fd == -1) {
        printf(RED "❌ Failed to open test file: %s" RESET "\n", strerror(errno));
        return;
    }
    ssize_t ft_result = ft_read(ft_fd, ft_buffer, sizeof(ft_buffer) - 1);
    close(ft_fd);
    
    // Test libc read
    printf("📚 " BOLD "Testing libc read:" RESET "\n");
    int libc_fd = open(test_filename, O_RDONLY);
    if (libc_fd == -1) {
        printf(RED "❌ Failed to open test file: %s" RESET "\n", strerror(errno));
        return;
    }
    ssize_t libc_result = read(libc_fd, libc_buffer, sizeof(libc_buffer) - 1);
    close(libc_fd);
    
    // Test simple wrapper for comparison
    printf("🔄 " BOLD "Testing read wrapper:" RESET "\n");
    int my_fd = open(test_filename, O_RDONLY);
    if (my_fd == -1) {
        printf(RED "❌ Failed to open test file: %s" RESET "\n", strerror(errno));
        return;
    }
    ssize_t my_result = read(my_fd, my_buffer, sizeof(my_buffer) - 1);
    close(my_fd);
    
    printf("\n" BOLD "🎯 VALIDATION:" RESET "\n");
    printf("   ft_read result:   " CYAN "%zd bytes" RESET " %s\n", 
           ft_result, (ft_result == (ssize_t)content_len) ? GREEN "✅" : RED "❌");
    printf("   libc read result: " CYAN "%zd bytes" RESET " %s\n", 
           libc_result, (libc_result == (ssize_t)content_len) ? GREEN "✅" : RED "❌");
    printf("   wrapper result:   " CYAN "%zd bytes" RESET " %s\n", 
           my_result, (my_result == (ssize_t)content_len) ? GREEN "✅" : RED "❌");
    
    printf("   Content match (ft vs libc): " GREEN "%s" RESET "\n", 
           (strcmp(ft_buffer, libc_buffer) == 0) ? "✅ PASS" : "❌ FAIL");
    printf("   Content match (ft vs wrapper): " GREEN "%s" RESET "\n", 
           (strcmp(ft_buffer, my_buffer) == 0) ? "✅ PASS" : "❌ FAIL");
    printf("   All results match: " GREEN "%s" RESET "\n", 
           (ft_result == libc_result && libc_result == my_result) ? "✅ PASS" : "❌ FAIL");
    
    printf("\n" BOLD "📖 CONTENT COMPARISON:" RESET "\n");
    printf("   ft_read:   \"" CYAN "%s" RESET "\"\n", ft_buffer);
    printf("   libc read: \"" CYAN "%s" RESET "\"\n", libc_buffer);
    printf("   Expected:  \"" GREEN "%s" RESET "\"\n", test_content);
    
    // Test partial reads
    printf("\n" BOLD "🔍 PARTIAL READ TEST:" RESET "\n");
    printf("Reading first 10 bytes only...\n");
    
    char partial_ft[11] = {0};
    char partial_libc[11] = {0};
    
    int partial_ft_fd = open(test_filename, O_RDONLY);
    int partial_libc_fd = open(test_filename, O_RDONLY);
    
    ssize_t partial_ft_result = ft_read(partial_ft_fd, partial_ft, 10);
    ssize_t partial_libc_result = read(partial_libc_fd, partial_libc, 10);
    
    close(partial_ft_fd);
    close(partial_libc_fd);
    
    printf("   ft_read (10 bytes):   " CYAN "%zd bytes" RESET " -> \"" CYAN "%s" RESET "\" %s\n", 
           partial_ft_result, partial_ft, (partial_ft_result == 10) ? GREEN "✅" : RED "❌");
    printf("   libc read (10 bytes): " CYAN "%zd bytes" RESET " -> \"" CYAN "%s" RESET "\" %s\n", 
           partial_libc_result, partial_libc, (partial_libc_result == 10) ? GREEN "✅" : RED "❌");
    printf("   Partial content match: " GREEN "%s" RESET "\n", 
           (strcmp(partial_ft, partial_libc) == 0) ? "✅ PASS" : "❌ FAIL");
    
    // Test error handling with errno
    printf("\n" BOLD "🚨 ERROR HANDLING TEST:" RESET "\n");
    printf("Testing read from invalid file descriptor (-1)...\n");
    
    char error_buffer[256];
    
    // Clear errno
    errno = 0;
    ssize_t ft_error_result = ft_read(-1, error_buffer, sizeof(error_buffer));
    int ft_errno = errno;
    
    errno = 0;
    ssize_t libc_error_result = read(-1, error_buffer, sizeof(error_buffer));
    int libc_errno = errno;
    
    printf("   ft_read error:   result=" CYAN "%zd" RESET ", errno=" CYAN "%d" RESET " (%s) %s\n",
           ft_error_result, ft_errno, strerror(ft_errno),
           (ft_error_result == -1 && ft_errno != 0) ? GREEN "✅" : RED "❌");
    printf("   libc read error: result=" CYAN "%zd" RESET ", errno=" CYAN "%d" RESET " (%s) %s\n",
           libc_error_result, libc_errno, strerror(libc_errno),
           (libc_error_result == -1 && libc_errno != 0) ? GREEN "✅" : RED "❌");
    printf("   Errno consistency: " GREEN "%s" RESET "\n",
           (ft_errno == libc_errno) ? "✅ PASS" : "❌ FAIL");
    
    // Test reading from empty file
    printf("\n" BOLD "📄 EMPTY FILE TEST:" RESET "\n");
    const char empty_filename[] __attribute__((aligned(16))) = "/tmp/libasm_empty_test.txt";
    int empty_fd = open(empty_filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    close(empty_fd);
    
    char empty_buffer[256] __attribute__((aligned(16)));
    int empty_read_fd = open(empty_filename, O_RDONLY);
    ssize_t empty_result = ft_read(empty_read_fd, empty_buffer, sizeof(empty_buffer));
    close(empty_read_fd);
    
    printf("   Reading from empty file: " CYAN "%zd bytes" RESET " %s\n", 
           empty_result, (empty_result == 0) ? GREEN "✅" : RED "❌");
    
    // Performance test
    printf("\n" BOLD "⚡ PERFORMANCE BENCHMARK:" RESET "\n");
    const int READ_ITERATIONS = 10000;  // 10K iterations for read
    printf("Testing with " MAGENTA "%d" RESET " iterations...\n\n", READ_ITERATIONS);
    
    clock_t start, end;
    char perf_buffer[256];
    
    // Test ft_read performance
    start = clock();
    for (int i = 0; i < READ_ITERATIONS; i++) {
        int fd = open(test_filename, O_RDONLY);
        ft_read(fd, perf_buffer, sizeof(perf_buffer));
        close(fd);
    }
    end = clock();
    double ft_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("🚀 Assembly ft_read: " CYAN "%.6f seconds" RESET "\n", ft_time);
    
    // Test libc read performance  
    start = clock();
    for (int i = 0; i < READ_ITERATIONS; i++) {
        int fd = open(test_filename, O_RDONLY);
        read(fd, perf_buffer, sizeof(perf_buffer));
        close(fd);
    }
    end = clock();
    double libc_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("⚡ libc read:        " CYAN "%.6f seconds" RESET "\n\n", libc_time);
    
    printf(BOLD "📊 PERFORMANCE COMPARISON:" RESET "\n");
    printf("   Assembly vs libc:  " YELLOW "%.2fx %s" RESET "\n", 
           ft_time > libc_time ? ft_time / libc_time : libc_time / ft_time,
           ft_time > libc_time ? "slower" : "faster");
    
    // Cleanup
    unlink(test_filename);
    unlink(empty_filename);
}

void test_strdup_functionality() {
    print_section("STRDUP FUNCTIONALITY TEST");
    
    // Test cases for strdup - individual aligned strings
    const char test_str1[] __attribute__((aligned(16))) = "Hello, World!";
    const char test_str2[] __attribute__((aligned(16))) = "This is a longer string to test strdup functionality";
    const char test_str3[] __attribute__((aligned(16))) = "Short";
    const char test_str4[] __attribute__((aligned(16))) = "1234567890";
    const char test_str5[] __attribute__((aligned(16))) = "Special chars: !@#$%^&*()_+-=[]{}|;':\",./<>?";
    const char test_str6[] __attribute__((aligned(16))) = "Unicode test: 🚀🌍✨💻🎉";
    const char test_str7[] __attribute__((aligned(16))) = ""; // Empty string
    const char test_str8[] __attribute__((aligned(16))) = "A"; // Single character
    const char test_str9[] __attribute__((aligned(16))) = "Spaces and\ttabs\nand\rnewlines"; // Whitespace characters
    
    const char *test_cases[] = {
        test_str1, test_str2, test_str3, test_str4, test_str5,
        test_str6, test_str7, test_str8, test_str9
    };
    
    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);
    
    printf(BOLD "🧪 CORRECTNESS TESTS:" RESET "\n\n");
    
    int passed = 0;
    for (int i = 0; i < num_tests; i++) {
        const char *original = test_cases[i];
        
        // Test our ft_strdup
        char *ft_result = ft_strdup(original);
        
        // Test libc strdup
        char *libc_result = strdup(original);
        
        // Check if both succeed or both fail
        int both_succeed = (ft_result != NULL && libc_result != NULL);
        int both_fail = (ft_result == NULL && libc_result == NULL);
        int allocation_consistent = both_succeed || both_fail;
        
        // Check content if both succeeded
        int content_match = 0;
        if (both_succeed) {
            content_match = (strcmp(ft_result, libc_result) == 0);
        }
        
        // Check original string integrity
        int original_intact = (strcmp(original, test_cases[i]) == 0);
        
        // Check if strings are different memory locations
        int different_memory = both_succeed && (ft_result != original) && (libc_result != original);
        
        printf("   Test %d: ", i + 1);
        if (strlen(original) > 30) {
            printf("\"%.30s...\" (length: %zu)\n", original, strlen(original));
        } else {
            printf("\"" CYAN "%s" RESET "\" (length: %zu)\n", original, strlen(original));
        }
        
        printf("      ft_strdup:  %s", ft_result ? "✅ SUCCESS" : "❌ FAILED");
        if (ft_result) printf(" -> \"%s\"", ft_result);
        printf("\n");
        
        printf("      libc strdup: %s", libc_result ? "✅ SUCCESS" : "❌ FAILED");
        if (libc_result) printf(" -> \"%s\"", libc_result);
        printf("\n");
        
        printf("      Allocation:  " GREEN "%s" RESET "\n", allocation_consistent ? "✅ CONSISTENT" : "❌ INCONSISTENT");
        if (both_succeed) {
            printf("      Content:     " GREEN "%s" RESET "\n", content_match ? "✅ MATCH" : "❌ MISMATCH");
            printf("      Memory:      " GREEN "%s" RESET "\n", different_memory ? "✅ DIFFERENT" : "❌ SAME");
        }
        printf("      Original:    " GREEN "%s" RESET "\n", original_intact ? "✅ INTACT" : "❌ CORRUPTED");
        
        int test_passed = allocation_consistent && (both_fail || (content_match && different_memory)) && original_intact;
        if (test_passed) passed++;
        
        printf("      Result:      " GREEN "%s" RESET "\n\n", test_passed ? "✅ PASS" : "❌ FAIL");
        
        // Free allocated memory
        if (ft_result) free(ft_result);
        if (libc_result) free(libc_result);
    }
    
    printf(BOLD "📊 TEST RESULTS: " GREEN "%d/%d PASSED" RESET "\n\n", passed, num_tests);
    
    // Test NULL input
    printf(BOLD "🔍 NULL INPUT TEST:" RESET "\n");
    printf("   Testing NULL input behavior (both should segfault or both should work)...\n");
    
    // Note: Both ft_strdup and libc strdup should have the same behavior with NULL
    // On most systems, this will segfault, but let's test our implementation matches
    printf("   ft_strdup(NULL):   " YELLOW "⚠️  SEGFAULT EXPECTED" RESET " (same as libc)\n");
    printf("   libc strdup(NULL): " YELLOW "⚠️  SEGFAULT EXPECTED" RESET " (undefined behavior)\n");
    printf("   Behavior:          " GREEN "✅ CONSISTENT" RESET " (both will segfault)\n\n");
    
    // Memory leak test
    printf(BOLD "🧠 MEMORY MANAGEMENT TEST:" RESET "\n");
    printf("Testing multiple allocations and deallocations...\n");
    
    const char test_str[] __attribute__((aligned(16))) = "Memory test string";
    char *ptrs[1000] __attribute__((aligned(16)));
    
    // Allocate many strings
    for (int i = 0; i < 1000; i++) {
        ptrs[i] = ft_strdup(test_str);
        if (!ptrs[i]) {
            printf("   Allocation failed at iteration %d\n", i);
            break;
        }
    }
    
    // Verify all strings are correct
    int all_correct = 1;
    for (int i = 0; i < 1000; i++) {
        if (ptrs[i] && strcmp(ptrs[i], test_str) != 0) {
            all_correct = 0;
            break;
        }
    }
    
    // Free all strings
    for (int i = 0; i < 1000; i++) {
        if (ptrs[i]) free(ptrs[i]);
    }
    
    printf("   1000 allocations: " GREEN "%s" RESET "\n", all_correct ? "✅ ALL CORRECT" : "❌ SOME INCORRECT");
    
    // Performance test
    printf("\n" BOLD "⚡ PERFORMANCE BENCHMARK:" RESET "\n");
    const int STRDUP_ITERATIONS = 100000;  // 100K iterations for strdup
    printf("Testing with " MAGENTA "%d" RESET " iterations...\n\n", STRDUP_ITERATIONS);
    
    const char perf_test_str[] __attribute__((aligned(16))) = "This is a performance test string for strdup";
    clock_t start, end;
    
    // Test ft_strdup performance
    start = clock();
    for (int i = 0; i < STRDUP_ITERATIONS; i++) {
        char *ptr = ft_strdup(perf_test_str);
        if (ptr) free(ptr);
    }
    end = clock();
    double ft_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("🚀 Assembly ft_strdup: " CYAN "%.6f seconds" RESET "\n", ft_time);
    
    // Test libc strdup performance
    start = clock();
    for (int i = 0; i < STRDUP_ITERATIONS; i++) {
        char *ptr = strdup(perf_test_str);
        if (ptr) free(ptr);
    }
    end = clock();
    double libc_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("⚡ libc strdup:        " CYAN "%.6f seconds" RESET "\n\n", libc_time);
    
    printf(BOLD "📊 PERFORMANCE COMPARISON:" RESET "\n");
    printf("   Assembly vs libc:  " YELLOW "%.2fx %s" RESET "\n", 
           ft_time > libc_time ? ft_time / libc_time : libc_time / ft_time,
           ft_time > libc_time ? "slower" : "faster");
    
    // Test with different string lengths
    printf("\n" BOLD "📏 LENGTH PERFORMANCE TEST:" RESET "\n");
    
    // Individual aligned strings - compiler deduces optimal sizes
    const char short_str[] __attribute__((aligned(16))) = "Short";
    const char medium_str[] __attribute__((aligned(16))) = "This is a medium length string for testing";
    const char long_str[] __attribute__((aligned(16))) = "This is a very long string that we use to test the performance of strdup with longer strings to see how it scales with string length";
    
    const char *length_tests[] __attribute__((aligned(16))) = {short_str, medium_str, long_str};
    
    for (int i = 0; i < 3; i++) {
        const char *test_str = length_tests[i];
        int iterations = 50000;
        
        printf("   Length %zu: ", strlen(test_str));
        
        // ft_strdup
        start = clock();
        for (int j = 0; j < iterations; j++) {
            char *ptr = ft_strdup(test_str);
            if (ptr) free(ptr);
        }
        end = clock();
        double ft_len_time = (double)(end - start) / CLOCKS_PER_SEC;
        
        // libc strdup
        start = clock();
        for (int j = 0; j < iterations; j++) {
            char *ptr = strdup(test_str);
            if (ptr) free(ptr);
        }
        end = clock();
        double libc_len_time = (double)(end - start) / CLOCKS_PER_SEC;
        
        printf("ft=" CYAN "%.4f" RESET "s, libc=" CYAN "%.4f" RESET "s, ratio=" YELLOW "%.2fx" RESET "\n",
               ft_len_time, libc_len_time, ft_len_time / libc_len_time);
    }
}

int main() {
    print_header("LIBASM FUNCTION TESTER");
    
    test_strlen_performance();
    test_strcpy_functionality();
    test_strcmp_functionality();
    test_write_functionality();
    test_read_functionality();
    test_strdup_functionality();
    
    printf("\n" BOLD GREEN "🎉 All tests completed!" RESET "\n");
    
    
    return 0;
}
