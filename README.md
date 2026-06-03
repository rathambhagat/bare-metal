 # Bare Metal: Phase 1 (The C/C++ Systems Engineering Track)

A public log of my journey shattering the "Passive Learning Trap" and building unshakeable, low-level systems intuition. No tutorial purgatory, no hand-holding. This repository contains the raw code, intentional crashes, assembly analysis, and structural mechanics documented through aggressive, active experimentation.

The core rule of engagement for this repository: **Code to discover gaps, break things on purpose, read the runtime errors, and commit the proof.**

---

## 🛠️ Phase 1 Core Execution Roadmap

This track is executed in strict sequential order, moving from raw hardware primitives up to modern managed memory architectures:

1. **Compilation Pipeline & Machine-Level Architecture**
2. **Raw Pointer Mechanics & Memory Visualization**
3. **Advanced C Syntax & Architectural Scope**
4. **Advanced Structs & Custom Type Alignment**
5. **The Build, Safety & Inspection Toolchain**
6. **C++ Object Model & RAII Memory Management**
7. **Smart Pointers & Explicit Ownership Models**

---

## 🔬 Directory Structure & Contents

Each topic folder contains complete, compiling source files accompanied by localized deep-dives into memory behavior.

### `/01_machine_architecture`
* **Focus:** Preprocessor-to-linker flows, Two's Complement math boundaries, signed/unsigned overflow wrapping, and raw bitwise masking.
* **Artifacts:** Code exploring byte representation of primitives, integer saturation, and flag masks.

### `/02_pointer_mechanics`
* **Focus:** Pointer arithmetic scaling calculations, dereferencing behaviors, `void*` type erasure, pointer-to-pointer chains, and virtual memory layout mapping.
* **Artifacts:** Applications showcasing exact byte-stepping layouts across contiguous and dynamic blocks.

### `/03_advanced_c_syntax`
* **Focus:** Rigorous `const` correctness combinations, `static` vs automatic storage lifespans, `extern` translation unit linkage, variadic arguments, and function pointer abstractions.
* **Artifacts:** Code enforcing data mutability constraints and runtime callback mechanics.

### `/04_structs_and_alignment`
* **Focus:** Natural hardware padding bounds, explicit structure optimization, overriding alignments with `__attribute__((packed))`, tracking member byte layouts via `offsetof()`, and shared `union` spaces.
* **Artifacts:** Code mapping exact struct footprints before and after optimization.

### `/05_defensive_toolchain`
* **Focus:** Maximizing compiler intelligence flags, runtime sanitization instrumentation, low-level GDB backtracing, symbol table dumps, and Valgrind heap tracking diagnostics.
* **Artifacts:** Build scripts executing deep structural analysis tools alongside intentional memory faults.

### `/06_cpp_raii_memory`
* **Focus:** Transitioning to C++ object lifecycles, array/scalar allocation disparities, placement `new` operations, explicit RAII resource hooks, the Rule of 0/3/5, and move semantics.
* **Artifacts:** Bare-metal implementations tracking object construction, deep copying, and rvalue resource transfers.

### `/07_smart_pointers`
* **Focus:** Zero-overhead single ownership (`std::unique_ptr`), atomic reference-counted graphs (`std::shared_ptr`), cycle-breaking observers (`std::weak_ptr`), and exception-safe heap allocation pipelines.
* **Artifacts:** Implementations detailing exact runtime performance trade-offs and memory layout footprints of standard smart pointer wrappers.

---

## ⚙️ The Defensive Compilation Standard

All C/C++ applications in this repository are compiled with strict diagnostic and instrumentation flags to guarantee memory safety and architectural compliance:

```bash
# Pure C Verification
gcc -Wall -Wextra -g -O2 -std=c11 -fsanitize=address,undefined <file>.c -o <output>

# Modern C++ Verification
g++ -Wall -Wextra -g -O2 -std=c++17 -fsanitize=address,undefined <file>.cpp -o <output>

# Heap Leak Profile
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./<output>
