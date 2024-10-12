/*
Name: Omar Masri
Date: 5/2/24
CPSC 1070 Project 2

Code Description: Header file with data members and class function implementations


*/

#ifndef CUSTNODE_H
#define CUSTNODE_H
using namespace std;
#include "Node.h"
#include "Customer.h"

class CustNode : public Node {
private:
    Customer* data; //stores the cutomer

public:
    CustNode(Customer* data); //constructor takes a pointer to a customer and stores it in data
    int getData() override; //this is not actually real but has to be implemented so should throw a warning
    void setData(int data) override; // same thing as the int getData() function
    Customer* getCustomerData(); //returns the customer stored 
    void setCustomerData(Customer* data); // sets the data to the given customer

};
#endif