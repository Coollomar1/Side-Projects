/*
Name: Omar Masri
Date: 5/2/24
CPSC 1070 Project 2

Code Description:

*/

#ifndef CUSTOMER_H
#define CUSTOMER_H
using namespace std;
#include <string>
#include "Stack.h"

class Customer {
private:
    string name;
    string dob; // date of birth
    string address; 
    Stack* bookStack; // a stack of books that they want to checkout

public:
    Customer(string* name, string* dob, string* address); // constructor sets values
    Customer(); // sets default values to name="Henry" dob="01/01/2000" address="N/A"
    string* getName() ;
    string* getDOB() ;
    string* getAddress() ;
    void addBookToStack(int ISBN); // pushes the given isbn number onto the stack
    void removeBookFromStack(int* ISBN); // pops the top of the stack off and store's its data in the given pointer
    Stack* getBookStack();// returns the entire stack of books
};

#endif