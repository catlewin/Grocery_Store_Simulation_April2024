//pre-processor
#include "LinkedList.h"

//default constructor
Linked::Linked() {
    headPtr = nullptr;
    tailPtr = nullptr;
}

//destructor
Linked::~Linked() {
    Node* tempPtr = headPtr;
    while (tempPtr != nullptr) {
        Node* next = tempPtr->nextPtr;
        delete tempPtr;
        tempPtr = next;
    }
    headPtr = nullptr;
}

//adds element to Linked List in order of enterQTime
void Linked::addElement(dataType d) {
    Node* newNode = new Node;
    newNode->data = d;
    newNode->nextPtr = nullptr;
    if (headPtr == nullptr) {
        headPtr = newNode;
    }
    else if (newNode->data.enterQTime < headPtr->data.enterQTime){
        newNode->nextPtr = headPtr;
        headPtr = newNode;
    }
    else {
        Node* tempPtr = headPtr;
        while (tempPtr!= nullptr && tempPtr->nextPtr != nullptr && tempPtr->nextPtr->data.enterQTime < newNode->data.enterQTime) {
            tempPtr = tempPtr->nextPtr;
        }
        newNode->nextPtr = tempPtr->nextPtr;
        tempPtr->nextPtr = newNode;
    }
}

//deletes element from top of Linked List
void Linked::delElement(){
    Node* delNode = headPtr;
    if (delNode == nullptr){
        cout << "WARNING: List is empty" << endl;
        return;
    }
    headPtr = headPtr->nextPtr;
    delete delNode;
    delNode = nullptr;
}

//checks if Linked List is empty
bool Linked::listIsEmpty(){
    if (headPtr == nullptr)
        return true;
    else
        return false;
}

//outputs Linked List
void Linked::printList() {
    Node* tempPtr = headPtr;
    while (tempPtr != nullptr) {
        cout << "CartID: " << tempPtr-> data.cartId << "\t Item Count: " << tempPtr->data.itemCount << "\tEnter Queue Time: " << tempPtr->data.enterQTime << endl;
        tempPtr = tempPtr->nextPtr;
    }
}

//returns the headPtr's data
dataType Linked::peek(){
    return headPtr->data;
}

//static int definition
int Linked::listCount = 0;