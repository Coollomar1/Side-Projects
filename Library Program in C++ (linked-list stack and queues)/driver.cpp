/*
Name: Omar Masri
Date: 5/2/24

Code Description:

*/

#include "BookStore.h"
#include "Customer.h"
#include <iostream>



int main() {
    // Create a bookstore
    int numBooks = 3;
    int ISBN[] = {123456, 789012, 345678};
    string bookNames[] = {"Book A", "Book B", "Book C"};
    int stock[] = {5, 3, 7};
    
    cout << "Creating bookstore" << endl << endl;
    
    BookStore bookstore(numBooks, ISBN, bookNames, stock);

    cout << endl;
    cout << "Bookstore created" << endl << endl;


    // output that their book was added to the stack
    cout << "Customer 1 is adding 2 books to stack!" << endl;


    // Create some customers
    string cust1Info[] = {"John Doe", "01/01/1990", "123 Main St"};
    Customer customer1(&cust1Info[0], &cust1Info[1], &cust1Info[2]); // had to change these indices
    customer1.addBookToStack(123456);
    customer1.addBookToStack(789012);

    // check if customers are being stored correctly
    // use the pointer to get the value of we passed to the function
    cout << endl;
    cout << "Customer 1 Information: " << endl; 
    cout << *customer1.getName() << endl;
    cout << *customer1.getDOB() << endl;
    cout << *customer1.getAddress() << endl << endl;


    // output that their book was added to the stack
    cout << "Customer 2 is adding a book to stack!" << endl;

    string cust2Info[] = {"Jane Smith", "05/10/1985", "456 Elm St"};
    Customer customer2(&cust2Info[0], &cust2Info[1], &cust2Info[2]);
    customer2.addBookToStack(345678);

    // check if customers are being stored correctly
    // use the pointer to get the value of we passed to the function
    cout << endl;
    cout << "Customer 2 Information: " << endl; 
    cout << *customer2.getName() << endl;
    cout << *customer2.getDOB() << endl;
    cout << *customer2.getAddress() << endl;


    // Add customers to the bookstore queue
    bookstore.addToQueue(&customer1);
    bookstore.addToQueue(&customer2);



    // test adding customers to queue and dequeuing them
    Queue queue;

    queue.enqueue(&customer1);
    queue.enqueue(&customer2);

    queue.printQueue();

    // Create customer pointers for the dequeue function to be called
    Customer* dequeue_1;
    Customer* dequeue_2;

    queue.dequeue(&dequeue_1);
    queue.dequeue(&dequeue_2);

    queue.printQueue();

    // Check if customers were dequeued successfully
    /* if (dequeue_1 != nullptr) {
        cout << "Customer checked out: " << dequeue_1->getName() << endl;
        cout << "Customer DOB: " << dequeue_1->getDOB() << endl;
        cout << "Customer Address: " << dequeue_1->getAddress() << endl;
    }

    if (dequeue_2 != nullptr) {
        cout << "Customer checked out: " << dequeue_2->getName() << endl;
        cout << "Customer DOB: " << dequeue_2->getDOB() << endl;
        cout << "Customer Address: " << dequeue_2->getAddress() << endl;
    } */

    // checked in the class


    // print checking out customers to ensure function is called
    cout << "Checking out customers:" << endl;
    
    // Checkout some customers
    bookstore.checkout();

    // output that their book was added to the stack
    cout << "Customer 3 is adding 2 books to stack!" << endl;

    // Add more customers
    string cust3Info[] = {"Alice Johnson", "03/15/1975", "789 Oak St"};
    Customer customer3(&cust3Info[0], &cust3Info[1], &cust3Info[2]);
    customer3.addBookToStack(123456);
    customer3.addBookToStack(345678);

    // check if customers are being stored correctly
    // use the pointer to get the value of we passed to the function
    cout << endl;
    cout << "Customer 3 Information: " << endl; 
    cout << *customer3.getName() << endl;
    cout << *customer3.getDOB() << endl;
    cout << *customer3.getAddress() << endl << endl;


    // output that their book was added to the stack
    cout << "Customer 4 is adding a book to stack!" << endl;

    string cust4Info[] = {"Bob Brown", "11/20/1988", "321 Pine St"};
    Customer customer4(&cust4Info[0], &cust4Info[1], &cust4Info[2]);
    customer4.addBookToStack(789012);

    // check if customers are being stored correctly
    // use the pointer to get the value of we passed to the function
    cout << endl;
    cout << "Customer 4 Information: " << endl; 
    cout << *customer4.getName() << endl;
    cout << *customer4.getDOB() << endl;
    cout << *customer4.getAddress() << endl;

    
    // Add customers to the bookstore queue
    bookstore.addToQueue(&customer3);
    bookstore.addToQueue(&customer4);
    
    // test adding customers to queue and dequeuing them
    
    queue.enqueue(&customer3);
    queue.enqueue(&customer4);

    queue.printQueue();

    // Create customer pointers for the dequeue function to be called
    Customer* dequeue_3;
    Customer* dequeue_4;

    queue.dequeue(&dequeue_3);
    queue.dequeue(&dequeue_4);

    queue.printQueue();

    // Check if customers were dequeued successfully
   /* if (dequeue_3 != nullptr) {
        cout << "Customer checked out: " << dequeue_3->getName() << endl;
        cout << "Customer DOB: " << dequeue_3->getDOB() << endl;
        cout << "Customer Address: " << dequeue_3->getAddress() << endl;
    }

    if (dequeue_4 != nullptr) {
        cout << "Customer checked out: " << dequeue_4->getName() << endl;
        cout << "Customer DOB: " << dequeue_4->getDOB() << endl;
        cout << "Customer Address: " << dequeue_4->getAddress() << endl;
    } */


    // checked in the class


    // print checking out customers to ensure function is called
    cout << "Checking out customers:" << endl;

    // Checkout all customers
    bookstore.checkout();

    // Print ledger
    string fileName = "ledger.txt";
    bookstore.printLedgerToFile(&fileName);


    return 0;
}
