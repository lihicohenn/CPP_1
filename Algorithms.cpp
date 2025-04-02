#include "Graph.hpp"
#include "Queue.hpp"
#include "Algorithms.hpp"
#include "PriorityQueue.hpp"
#include "UnionFind.hpp"
#define INF 1000000000
#include <iostream>

namespace graph{
    
    Algorithms::Algorithms(){
        std::cout << "Algorithms constructor called" << std::endl;
    }
    Algorithms::~Algorithms(){
        std::cout << "Algorithms destructor called" << std::endl;
    }

    Graph Algorithms::bfs(Graph& graph, int src) {
            
    if (src < 0 || src >= graph.getNumVertex()) {
    throw "Invalid source vertex";}

    enum Color { WHITE, GREY, BLACK };
    int num = graph.getNumVertex();
    Color color [num];
    int d[num];
    int p[num];

    for (int i = 0; i < num; ++i) {
        color[i] = WHITE;
        d[i] = INF;
        p[i] = -1; 
    }

    color[src] = GREY;
    d[src] = 0;
    p[src] = -1;

    Queue q;
    q.enqueue(src);

    while (!q.isEmpty()) {
        int u = q.dequeue().data;
        if (u < 0 || u >= num) {
        throw "Invalid vertex dequeued from queue";}


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

    Graph tree(num);
    for (int v = 0; v < num; ++v) {
        if (p[v] != -1) {
            tree.addEdge(v, p[v]); 
        }
    }

    return tree;
}

Graph Algorithms::dfs(Graph& graph, int src){
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
            dfs_visit(graph,i,color, p,d,f,time);
        }
    }

    Graph tree(numVer);
    for (int v = 0; v < numVer; ++v) {
        if (p[v] != -1) {
            tree.addEdge(v, p[v]); // או tree.addEdge(p[v], v)
        }
    }

    return tree;
    

}


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



    Graph Algorithms::dijkstra(Graph& graph, int src) {
        int numVer = graph.getNumVertex();
        int d[numVer];
        int p[numVer];

        for (int i = 0; i < numVer; i++) {
            d[i] = INF;
            p[i] = -1;
        }

        d[src] = 0;
        PriorityQueue pq(numVer);

        for (int i = 0; i < numVer; i++) {
            pq.insert(i, d[i]);
        }

        while (!pq.isEmpty()) {
            PQNode u = pq.ExtractMin();
            relax(u.value, graph, d, p, pq); 
        }

        Graph tree(numVer);
        for (int i = 0; i < numVer; i++) {
            if (p[i] != -1) {
                int weight = d[i] - d[p[i]];
                tree.addEdge(i, p[i], weight);
            }
        }

        return tree;
    }

    void Algorithms::relax(int u, Graph& graph, int d[], int p[], PriorityQueue& pq) {
    int neighborCount = graph.getNeighborCount(u);

    for (int i = 0; i < neighborCount; i++) {
        Edge e = graph.getNeighbor(u, i);   
        int v = e.dest;
        int weight = e.weight;

        if (v < 0 || v >= graph.getNumVertex()) {
            throw std::out_of_range("Invalid vertex index in relax()");
        }

        if (d[u] + weight < d[v]) {
            d[v] = d[u] + weight;
            p[v] = u;
            pq.DecreaseKey(v, d[v]);
            }
        }
    }

   
    Graph Algorithms::kruskal(Graph& graph) {
    int n = graph.getNumVertex();
    Graph A(n);  // A ← ∅

    UnionFind S(n);  // Union-Find
    for (int i = 0; i < n; ++i) {
        S.create(i);  // {v}
    }

    int m = graph.getNumEdges();
    Edge* edges = new Edge[m];
    int* srcs = new int[m];  // כאן נשמור את ה־src של כל קשת

    // נבנה edges[] ו־srcs[] בלולאה משלנו
    int index = 0;
    for (int src = 0; src < n; ++src) {
        int deg = graph.getNeighborCount(src);
        for (int i = 0; i < deg; ++i) {
            Edge e = graph.getNeighbor(src, i);
            int dest = e.dest;
            if (src < dest) { // הימנעות מקשתות כפולות
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
    



}


}



            





