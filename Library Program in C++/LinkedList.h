/*
Name: Omar Masri
Date: 5/2/24
CPSC 1070 Project 2

Code Description:

*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
using namespace std;
#include "Node.h"
class LinkedList {
protected:
    Node* head; //used to store the list
//these should all have been done for the LAB
public:
    LinkedList();
    virtual ~LinkedList();
    virtual void insertFront(int data) = 0;
    virtual void removeFront(int* data) = 0;
    virtual void insertBack(int data) = 0;
    virtual int size()  = 0;
    virtual bool empty() = 0;
};
#endif