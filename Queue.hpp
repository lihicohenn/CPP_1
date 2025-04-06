//lihicohen1123@gmail.com
#pragma once
namespace graph {

    struct Vertex {
        int data;
        Vertex* next;
    };

    class Queue {
    private:
        Vertex* front;
        Vertex* rear;
        int size;

    public:
        Queue();
        ~Queue();
        void enqueue(int val);
        Vertex dequeue();
        bool isEmpty();
    };

}