/*
Name: Omar Masri
Date: 5/2/24
CPSC 1070 Project 2

Code Description:

*/

#ifndef NODE_H
#define NODE_H
using namespace std;
class Node {
private:
    int data;
    Node* next;
//these should all have been done for the LAB
// some changes required with the node as it needs to be virtual see below and compare to what you already have done
public:
    virtual int getData() = 0;
    virtual void setData(int data) = 0;
    virtual Node* getNextNode();  // should return the next node
    virtual void setNextNode(Node* nextNode); // should set the next node 
    virtual ~Node(); // should delete the next node
};
#endif