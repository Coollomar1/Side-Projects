/*
Name: Omar Masri
Date: 5/2/24

Code Description: Bookstore file to create the bookstore with the books ISBN, name, stock, and number of books.
Adds customers to queue, checks them out (dequeues them), and prints the ledger of the books to an output file

*/

#include "BookStore.h"
#include <vector> // include vector for the readLedgerFromFile function
#include <iostream>
#include <fstream> // for input and output streams

    BookStore::BookStore() //default constructor should set all pointers to nullptr and do any other setup that is required
    {
        // set array of ISBN numbers for the books to nullptr
        this->ISBN = nullptr;
        // set array of book names to null ptr
        this->bookNames = nullptr;
        // set array of the number of books currently in stock to nullptr
        this->stock = nullptr;
        // set the number of different books the library has to 0
        this->numBooks = 0;

        // set the checkout queue object equal to the queue class constructor (which is empty)
        this->checkoutQueue = Queue();

        
    }

    //an overloaded constructor for setting the books in stock
    BookStore::BookStore(int numBooks, int* ISBN, string* bookNames, int* stock) : numBooks(numBooks) // initialize the numbooks data member to the integer passed in function parameter
    {
        
        // ensure that the number of books is greater than 0 when passed in parameter
        if (numBooks > 0) {

            // Allocate memory for ISBN, bookNames, and stock arrays
            this->ISBN = new int[numBooks]; // put numbooks as the size for these arrays
            this->bookNames = new string[numBooks];
            this->stock = new int[numBooks];

            // Copy data from input parameter arrays from the function to member arrays we created
            for (int i = 0; i < numBooks; ++i) {
                
                // put each member at each index to the private member variable at each index
                this->ISBN[i] = ISBN[i];
                
                this->bookNames[i] = bookNames[i];
                
                this->stock[i] = stock[i];

            }
        }

        // if numbooks are 0 or less, set everything to null
        else {

            this->ISBN = nullptr;
            this->bookNames = nullptr;
            this->stock = nullptr;

        }

        // see if the contents are being added from the driver.cpp file
        cout << "BookStore Contents:" << endl;
        for (int i = 0; i < numBooks; ++i) {
            cout << "ISBN: " << ISBN[i] << ", Book Name: " << bookNames[i] << ", Stock: " << stock[i] << endl;
        }
    }


    BookStore::~BookStore() // a destructor to free any memory that needs freeing, be careful not to free things that have already been freed 
    {

        // delete memory for allocated arrays

        delete[] ISBN;
        
        delete[] bookNames;

        delete[] stock;


        // checkout queue doesn't need to be deallocated since it is a member object of the Queue class (meaning it is automatically destroyed)
    }
    void BookStore::addToQueue(Customer* customer) // should add the given customer to the queue
    {

        // call the enqueue function from queue class and use the checkout queue object 
        checkoutQueue.enqueue(customer);

        if (customer != nullptr) {

            // to check customers in queue
            cout << "Customer: " << *customer->getName() << " added to the queue" << endl;

        }

    }
    void BookStore::checkout() // should checkout all customers that are waitting
    {

        // check customers in queue
       // cout << "Customers in checkout queue:" << endl;

        // dequeue the customers until checkout queue is empty
        while (!checkoutQueue.empty()) {

            // create customer pointer object and initialize as nullptr
            Customer* customer = nullptr;


            // call the dequeue function from queue class and use checkout queue object to checkout the customers
            // this will remove them from front of queue and store them
            checkoutQueue.dequeue(&customer);

            // print out name of each customer checked out
            cout << "Customer checked out: " << customer->getName() << endl; // call getName function from customer class to get each customer name

        }

    }

    void BookStore::printLedgerToFile(string* filename) // prints the books and their stock to the given ledger
    {

            // create an output file stream
            ofstream outputFile;

            // open the file inputted
            outputFile.open(*filename);

            // check if open
            if (!outputFile.is_open()) {

                cout << "Output file is not open!" << endl;
                return; // exit function if this error occurs

            }


            // write books and stock to the file
            // iterate through the number of books
            for (int i = 0; i < numBooks; ++i) {

                // write each book's ISBN, book name, and stock to the file
                outputFile << "ISBN: " << ISBN[i] << ", BOOK NAME: " << bookNames[i] << ", STOCK: " << stock[i] << endl;

            }

        // close file when done to free memory
        outputFile.close();

        cout << "Ledger printed to file: " << *filename << endl;

        
    }
    void BookStore::readLedgerFromFile(string* filename)// reads a ledger (same format as output one) and uses it to generate ISBN booknames and stock arrays as well as number of books
    {

        // create input file stream
        ifstream inputFile;

        // open the inputted file
        inputFile.open(*filename);

        // check if file is open
        if (!inputFile.is_open()) {

            cout << "Input file not open!" << endl;
            return; // exit function if this error occurs

        }

        // vectors to store the data read from file
        vector<int> temporaryISBN;

        vector<string> temporaryBOOK_NAME;

        vector<int> temporarySTOCK;

        // create variables for isbn, bookname, and stock
        int isbn;

        string bookName;

        int sttock;

        // create comma string variable to read from the file
        string comma;


        // loop through each line of the file
        // read through each line of the file based on the format we created in the output file
        // reads the number, book name, and stock with commas in between to keep iterating through lines
        while (inputFile >> isbn >> comma >> bookName >> comma >> sttock) {
            
            // put the read isbn into the temporary vector
            temporaryISBN.push_back(isbn);

            // put read book names into temporary vector
            temporaryBOOK_NAME.push_back(bookName);

            // put read stock number into temporary vector
            temporarySTOCK.push_back(sttock);

        }

        // close the file
        inputFile.close();

        // Deallocate existing arrays
        delete[] ISBN;
        delete[] bookNames;
        delete[] stock;


        // update the number of books based on the size of the ISBN vector
        numBooks = temporaryISBN.size();


        // allocate memory for the arrays based on the number books size
        ISBN = new int[numBooks]; // isbn integer with size numBooks (like malloc)
        bookNames = new string[numBooks]; // string array
        stock = new int[numBooks]; // same here (use this pointer to access private data member in class)

        // use the temporary vectors we created to copy the data into these newly allocated arrays
        for (int i = 0; i < numBooks; ++i) {

            // Each isbn at each index copied from vector, and so on for the rest of the arrays
            ISBN[i] = temporaryISBN[i];

            bookNames[i] = temporaryBOOK_NAME[i];
            
            stock[i] = temporarySTOCK[i];

        }


        // clear the vectors
        temporaryISBN.clear();
        temporaryBOOK_NAME.clear();
        temporarySTOCK.clear();

        }
