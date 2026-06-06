#include <stdio.h>

typedef unsigned char *byte_pointer;

static void show_bytes(byte_pointer start, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

static void show_string_bytes(const char *str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    len++;

    printf("String: \"%s\"\n", str);
    printf("Bytes (hex): ");
    show_bytes((byte_pointer)str, len);
    printf("Length (including NULL): %zu bytes\n", len);
}

static void demonstrate_ascii_digits(void) {
    printf("\n--- ASCII DIGIT ENCODING PATTERN ---\n");
    printf("Pattern: ASCII code for digit 'x' is 0x3x\n\n");

    const char *test_str = "0123456789";
    printf("String: \"%s\"\n", test_str);
    printf("Bytes:   ");
    show_bytes((byte_pointer)test_str, 10);
}

static void demonstrate_string_null_terminator(void) {
    printf("\n--- STRING NULL TERMINATOR ---\n");

    const char *str = "Hello";
    printf("String: \"%s\"\n", str);
    printf("Bytes with NULL: ");
    show_bytes((byte_pointer)str, 6);
}

static void demonstrate_string_variety(void) {
    printf("\n--- VARIOUS STRING EXAMPLES ---\n");

    show_string_bytes("ABC");
    printf("\n");
    show_string_bytes("123");
    printf("\n");
    show_string_bytes("a");
    printf("\n");
    show_string_bytes("");
    printf("\n");
}

static void demonstrate_string_portability(void) {
    printf("\n--- STRING PORTABILITY (PLATFORM INDEPENDENT) ---\n");

    const char *test = "TEXT";
    printf("String: \"%s\"\n", test);
    printf("Bytes:   ");
    show_bytes((byte_pointer)test, 5);
}

static void show_ascii_table(void) {
    printf("\n--- ASCII CHARACTER TABLE ---\n");
    printf("Uppercase letters (A-Z):\n");
    for (char c = 'A'; c <= 'Z'; c++) {
        printf("  '%c' = 0x%02x  ", c, (unsigned char)c);
        if ((c - 'A' + 1) % 6 == 0) {
            printf("\n");
        }
    }

    printf("\n\nLowercase letters (a-z):\n");
    for (char c = 'a'; c <= 'z'; c++) {
        printf("  '%c' = 0x%02x  ", c, (unsigned char)c);
        if ((c - 'a' + 1) % 6 == 0) {
            printf("\n");
        }
    }

    printf("\n\nSpecial characters:\n");
    printf("  Space = 0x%02x\n", (unsigned char)' ');
    printf("  NULL  = 0x%02x (string terminator)\n", 0);
}

int main(void) {
    printf("========== CSAPP SECTION 2.1.4: REPRESENTING STRINGS ==========\n");

    demonstrate_ascii_digits();
    demonstrate_string_null_terminator();
    demonstrate_string_variety();
    demonstrate_string_portability();
    show_ascii_table();

    return 0;
}

