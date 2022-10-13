//
// Created by Alexander Allis on 9/2/22.
//

#ifndef GALE_SHAPELY_STACK_H
#define GALE_SHAPELY_STACK_H


class Stack {
public:
    Stack();
    Stack(int);
    ~Stack() { delete[] stackArr; }
    void push(int num);
    int pop();
    bool isEmpty() const;
    bool isFull() const;


private:
    int* stackArr;
    int pointer;
    int size;

};


#endif //GALE_SHAPELY_STACK_H
