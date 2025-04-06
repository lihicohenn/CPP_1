//lihicohen1123@gmail.com
#pragma once
#include <iostream>

namespace graph {

    struct PQNode {
    int key;
    int value;
    };

    class PriorityQueue {

    private:
    PQNode* heap;   
    int size; 
    int capacity;

    void heapifyUp(int index);
    void heapifyDown(int index);
    void swap(int i, int j); // for heapify down-up

    public:
    PriorityQueue(int maxSize);
    ~PriorityQueue();
    PQNode extractMin();
    void decreaseKey(int value, int newKey); 
    void insert(int value, int key); 
    bool isEmpty() const;
    int getIndex(int value) const; 

};

};
