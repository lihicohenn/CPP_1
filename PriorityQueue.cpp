//lihicohen1123@gmail.com
#include "PriorityQueue.hpp"
#include <stdexcept>

namespace graph {

    PriorityQueue::PriorityQueue(int maxSize) {
        capacity = maxSize;
        size = 0;
        heap = new PQNode[capacity];
    }
    
    PriorityQueue::~PriorityQueue(){
        delete[] heap;
    }
    

    void PriorityQueue::swap(int i, int j) {
        PQNode temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }


    void PriorityQueue::heapifyUp(int index) {
        
        if (index < 0 || index > size) {
            throw std::out_of_range("Index is out of range in heapifyUp");}

        int parent = (index - 1) / 2;
        while (index > 0 && heap[index].key < heap[parent].key) {
            swap(index, parent);
            index = parent;
            parent = (index - 1) / 2;
        }

    }

    void PriorityQueue::heapifyDown(int index) {
        int leftson = 2 * index + 1;
        int rightson  = 2 * index + 2;
        int smallest = index;

        if (leftson == size && heap[leftson].value < heap[index].value){ //only have one child
            swap(smallest, leftson);
        }

        if (leftson < size && heap[leftson].value < heap[smallest].value) {
        smallest = leftson;
        }
        if (rightson < size && heap[rightson].value < heap[smallest].value) {
        smallest = rightson;
        }

        if (smallest != index) {
        swap(index, smallest);
        heapifyDown(smallest);
        }
        }

        void PriorityQueue::insert(int value, int key) {
        if (size >= capacity) {
        throw std::overflow_error("Priority Queue is full"); }

        heap[size].value = value;
        heap[size].key = key;
        heapifyUp(size);
        size++; }


        void PriorityQueue::decreaseKey(int value, int newKey) {
        int i = getIndex(value);
        if (i == -1) {
        throw std::invalid_argument("Value not found in heap");
        }

        if (newKey > heap[i].key) {
        throw std::invalid_argument("New key is greater than current key");
        }

        heap[i].key = newKey;
        heapifyUp(i);
        }

        int PriorityQueue::getIndex(int value) const {
        for (int i = 0; i < size; ++i) {
        if (heap[i].value == value) {
            return i;
        }
        }
        return -1;
        }

        bool PriorityQueue::isEmpty() const {
        return size == 0;
        }

    PQNode PriorityQueue::extractMin() {
        if (isEmpty()) {
            throw std::out_of_range("PriorityQueue is empty");
        }
        PQNode min = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
        return min;
    }

    }




   

