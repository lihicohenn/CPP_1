#include <iostream>
#include "Graph.hpp"
#include "Queue.hpp"
#include "Algorithms.hpp"
#include "PriorityQueue.hpp"

using namespace graph;


int main() {

    Graph g(5);
    g.addEdge(0,1,10);
    g.addEdge(0,4,10);
    g.addEdge(1,2,20);
    g.addEdge(1,3,40);
    g.addEdge(2,3,60);

    g.print_graph();

    Algorithms algo;
    //Graph bfsTree = algo.bfs(g, 0); 
    //Graph dfsTree = algo.dfs(g, 0);

    Graph kruskalTree = algo.kruskal(g);

    kruskalTree.print_graph();
    
    }
