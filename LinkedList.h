// pre-processors
#pragma once
#include <iostream>
#include <string>
using namespace std;

// dataType struct used to store all data
struct dataType {
    int cartId;
    int itemCount;
    int enterQTime;
};

// Node struct used to define nodes in the linked list
struct Node {
    dataType data; // data stored in the dataType structure
    Node *nextPtr; // pointer to the next node structure
};

// Linked class declaration
class Linked {
protected:
    Node *headPtr;
    Node *tailPtr;
public:
    Linked(); //default constructor
    ~Linked(); //destructor
    //function declarations
    void addElement(dataType d);
    void delElement();
    void printList();
    dataType peek();
    bool listIsEmpty();
    //static int
    static int listCount;
};