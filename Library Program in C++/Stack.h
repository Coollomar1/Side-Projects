/*
Name: Omar Masri
Date: 5/2/24

Code Description:

*/

#ifndef STACK_H
#define STACK_H
using namespace std;
#include "LinkedList.h"
#include "IntNode.h"

class Stack : public LinkedList {
public:
    Stack();
    void push(int data); // adds an integer to the top of the stack
    void pop(int* data); // removes and stores the integer at the top of the stack (stores in the given pointer)
    void insertFront(int data) override;  // should already be done
    void removeFront(int* data) override;// should already be done
    void insertBack(int data) override;// should already be done
    int size() override;// should already be done
    bool empty() override;// should already be done
};
#endif 
