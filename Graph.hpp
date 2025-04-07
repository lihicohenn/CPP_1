//lihicohen1123@gmail.com
#include "Edge.hpp"
#pragma once

namespace graph {

    class Graph {

        private:
        int numOfVertex;
        Edge ** adjList;
        int* size;

        public:
            Graph(int num);
            ~Graph();

            void addEdge(int src, int dest, int weight = 1);
            void removeEdge(int src, int dest);
            int findEdgeIndex(int src, int dest);
            void print_graph() const;
            int getNumVertex();
            int getNeighborCount(int vertex);
            int getNumEdges() const;
            void getAllEdges(Edge* arr) const;
            Edge getNeighbor(int vertex, int index);
            bool isConnected();
            
        };
    };