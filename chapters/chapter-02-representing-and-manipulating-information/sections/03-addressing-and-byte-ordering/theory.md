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
