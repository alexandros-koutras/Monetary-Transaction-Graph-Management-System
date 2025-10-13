# Monetary-Transaction-Graph-Management-System


---


## 💡 Overview

This project is a command-line application developed in C for the Operating Systems course at the University of Athens, Department of Informatics and Telecommunications.

The primary goal of the project is to manage and monitor financial transfers between users by implementing a dynamic directed multi-graph data structure. This graph structure provides a mechanism to monitor the movement of funds and trace the diffusion of transfers. The Nodes represent users or bank accounts and the Edges represent directed money transfers between accounts, carrying information about amount and date.

The project emphasizes strong C programming practices, modularity, dynamic memory management, and efficient, constant-time (O(1)) node lookup with the use of a hash table.


---


## ⚙️ Features

- **Dynamic Directed Multi-Graph**: Implemented in C. The structure must be able to grow without static size limits to accommodate an       
    unknown number of nodes (accounts) and edges (transactions).
- **Weighted Edges (Transactions)**: Each directed edge is weighted by the total transfer amount and the date of the transaction. Multiple
    edges can exist between any two nodes.
- **Hash Table Lookup**:  Utilizes an additional auxiliary structure for O(1) average-case access to a specific account/user by ID.
- **Modular Design**: The source code consists of at least two, but preferably more, distinct files, using separate compilation via a
    Makefile.
- **Memory Management**: Full, gradual, and controlled memory deallocation upon program exit.
- **Runtime Commands**:
    - i / insert —— Insert one or more new nodes (accounts).
    - in / insert2 —— Insert a new weighted edge (transfer) between two nodes.
    - d / delete —— Delete a node and all its incoming/outgoing edges.
    - del / delete2	—— Delete a single edge between two nodes.
    - m / modify —— Modify the amount and date of a specific transaction (edge).
    - f / find —— Display all outgoing transactions for a node.
    - r / receiving	—— Display all incoming transactions for a node.
    - c / circlefind —— Find and display all simple cycles involving a specific node.
    - fi / findcircles —— Find cycles involving a node where every edge has a minimum sum of k.
    - t / traceflow —— Find all flow paths starting from a node, up to a maximum path length (depth) of m edges.
    - co / connected —— Identify if a path exists between node Ni and node Nj and print the path.
    - e / exit —— Terminate the program, save the graph state to the output file, and free all dynamically allocated memory.


---


## 🧰 Technologies Used

- **C Language**
- **Makefile** for build automation
- **Valgrind** for memory checking
- **Separate compilation** (headers + multiple `.c` files)


---


## 🧑‍💻 How to Build and Run

### 1. Clone the repository
git clone https://github.com/alexandros-koutras/Monetary-Transaction-Graph-Management-System  
cd Monetary-Transaction-Graph-Management-System

### 2. Compile and run
make run


---


## 📂 Project Structure

Monetary-Transaction-Graph-Management-System/  
├── ADTs/           # Abstract Data Type implementations (e.g., Hash Table, Graph Node, Linked List)  
├── data/           # # Example initialisation data files  
├── include/        # Header files (.h) for all ADTs and module interfaces  
├── modules/        # Core application logic and command handlers  
├── Makefile        # Build file for separate compilation  
└── README.md       # Project documentation  
