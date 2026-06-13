# 1.6 Storage Devices Form a Hierarchy

The notion of inserting a smaller, faster storage device between the processor and a larger, slower device turns out to be a general idea. Storage devices in every computer system are organized as a **memory hierarchy**.

![An example of a memory hierarchy](./images/_page_13_Figure_0.jpeg)

**Figure 1.9 — An example of a memory hierarchy**

## The Hierarchy Levels

| Level | Device | Technology |
|-------|--------|------------|
| L0 | Registers | CPU registers |
| L1 | L1 cache (SRAM) | On-chip cache |
| L2 | L2 cache (SRAM) | On-chip or near-chip cache |
| L3 | L3 cache (SRAM) | Shared cache |
| L4 | Main memory (DRAM) | Primary storage |
| L5 | Local secondary storage (disk/SSD) | Persistent storage |
| L6 | Remote secondary storage (distributed) | Network storage |

As we move from the top of the hierarchy to the bottom:
- Devices become **slower**
- Devices become **larger** in capacity
- Devices become **less costly** per byte

## The Cache Concept at Every Level

The main idea of a memory hierarchy is that **storage at one level serves as a cache for storage at the next lower level**:

- Register file is a cache for L1 cache
- L1 cache is a cache for L2 cache
- L2 cache is a cache for L3 cache
- L3 cache is a cache for main memory
- Main memory is a cache for disk
- On networked systems with distributed file systems, the local disk serves as a cache for data stored on remote disks

Just as programmers can exploit knowledge of caches to improve performance, they can exploit their understanding of the entire memory hierarchy.
