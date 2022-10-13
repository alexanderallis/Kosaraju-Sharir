//
// Created by Alexander Allis on 9/2/22.
//

#include "Stack.h"

Stack::Stack() {
    this -> size = 10;
    this -> stackArr = new int[size];
    this -> pointer = -1;
}

Stack::Stack(int size) {
    this -> size = size;
    this -> stackArr = new int[size];
    this -> pointer = -1;
}

void Stack::push(int num) {
    if (!isFull()) {
        this -> stackArr[++(this -> pointer)] = num;
    }
}

int Stack::pop() {
    if(isEmpty()) return -1;
    return (this -> stackArr[this -> pointer--]);
}

bool Stack::isEmpty() const {
    return this -> pointer == -1;
}

bool Stack::isFull() const {
    return this -> pointer == this -> size - 1;
}

// TODO: Need a destructor function??

