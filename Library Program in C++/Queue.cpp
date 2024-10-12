/*
Name: Omar Masri
Date: 5/2/24
CPSC 1070 Project 2

Code Description:

*/

#include "Queue.h"
#include <iostream>
//a queue is a data structure that acts like a line for more information please see the class slides 

Queue::Queue() //should default to being empty
{
    //see explanation in stack.cpp

    // set head to null to make queue empty
    head = nullptr;
}
void Queue::enqueue(Customer* customer) // adds a customer to the back of the queue
{

    // Create CustNode object pointer with customer passed in parameter
    CustNode* cust = new CustNode(customer);

    // check if queue is empty if the head points to nothing
    if (head == nullptr) {

        // if it is empty, make the new node the head
        // this is what was giving me so many issues as my getCustomerData function kept returning nullptr
        head = cust;

    }

    else {

        // Create a lastNode objet from CustNode
        CustNode* last;

        // set it equal to the head of the node
        // use static cast to change the head from being of type Node* to type CustNode*
        // found on geeksforgeeks
        last = static_cast<CustNode*>(head);

        // iterate through the linked list to find the last node
        while (last->getNextNode() != nullptr) {

            // set the last node to the CustNode type to get the next node
            // use static cast to change the getNextNode function to a CustNode* type instead of Node* type
            last = static_cast<CustNode*>(last->getNextNode());
        }


        // add the customer node to the end of the queue after iterating through the linked list to find the last node
        last->setNextNode(cust);

    }
}

// helper to see who is in the queue
void Queue::printQueue() const {
    
    // Start traversing from the head of the queue
    CustNode* currentNode = static_cast<CustNode*>(head);

    // Check if the queue is empty
    if (currentNode == nullptr) {
       
        cout << "Queue is empty. Exiting..." << endl;
        return;

    }

    cout << endl;

    cout << "Queue contents:" << endl;

    // Traverse the queue and print each customer's data
    while (currentNode != nullptr) {
        
        // Get the customer data from the current node
        Customer* customer = currentNode->getCustomerData();

        // Print the customer data
        if (customer != nullptr) {
            
            cout << "Customer: " << customer->getName() << endl;

        } else {

            // otherwise output an error message
            cout << "Customer: <nullptr>" << endl;

        }

        // Move to the next node in the queue
        currentNode = static_cast<CustNode*>(currentNode->getNextNode());

    }
}

void Queue::dequeue(Customer** customer) // removes and stores the customer at the front of the queue in the given pointer
{

    // if the list is empty, set the customer pointer to null
    if (head == nullptr) {

        *customer = nullptr;
        return;

    }

    // Create custnode object to get customer data from the head of the node
    // use static_cast to change the head from type node* to type custnode*
    CustNode* front = static_cast<CustNode*>(head);

    // set the customer pointer object in the parameter to get the front customer's data
    *customer = front->getCustomerData();

    // let the head point to the next node now since we are pointing the customer object to the current node
    head = front->getNextNode();

    // delete the front customer from the queue
    delete front;

}
void Queue::insertFront(int data) // should already be done
{
        
    // insert new node with given data at head
    CustNode *my_node = new CustNode(nullptr); // create new custnode object with null pointer initially

    my_node->setData(data); // set the data of the new node to inputted data

    my_node->setNextNode(head); // Set next node of new node to the head

    head = my_node; // Head now points to the new node

}
void Queue::removeFront(int* data)  // should already be done
{
    
    // if linked list is empty, exit function with error message
    if (head == nullptr) {

        cout << "ERROR, LIST IS EMPTY" << endl;

        *data = -1; // set to -1 to indicate error (caused a lot of seg faults)

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
void Queue::insertBack(int data) // should already be done
{
       
    // insert new node at end of list using the custnode subclass
    CustNode* end_node = new CustNode(nullptr); // create custnode object with nullptr initialized

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
int Queue::size()  // should already be done
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
bool Queue::empty() // should already be done
{
    
    // check if head is null, which indicates empty list
    if (head == NULL) {

        // return true if list is empty
        return true;
    }

    // return false otherwise
    return false;
    
}