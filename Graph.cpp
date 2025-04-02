#include "Graph.hpp"
//#include "Edge.hpp"
#include <iostream>

namespace graph{


Graph::Graph(int num){
    numOfVertex = num;
    adjList = new Edge*[numOfVertex];
    size = new int[numOfVertex];

    for (int i = 0; i < numOfVertex; ++i) {
        adjList[i] = new Edge[numOfVertex];  
        size[i] = 0;                         
    }
}

Graph::~Graph(){
    for (int i = 0; i < numOfVertex; ++i) {
        delete[] adjList[i]; 
    }
        delete[] adjList;        
        delete[] size;            
}


void Graph::addEdge(int src, int dest, int weight){
    if (src < 0 || dest < 0 || src >= numOfVertex || dest >= numOfVertex)
    throw "Invalid vertex index";


    adjList[src][size[src]] = Edge(dest, weight);
    size[src]++;

    adjList[dest][size[dest]] = Edge(src, weight);
    size[dest]++;    

    }

    void Graph::removeEdge(int src, int dest){
        if (src < 0 || dest < 0 || src >= numOfVertex || dest >= numOfVertex){
            throw "Invalid vertex index";
        }
        
        int indexSrc = findEdgeIndex(src, dest);
        int indexDest = findEdgeIndex(dest, src);

        if (indexSrc == -1 || indexDest == -1) {
        throw "Edge does not exist";
        }

        for (int i = indexSrc; i < size[src] - 1; ++i) {
            adjList[src][i] = adjList[src][i + 1];
        }
        size[src]--;

        for (int i = indexDest; i < size[dest] - 1; ++i) {
            adjList[dest][i] = adjList[dest][i + 1];
        }
        size[dest]--;

    }

    int Graph::findEdgeIndex(int src, int dest) {
    if (src < 0 || src >= numOfVertex || dest < 0 || dest >= numOfVertex) {
        throw "Invalid vertex index";
    }

    for (int i = 0; i < size[src]; ++i) {
        if (adjList[src][i].dest == dest) {
            return i; // Found it
    }
    }

    return -1;
    
}

   Edge Graph::getNeighbor(int vertex, int index) {
    if (vertex < 0 || vertex >= numOfVertex || index < 0 || index >= size[vertex]) {
        throw std::out_of_range("Invalid neighbor index");
    }
    return adjList[vertex][index];
}
 

    void Graph::print_graph() {
        for (int i = 0; i < numOfVertex; i++) {
            std::cout << "Vertex " << i << ":";
            for (int j = 0; j < size[i]; j++) {
                std::cout << " dest:" << adjList[i][j].dest
                        << " weight:" << adjList[i][j].weight;
            }
            std::cout << std::endl; 
        }
    }


    int Graph::getNumVertex(){
        return numOfVertex;
    }

    int Graph::getNeighborCount(int vertex) {
    if (vertex < 0 || vertex >= numOfVertex) {
        throw "Invalid vertex index";
    }
    return size[vertex];
    }


    int Graph::getNumEdges() const {
    int count = 0;
    for (int i = 0; i < numOfVertex; ++i) {
        count += size[i];  // סופר את כל השכנים של כל קודקוד
    }
    return count / 2;  // כל קשת מופיעה פעמיים (גרף לא מכוון)
    }
}


   
