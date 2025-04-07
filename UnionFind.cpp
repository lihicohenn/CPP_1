//lihicohen1123@gmail.com
#include "UnionFind.hpp"
#include <stdexcept>

namespace graph {

    UnionFind::UnionFind(int n) {
        size = n; // size of the union-find structure
        count = 0; // number of elements in the union-find structure
        nodes = new UFNode[n]; // creats an array of n union-find nodes 

    for (int i = 0; i < n; ++i) {
        nodes[i].parent = nullptr; } // initialize the parent pointer to null-ptr
    }


    UnionFind::~UnionFind(){
        delete[] nodes; // delete the array of union-find nodes
    }
    
    UFNode* UnionFind::find(UFNode* node) {
        if (node == nullptr) {
            throw std::invalid_argument("Invalid node"); // check if the node is null
        }
        if (node->parent != node) {
            node->parent = find(node->parent);  // path compression
        }
        return node->parent; // return the root of the set
    }
    
    void UnionFind::merge(UFNode* node1, UFNode* node2) {
        if (!node1 || !node2) return; // check if the nodes are null

        UFNode* root1 = find(node1);
        UFNode* root2 = find(node2);  // find the roots of the sets

        if (root1 == root2) return; // if they are already in the same set

        // Union by rank
        if (root1->rank < root2->rank) {
            root1->parent = root2;
        } else if (root1->rank > root2->rank) {
            root2->parent = root1;
        } else {
            root2->parent = root1;
            root1->rank++;
        }
    }

    void UnionFind::create(int value) { // creates a new element as singelton
    if (value < 0 || value >= size) {
        throw std::out_of_range("Value out of range in create()");
    }
    nodes[value].value = value;
    nodes[value].parent = &nodes[value]; // represent of himself
    nodes[value].rank = 0;

    count++;
    }

    UFNode* UnionFind::getNode(int index) {
        return &nodes[index]; // return the node at the given index
    }


    }
