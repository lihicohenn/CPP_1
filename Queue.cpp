//lihicohen1123@gmail.com
#include "Queue.hpp"

namespace graph {

Queue::Queue() {
    front = nullptr;
    rear = nullptr;
    size = 0;
}

Queue::~Queue() {
    while (front != nullptr) {
        Vertex* temp = front;
        front = front->next;
        delete temp;
    }
    rear = nullptr;
    size = 0;
}

void Queue::enqueue(int val) {
    Vertex* newNode = new Vertex{val, nullptr};

    if (front == nullptr) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    size++;
}

Vertex Queue::dequeue() {
    if (isEmpty()) {
        throw "queue is empty";
    }

    Vertex* temp = front;
    Vertex result = *temp;
    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    delete temp;
    size--;
    return result;
}

bool Queue::isEmpty() {
    return front == nullptr;
}

}
