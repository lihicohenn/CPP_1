//lihicohen1123@gmail.com
#include "Graph.hpp"
#include "Queue.hpp"
#include <iostream>

namespace graph{


Graph::Graph(int num){
    if (num <= 0){ 
        throw "Graph size must be positive"; 
    }

    numOfVertex = num;
    adjList = new Edge*[numOfVertex]; //Initialize the adjacency list
    size = new int[numOfVertex]; // num of neighbors for each vertex

    for (int i = 0; i < numOfVertex; ++i) {
        adjList[i] = new Edge[numOfVertex];  // allocate space for neighbors
        size[i] = 0;                         
    }
}

Graph::~Graph(){
    for (int i = 0; i < numOfVertex; ++i) {
        delete[] adjList[i]; // Delete each neighbor list
    }
        delete[] adjList;  // Delete the array of lists      
        delete[] size;     //Delete the array of neighbor count      
}


void Graph::addEdge(int src, int dest, int weight){
    if (src < 0 || dest < 0 || src >= numOfVertex || dest >= numOfVertex)
    throw "Invalid vertex index";

    // Check if the edge already exists

    if (findEdgeIndex(src, dest) != -1) {
        throw std::runtime_error("Edge already exists");
    }

    // Check if the adjacency list is full

    if (size[src] >= numOfVertex || size[dest] >= numOfVertex) {
        throw std::runtime_error("Adjacency list is full");
    }
    // Add the edge to the adjacency list

    adjList[src][size[src]] = Edge(dest, weight);
    size[src]++;

    adjList[dest][size[dest]] = Edge(src, weight);
    size[dest]++;    

    }

    void Graph::removeEdge(int src, int dest){
        if (src < 0 || dest < 0 || src >= numOfVertex || dest >= numOfVertex){
            throw "Invalid vertex index";
        }
        
        // Get the index of the edge in the adjacency list
        int indexSrc = findEdgeIndex(src, dest);
        int indexDest = findEdgeIndex(dest, src);

        if (indexSrc == -1 || indexDest == -1) {
        throw "Edge does not exist";
        }

        //Shift elements left to remove edge from src list
        for (int i = indexSrc; i < size[src] - 1; ++i) {
            adjList[src][i] = adjList[src][i + 1];
        }
        size[src]--;

        //Shift elements left to remove edge from dest list
        for (int i = indexDest; i < size[dest] - 1; ++i) {
            adjList[dest][i] = adjList[dest][i + 1];
        }
        size[dest]--;

    }

    int Graph::findEdgeIndex(int src, int dest) {
    if (src < 0 || src >= numOfVertex || dest < 0 || dest >= numOfVertex) {
        throw "Invalid vertex index";
    }

    // Iterate through src neighbors to find the matching dest
    for (int i = 0; i < size[src]; ++i) {
        if (adjList[src][i].dest == dest) {
            return i; // Found it
    }
    }

    return -1;
    
}

   Edge Graph::getNeighbor(int vertex, int index) {
    if (vertex < 0 || vertex >= numOfVertex || index < 0 || index >= size[vertex]) {
        throw std::out_of_range("Invalid vertex index");
    }
    return adjList[vertex][index];
}
 

    void Graph::print_graph() const {
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
        count += size[i];  // count thee neighbors of each vertex
    }
    return count / 2;  //because every edge shows twice
    }

    // Fills the given array with all the edges in the graph
    void Graph::getAllEdges(Edge* arr) const {
        int index = 0;
        for (int src = 0; src < numOfVertex; ++src) {
            for (int i = 0; i < size[src]; ++i) {
                int dest = adjList[src][i].dest;
                int weight = adjList[src][i].weight;
    
                // Only add one direction to avoid duplicates
                if (src < dest) {
                    arr[index].dest = dest;
                    arr[index].weight = weight;
                    index++;
                }
            }
        }
    }

    // Check if the graph is connected
    bool Graph::isConnected() {
        if (getNumVertex() == 0) return false;
    
        bool* visited = new bool[getNumVertex()]();
        Queue q;
        q.enqueue(0);
        visited[0] = true;
    
        while (!q.isEmpty()) {
            int u = q.dequeue().data;
            int deg = getNeighborCount(u);
            for (int i = 0; i < deg; i++) {
                int v = getNeighbor(u, i).dest;
                if (!visited[v]) {
                    visited[v] = true;
                    q.enqueue(v);
                }
            }
        }
        // If sny vertex was not visited graph is not connected
        for (int i = 0; i < getNumVertex(); i++) {
            if (!visited[i]) {
                delete[] visited;
                return false;
            }
        }
    
        delete[] visited;
        return true;
    }
    
}


   
