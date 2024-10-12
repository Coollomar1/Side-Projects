/*
Name: Omar Masri
Date: 5/2/24
CPSC 1070 Project 2

Code Description: Getter and setter functions that set the customer object data and return the data.
Also has a default constructor for customer object

*/

#include "CustNode.h"
#include <iostream>

CustNode::CustNode(Customer* data) : data(data) //constructor takes a pointer to a customer and stores it in data
{

    // store the customer pointer object passed in parameter to data (which we did above)

}

int CustNode::getData() //this is not actually real but has to be implemented so should throw a warning
{
    
    // THIS WAS MESSING ME UP SO MUCH
    //return this->some_random_data;

   return -1;


}
void CustNode::setData(int data) // same thing as the int getData() function
{

    // SAME HERE OMG
    //this->some_random_data = data;


}
void CustNode::setCustomerData(Customer* data) // sets the data to the given customer
{

    // set the data to data passed in parameter
    this->data = data;
}

Customer* CustNode::getCustomerData() //returns the customer stored 
{

    // return the data
    return data;

}


