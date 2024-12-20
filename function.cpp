#include "function.h"

void enterCheckOutLane(vector<Queue> &AllLanes, dataType customerEnteringQ,int i) {
    // ADDS CUSTOMER TO SHORTEST QUEUE

    // INITIALIZE shortestIndex to the first lane
    int shortestIndex = 0;
    // ITERATE over all lanes & compare # items
    for (int c = 0; c < AllLanes.size(); c++) {
        int tempItems = AllLanes.at(c).laneInfo.currItems;
        // REASSIGN shortestIndex IF tempItems shorter
        if (tempItems < AllLanes[shortestIndex].laneInfo.currItems) {
            shortestIndex = c;
        }
    }
    // CREATE queueNodeData temp, assign customer's item # & increase lane item count
    queueNodeData temp{};
    temp.itemCount = customerEnteringQ.itemCount;
    AllLanes[shortestIndex].laneInfo.currItems += temp.itemCount;

    // ASSIGN DeQueue time
    // IF checkout length < 1, ASSIGN current min + 1
    if ((AllLanes[shortestIndex].laneInfo.currItems * .15) < 1) {
        temp.timeDQ = i + 1;
    }
        // ELSE ASSIGN checkout length + current min
    else {
        temp.timeDQ = static_cast<int>(AllLanes[shortestIndex].laneInfo.currItems * .15) + i;
    }

    // INCREASE lane totalItems, queueCount, & totalCostumers
    AllLanes[shortestIndex].laneInfo.totalItems += temp.itemCount;
    AllLanes[shortestIndex].laneInfo.queueCount++;
    AllLanes[shortestIndex].laneInfo.totalCustomers++;

    // ADD temp to shortest lane
    AllLanes[shortestIndex].enQueue(temp);
}

void exitCheckOutLane(vector<Queue> &AllLanes, int i) {
    // DEQUEUES CUSTOMER FROM QUEUE & CALCULATES IDLE TIME

    for (auto & AllLane : AllLanes) {
        // INCREMENTS idleTime if Q empty & during store hours
        if (AllLane.queueEmpty() && i <= 719) {
            AllLane.laneInfo.totalIdleTime++;
        }
        // DEQUEUES head Customer if current time >= customer DQ time
        while (!(AllLane.queueEmpty()) && i >= AllLane.peek().timeDQ) {
            // REMOVES head customer items
            AllLane.laneInfo.currItems -= AllLane.peek().itemCount;
            // DQ customer
            AllLane.deQueue();
            // DECREMENT Q count
            AllLane.laneInfo.queueCount--;
        }
    }
}

void runStore(Linked &Customerlist, vector<Queue> &AllLanes) {
    // ITERATE min 0-719 (9AM-9PM)
    for (int i = 0; i < 720; i++) {
        // RANDOMLY assign # of new customers 1-3
        int people = rand() % 3 + 1;
        // FOR EACH CUSTOMER
        for (int j = 0; j < people; j++) {
            // RANDOMLY assign shop time 30-60 seconds
            int shopTime = rand() % 30 + 31;

            // RANDOMLY assign number of items
            int items = rand() % 10 + 1;
            if (items == 1) {
                items = rand() % 30 + 31;
            } else if (items <= 3) {
                items = rand() % 10 + 21;
            } else if (items <= 6) {
                items = rand() % 10 + 11;
            } else {
                items = rand() % 10 + 1;
            }

            // CREATE tempCustomer, ASSIGN itemCount & enterQTime
            dataType tempCustomer{};
            tempCustomer.itemCount = items;
            tempCustomer.enterQTime = (shopTime * items) / 60 + i;

            // INCREMENT listCount, ASSIGN as cart ID for tempCustomer
            Linked::listCount++;
            int tempCartID = Linked::listCount;
            tempCustomer.cartId = tempCartID;

            // ADD tempCustomer to LinkedList
            Customerlist.addElement(tempCustomer);
        }

        // DQ Customers
        exitCheckOutLane(AllLanes, i);

        // MOVE headCustomer from list to queue if i == enterQTime
        while (i == Customerlist.peek().enterQTime) {
            dataType customerEnteringQ{};
            customerEnteringQ = Customerlist.peek();
            enterCheckOutLane(AllLanes, customerEnteringQ, i);
            // DELETE customer from linkedList
            Customerlist.delElement();
        }

        // REASSIGN maxQLength if current length > max
        for (auto & AllLane : AllLanes) {
            // IF QUEUE NOT EMPTY
            if (!AllLane.queueEmpty()) {
                // IF CURRENT # CUSTOMERS IN QUEUE > MAX Q
                if (AllLane.laneInfo.queueCount >
                    AllLane.laneInfo.maxQueueLength) {
                    // REASSIGN MAX
                    AllLane.laneInfo.maxQueueLength = AllLane.laneInfo.queueCount;
                }
            }
        }
    }
    // LAST ITERATION 719 COMPLETE -- CALL OVERTIME
    overtime(Customerlist, AllLanes);
}

void overtime(Linked &Customerlist, vector<Queue> &AllLanes) {
    int currentMin = 720;
    // ITERATE until list empty
    while (!Customerlist.listIsEmpty()) {
        // DQ customers
        exitCheckOutLane(AllLanes, currentMin);

        // CUSTOMERS enterQ
        while (!Customerlist.listIsEmpty() &&
               currentMin == Customerlist.peek().enterQTime) {
            dataType customerEnteringQ{};
            customerEnteringQ = Customerlist.peek();
            enterCheckOutLane(AllLanes, customerEnteringQ, currentMin);
            // DELETE customer from list
            Customerlist.delElement();
        }
        // INCREMENT MIN
        currentMin++;
        // INCREMENT totalOverTime IF queue NOT empty
        for (auto & AllLane : AllLanes) {
            if (!AllLane.queueEmpty()) {
                AllLane.laneInfo.totalOverTime++;
            }
        }
    }

    // ITERATE until Q empty
    while (true) {
        // CHECKOUT customers
        exitCheckOutLane(AllLanes, currentMin);
        // INCREMENT min
        currentMin++;
        // INCREMENT totalOverTime IF queue NOT empty
        for (auto & AllLane : AllLanes) {
            if (!AllLane.queueEmpty()) {
                AllLane.laneInfo.totalOverTime++;
            }
        }
        // CHECK IF PEOPLE STILL IN STORE
        bool peopleInStore = false;
        for (auto & AllLane : AllLanes) {
            if (!AllLane.queueEmpty()) {
                peopleInStore = true;
                break;
            }
        }
        // IF store empty, BREAK from iteration
        if (!peopleInStore) {
            break;
        }
    }
}