// pre-processor
#pragma once

//queueNodeData struct to store all data for the Queues
struct queueNodeData {
    int timeDQ;       // clock time when the customer is dequeued
    int itemCount;    // the number of items for the customer
};

// queueNode struct used to define nodes in the Queue
struct queueNode {
    queueNodeData data;
    queueNode *nextPtr;
};

//structure to keep track of data for EACH Queue
struct queueData {
    int queueCount = 0;
    int totalIdleTime = 0;
    int totalOverTime = 0;
    int maxQueueLength = 0;
    int currItems = 0;
    int totalItems = 0;
    int totalCustomers = 0;
};

// Queue class declaration
class Queue {
private:
    queueNode *front;
    queueNode *rear;
public:
    Queue(); //default constructor
    ~Queue(); //destructor
    //function declarations
    queueNode *getRear() { return rear; } //unused
    void enQueue(queueNodeData d);
    void deQueue();
    queueNodeData peek();
    bool queueEmpty();
    void printQueue() const;
    //queueData struct
    queueData laneInfo;
};