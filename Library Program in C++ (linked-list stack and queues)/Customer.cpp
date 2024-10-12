/*
Name: Omar Masri
Date: 5/2/24

Code Description:

*/

#include "Customer.h"
#include <iostream>
#include <stack> // for testing

Customer::Customer(string* name, string* dob, string* address) // constructor sets values 
{ 
    // set the private values in the class equal to the parameter string pointer values
    // use this pointer to access private data members and set equal to parameter pointers

    this->name = *name;

    this->dob = *dob;

    this->address = *address;

    // initialize book stack (create an object for it)
    // initialize this object to the stack class in the stack.cpp file
    bookStack = new Stack();



}
Customer::Customer() // sets default values to name="Henry" dob="01/01/2000" address="N/A"
{

    // set default values in private area of class to the default values provided
    // use this pointer to access private data members
    this->name = "Henry";
    this->dob = "01/01/2000";
    this->address = "My Address";

    // initialize book stack (create an object for it)
    bookStack = new Stack(); // initialize this object to the stack class in the stack.cpp file


}
string* Customer::getName()
{

    // return pointer to name string (since the function was written by declaring these variables as pointers)
    return &name; // returns address so we can access value in string
}
string* Customer::getDOB()
{

    // return pointer to dob string (since the function was written by declaring these variables as pointers)
    return &dob; // returns address so we can access value in string
}
string* Customer::getAddress()
{

    // return pointer to address string (since the function was written by declaring these variables as pointers)
    return &address; // returns address so we can access value in string
}
void Customer::addBookToStack(int ISBN) // pushes the given isbn number onto the stack
{

    // call the stack push function to put the ISBN number onto the top of the bookStack object
    bookStack->push(ISBN);

    // check if the book is in the stack
    cout << "Book added: " << ISBN << endl;

}
void Customer::removeBookFromStack(int* ISBN) // pops the top of the stack off and store's its data in the given pointer
{

    // call stack pop function to remove ISBN number from top of bookStack object
    bookStack->pop(ISBN);

}
Stack* Customer::getBookStack()// returns the entire stack of books
{

    // return bookStack object we created
    return bookStack;

}

