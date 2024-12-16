// NAMES: Shree, Elias, Cat
// COURSE: CS201 Problem Solving & Programming II

// PEOPLE WERE STUCK IN QUEUE, current min > head queue's exit time
// OUR SOLUTION: CHECK if current min >= head queue's exit time

//pre-processors
#include "LinkedList.h"
#include "Queue.h"
#include "function.h"
#include <iostream>
#include <random>
using namespace std;

int main() {
    // GET numQ from user
    int numQ = 0;
    while (numQ == 0 || numQ > 10) {
        cout << "Enter # of Checkout Lines (1-10): ";
        cin >> numQ;
        cout << endl;
        // CHECK numQ in range 1-10
        if (numQ > 10) {
            cout << "Can not exceed 10" << endl;
        }
        else if (numQ < 1) {
            cout << "Cannot be less than 1" << endl;
        }
    }

    // CREATE Linked List Customers & vector of Queues AllLanes
    Linked Customers;
    vector<Queue> Lanes;
    for (int i = 0; i < numQ; i++) {
        Queue checkoutLane;
        Lanes.push_back(checkoutLane);
    }

    // FUNCTION runs simulation with user defined numQ
    runStore(Customers, Lanes);

    // DISPLAY Queue Data
    for (int i = 0; i < Lanes.size(); i++) {
        cout << "\n\n************* LANE " << i << " ****************\n";
        Lanes[i].printQueue();
        cout << "\n\n--------------------------------------\n" << endl;
    }
}