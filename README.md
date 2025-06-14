# STL_From_Scratch 🚀

A hand-crafted C++ Standard Template Library clone built from the ground up to demonstrate deep understanding of C++ internals including **templates**, **manual memory management**, **move semantics**, **RTTI**, and **runtime polymorphism**.

## 📦 Data Structures Implemented
- `Vector<T>` – Dynamic array with custom memory management
- `Map<K, V>` – Key-value store using self-balancing BST
- `Set<T>` – Sorted unique container
- `Stack<T>` – LIFO structure using Vector
- `Queue<T>` – FIFO structure using Linked List
- `LinkedList<T>` – Doubly linked list with indexing support

## 🧠 Core C++ Concepts Demonstrated
- Templates & Generic Programming  
- Move Semantics & Copy Elision  
- Runtime Polymorphism (vtable/vptr)  
- RTTI-Based Casting  
- Manual Memory Management (including internal padding)
- Clean modular architecture

## 🛠 How to Build and Run (Using CMake)

### 🔧 Requirements
- C++ compiler (GCC, Clang, or MSVC)
- [CMake](https://cmake.org/download/) (≥ 3.10)
- [MinGW](https://www.mingw-w64.org/) (on Windows) or equivalent toolchain

### 📂 Directory Structure

STL_From_Scratch/
├── include/ # Header files (Vector, Map, etc.)
├── src/ # Main driver (main.cpp)
├── build/ # Build directory (created manually)
├── CMakeLists.txt # CMake config
└── README.md # Project info


### ⚙️ Build Instructions

```bash
# Step 1: Clone or download this repo
cd STL_From_Scratch

# Step 2: Create and enter build directory
mkdir build && cd build

# Step 3: Generate build files using CMake
cmake .. -G "MinGW Makefiles"   # or just cmake .. if using Linux/macOS

# Step 4: Compile
mingw32-make   # or make on Linux/macOS

# Step 5: Run the binary
./main.exe     # or ./main on Linux/macOS

Pull requests and forks are welcome.
For questions or feedback, feel free to open an issue or drop a message.

