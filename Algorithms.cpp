//lihicohen1123@gmail.com
#include "Graph.hpp"
#include "Queue.hpp"
#include "Algorithms.hpp"
#include "PriorityQueue.hpp"
#include "UnionFind.hpp"
#include <limits>
#include <iostream>

namespace graph{
    
    Algorithms::Algorithms(){}
    Algorithms::~Algorithms(){}

    Graph Algorithms::bfs(Graph& graph, int src) {
            
    if (src < 0 || src >= graph.getNumVertex()) {
    throw "Invalid source vertex";}

    enum Color { WHITE, GREY, BLACK };
    int num = graph.getNumVertex();
    Color color [num];
    int d[num]; // Array of distances from each vertex to the source
    int p[num]; // Array of predecessors for each vertex

    // Initialize color, distance, and predecessor arrays, doesn not found yet path
    for (int i = 0; i < num; ++i) {
        color[i] = WHITE;
        d[i] = std::numeric_limits<int>::max(); 
        p[i] = -1; 
    }
    // Path from s to himself
    color[src] = GREY;
    d[src] = 0;
    p[src] = -1;

    Queue q;
    q.enqueue(src);
    
    while (!q.isEmpty()) {
        int u = q.dequeue().data; // Dequeue the front vertex
        // Check if the vertex is valid
        if (u < 0 || u >= num) {
        throw "Invalid vertex dequeued from queue";}

        // Process all neighbors of u
        for (int i = 0; i < graph.getNeighborCount(u); ++i) {
            Edge e = graph.getNeighbor(u, i);
            int v = e.dest;
            if (color[v] == WHITE) {
                color[v] = GREY;
                d[v] = d[u] + 1;
                p[v] = u;
                q.enqueue(v);
            }
        }

        color[u] = BLACK;
    }
    // Create a new graph to represent the BFS tree
    Graph tree(num);
    for (int v = 0; v < num; ++v) {
        if (p[v] != -1) {
            tree.addEdge(v, p[v]); 
        }
    }

    return tree;
}

// DFS algorithm
    // This function performs a depth-first search on the graph starting from the source vertex
    // It returns a tree representing the DFS traversal
    // The function uses recursion to visit each vertex and its neighbors
    // It also keeps track of the discovery and finishing times of each vertex
Graph Algorithms::dfs(Graph& graph, int src){
    if (src < 0 || src >= graph.getNumVertex()) {
        throw std::runtime_error("Invalid source vertex");
    }
    // Initialize color, parent, discovery time, and finishing time arrays
    int numVer = graph.getNumVertex();
    Color color[numVer];
    int p[numVer]; 
    int time;
    int d[numVer];
    int f[numVer]; 

    for (int i=0; i<numVer; i++){
        color[i] = WHITE;
        p[i] = -1;
    }

    time = 0;
    for (int i=0; i<numVer; i++){
        if (color[i] == WHITE){
            dfs_visit(graph,i,color, p,d,f,time); // visit the vertex
        }
    }
 
    // Create a new graph to represent the DFS tree
    Graph tree(numVer);
    for (int v = 0; v < numVer; ++v) {
        if (p[v] != -1) {
            tree.addEdge(v, p[v]); // add the edge to the tree(tree edges)
        }
    }

    return tree;
    

}

// This function is a helper function for the DFS algorithm
void Algorithms::dfs_visit(Graph& graph, int src , Color* color, int* p, int* d, int* f, int& time){

    color[src] = GREY; 
    time++;
    d[src] = time;
    
    int n = graph.getNeighborCount(src);
    for (int i = 0; i < n; i++) {
        Edge e = graph.getNeighbor(src, i);
        int v = e.dest;
        if (color[v] == WHITE) {
            p[v] = src;
            dfs_visit(graph, v, color, p, d, f, time);
        }
    }

    color[src] = BLACK;
    time++;
    f[src] = time;
}


    // This function implements Dijkstra's algorithm to find the shortest path from a source vertex to all other vertices in the graph
    Graph Algorithms::dijkstra(Graph& graph, int src) {
        if (src < 0 || src >= graph.getNumVertex()) {
            throw "Invalid source vertex";
        }
        int numVer = graph.getNumVertex();
        int d[numVer];
        int p[numVer];

        for (int i = 0; i < numVer; i++) {
            d[i] = std::numeric_limits<int>::max();
            p[i] = -1;
        }

        d[src] = 0;
        PriorityQueue pq(numVer); // Create a priority queue

        for (int i = 0; i < numVer; i++) {
            pq.insert(i, d[i]); // Insert all vertices into the priority queue
        }

        while (!pq.isEmpty()) {
            PQNode u = pq.extractMin(); // Extract the vertex with the smallest distance
            relax(u.value, graph, d, p, pq); // Relax all neighbors of u
        }

        // Create a new graph to represent the shortest path tree
        Graph tree(numVer);
        for (int i = 0; i < numVer; i++) {
            if (p[i] != -1) {
                int weight = d[i] - d[p[i]];
                tree.addEdge(i, p[i], weight);
            }
        }

        return tree;
    }

    // This function relaxes the edges of a vertex u
    void Algorithms::relax(int u, Graph& graph, int d[], int p[], PriorityQueue& pq) {
    int neighborCount = graph.getNeighborCount(u);

    for (int i = 0; i < neighborCount; i++) {
        Edge e = graph.getNeighbor(u, i);   
        int v = e.dest;
        int weight = e.weight;

        if (v < 0 || v >= graph.getNumVertex()) {
            throw std::out_of_range("Invalid vertex index in relax()");
        }
        // Relax
        if (d[u] + weight < d[v]) {
            d[v] = d[u] + weight;
            p[v] = u;
            pq.decreaseKey(v, d[v]);
            }
        }
    }

   
    Graph Algorithms::kruskal(Graph& graph) {

    if (graph.getNumVertex()==0 || graph.getNumEdges()==0) {
        throw std::runtime_error("Graph is empty");
    }

    if (!graph.isConnected()) {
        throw std::runtime_error("Graph is not connected");
    }


    int n = graph.getNumVertex();
    Graph A(n);  // A ← ∅

    UnionFind S(n);  // Union-Find
    for (int i = 0; i < n; ++i) {
        S.create(i);  // {v}
    }

    int m = graph.getNumEdges();
    Edge* edges = new Edge[m];
    int* srcs = new int[m]; 

    int index = 0;
    for (int src = 0; src < n; ++src) {
        int deg = graph.getNeighborCount(src);
        for (int i = 0; i < deg; ++i) {
            Edge e = graph.getNeighbor(src, i);
            int dest = e.dest;
            if (src < dest) { // avoid duplicates
                edges[index] = e;
                srcs[index] = src;
                index++;
            }
        }
    }

    // bubble sort for weight
    for (int i = 0; i < index - 1; ++i) {
        for (int j = 0; j < index - i - 1; ++j) {
            if (edges[j].weight > edges[j + 1].weight) {
                swap(edges[j], edges[j + 1]);
                swap(srcs[j], srcs[j + 1]);
            }
        }
    }
    
    for (int i = 0; i < index; ++i) {
        int v = srcs[i];
        int w = edges[i].dest;

        if (S.find(S.getNode(v)) != S.find(S.getNode(w))) {
            A.addEdge(v, w, edges[i].weight);
            S.merge(S.getNode(v), S.getNode(w));
        }
    }

        delete[] edges;
        delete[] srcs;
        return A;
    }

    void Algorithms::swap(Edge& a, Edge& b) {
        Edge temp = a;
        a = b;
        b = temp;
    }

    void Algorithms::swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }


        Graph Algorithms::prim(Graph& graph) {
            
        if (graph.getNumVertex() == 0 || graph.getNumEdges() == 0) {
            throw std::runtime_error("Graph is empty");
            }

            if (!graph.isConnected()) {
                throw std::runtime_error("Graph is not connected");
            }
        
            
        int n = graph.getNumVertex();
        int key[n];
        int p[n];

        PriorityQueue pq(n);

        // Step 1: Initialization
        for (int i = 0; i < n; i++) {
            key[i] = std::numeric_limits<int>::max(); 
            p[i] = -1;
            pq.insert(i, key[i]);  // insert vertex with INF initially
        }

        int s = 0;
        key[s] = 0;
        pq.decreaseKey(s, 0);  // source starts with key 0

        // Step 2: Prim's main loop
        while (!pq.isEmpty()) {
            PQNode u = pq.extractMin();  // vertex with smallest key
            int uIndex = u.value;

            int deg = graph.getNeighborCount(uIndex);
            for (int i = 0; i < deg; i++) {
                Edge e = graph.getNeighbor(uIndex, i);
                int v = e.dest;
                int weight = e.weight;

                // If v is still in the queue and this edge is better
                int idx = pq.getIndex(v);
                if (idx != -1 && weight < key[v]) {
                    key[v] = weight;
                    p[v] = uIndex;
                    pq.decreaseKey(v, weight);
                }
            }
        }

        // Step 3: Build the MST
        Graph mst(n);
        for (int v = 0; v < n; v++) {
            if (p[v] != -1) {
                mst.addEdge(v, p[v], key[v]);  // or (p[v], v)
            }
        }

        return mst;
    }

}

