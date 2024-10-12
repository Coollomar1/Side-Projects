/*
Name: Omar Masri
Date: 5/2/24
CPSC 1070 Project 2

Code Description:

*/

#ifndef INTNODE_H
#define INTNODE_H
using namespace std;
#include "Node.h"
class IntNode : public Node {
private:
    int data;

public:
    IntNode(int data); // constructor 
    int getData() override; // returns the integer
    void setData(int data) override; // sets the integer
};
#endif