# 🧠 Custom Memory Allocator in C

This project implements a **simple, custom memory allocator in C** designed for **64-bit systems**. It mimics basic heap allocation functionality (similar to `malloc` and `free`) within a **manually allocated 1GB memory space**.

It supports:
- Block-based allocation
- Manual deallocation
- Word-aligned memory (8-byte words)
- Basic memory clearing (`zero`)
- Heap visualization for debugging

---

## 📦 Features
- ✅ Manual memory allocation & deallocation  
- ✅ Fixed-size heap of **1GB** (allocated via assembly)  
- ✅ Word-based memory management (8 bytes per word)  
- ✅ Block splitting to minimize waste  
- ✅ Heap visualization to see allocations  
- ✅ Simple, menu-based test interface in C  

---

## 📂 Project Structure

```plaintext
.
├── allocater.c        # Core allocator implementation
├── allocater.h        # Allocator header definitions
├── heap.asm           # Assembly code allocating 1GB memory
├── Makefile           # (Optional) Build instructions
└── README.md          # Project documentation

```

---

## 🧠 How It Works
- The memory allocator works on **8-byte words**.
- Memory blocks have a **header** containing:
  - Block size (`w` in words)
  - Allocation status (`alloced`)
- Memory operations:
  - **Allocate**: Finds free block large enough and marks it allocated.
  - **Free**: Clears memory and marks block as free.
  - **Split blocks** if a larger-than-needed block is found.

---


## 🏗️ Assembly File: heap.asm

- A custom assembly file is used to reserve a 1GB .bss section:
- This reserved memory acts as the program’s heap space.


## ⚙️ Build & Run
### Build (Example with NASM and GCC):

```bash
nasm -f elf64 heap.asm -o heap.o
gcc -o allocator allocater.c heap.o
```
Or, using a Makefile:
```
make
```
Run:
```
./allocator
```
## 🧪 Menu Interface Example
```
1. Allocate 
2. Destroy
3. Quit
```
You can:

    Allocate memory (input bytes)

    Free memory by index

    Visualize heap allocations after each operation

🔥 Example Output
```
Alloc 1 = 2 alloced words
Alloc 2 = 500 alloced words
Alloc 3 = 1 alloced words
```
---

## 🪄 Known Limitations

    No block coalescing after free (no merging of adjacent free blocks yet)

    No realloc support

    Fixed 1GB heap space (no dynamic resizing)

    No thread-safety (single-threaded)



## 🚀 Possible Improvements

    Implement block coalescing after free

    Add support for realloc

    Better error handling

    Optimize allocation search (iterative or free list)

---

## 📝 License

This project is open-source and licensed under the MIT License.
## 🙌 Contributing

Pull requests and suggestions are welcome!
