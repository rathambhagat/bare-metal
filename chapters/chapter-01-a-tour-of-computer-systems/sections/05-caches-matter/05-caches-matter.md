# 1.5 Caches Matter

An important lesson from the `hello` example is that a system spends a lot of time **moving information from one place to another**:

- Machine instructions are originally stored on disk
- When the program is loaded, they are copied to main memory
- As the processor runs, instructions are copied from main memory into the processor
- The data string is copied from disk → main memory → display device

From a programmer's perspective, much of this copying is overhead that slows down the "real work." A major goal for system designers is to make these copy operations run as fast as possible.

## The Processor-Memory Gap

Due to physical laws:
- **Larger** storage devices are **slower** than smaller devices
- **Faster** devices are more **expensive** to build

| Comparison | Ratio |
|------------|-------|
| Disk size vs. main memory size | ~1,000× larger |
| Disk read time vs. memory read time | ~10,000,000× slower |
| Register file vs. main memory speed | ~100× faster |

Even more troublesome, as semiconductor technology progresses, the **processor-memory gap** continues to increase. It is easier and cheaper to make processors run faster than to make main memory run faster.

## Cache Memories

To deal with the processor-memory gap, system designers include smaller, faster storage devices called **cache memories** (or simply **caches**) that serve as temporary staging areas for information the processor is likely to need in the near future.

![Cache memories](./images/_page_12_Figure_1.jpeg)

**Figure 1.8 — Cache memories**

### L1 Cache
- Located on the processor chip
- Holds tens of thousands of bytes
- Can be accessed nearly as fast as the register file

### L2 Cache
- Larger (hundreds of thousands to millions of bytes)
- Connected to the processor by a special bus
- ~5× slower than L1, but still 5–10× faster than main memory

### L3 Cache (newer systems)
- A third level found in more powerful systems

Both L1 and L2 caches are implemented with a hardware technology known as **static random access memory (SRAM)**.

## The Principle of Locality

The idea behind caching is that a system can get the effect of both a very large memory and a very fast one by exploiting **locality** — the tendency for programs to access data and code in localized regions. By setting up caches to hold data that are likely to be accessed often, we can perform most memory operations using the fast caches.

> One of the most important lessons in this book: application programmers who are aware of cache memories can exploit them to improve the performance of their programs by an **order of magnitude**.
