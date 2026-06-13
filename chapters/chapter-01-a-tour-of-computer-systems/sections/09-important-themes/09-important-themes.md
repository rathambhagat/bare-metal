# 1.9 Important Themes

A system is more than just hardware. It is a collection of intertwined hardware and systems software that must cooperate to run application programs. This section highlights several important concepts that cut across all aspects of computer systems.

## 1.9.1 Amdahl's Law

**Gene Amdahl**, one of the early pioneers in computing, made a simple but insightful observation about the effectiveness of improving the performance of one part of a system. This is known as **Amdahl's Law**.

### The Formula

When we speed up one part of a system, the effect on overall system performance depends on both:

- **α** (alpha) — the fraction of the original time consumed by the part being improved
- **k** — the speedup factor applied to that part (e.g., k = 3 means it runs 3× faster)

If the original execution time is **Tₒₗ**:

> Tₙₑ = (1 − α)Tₒₗ + (αTₒₗ)/k
> Tₙₑ = Tₒₗ[(1 − α) + α/k]

The overall **speedup S** is:

> **S = 1 / [(1 − α) + α/k]**

### Example

Consider a part of the system that initially consumed 60% of the time (α = 0.6) and is sped up by a factor of 3 (k = 3):

> S = 1 / [0.4 + 0.6/3]
> S = 1 / [0.4 + 0.2]
> S = 1 / 0.6
> **S = 1.67×**

Even though we made a substantial improvement to a major part of the system, the net speedup (1.67×) is significantly less than the speedup for that one part (3×). The key insight of Amdahl's Law: **to significantly speed up the entire system, we must improve the speed of a very large fraction of the overall system.**

### The Limit Case (k → ∞)

If we can speed up a fraction α of the system to the point where it takes negligible time:

> **S∞ = 1 / (1 − α)**

For example, if we can speed up 60% of the system to require close to no time:

> S∞ = 1 / 0.4 = 2.5×

This shows that even infinite speedup of 60% of the system gives only a 2.5× overall speedup.

---

### Aside: Expressing Relative Performance

The best way to express a performance improvement is as a ratio **Tₒₗ/Tₙₑ**, where Tₒₗ is the original time and Tₙₑ is the modified time. A number greater than 1.0 indicates improvement. We use the suffix '×' (e.g., "2.2×" is "2.2 times").

Percentages are more ambiguous: should it be 100·(Tₒₗ − Tₙₑ)/Tₙₑ or 100·(Tₒₗ − Tₙₑ)/Tₒₗ?

---

### Practice Problem 1.1

> You work as a truck driver carrying potatoes from Boise, Idaho to Minneapolis, Minnesota — a distance of 2,500 km. You average 100 km/hr, requiring 25 hours for the trip.

#### Part A

You hear Montana has abolished its speed limit. Montana constitutes 1,500 km of the trip. Your truck can travel at 150 km/hr in Montana. What is the speedup for the trip?

**Solution:**

Original time: 25 hours

Part outside Montana: 1,000 km at 100 km/hr = **10 hours**

Part through Montana:
- Original Montana time: 1,500 km / 100 km/hr = 15 hours
- New Montana time: 1,500 km / 150 km/hr = **10 hours**

In terms of Amdahl's Law:
- α = 0.6 (Montana was 15/25 = 60% of the trip)
- k = 1.5 (speed increased from 100 to 150 km/hr)

New total time = 10 + 10 = **20 hours**

> **Speedup = 25 / 20 = 1.25×**

#### Part B

You can buy a turbocharger. How fast must you travel through Montana to get an overall speedup of 1.67×?

**Solution:**

Required speedup S = 1.67×
Required new total time = 25 / 1.67 = **15 hours**

Parts outside Montana still require 10 hours, so Montana must take 5 hours.

> Required speed = 1,500 km / 5 hr = **300 km/hr**

Using Amdahl's Law formula:
> S = 1 / [(1 − α) + α/k]
> 1.67 = 1 / [(1 − 0.6) + 0.6/k]
> 0.4 + 0.6/k = 1 / 1.67 = 0.6
> 0.6/k = 0.2
> **k = 3**

So the Montana portion must be 3× faster, meaning 300 km/hr (100 × 3).

---

### Practice Problem 1.2

> A car company promises a 4× performance improvement in a new engine. Only 90% of the engine can be improved. How much (k) must this part be improved to meet the target?

**Solution:**

Given:
- S = 4 (overall target speedup)
- α = 0.9 (fraction that can be improved)

> S = 1 / [(1 − α) + α/k]
> 4 = 1 / [(1 − 0.9) + 0.9/k]
> 4 = 1 / [0.1 + 0.9/k]
> 0.1 + 0.9/k = 1/4 = 0.25
> 0.9/k = 0.15
> k = 0.9 / 0.15
> **k = 6**

The improved part must be **6× faster**.

---

## 1.9.2 Concurrency and Parallelism

Two constant forces drive improvements in computing: we want computers to do **more** and we want them to run **faster**. Both improve when the processor does more things at once.

- **Concurrency** — the general concept of a system with multiple, simultaneous activities
- **Parallelism** — the use of concurrency to make a system run faster

Parallelism can be exploited at multiple levels of abstraction:

### Thread-Level Concurrency

Building on the process abstraction, we can devise systems where multiple programs execute at the same time. With **threads**, we have multiple control flows executing within a single process.

**Uniprocessor systems** simulate concurrency by rapidly switching among processes (time-sharing).

**Multiprocessor systems** have multiple processors under a single operating system kernel.

![Categorizing different processor configurations](./images/_page_23_Figure_8.jpeg)

**Figure 1.16 — Categorizing different processor configurations**

#### Multi-Core Processors

Multi-core processors integrate several CPUs (called "cores") onto a single integrated-circuit chip.

![Multi-core processor organization](./images/_page_24_Figure_1.jpeg)

**Figure 1.17 — Multi-core processor organization**

The example shows four CPU cores, each with its own L1 and L2 caches. The L1 cache is split into two parts: one for instructions and one for data. Cores share higher levels of cache and the interface to main memory. Experts predict dozens, and ultimately hundreds, of cores on a single chip.

#### Hyperthreading (Simultaneous Multi-Threading)

**Hyperthreading** allows a single CPU to execute multiple flows of control. It involves multiple copies of some CPU hardware (program counters and register files) but only single copies of other parts (floating-point arithmetic units).

- Conventional processor: ~20,000 clock cycles to switch between threads
- Hyperthreaded processor: decides which thread to execute on a cycle-by-cycle basis
- Intel Core i7: each core can execute two threads, so a 4-core system runs 8 threads in parallel

#### Benefits of Multiprocessing

1. **Reduces the need to simulate concurrency** when performing multiple tasks
2. **Can run a single application program faster** if expressed in terms of multiple threads that can execute in parallel

### Instruction-Level Parallelism

At a much lower level, modern processors can execute **multiple instructions at one time**. 

- Early microprocessors (e.g., Intel 8086, 1978): 3–10 clock cycles per instruction
- Modern processors: 2–4 instructions per clock cycle
- Individual instructions: 20+ cycles from start to finish

Processors use **pipelining** — the actions required to execute an instruction are partitioned into different steps, and the processor hardware is organized as a series of stages. Each stage handles different parts of different instructions in parallel. A fairly simple hardware design can sustain close to 1 instruction per clock cycle.

**Superscalar processors** sustain execution rates faster than 1 instruction per cycle — most modern processors support this.

### Single-Instruction, Multiple-Data (SIMD) Parallelism

At the lowest level, many modern processors have special hardware allowing a **single instruction to cause multiple operations in parallel**.

- Recent Intel and AMD processors: instructions that can add 8 pairs of single-precision floats in parallel
- Primarily used for image, sound, and video data processing
- Some compilers can automatically extract SIMD parallelism from C programs
- More reliably achieved by using special **vector data types** supported in compilers like GCC

## 1.9.3 The Importance of Abstractions in Computer Systems

The use of **abstractions** is one of the most important concepts in computer science. A good abstraction provides a simple API that allows programmers to use code without delving into inner workings.

![Some abstractions provided by a computer system](./images/_page_26_Figure_2.jpeg)

**Figure 1.18 — Some abstractions provided by a computer system**

### Processor-Side Abstractions

The **instruction set architecture (ISA)** provides an abstraction of the actual processor hardware. With this abstraction:
- A machine-code program behaves as if executed on a processor performing one instruction at a time
- The underlying hardware is far more elaborate (multiple instructions in parallel)
- But it always remains consistent with the simple, sequential model
- Different processor implementations can execute the same machine code while offering different cost and performance

### Operating System Abstractions

| Abstraction | What It Abstracts |
|-------------|-------------------|
| **Files** | I/O devices |
| **Virtual memory** | Program memory (main memory + disk) |
| **Processes** | A running program (processor, memory, I/O) |
| **Virtual machine** | The entire computer (OS, processor, programs) |

The **virtual machine** abstraction, introduced by IBM in the 1960s, has become more prominent recently as a way to manage computers that must run programs designed for multiple operating systems (Windows, Mac OS X, Linux) or different versions of the same OS.
