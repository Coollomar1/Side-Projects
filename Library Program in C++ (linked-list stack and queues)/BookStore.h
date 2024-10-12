/*
Name: Omar Masri
Date: 5/2/24

Code Description: Header file with data members and class function implementations

*/

#ifndef BOOKSTORE_H
#define BOOKSTORE_H
using namespace std;
#include <string>
#include "Customer.h"
#include "Queue.h"  

class BookStore {
private:
    int* ISBN; //an array of ISBN numbers for the books
    string* bookNames; //an array of book names the book at location 0 should correspond to the stock at 0 and the ISBN at 0
    int* stock; //an array of the number of books currently in stock
    int numBooks; //the number of different books the library has
    Queue checkoutQueue; //a queue of customers that is waiting to checkout

public:
    BookStore(); //default constructor should set all pointers to nullptr and do any other setup that is required
    BookStore(int numBooks, int* ISBN, string* bookNames, int* stock); //an overloaded constructor for setting the books in stock
    ~BookStore(); // a destructor to free any memory that needs freeing, be careful not to free things that have already been freed 
    void addToQueue(Customer* customer); // should add the given customer to the queue
    void checkout(); // should checkout all customers that are waitting
    void printLedgerToFile(string* filename); // prints the books and their stock to the given ledger
    void readLedgerFromFile(string* filename); // reads a ledger (same format as output one) and uses it to generate ISBN booknames and stock arrays as well as number of books
};

#endif
