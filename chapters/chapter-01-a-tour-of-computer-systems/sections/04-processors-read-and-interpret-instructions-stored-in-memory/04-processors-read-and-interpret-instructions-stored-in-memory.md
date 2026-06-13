# 1.4 Processors Read and Interpret Instructions Stored in Memory

At this point, our `hello.c` source program has been translated by the compilation system into an executable object file called `hello` that is stored on disk. To run the executable file on a Unix system, we type its name to an application program known as a **shell**:

```bash
linux> ./hello
hello, world
linux>
```

The shell is a command-line interpreter that prints a prompt, waits for you to type a command line, and then performs the command. If the first word of the command line does not correspond to a built-in shell command, the shell assumes it is the name of an executable file that it should load and run.

## 1.4.1 Hardware Organization of a System

![Hardware organization of a typical system](./images/_page_7_Figure_2.jpeg)

**Figure 1.4 — Hardware organization of a typical system.** CPU: central processing unit, ALU: arithmetic/logic unit, PC: program counter, USB: Universal Serial Bus.

### Buses

Running throughout the system is a collection of electrical conduits called **buses** that carry bytes of information back and forth between the components. Buses are typically designed to transfer fixed-size chunks of bytes known as **words**. The number of bytes in a word (the **word size**) is a fundamental system parameter. Most machines today have word sizes of either 4 bytes (32 bits) or 8 bytes (64 bits).

### I/O Devices

Input/output (I/O) devices are the system's connection to the external world. The example system has four I/O devices:
- **Keyboard and mouse** — for user input
- **Display** — for user output
- **Disk drive** — for long-term storage of data and programs

Each I/O device is connected to the I/O bus by either a **controller** (chip set in the device itself or on the motherboard) or an **adapter** (a card that plugs into a slot on the motherboard).

### Main Memory

The **main memory** is a temporary storage device that holds both a program and the data it manipulates while the processor is executing the program.

- **Physically:** Consists of **dynamic random access memory (DRAM)** chips
- **Logically:** Organized as a linear array of bytes, each with its own unique address (starting at zero)

Machine instructions can consist of a variable number of bytes. Data item sizes vary by type on an x86-64 machine running Linux:
| Type | Size |
|------|------|
| `short` | 2 bytes |
| `int`, `float` | 4 bytes |
| `long`, `double` | 8 bytes |

### Processor

The **central processing unit (CPU)**, or simply **processor**, is the engine that interprets (or **executes**) instructions stored in main memory. At its core is a word-size storage device (or **register**) called the **program counter (PC)**. At any point in time, the PC points at (contains the address of) some machine-language instruction in main memory.

From the time power is applied until it is shut off, the processor repeatedly:
1. Reads the instruction from memory pointed at by the PC
2. Interprets the bits in the instruction
3. Performs some simple operation dictated by the instruction
4. Updates the PC to point to the next instruction

#### Simple Operations the CPU Can Perform

| Operation | Description |
|-----------|-------------|
| **Load** | Copy a byte or word from main memory into a register |
| **Store** | Copy a byte or word from a register to main memory |
| **Operate** | Copy contents of two registers to the ALU, perform arithmetic, store result in a register |
| **Jump** | Extract a word from the instruction and copy it into the PC |

#### Instruction Set Architecture vs. Microarchitecture

- **Instruction set architecture (ISA):** Describes the effect of each machine-code instruction (the abstraction)
- **Microarchitecture:** Describes how the processor is actually implemented (the concrete implementation)

Modern processors use far more complex mechanisms than the simple sequential model to speed up execution.

## 1.4.2 Running the `hello` Program

### Step 1: Reading the Command

Initially, the shell program is executing its instructions, waiting for us to type a command. As we type `./hello` at the keyboard, the shell program reads each character into a register and then stores it in memory.

![Reading the hello command from the keyboard](./images/_page_10_Figure_1.jpeg)

**Figure 1.5 — Reading the hello command from the keyboard**

### Step 2: Loading the Executable

When we hit Enter, the shell knows we have finished typing the command. The shell loads the executable `hello` file by executing a sequence of instructions that copies the code and data from disk to main memory. Using a technique known as **direct memory access (DMA)**, the data travel directly from disk to main memory without passing through the processor.

![Loading the executable from disk into main memory](./images/_page_11_Figure_0.jpeg)

**Figure 1.6 — Loading the executable from disk into main memory**

### Step 3: Executing and Displaying

Once the code and data are loaded into memory, the processor begins executing the machine-language instructions in `hello`'s `main` routine. These instructions copy the bytes in the `"hello, world\n"` string from memory to the register file, and from there to the display device.

![Writing the output string from memory to the display](./images/_page_11_Figure_2.jpeg)

**Figure 1.7 — Writing the output string from memory to the display**
