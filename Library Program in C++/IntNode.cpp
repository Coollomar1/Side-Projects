/*
Name: Omar Masri
Date: 5/2/24
CPSC 1070 Project 2

Code Description:

*/

#include "IntNode.h"

IntNode::IntNode(int data) // constructor 
{
    // set private data variable to data passed in parameter of function
    this->data = data;

}
int IntNode::getData() // returns the integer
{

    // return the data from the constructor
    return this->data;

}
void IntNode::setData(int data) // sets the integer
{

    // set private data variable to data passed in parameter of function
    this->data = data;

}
