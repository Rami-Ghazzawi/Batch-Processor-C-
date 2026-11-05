# Distributed Batch Processor

A C++ project exploring parallel and distributed batch processing.

**Current implementation:** Multithreaded batch processor running on a single machine.

**Goal:** Build a distributed coordinator-worker system using TCP sockets.

**Status:** Work in Progress 🚧

## Technologies

- C++17
- Multithreading
- Atomic Operations
- TCP Sockets (planned)
- Linux

## Current Features

- [x] Single-process batch processing
- [x] Multithreaded job processing
- [x] Parallel execution using multiple threads
- [x] Performance benchmarking

## Performance Benchmark

8 jobs on a system with 12 logical CPUs:

| Threads | Execution Time |
|---|---:|
| 1 | 1.30 s |
| 8 | 0.37 s |

**Speedup: 3.5x**

The performance is affected by workload distribution and load imbalance.

## Job Input Format

Jobs are provided through `jobs.txt`.

Each line contains:
```
text
id N
```

Negative values are rejected.

## Build & Run

Compile:

```bash
g++ -std=c++17 -O2 -pthread parallel.cpp -o parallel
```

Run:

```bash
./parallel
```

## Roadmap

- [ ] Coordinator-worker architecture
- [ ] Distributed job execution over TCP
- [ ] Job state management
- [ ] Failure handling and retries
- [ ] Distributed performance benchmarking

---

*This project is under active development. Features and documentation will evolve as development progresses.*
