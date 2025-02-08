# OS Multithreading & Multiprocessing Assignments

This repository contains assignments related to multithreading and multiprocessing concepts in operating systems. The assignments cover topics such as:

- **Heap Search Optimization** using multiple threads
- **Multi-threaded Directory Copy** (`cp -R` implementation)
- **Multi-process Download Manager**
- **Automated Compilation and Execution**
- **Stack Memory Handling**

## 📂 Project Structure
```
.
├── Heap_Search/                # Searching elements in a heap using threads
├── MultiThreaded_Copy/         # Custom implementation of `cp -R`
├── MultiProcess_Download/      # Parallel download manager using `curl`
├── Auto_Compile_Run/          # Automating compilation & execution
├── Stack_Memory/              # Managing stack memory limits
└── README.md                  # This file
```

## 📌 Assignment Descriptions

### Q1: Heap Search Optimization (25 points)
Performs heap search using multithreading and multiprocessing to optimize search time. The task involves implementing a parallelized approach to checking if an element exists in a heap.

### Q2: Multi-threaded `cp -R` Implementation (25 points)
Reimplements the `cp -R` command using multithreading to improve file copy performance in Linux. This involves reading directories using `dirent.h` and handling file operations concurrently.

### Q3: Multi-process Download Manager (25 points)
Develops a parallel file downloader using multiple processes. It utilizes `curl/curl.h` to handle multiple file downloads simultaneously, preventing a single slow file from blocking the queue.

### Q4: Automated Compilation & Execution (25 points)
Creates a script to automatically compile and execute a C program in a single step, instead of manually running `gcc` and then executing the output binary.

### Q5: Stack Memory Handling (10 bonus points)
Implements a program that takes `n` numbers from the user and sums them, ensuring that stack memory constraints are handled properly.
