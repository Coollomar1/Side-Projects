/*
Name: Omar Masri
Date: 5/2/24
CPSC 1070 Project 2

Code Description:

*/

#include "Node.h"


Node* Node::getNextNode()  // should return the next node
{

    return next; // get the nextNode we set

}
void Node::setNextNode(Node* nextNode) // should set the next node 
{

    next = nextNode; // set nextnode to parameter

}
Node::~Node()// should delete the next node
{

    // destructor (done in lab)
    if (next != nullptr) {

        // instead, set the nextNode to be a nullptr if the next node is a value in the linked list
        next = nullptr;
    }

}
