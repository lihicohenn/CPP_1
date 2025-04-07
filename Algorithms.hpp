//lihicohen1123@gmail.com
#include "PriorityQueue.hpp"
#include "Queue.hpp"
#pragma once


namespace graph{

    enum Color { WHITE, GREY, BLACK };

    class Algorithms{

        public:
        Algorithms();
        ~Algorithms();
        Graph bfs(Graph& graph, int src);
        Graph dfs(Graph& graph, int src);
        void dfs_visit(Graph& graph, int src , Color* color, int* p, int* d, int* f, int& time);
        void relax(int u, Graph& graph, int d[], int p[], PriorityQueue& pq);
        Graph dijkstra(Graph& graph, int src);
        Graph kruskal(Graph& graph);
        void swap(Edge& a, Edge& b);
        void swap(int& a, int& b);
        Graph prim(Graph& graph);

};
};