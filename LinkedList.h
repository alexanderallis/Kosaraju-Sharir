//
// Created by Alexander Allis on 10/11/22.
//

#ifndef KOSARAJU_SHARIR_LINKEDLIST_H
#define KOSARAJU_SHARIR_LINKEDLIST_H

#include <vector>
#include "Node.h"

class LinkedList {
public:
    LinkedList();
    explicit LinkedList(std::vector<int>);
//        ~LinkedList();
    void add(int);
    void addTail(int);
    int pop();
    bool isEnd() const;
    int hasNext() const;
    void clearList();

private:
    Node* listPointer{};
    Node* tail{};

};

#endif //KOSARAJU_SHARIR_LINKEDLIST_H
