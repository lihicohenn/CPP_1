//lihicohen1123@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Graph.hpp"
#include "Algorithms.hpp"
#include "UnionFind.hpp"
#include "Queue.hpp"
#include "PriorityQueue.hpp"
using namespace graph;

TEST_CASE("Graph Test") {
    Graph g(4);
    g.addEdge(0,1,5);
    g.addEdge(1,3,10);
    g.addEdge(3,2,8);

    CHECK(g.getNumVertex() == 4);
    CHECK(g.getNeighborCount(1) == 2);
    CHECK(g.getNeighborCount(0) == 1);
    CHECK(g.getNeighbor(0, 0).dest == 1);
    CHECK(g.findEdgeIndex(1, 3) != -1);

    g.removeEdge(0,1);
    CHECK(g.getNeighborCount(0) == 0);
    CHECK(g.findEdgeIndex(0, 1) == -1);

    CHECK_THROWS_WITH(g.addEdge(-1, 2), "Invalid vertex index");
    CHECK_THROWS_WITH(g.getNeighbor(10, 0), "Invalid vertex index");
    CHECK_THROWS_WITH(g.removeEdge(0, 2), "Edge does not exist");

    CHECK(g.getNumEdges() == 2);

    Edge* arr = new Edge[g.getNumEdges()];
    g.getAllEdges(arr);

    bool found13 = false, found32 = false;
    for (int i = 0; i < g.getNumEdges(); ++i) {
        if (arr[i].weight == 10) found13 = true;
        if (arr[i].weight == 8) found32 = true;
    }
    CHECK(found13);
    CHECK(found32);
    delete[] arr;

    
}


TEST_CASE("Algorithms - BFS") {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);

    Algorithms a;
    Graph tree = a.bfs(g, 0);

    CHECK(tree.getNumEdges() == 3);
    CHECK(tree.getNeighborCount(0) == 2); // should have edges to 1 and 2
    CHECK(tree.getNeighborCount(1) == 2); // back to 0 and to 3
    CHECK(tree.getNeighborCount(3) == 1); // only to 1
}

TEST_CASE("Algorithms - DFS") {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);

    Algorithms a;
    Graph tree = a.dfs(g, 0);

    CHECK(tree.getNumEdges() == 3);
}

TEST_CASE("Algorithms - Dijkstra") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(2, 3, 1);

    Algorithms a;
    Graph tree = a.dijkstra(g, 0);

    CHECK(tree.getNumEdges() == 3); // MST rooted at 0
    CHECK(tree.getNeighborCount(0) == 1); // should connect to 1
    CHECK(tree.getNeighborCount(2) == 2); // connects to 1 and 3
}

TEST_CASE("Algorithms - Kruskal") {
    Graph g(4);
    g.addEdge(0, 1, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 2);
    g.addEdge(0, 3, 5);

    Algorithms a;
    Graph mst = a.kruskal(g);

    CHECK(mst.getNumEdges() == 3);
    CHECK(mst.findEdgeIndex(0, 3) == -1); // should not be included because of high weight
}

TEST_CASE("Algorithms - Prim") {
    Graph g(4);
    g.addEdge(0, 1, 2);
    g.addEdge(1, 2, 3);
    g.addEdge(2, 3, 1);
    g.addEdge(0, 3, 4);

    Algorithms a;
    Graph mst = a.prim(g);

    CHECK(mst.getNumEdges() == 3);

}

TEST_CASE("UnionFind basic tests") {
    UnionFind uf(5);
    for (int i = 0; i < 5; ++i) uf.create(i);
    uf.merge(uf.getNode(0), uf.getNode(1));
    uf.merge(uf.getNode(1), uf.getNode(2));
    CHECK(uf.find(uf.getNode(0)) == uf.find(uf.getNode(2)));
    CHECK(uf.find(uf.getNode(3)) != uf.find(uf.getNode(0)));
}

TEST_CASE("PriorityQueue basic tests") {
    PriorityQueue pq(3);
    pq.insert(0, 10);
    pq.insert(1, 5);
    pq.insert(2, 8);
    CHECK(pq.extractMin().value == 1);
    pq.decreaseKey(2, 2);
    CHECK(pq.extractMin().value == 2);
    CHECK(pq.extractMin().value == 0);
    CHECK(pq.isEmpty());
}

TEST_CASE("Queue basic tests") {
    Queue q;
    CHECK(q.isEmpty());
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    CHECK(!q.isEmpty());
    CHECK(q.dequeue().data ==1);
    CHECK(q.dequeue().data ==2);
    CHECK(q.dequeue().data == 3);
    CHECK(q.isEmpty());
    CHECK_THROWS(q.dequeue());
}




TEST_CASE("Graph Test") {
    Graph g(4);
    g.addEdge(0,1,5);
    g.addEdge(1,3,10);
    g.addEdge(3,2,8);

    CHECK(g.getNumVertex() == 4);
    CHECK(g.getNeighborCount(1) == 2);
    CHECK(g.getNeighborCount(0) == 1);
    CHECK(g.getNeighbor(0, 0).dest == 1);
    CHECK(g.findEdgeIndex(1, 3) != -1);

    g.removeEdge(0,1);
    CHECK(g.getNeighborCount(0) == 0);
    CHECK(g.findEdgeIndex(0, 1) == -1);

    CHECK_THROWS_WITH(g.addEdge(-1, 2), "Invalid vertex index");
    CHECK_THROWS_WITH(g.getNeighbor(10, 0), "Invalid vertex index");
    CHECK_THROWS_WITH(g.removeEdge(0, 2), "Edge does not exist");

    CHECK(g.getNumEdges() == 2);

    Edge* arr = new Edge[g.getNumEdges()];
    g.getAllEdges(arr);

    bool found13 = false, found32 = false;
    for (int i = 0; i < g.getNumEdges(); ++i) {
        if (arr[i].weight == 10) found13 = true;
        if (arr[i].weight == 8) found32 = true;
    }
    CHECK(found13);
    CHECK(found32);
    delete[] arr;

    // Additional Graph Edge Cases
    Graph g2(3);
    g2.addEdge(0, 1);
    CHECK_THROWS_WITH(g2.addEdge(0, 1), "Edge already exists");
    g2.removeEdge(0, 1);
    CHECK(g2.findEdgeIndex(0, 1) == -1); // no hasEdge, check via findEdgeIndex
    CHECK_THROWS_WITH(Graph(-1), "Graph size must be positive");
    CHECK_THROWS_WITH(Graph(0), "Graph size must be positive");
    CHECK_THROWS_WITH(g2.findEdgeIndex(-1, 2), "Invalid vertex index");
    CHECK_THROWS_WITH(g2.addEdge(-1, 0),"Invalid vertex index");
    CHECK_THROWS_WITH(g2.removeEdge(0, 2), "Edge does not exist");
    CHECK_THROWS_WITH(g2.getNeighbor(100, 0), "Invalid vertex index");
    CHECK_THROWS_WITH(g2.getNeighbor(-1, 0), "Invalid vertex index");
}

// Additional tests for the rest are to be added in next steps for clarity

TEST_CASE("UnionFind basic tests") {
    UnionFind uf(5);
    for (int i = 0; i < 5; ++i) uf.create(i);
    uf.merge(uf.getNode(0), uf.getNode(1));
    uf.merge(uf.getNode(1), uf.getNode(2));
    CHECK(uf.find(uf.getNode(0)) == uf.find(uf.getNode(2)));
    CHECK(uf.find(uf.getNode(3)) != uf.find(uf.getNode(0)));
}

TEST_CASE("PriorityQueue basic tests") {
    PriorityQueue pq(3);
    pq.insert(0, 10);
    pq.insert(1, 5);
    pq.insert(2, 8);
    CHECK(pq.extractMin().value == 1);
    pq.decreaseKey(2, 2);
    CHECK(pq.extractMin().value == 2);
    CHECK(pq.extractMin().value == 0);
    CHECK(pq.isEmpty());
}

TEST_CASE("Queue basic tests") {
    Queue q;
    CHECK(q.isEmpty());
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    CHECK(!q.isEmpty());
    CHECK(q.dequeue().data ==1);
    CHECK(q.dequeue().data ==2);
    CHECK(q.dequeue().data == 3);
    CHECK(q.isEmpty());
    CHECK_THROWS(q.dequeue());
}

TEST_CASE("Algorithms - BFS edge cases") {
    Algorithms a;

    // 1. Graph is connected
    Graph connected(4);
    connected.addEdge(0, 1);
    connected.addEdge(0, 2);
    connected.addEdge(1, 3);
    Graph tree = a.bfs(connected, 0);
    CHECK(tree.getNumEdges() == 3);
    CHECK(tree.getNeighborCount(0) == 2);
    CHECK(tree.getNeighborCount(1) == 2);
    CHECK(tree.getNeighborCount(3) == 1);

    // 2. Graph is unconnected
    Graph unconnected(5);
    unconnected.addEdge(0, 1);
    unconnected.addEdge(1, 2);
    // vertices 3 and 4 are disconnected
    Graph bfsResult = a.bfs(unconnected, 0);
    CHECK(bfsResult.getNumEdges() == 2);  // Only part of the graph is visited

    // 3. BFS with out-of-range vertex
    CHECK_THROWS_WITH(a.bfs(unconnected, 10), "Invalid source vertex");

    // 4. Check level-by-level logic – here we assume BFS builds tree level by level
    Graph levelGraph(7);
    levelGraph.addEdge(0, 1);
    levelGraph.addEdge(0, 2);
    levelGraph.addEdge(1, 3);
    levelGraph.addEdge(1, 4);
    levelGraph.addEdge(2, 5);
    levelGraph.addEdge(2, 6);
    Graph levelTree = a.bfs(levelGraph, 0);
    CHECK(levelTree.getNumEdges() == 6);
    CHECK(levelTree.getNeighborCount(0) == 2); // 1,2
    CHECK(levelTree.getNeighborCount(1) == 3); // 0,3,4
    CHECK(levelTree.getNeighborCount(2) == 3); // 0,5,6
}
TEST_CASE("Algorithms - DFS edge cases") {
    Algorithms a;

    // 1. Graph is connected
    Graph connected(4);
    connected.addEdge(0, 1);
    connected.addEdge(0, 2);
    connected.addEdge(1, 3);
    Graph tree = a.dfs(connected, 0);
    CHECK(tree.getNumEdges() == 3);
    CHECK(tree.getNeighborCount(0) == 2);
    CHECK(tree.getNeighborCount(1) == 2);
    CHECK(tree.getNeighborCount(3) == 1);

    // 2. Graph is unconnected
    Graph unconnected(5);
    unconnected.addEdge(0, 1);
    unconnected.addEdge(1, 2);
    // vertices 3 and 4 are disconnected
    Graph dfsResult = a.dfs(unconnected, 0);
    CHECK(dfsResult.getNumEdges() == 2);  // Only part of the graph is visited

    // 3. DFS with out-of-range vertex
   CHECK_THROWS_AS(a.dfs(unconnected, 10), std::runtime_error);

}
TEST_CASE("Algorithms - Dijkstra edge cases") {
    Algorithms a;

    // 1. Graph is connected
    Graph connected(4);
    connected.addEdge(0, 1, 1);
    connected.addEdge(1, 2, 2);
    connected.addEdge(0, 2, 4);
    connected.addEdge(2, 3, 1);
    Graph tree = a.dijkstra(connected, 0);
    CHECK(tree.getNumEdges() == 3);
    CHECK(tree.getNeighborCount(0) == 1); // should connect to 1
    CHECK(tree.getNeighborCount(2) == 2); // connects to 1 and 3

    // 2. Graph is unconnected
    Graph unconnected(5);
    unconnected.addEdge(0, 1, 1);
    unconnected.addEdge(1, 2, 2);
    // vertices 3 and 4 are disconnected
    Graph dijkstraResult = a.dijkstra(unconnected, 0);
    CHECK(dijkstraResult.getNumEdges() == 2); // Only part of the graph is visited

    // 3. Dijkstra with out-of-range vertex
    CHECK_THROWS_WITH(a.dijkstra(unconnected, -1), "Invalid source vertex");

}
// TEST_CASE("Algorithms - Kruskal edge cases") {
//     Algorithms a;

//     // 1. Graph is connected
//     Graph connected(4);
//     connected.addEdge(0, 1, 3);
//     connected.addEdge(1, 2, 1);
//     connected.addEdge(2, 3, 2);
//     connected.addEdge(0, 3, 5);
//     Graph mst = a.kruskal(connected);
//     CHECK(mst.getNumEdges() == 3);
//     CHECK(mst.findEdgeIndex(0, 3) == -1); // should not be included because of high weight

//     // 2. Graph is unconnected
//     Graph unconnected(5);
//     unconnected.addEdge(0, 1, 1);
//     unconnected.addEdge(1, 2, 2);
//     // vertices 3 and 4 are disconnected
//     Graph kruskalResult = a.kruskal(unconnected);
//     CHECK(kruskalResult.getNumEdges() == 2); // Only part of the graph is visited

//     // 3. Kruskal with out-of-range vertex
//     CHECK_THROWS(a.kruskal(unconnected));

// }

TEST_CASE("Algorithms - Kruskal edge cases") {
    Algorithms a;

    Graph connected(4);
    connected.addEdge(0, 1, 3);
    connected.addEdge(1, 2, 1);
    connected.addEdge(2, 3, 2);
    connected.addEdge(0, 3, 5);
    Graph mst = a.kruskal(connected);
    CHECK(mst.getNumEdges() == 3);
    CHECK(mst.findEdgeIndex(0, 3) == -1);

    Graph unconnected(5);
    unconnected.addEdge(0, 1, 1);
    unconnected.addEdge(1, 2, 2);
    CHECK_THROWS_WITH(a.kruskal(unconnected), "Graph is not connected");
}

TEST_CASE("Algorithms - Prim edge cases") {
    Algorithms a;

    Graph connected(4);
    connected.addEdge(0, 1, 2);
    connected.addEdge(1, 2, 3);
    connected.addEdge(2, 3, 1);
    connected.addEdge(0, 3, 4);
    Graph mst = a.prim(connected);
    CHECK(mst.getNumEdges() == 3);

    Graph unconnected(5);
    unconnected.addEdge(0, 1, 1);
    unconnected.addEdge(1, 2, 2);
    CHECK_THROWS_WITH(a.prim(unconnected), "Graph is not connected");}

//  TEST_CASE("Algorithms - Prim edge cases") {
//     Algorithms a;

//     // 1. Graph is connected
//     Graph connected(4);
//     connected.addEdge(0, 1, 2);
//     connected.addEdge(1, 2, 3);
//     connected.addEdge(2, 3, 1);
//     connected.addEdge(0, 3, 4);
//     Graph mst = a.prim(connected);
//     CHECK(mst.getNumEdges() == 3);

//     // 2. Graph is unconnected
//     Graph unconnected(5);
//     unconnected.addEdge(0, 1, 1);
//     unconnected.addEdge(1, 2, 2);
//     // vertices 3 and 4 are disconnected
//     Graph primResult = a.prim(unconnected);
//     CHECK(primResult.getNumEdges() == 2); // Only part of the graph is visited

//     // 3. Prim with out-of-range vertex
//     CHECK_THROWS(a.prim(unconnected));

// }
TEST_CASE("PriorityQueue edge cases") {
    PriorityQueue pq(3);
    pq.insert(0, 10);
    pq.insert(1, 5);
    pq.insert(2, 8);
    CHECK(pq.extractMin().value == 1);
    pq.decreaseKey(2, 2);
    CHECK(pq.extractMin().value == 2);
    CHECK(pq.extractMin().value == 0);
    CHECK(pq.isEmpty());
    
    // Edge case: empty queue
    CHECK_THROWS_WITH(pq.extractMin(), "PriorityQueue is empty");
}
TEST_CASE("Queue edge cases") {
    Queue q;
    CHECK(q.isEmpty());
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    CHECK(!q.isEmpty());
    CHECK(q.dequeue().data ==1);
    CHECK(q.dequeue().data ==2);
    CHECK(q.dequeue().data == 3);
    CHECK(q.isEmpty());
    
    // Edge case: empty queue
    CHECK_THROWS_WITH(q.dequeue(), "queue is empty");
}
TEST_CASE("UnionFind edge cases") {
    UnionFind uf(5);
    for (int i = 0; i < 5; ++i){  uf.create(i);  }
    uf.merge(uf.getNode(0), uf.getNode(1));
    uf.merge(uf.getNode(1), uf.getNode(2));
    CHECK(uf.find(uf.getNode(0)) == uf.find(uf.getNode(2)));
    CHECK(uf.find(uf.getNode(3)) != uf.find(uf.getNode(0)));

    // Edge case: invalid node
    UFNode* nullNode = nullptr;
    CHECK_THROWS_WITH(uf.find(nullNode), "Invalid node");
}