//
// Created by Alexander Allis on 10/11/22.
//

#include <vector>
#include "Node.h"
#include "LinkedList.h"

/*
 * Singly linked list of type <int>
 * Methods:
 *  add()
 *  addTail()
 *  isEnd()
 *  pop()
 *  reset()
 *  clearList()
 */

LinkedList::LinkedList() {
    this -> listPointer = nullptr;
    this -> head = nullptr;
    this -> tail = nullptr;
}

LinkedList::LinkedList(std::vector<int> list) {
    for(int i = 0; i < list.size(); i++) {
        addTail(list.at(i));
    }
}

/*
 * Adds to the head of the list
 * Args:
 *  data: <int>
*  Returns:
 *  void
 */
void LinkedList::add(int data) {
    Node* nodePointer = new Node;
    if (listPointer == nullptr){
        this -> tail = nodePointer;  // if first node created, set tail
        this -> head = nodePointer;  // if first node created, set head
    }
    nodePointer -> data = data;
    nodePointer -> next = listPointer;
    this -> listPointer = nodePointer;
    this -> head = nodePointer;
}

/*
 * Adds a node to the tail of the linked list
 * Args:
 *  data: <int>
 */
void LinkedList::addTail(int data) {
    if (listPointer == nullptr) {
        add(data);  // if the list is isEmpty, invoke the normal add member function
        return;
    }
    else{
        Node* nodePointer = new Node;
        nodePointer -> data = data;
        this -> tail -> next = nodePointer;
        this -> tail = nodePointer;
        return;
    }
}

/*
 * Determines if listPointer is at the end of the list
 * Returns:
 *  Boolean value true if at end, false otherwise.
 */
bool LinkedList::isEnd() const {
    if (this -> listPointer == nullptr) return true;
    else return false;
}

/*
 * Determines if listpointer has a node after it
 * Returns:
 *  1 if next is not null
 *  0 otherwise
 */
int LinkedList::hasNext() const {
    if (this -> listPointer != nullptr && this->listPointer->next != nullptr) return 1;
    else return 0;
}

/*
 * Returns an item in the linked list and increments the list pointer
 */
int LinkedList::pop() {
    Node* tmp = listPointer;
    listPointer = listPointer -> next;
    return (tmp -> data);
}

/*
 * Resets the listpointer back to the top of the list.
 */
void LinkedList::reset() {
    this -> listPointer = this -> head;
}

/*
 * clears the items from the linked list and cleans up the memory.
 */
void LinkedList::clearList() {
    Node* next;
    while(listPointer != nullptr){
        next = listPointer -> next;
        delete listPointer;
        listPointer = next;
    }
}