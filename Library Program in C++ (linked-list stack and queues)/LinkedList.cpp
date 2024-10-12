/*
Name: Omar Masri
Date: 5/2/24

Code Description:

*/

#include "LinkedList.h"
LinkedList::LinkedList()
{

    // constructor that sets head to nullptr
    // done in lab
    head = nullptr;

}

// destructor (done in lab)
// since this deletes all nodes in the list, I don't need to manually delete nodes in my code
// This was giving me lots of issues spent 5 hours trying to debug
LinkedList::~LinkedList()
{

    // set variable to the head
    Node * node_at_i = head;

    // destructor that frees all nodes in list
    // iterate through list until end
    while (node_at_i != nullptr) {

        // get the next node by setting a variable equal to the node_at_i node
        Node * get_next = node_at_i->getNextNode();

        // delete the current node_at_i
        delete node_at_i;

        // set the node_at_i to move to the next node
        node_at_i = get_next;


    }

    // set head to null to indicate an empty list
    head = nullptr;

}

