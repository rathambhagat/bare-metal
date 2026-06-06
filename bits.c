/*Modern computers store and process information represented as two-valued
signals. These lowly binary digits, or bits, form the basis of the digital revolution.*/


/*Computer representations use a limited number of bits to encode a number,
and hence some operations can overflow when the results are too large to be rep
resented.*/ 
/* #include<stdio.h>
int main(){
  printf("%d",200*300*400*500);
  return 0;
} */
// When we complie the Above function we get a warning

/* bits.c: In function ‘main’:
bits.c:8:26: warning: integer overflow in expression of type ‘int’ results in ‘-884901888’ [-Woverflow]
    8 |   printf("%d",200*300*400*500);*/

// The Output of it is a negative number = -884901888
/*Word Size: Defines the nominal size of pointer data and dictates the maximum virtual address space.
A w-bit machine can access at most 2^w bytes of memory
Memory Limits: 32-bit systems are capped at 4 Gigabytes of virtual memory
64-bit systems expand this limit to 16 Exabytes
Program vs. Machine: A "32-bit program" or "64-bit program" refers to how the code is compiled, not the physical hardware.
64-bit machines are backward compatible and can seamlessly run 32-bit programs
C Data Type Byte Sizes (32-bit / 64-bit):
char: 1 byte (It is the only type not guaranteed to be signed by default; use signed char if needed)
short: 2 bytes
int: 4 bytes
long: 4 bytes / 8 bytes
Pointers (char *): 4 bytes / 8 bytes
float / double: 4 bytes / 8 bytes
ISO C99 Fixed-Size Types: To eliminate size ambiguity across different compilers and machines, C99 introduced exact-size data types like int32_t (exactly 4 bytes) and int64_t (exactly 8 bytes).
Common Portability Bug: Storing a memory pointer inside an int variable works on 32-bit systems but catastrophically truncates the data on 64-bit systems because the pointer size doubles to 8 bytes.*/

/* ==================== SECTION 2.1.3: ADDRESSING AND BYTE ORDERING ====================

KEY CONCEPT: Multi-byte Object Addressing
- Multi-byte objects (int, float, pointers) are stored as CONSECUTIVE BYTES in memory
- The ADDRESS of a multi-byte object = the LOWEST byte address it occupies
- Example: A 4-byte int at address 0x100 occupies bytes at: 0x100, 0x101, 0x102, 0x103

CRITICAL: Two Byte Ordering Conventions Exist
- These conventions determine HOW bytes are arranged in memory for multi-byte values
- Both are equally valid; choice depends on machine architecture

1. LITTLE ENDIAN (LSB First - Least Significant Byte comes first)
   - Lowest-order byte stored at LOWEST memory address
   - Lowest-order byte printed FIRST
   - Used by: Intel x86/x64 processors (most common today), ARM processors
   - Operating Systems using it: Windows, Linux on x86/x64, Android, iOS
   
   Example: Value 0x01234567 at address 0x100 in Little Endian:
   Address 0x100: 0x67 (lowest byte, least significant)
   Address 0x101: 0x45
   Address 0x102: 0x23
   Address 0x103: 0x01 (highest byte, most significant)

2. BIG ENDIAN (MSB First - Most Significant Byte comes first)
   - Highest-order (most significant) byte stored at LOWEST memory address
   - Most significant byte printed FIRST
   - Used by: IBM POWER processors, Oracle SPARC processors, Network protocols
   - Network applications use Big Endian as standard (called "Network Byte Order")
   
   Example: Value 0x01234567 at address 0x100 in Big Endian:
   Address 0x100: 0x01 (highest byte, most significant)
   Address 0x101: 0x23
   Address 0x102: 0x45
   Address 0x103: 0x67 (lowest byte, least significant)

COMPARISON TABLE:
Value = 0x01234567 at address 0x100
┌─────────────┬──────────────────────────┐
│ BIG ENDIAN  │ 01 23 45 67              │
│ LITTLE END. │ 67 45 23 01              │
└─────────────┴──────────────────────────┘

WHY Does Byte Ordering Matter? Three Critical Cases:

1. NETWORK COMMUNICATION
   - When little-endian machine sends data to big-endian machine (or vice versa), bytes appear reversed
   - Network programs must convert to/from "Network Byte Order" (Big Endian)
   - Libraries provide htonl() / ntohl() for automatic conversion

2. READING MACHINE-LEVEL CODE (Assembly/Disassembly)
   - When examining compiled code for x86/x64 (little-endian), bytes appear in reverse order
   - A 4-byte hex value 0x200b43 appears as "43 0b 20 00" in assembly output
   - This reversal is NORMAL for little-endian processors

3. TYPE CIRCUMVENTION (Casting/Unions)
   - Casting a pointer to a different type or using unions allows viewing same data as different type
   - Byte ordering becomes visible when interpreting the raw bytes
   - Example: Cast int pointer to byte pointer to inspect individual bytes
   - Common in system programming, though generally discouraged in application code

BI-ENDIAN PROCESSORS:
- Some modern chips (certain ARMs, MIPS) can operate in EITHER byte order
- Operating system selection determines which mode is used in practice
- Once OS boots, byte order is FIXED for that system

IMPORTANT: For Application Programmers
- Byte ordering is INVISIBLE to normal C/C++ code
- Programs produce IDENTICAL RESULTS on both architectures
- Only visible when: (1) Networking, (2) Inspecting raw bytes, (3) Type casting tricks
- Portability: Write code WITHOUT assuming specific byte order
  
USE CASES FOR BYTE MANIPULATION:
- Debugging network protocols
- Reading binary file formats
- Low-level hardware interaction
- System programming and optimization
- Detecting endianness of current system

DETECTING BYTE ORDER AT RUNTIME:
- Create known value (e.g., 0x01020304)
- Cast to byte pointer
- Check which byte is at lowest address
- If 0x04 at lowest address → Little Endian
- If 0x01 at lowest address → Big Endian

REAL-WORLD EXAMPLE:
On Intel x86-64 (Little Endian), value 12,345 = 0x00003039:
int: 39 30 00 00 (LSB first, reverse order)
float: 00 e4 40 46 (bytes also appear reversed)

On Sun SPARC (Big Endian), same values:
int: 00 00 30 39 (MSB first, natural order)
float: 46 40 e4 00 (bytes in natural order)

The ACTUAL BYTES of data are IDENTICAL, only their ORDER differs!

==================== END SECTION 2.1.3 ====================
*/

 
#include <stdio.h>
typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
 int i;
 for (i = 0; i < len; i++)
 printf(" %.2x", start[i]);
 printf("\n");
 }

void show_int(int x) {
 show_bytes((byte_pointer) &x, sizeof(int));
 }

void show_float(float x) {
 show_bytes((byte_pointer) &x, sizeof(float));
 }

void show_pointer(void *x) {
 show_bytes((byte_pointer) &x, sizeof(void *));
 }

/* ===== PRACTICAL EXAMPLES OF BYTE ORDERING AND ADDRESSING ===== */

/* Function to detect current system's byte order */
void detect_endianness() {
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

/* Demonstrate addressing of multi-byte objects */
void demonstrate_addressing() {
    int value = 0x12345678;
    byte_pointer ptr = (byte_pointer) &value;
    
    printf("\n--- ADDRESSING OF MULTI-BYTE OBJECTS ---\n");
    printf("Integer value: 0x%x\n", value);
    printf("Address of value: %p\n", (void*)&value);
    printf("Size: %zu bytes\n", sizeof(int));
    
    printf("\nByte-by-byte breakdown:\n");
    for (int i = 0; i < sizeof(int); i++) {
        printf("  Address %p: 0x%02x\n", (void*)(ptr + i), ptr[i]);
    }
}

/* Show byte representations of different data types */
void show_all_types() {
    printf("\n--- BYTE REPRESENTATION OF DIFFERENT TYPES ---\n");
    
    int int_val = 42;
    float float_val = 3.14f;
    double double_val = 3.14159;
    char *str_ptr = "hello";
    
    printf("int(42) bytes:        ");
    show_int(int_val);
    
    printf("float(3.14) bytes:    ");
    show_float(float_val);
    
    printf("pointer bytes:        ");
    show_pointer(str_ptr);
}

/* Demonstrate overflow and byte patterns */
void demonstrate_overflow() {
    printf("\n--- INTEGER OVERFLOW AND BYTE PATTERNS ---\n");
    
    int result = 200 * 300 * 400 * 500;
    printf("200 * 300 * 400 * 500 = %d\n", result);
    printf("Byte representation: ");
    show_int(result);
    printf("(Expected: ~26.8 billion, got negative due to 32-bit overflow)\n");
}

/* Compare byte ordering by printing same value as different types */
void compare_type_interpretations() {
    printf("\n--- SAME MEMORY, DIFFERENT INTERPRETATIONS ---\n");
    
    union {
        int int_val;
        float float_val;
        unsigned char bytes[4];
    } data;
    
    data.int_val = 12345;
    
    printf("As int (12345):      ");
    show_int(data.int_val);
    
    printf("As float equivalent: ");
    show_float(*(float*)&data.int_val);
    
    printf("Raw bytes:           ");
    show_bytes(data.bytes, sizeof(data.bytes));
}

/* Main function demonstrating all concepts */
int main() {
    printf("===== CSAPP SECTION 2.1.3: ADDRESSING AND BYTE ORDERING =====\n");
    
    detect_endianness();
    demonstrate_addressing();
    show_all_types();
    demonstrate_overflow();
    compare_type_interpretations();
    
    printf("\n===== SUMMARY =====\n");
    printf("1. Multi-byte objects use address of LOWEST byte\n");
    printf("2. Byte order depends on machine architecture\n");
    printf("3. Little Endian (Intel): LSB at lowest address\n");
    printf("4. Big Endian (SPARC): MSB at lowest address\n");
    printf("5. Applications rarely see byte ordering; it's transparent\n");
    printf("6. Only visible in networking, assembly, or type casting\n");
    
    return 0;
}

