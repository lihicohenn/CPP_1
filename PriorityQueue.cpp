//lihicohen1123@gmail.com
#include "PriorityQueue.hpp"
#include <stdexcept>

namespace graph {

    PriorityQueue::PriorityQueue(int maxSize) {
        capacity = maxSize; // Define the capacity of the priority queue
        size = 0; // Initialize the size to 0
        heap = new PQNode[capacity]; // Create a new array of PQNode
    }
    
    PriorityQueue::~PriorityQueue(){
        delete[] heap; // Delete the array of PQNode
    }
    
    // Swap two nodes in the heap
    void PriorityQueue::swap(int i, int j) {
        PQNode temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    // Heapify up the node at the given index
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

    // Heapify down the node at the given index
    void PriorityQueue::heapifyDown(int index) {
        int leftson = 2 * index + 1;
        int rightson  = 2 * index + 2;
        int smallest = index;

        if (leftson == size && heap[leftson].value < heap[index].value){ //only have left child and his value smaller then the parent
            swap(smallest, leftson);
        }

        if (leftson < size && heap[leftson].value < heap[smallest].value) { // have left child and his value smallest then hid parent, modify smallest
        smallest = leftson; 
        }
        if (rightson < size && heap[rightson].value < heap[smallest].value) { //have right child and he smaller from smallest, modify smallest
        smallest = rightson;
        }

        if (smallest != index) { //if found child bigger then his parent - swap and continue recouresion
        swap(index, smallest);
        heapifyDown(smallest);
        }
        }

        // Insert a new node into the priority queue
        void PriorityQueue::insert(int value, int key) {
        if (size >= capacity) {
        throw std::overflow_error("Priority Queue is full"); }

        heap[size].value = value;
        heap[size].key = key;
        heapifyUp(size);
        size++; }


        void PriorityQueue::decreaseKey(int value, int newKey) {
        int i = getIndex(value);
        if (i == -1) {  // Check if the value exists in the heap
        throw std::invalid_argument("Value not found in heap");
        }

        if (newKey > heap[i].key) {
        throw std::invalid_argument("New key is greater than current key");
        }

        heap[i].key = newKey; // Update the key
        heapifyUp(i); // Move the node up to maintain heap property
        }

        // Get the index of a value in the heap
        int PriorityQueue::getIndex(int value) const {
        for (int i = 0; i < size; ++i) {
        if (heap[i].value == value) {
            return i;
        }
        }
        return -1;
        }

        // Check if the priority queue is empty
        bool PriorityQueue::isEmpty() const {
        return size == 0;
        }


        PQNode PriorityQueue::extractMin() {
        if (isEmpty()) {
            throw std::out_of_range("PriorityQueue is empty");
        }
        PQNode min = heap[0]; // Sets the defult min to the first element
        heap[0] = heap[size - 1]; //Swap the least element with the first - to remove the min
        size--; 
        heapifyDown(0);// Run the hipify down to save the min heap attribute
        return min;
    }

    }



