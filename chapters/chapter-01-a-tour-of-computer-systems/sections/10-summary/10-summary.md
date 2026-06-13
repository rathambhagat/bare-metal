# 1.10 Summary

A computer system consists of **hardware** and **systems software** that cooperate to run application programs.

## Key Concepts

**Information as Bits:**
Information inside a computer is represented as groups of bits that are interpreted in different ways depending on context.

**Program Translation:**
Programs begin as ASCII text and are translated by **compilers** and **linkers** into binary executable files.

**Processor Execution:**
Processors read and interpret binary instructions stored in main memory. The processor repeatedly fetches, decodes, and executes instructions pointed to by the program counter (PC).

**The Memory Hierarchy:**
Since computers spend most of their time copying data between memory, I/O devices, and CPU registers, storage devices are arranged in a hierarchy:

| Level | Device | Speed | Size |
|-------|--------|-------|------|
| L0 | Registers | Fastest | Smallest |
| L1 | L1 cache (SRAM) | ~1 cycle | Tens of KB |
| L2 | L2 cache (SRAM) | ~5 cycles | Hundreds of KB–MB |
| L3 | L3 cache (SRAM) | ~10–20 cycles | MB |
| L4 | Main memory (DRAM) | ~100 cycles | GB |
| L5 | Disk/SSD | ~10⁷ cycles | TB |

Higher levels serve as **caches** for lower levels. Programmers who understand and exploit the memory hierarchy can optimize program performance by an order of magnitude.

**Operating System Abstractions:**
The operating system kernel serves as an intermediary between the application and the hardware, providing three fundamental abstractions:

1. **Files** — abstractions for I/O devices
2. **Virtual memory** — an abstraction for both main memory and disks
3. **Processes** — abstractions for the processor, main memory, and I/O devices

**Networks:**
Networks provide ways for computer systems to communicate with one another. From the viewpoint of a particular system, a network is just another I/O device.

**Amdahl's Law:**
The speedup of a system is limited by the fraction of the system that can be improved. To significantly speed up the entire system, we must improve a very large fraction of it.

**Concurrency and Parallelism:**
Parallelism can be exploited at multiple levels:
- **Thread-level** — multiple cores and hyperthreading
- **Instruction-level** — pipelining and superscalar execution
- **SIMD** — single-instruction, multiple-data parallelism

**Abstractions:**
Abstractions hide complexity at every level — from the instruction set architecture (abstracting the processor) to files, virtual memory, processes, and virtual machines (abstracting the operating system and hardware).
