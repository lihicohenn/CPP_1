#include "UnionFind.hpp"
#include <stdexcept>

namespace graph {

    UnionFind::UnionFind(int n) {
        size = n;
        count = 0;
        nodes = new UFNode[n];

    for (int i = 0; i < n; ++i) {
        nodes[i].parent = nullptr; }
    }


    UnionFind::~UnionFind(){
        delete[] nodes;
    }
    
    UFNode* UnionFind::find(UFNode* node) {
        if (node->parent != node) {
            node->parent = find(node->parent);  // דחיסת נתיב
        }
        return node->parent;
    }
    
    void UnionFind::merge(UFNode* node1, UFNode* node2) {
        if (!node1 || !node2) return;

        UFNode* root1 = find(node1);
        UFNode* root2 = find(node2);

        if (root1 == root2) return;

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
        return &nodes[index];
    }


    }
