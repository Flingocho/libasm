#include "libasm.h"
#include <stdio.h>
#include <string.h>

void test_strcmp_case(const char *s1, const char *s2) {
    int ft_result = ft_strcmp(s1, s2);
    int libc_result = strcmp(s1, s2);
    
    // Normalize results to -1, 0, 1 for comparison
    int ft_norm = (ft_result > 0) ? 1 : (ft_result < 0) ? -1 : 0;
    int libc_norm = (libc_result > 0) ? 1 : (libc_result < 0) ? -1 : 0;
    
    printf("strcmp(\"%s\", \"%s\"):\n", s1, s2);
    printf("  ft_strcmp:  %d\n", ft_result);
    printf("  libc strcmp: %d\n", libc_result);
    printf("  Match: %s\n\n", (ft_norm == libc_norm) ? "✅ YES" : "❌ NO");
}

int main() {
    printf("🔍 STRCMP FUNCTION TEST\n");
    printf("========================\n\n");
    
    // Test cases
    test_strcmp_case("hello", "hello");       // Equal strings
    test_strcmp_case("abc", "abd");           // First < Second
    test_strcmp_case("abd", "abc");           // First > Second
    test_strcmp_case("hello", "hello world"); // First is prefix of second
    test_strcmp_case("hello world", "hello"); // Second is prefix of first
    test_strcmp_case("", "");                 // Both empty
    test_strcmp_case("a", "");                // First non-empty, second empty
    test_strcmp_case("", "a");                // First empty, second non-empty
    
    return 0;
}
