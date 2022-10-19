//
// Created by Alexander Allis on 9/2/22.
//

#include "Stack.h"

/*
 * A stack data structure of type <int>
 */

/*
 * Default constructor
 * Initializes size to 10
 */
Stack::Stack() {
    this -> size = 10;
    this -> stackArr = new int[size];
    this -> pointer = -1;
}

/*
 * Constructor overload
 * Args:
 *  size: the size of the stack
 */
Stack::Stack(int size) {
    this -> size = size;
    this -> stackArr = new int[size];
    this -> pointer = -1;
}

/*
 * Add an element to the stack
 * Args:
 *  num: the number to add to the stack
 */
void Stack::push(int num) {
    if (!isFull()) {
        this -> stackArr[++(this -> pointer)] = num;
    }
}

/*
 * Get an item from the stack
 * Returns:
 *  data element of type <int>
 */
int Stack::pop() {
    if(isEmpty()) return -1;
    return (this -> stackArr[this -> pointer--]);
}

/*
 * Determines if the stack is empty
 * Returns:
 *  boolean: true if empty, false otherwise
 */
bool Stack::isEmpty() const {
    return this -> pointer == -1;
}

/*
 * Determines if stack has reached maximum size
 * Returns:
 *  boolean: true if full, false otherwise
 */
bool Stack::isFull() const {
    return this -> pointer == this -> size - 1;
}
