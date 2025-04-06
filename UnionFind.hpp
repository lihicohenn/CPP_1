//lihicohen1123@gmail.com
#pragma once

namespace graph {

    struct UFNode{
        struct UFNode* parent;
        int value;
        int rank;
    };

    class UnionFind {

    private:
        UFNode* nodes;
        int size;
        int count;

    public:
        UnionFind(int n);
        ~UnionFind();
        UFNode* find(UFNode* set);
        void merge(UFNode* setone, UFNode* settwo);
        void create(int value);
        UFNode* getNode(int index);

};}
