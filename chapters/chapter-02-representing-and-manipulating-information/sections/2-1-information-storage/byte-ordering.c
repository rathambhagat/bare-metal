#include <stdio.h>
#include <string.h>

typedef unsigned char *byte_pointer;

static void show_bytes(byte_pointer start, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

static void show_int(int x) {
    show_bytes((byte_pointer)&x, sizeof(int));
}

static void show_float(float x) {
    show_bytes((byte_pointer)&x, sizeof(float));
}

static void show_pointer(void *x) {
    show_bytes((byte_pointer)&x, sizeof(void *));
}

static void detect_endianness(void) {
    unsigned int test_value = 0x01020304;
    unsigned char *byte_ptr = (unsigned char *)&test_value;

    printf("\n--- DETECTING SYSTEM ENDIANNESS ---\n");
    printf("Test value: 0x01020304\n");
    printf("Byte at lowest address: 0x%02x\n", byte_ptr[0]);

    if (byte_ptr[0] == 0x04) {
        printf("System is: LITTLE ENDIAN (LSB first)\n");
    } else if (byte_ptr[0] == 0x01) {
        printf("System is: BIG ENDIAN (MSB first)\n");
    }
}

static void demonstrate_addressing(void) {
    int value = 0x12345678;
    byte_pointer ptr = (byte_pointer)&value;

    printf("\n--- ADDRESSING OF MULTI-BYTE OBJECTS ---\n");
    printf("Integer value: 0x%x\n", value);
    printf("Address of value: %p\n", (void *)&value);
    printf("Size: %zu bytes\n", sizeof(int));

    printf("\nByte-by-byte breakdown:\n");
    for (size_t i = 0; i < sizeof(int); i++) {
        printf("  Address %p: 0x%02x\n", (void *)(ptr + i), ptr[i]);
    }
}

static void show_all_types(void) {
    printf("\n--- BYTE REPRESENTATION OF DIFFERENT TYPES ---\n");

    int int_val = 42;
    float float_val = 3.14f;
    double double_val = 3.14159;
    char *str_ptr = "hello";

    printf("int(42) bytes:        ");
    show_int(int_val);

    printf("float(3.14) bytes:    ");
    show_float(float_val);

    printf("double(3.14159) bytes:");
    show_bytes((byte_pointer)&double_val, sizeof(double));

    printf("pointer bytes:        ");
    show_pointer(str_ptr);
}

static void demonstrate_overflow(void) {
    printf("\n--- INTEGER OVERFLOW AND BYTE PATTERNS ---\n");

    int a = 200;
    int b = 300;
    int c = 400;
    int d = 500;
    int result = a * b * c * d;
    printf("200 * 300 * 400 * 500 = %d\n", result);
    printf("Byte representation: ");
    show_int(result);
}

static void compare_type_interpretations(void) {
    printf("\n--- SAME MEMORY, DIFFERENT INTERPRETATIONS ---\n");

    union {
        int int_val;
        float float_val;
        unsigned char bytes[4];
    } data;

    data.int_val = 12345;
    float float_equiv;
    memcpy(&float_equiv, &data.int_val, sizeof(float_equiv));

    printf("As int (12345):      ");
    show_int(data.int_val);

    printf("Raw bytes:           ");
    show_bytes(data.bytes, sizeof(data.bytes));

    printf("As float equivalent:  ");
    show_float(float_equiv);
}

int main(void) {
    printf("===== CSAPP SECTION 2.1.3: ADDRESSING AND BYTE ORDERING =====\n");

    detect_endianness();
    demonstrate_addressing();
    show_all_types();
    demonstrate_overflow();
    compare_type_interpretations();

    return 0;
}
