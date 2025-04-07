//lihicohen1123@gmail.com
#include <iostream>
#include "Graph.hpp"
#include "Queue.hpp"
#include "Algorithms.hpp"
#include "PriorityQueue.hpp"

using namespace graph;
using namespace std;

int main() {
    Graph g(6);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 2, 5);
    g.addEdge(1, 3, 10);
    g.addEdge(2, 4, 3);
    g.addEdge(4, 3, 4);
    g.addEdge(3, 5, 11);

    cout << "Original graph:" << endl;
    g.print_graph();

    Algorithms algo;

    // BFS
    cout << "\nBFS Tree from vertex 0:" << endl;
    Graph bfsTree = algo.bfs(g, 0);
    bfsTree.print_graph();

    // DFS
    cout << "\nDFS Tree from vertex 0:" << endl;
    Graph dfsTree = algo.dfs(g, 0);
    dfsTree.print_graph();

    // Dijkstra
    cout << "\nDijkstra Tree from vertex 0:" << endl;
    Graph dijkstraTree = algo.dijkstra(g, 0);
    dijkstraTree.print_graph();

    // Kruskal
    cout << "\nKruskal MST:" << endl;
    Graph kruskalMST = algo.kruskal(g);
    kruskalMST.print_graph();

    // Prim
    cout << "\nPrim MST:" << endl;
    Graph primMST = algo.prim(g);
    primMST.print_graph();

    return 0;
}