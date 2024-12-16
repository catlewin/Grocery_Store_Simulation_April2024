// pre-processors
#include "Queue.h"
#include <iomanip>
#include <iostream>
using namespace std;

//default constructor
Queue::Queue() {
    front = nullptr;
    rear = nullptr;
}

//destructor
Queue::~Queue() {
    queueNode *tempPtr = front;
    while (tempPtr != nullptr) {
        queueNode *next = tempPtr->nextPtr;
        delete tempPtr;
        tempPtr = next;
    }
    front = nullptr;
}

//adds element to the end of the Queue
void Queue::enQueue(queueNodeData d) {
    queueNode *newQueueNode = new queueNode;
    newQueueNode->data = d;
    newQueueNode->nextPtr = nullptr;
    if (front == nullptr) {
        front = newQueueNode;
        rear = newQueueNode;
    }
    else {
        rear->nextPtr = newQueueNode;
        rear = newQueueNode;
    }
}

//removes element from the front of the Queue
void Queue::deQueue() {
    queueNode* delNode = front;
    if (delNode == nullptr) {
        cout << "WARNING: Queue is empty" << endl;
    }
    else {
        front = front->nextPtr;
        delete delNode;
        delNode = nullptr;
    }
}

//checks if Queue is empty (returns true if empty)
bool Queue::queueEmpty() {
    if (front == nullptr)
        return true;
    else
        return false;
}

//outputs the Queue information / required information
void Queue::printQueue(){
    cout << "\tTotal Customers Helped:  " << setw(5) << laneInfo.totalCustomers << endl;
    cout << "\tTotal Number of Items:   " << setw(5) << laneInfo.totalItems << endl;
    cout << "\tMax Line Length:         " << setw(5) << laneInfo.maxQueueLength << endl;
    cout << "\tTotal Idle Time:         " << setw(5) << laneInfo.totalIdleTime << endl;
    cout << "\tTotal Over Time:         " << setw(5) << laneInfo.totalOverTime << endl;
}

//returns the headPtr "front" data
queueNodeData Queue::peek(){
    return front->data;
}