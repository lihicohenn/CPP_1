//lihicohen1123@gmail.com

# Assignment 1 - Graph and Algorithms in c++

* **Run Example:**
```bash
make
./main
```
* **to compile the project and run the tests:**
```bash
make Test
./Test
```


* **Project stracture:**
```bash
├── CCP_files/          
│   ├── main.cpp
│   ├── Algorithms.cpp
|   ├── Graph.cpp
|   ├── PriorityQueue.cpp
|   ├── Queue.cpp
|   ├── test.cpp
|   └── UnionFind.cpp
├── HPP_files/        
│   ├── doctest.h
│   ├── Algorithms.hpp
│   ├── Edge.hpp
|   ├── Graph.hpp
|   ├── PriorityQueue.hpp
|   ├── Queue.hpp
|   └── UnionFind.hpp
├── Makefile       
└── README.md        
```

## General Explanation of the Code:
The main goal of the projects is to implement: 
1.Graph representation (undirected and weighted)
2.Breadth-First Search (BFS)
3.Depth-First Search (DFS)
4.Dijkstra’s Shortest Path Algorithm
5.Kruskal’s Minimum Spanning Tree (MST)
6.Prim’s Minimum Spanning Tree (MST)
Supporting by Data Structures such as:
 • PriorityQueue
 • UnionFind
 • Queue



### Details:

Graph
 Manages vertices and edges (undirected).
 Supports methods:
 1.addEdge, removeEdge
 2.getNeighbor, getNeighborCount
 3.getAllEdges, getNumEdges, getNumVertex
 4.findEdgeIndex, isConnected
 5.print_graph

            
Edge
 A struct that stores:
 1.dest — destination vertex
 2.weight — edge weight

Algorithms
 Implements:
 1.bfs -finds the shortest path from a source vertex
 2.dfs - performs depth-first traversal.
 3.dijkstra - computes shortest paths from a source using a priority queue.
 4.kruskal - constructs the Minimum Spanning Tree (MST) using the Union-Find
 5.prim - constructs the MST using a priority queue



Queue
 Methods:
 enqueue, dequeue, isEmpty

PriorityQueue
 A min-priority queue used in Dijkstra & Prim.
 Supports:
 insert, decreaseKey, extractMin, getIndex, isEmpty

UnionFind
 Disjoint set data structure for Kruskal’s algorithm.
 Supports:
 1.create, find, merge
 2.Prevents cycles in MST construction.


Testing
 All core functionality is tested using the Doctest framework.
 Tests include:
 1.Functional checks (e.g. BFS returns correct tree)
 2,Exception handling (e.g. out-of-range, duplicate edge)
 3.Edge cases (empty graphs, disconnected components)