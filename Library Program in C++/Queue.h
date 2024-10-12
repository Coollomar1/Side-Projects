/*
Name: Omar Masri
Date: 5/2/24
CPSC 1070 Project 2

Code Description:

*/

#ifndef QUEUE_H
#define QUEUE_H
using namespace std;
#include "LinkedList.h"
#include "Customer.h"
#include "CustNode.h"
//a queue is a data structure that acts like a line for more information please see the class slides 
class Queue : public LinkedList {
public:
    Queue(); //should default to being empty
    void enqueue(Customer* customer); // adds a customer to the back of the queue
    void dequeue(Customer** customer); // removes and stores the customer at the front of the queue in the given pointer
    void insertFront(int data) override; // should already be done
    void removeFront(int* data) override; // should already be done
    void insertBack(int data) override;// should already be done
    int size() override; // should already be done
    bool empty() override; // should already be done
    void printQueue() const; // helper
};
#endif