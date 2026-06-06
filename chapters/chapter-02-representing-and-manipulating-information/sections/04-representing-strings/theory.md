/* ==================== SECTION 2.1.4: REPRESENTING STRINGS ====================

KEY CONCEPT: String Encoding in C
- A string in C is an ARRAY OF CHARACTERS terminated by NULL (value 0)
- Each character is encoded using ASCII (American Standard Code for Information Exchange)
- NULL terminator signals the END of the string (like stop sign)

ASCII CHARACTER ENCODING:
- ASCII uses ONE BYTE (8 bits) to represent each character
- Standard printable ASCII: 32 (space) to 126 (~)
- Control characters: 0-31 (including NULL at 0)
- Extended ASCII: 128-255

KEY ASCII VALUES FOR REFERENCE:
- '0' to '9' (digits):     0x30 to 0x39 (decimal 48-57)
- 'A' to 'Z' (uppercase):  0x41 to 0x5A (decimal 65-90)
- 'a' to 'z' (lowercase):  0x61 to 0x7A (decimal 97-122)
- NULL terminator:         0x00 (marks end of string)
- Space character:         0x20

IMPORTANT PATTERN: ASCII Digit Encoding
- The ASCII code for digit 'x' is 0x3x (where x is 0-9)
- Example: '0' = 0x30, '5' = 0x35, '9' = 0x39
- This makes it easy to convert ASCII digit to numeric value (just AND with 0x0F)

STRING EXAMPLE: "12345"
- Character '1' → 0x31 (ASCII 49)
- Character '2' → 0x32 (ASCII 50)
- Character '3' → 0x33 (ASCII 51)
- Character '4' → 0x34 (ASCII 52)
- Character '5' → 0x35 (ASCII 53)
- NULL terminator → 0x00 (marks end)
- Byte representation: 31 32 33 34 35 00

PLATFORM INDEPENDENCE OF TEXT DATA:
- Text strings are MORE PORTABLE than binary data
- Why? Because ASCII is a STANDARD across all systems
- Unlike binary data (which changes with byte ordering), strings are identical everywhere
- Little-endian Intel and big-endian SPARC produce the SAME byte sequence for "12345"
- This makes text format ideal for data exchange between different computer architectures

C STRING FUNCTIONS RELY ON NULL TERMINATOR:
- strlen(str) - counts chars until NULL is found, then returns count
- strcpy(dest, src) - copies chars until NULL is found
- strcmp(s1, s2) - compares chars until NULL is found
- printf("%s", str) - prints chars until NULL is found

IMPORTANT: String Length NOT Stored in C
- C strings DON'T store the length; they rely on NULL terminator
- No built-in length field like in Java or Python
- Programmer must ensure proper NULL termination
- Buffer overflow vulnerability: writing past end of string without NULL

NULL TERMINATOR IS CRITICAL:
- Forgetting NULL terminator causes undefined behavior
- Functions will read memory past intended string
- Common source of security vulnerabilities
- Always allocate 1 extra byte for NULL: char str[n+1] for n chars

UNICODE AND INTERNATIONAL TEXT:
- ASCII only supports English and basic symbols
- UTF-8 (Unicode Transformation Format, 8-bit) is modern standard
- UTF-8 is backward compatible: ASCII chars are same as UTF-8
- For international text: use wide characters (wchar_t) or UTF-8 strings
- Java uses Unicode natively; C requires special libraries

COMPARISON: Binary vs Text Data
Binary Data (like integers):
- Byte order MATTERS (endianness affects representation)
- Different on little-endian vs big-endian machines
- Not human-readable
- Efficient storage

Text Data (strings):
- Byte order DOESN'T matter
- Same on all machines
- Human-readable
- Slightly less efficient (multiple bytes per character)

PRACTICAL IMPLICATIONS:
- Store data in text format when portability is critical
- Use binary format only when efficiency is essential
- Network protocols use text (HTTP, FTP) or convert to network byte order
- Configuration files use text for human readability

MEMORY LAYOUT EXAMPLE: String "ABC\0"
Memory Address:  0x1000    0x1001    0x1002    0x1003
Content:         0x41      0x42      0x43      0x00
Character:       'A'       'B'       'C'       NULL

strlen("ABC") returns 3 (not counting the NULL terminator)
Memory used: 4 bytes (including NULL)

==================== END SECTION 2.1.4 ====================
*/
