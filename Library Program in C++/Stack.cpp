/*
Name: Omar Masri
Date: 5/2/24

Code Description:

*/

#include "Stack.h"
#include <iostream>

    Stack::Stack()
    {

        // set head to null ptr to initialize the constructor as empty
        head = nullptr;

    }
    void Stack::push(int data) // adds an integer to the top of the stack
    {

        // insert the integer to the top of the stack
        insertFront(data); // call insert front function

    }
    void Stack::pop(int* data) // removes and stores the integer at the top of the stack (stores in the given pointer)
    {

        // remove inputted data from top of stack and store in pointer
        removeFront(data);
        
    }
    void Stack::insertFront(int data)  // should already be done
    {
        
        // insert new node with given data at head
        IntNode *my_node = new IntNode(data); // create new node using the intnode class which derives from node

        my_node->setData(data); // set the data of the new node to inputted data

        my_node->setNextNode(head); // Set next node of new node to the head

        head = my_node; // Head now points to the new node

    }
    void Stack::removeFront(int* data)// should already be done
    {
        // if linked list is empty, exit function with error message
        if (head == nullptr) {

            cout << "ERROR, LIST IS EMPTY" << endl;

            return; // exit function
        }

        // store data of head node
        *data = head->getData();

        // temp variable to store the head in
        Node* temp = head;

        // let head be the next node variable
        head = head->getNextNode();

        // delete temp variable (which removes the node)
        delete temp; // might need to delete



        //cout << "Removing node at start:  " << *data << endl; debug

    }
    void Stack::insertBack(int data)// should already be done
    {

            
        // insert new node at end of list
        IntNode* end_node = new IntNode(data); // create new intnode with given data

        // set data for node
        end_node->setData(data);

        // if the head points to nothing, let it point to the node now
        if (head == nullptr) {

            head = end_node; // end node is now the head if the list is empty

        }

        else {

            // create an index at i node
            Node* index = head; // let it be the head

            // keep going through the linked list until the end of the list (in which it points to null)
            while(index->getNextNode() != NULL) {

                index = index->getNextNode(); // let the index point to the next node
            }

            // once we reach the end of the list, set the index equal to the end_node variable we made
            index->setNextNode(end_node);

        }
        
    }
    int Stack::size()// should already be done
    {
        
        // size counter variable
        int size = 0;

        // set iterator to head
        Node * iterator = head;

        // if linked list is empty, return a size of 0
        if (iterator == NULL) {

            return 0; // indicates empty list
        }

        // traverse list until end
        // fixed this test case since I did iterator->Get_nextNode it wasn't accounting for the head in the size incrementation
        while (iterator != NULL) {

            // get next node
            iterator = iterator->getNextNode();

            // increment size counter
            size++;

        }

        // return size of linked list
        return size;
        
    }
    bool Stack::empty()// should already be done
    {

        // check if head is null, which indicates empty list
        if (head == NULL) {

            // return true if list is empty
            return true;
        }

        // return false otherwise
        return false;
        
    }
