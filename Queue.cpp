//lihicohen1123@gmail.com
#include "Queue.hpp"

namespace graph {

Queue::Queue() {
    front = nullptr; // Initialize front pointer to null
    rear = nullptr; // Initialize rear pointer to null
    size = 0; // Initialize size to 0
}

Queue::~Queue() {
    while (front != nullptr) { // While the queue is not empty
        Vertex* temp = front; // Store the current front node
        front = front->next; // Move front pointer to the next node
        delete temp; // Delete the current front node
    }
    rear = nullptr; // Set rear pointer to null
    size = 0;
}

void Queue::enqueue(int val) {
    Vertex* newNode = new Vertex{val, nullptr}; // Create a new node with the given value

    if (front == nullptr) {
        front = rear = newNode; // If the queue is empty, set both front and rear to the new node
    } else {
        rear->next = newNode; // Link the new node to the end of the queue
        rear = newNode;
    }
    size++; // Increment the size of the queue
}

Vertex Queue::dequeue() {
    if (isEmpty()) {
        throw "queue is empty"; // Check if the queue is empty
    }

    Vertex* temp = front; // Store the current front node
    Vertex result = *temp; // Copy the data from the front node
    front = front->next; // Move front pointer to the next node

    if (front == nullptr) { // If the queue is now empty
        rear = nullptr; // Set rear pointer to null
    }

    delete temp; // Delete the old front node
    size--;
    return result;
}

bool Queue::isEmpty() {
    return front == nullptr; // Check if the queue is empty
}

}
