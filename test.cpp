#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
// #include <doctest/doctest.h>
#include "Graph.hpp"
#include "Algorithms.hpp"
#include "UnionFind.hpp"
#include "Queue.hpp"
#include "PriorityQueue.hpp"
using namespace graph;

TEST_CASE("Graph testing"){
    Graph g(4);
    g.addEdge(0,1,5);
    g.addEdge(1,3,10);
    g.addEdge(3,2,8);

    CHECK(g.getNeighborCount(1) == 2);
    CHECK(g.getNeighborCount(0) == 1);
    CHECK(g.getNeighbor(0, 0).dest == 1);



}

