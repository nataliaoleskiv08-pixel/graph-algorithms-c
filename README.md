# graph-algorithms-c
Classic graph algorithms implemented in C (Kruskal's MST, Prufer code decoder)
# 🧩 Graph Algorithms in C

A collection of classic graph theory and discrete mathematics algorithms implemented in pure C. Developed as part of university coursework in Software Engineering.

---

## 📂 Included Projects

### 1. Kruskal's Algorithm (`kruskal.c`)
* **Description:** Finds the Minimum Spanning Tree (MST) in a weighted connected graph.
* **Key Concepts:** Disjoint Set Union (DSU) with path compression and union by rank, edge sorting, matrix representation.
* **Features:** Supports both a ready-made test matrix ($5 \times 5$) and custom user input with validation.

### 2. Prüfer Code Reconstruction (`prufer.c`)
* **Description:** Reconstructs a tree structure from a given Prüfer sequence.
* **Key Concepts:** Dynamic memory allocation (`malloc`, `calloc`, `free`), degree tracking of vertices, edge list generation.
* **Features:** Interactive menu to load a pre-defined sequence or enter custom vertex degrees and code elements.

---

## 🚀 How to Run

1. Open **Microsoft Visual Studio** (or any C compiler like GCC).
2. Create a new empty project or console application.
3. Add either `kruskal.c` or `prufer.c` to your project source files.
4. Build and run (`Ctrl + F5`).
