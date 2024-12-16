#pragma once
#include "LinkedList.h"
#include "Queue.h"
#include <iomanip>
#include <vector>
using namespace std;

//PRE:  Linked List & vector of queues created
//POST: While store open, each min randomly generate customer item # & shopping 
//      time, then assign enterQ time. At enterQ time, remove from list & add 
//      to queue. Remove from q at DQ time. Calculate maxqueue length. 
//      After store close, run overtime to check out remaining customers.
void runStore(Linked &Customerlist, vector <Queue> &AllLanes);

//PRE:  CustomerEnterQ time == i, vector of queues created
//POST: Finds shortest Queue, creates temp queueNode, assigns 
//      items & DQtime, adds to Queue, & increments lane totalItems,
//      queueCount, & totalCostumers
void enterCheckOutLane(vector <Queue> &AllLanes, dataType customerEnteringQ, int i);

//PRE:  Vector of queues created
//POST: DeQueues customer if current min >= head customer DQ time
//      & increments queue idle time during store hours
void exitCheckOutLane(vector <Queue> &AllLanes, int i);

//PRE:  Store closed (min 719 reached), Customerlist & AllLanes created
//POST: Calls enterCheckOutLane & exitCheckOutLane until store empty. 
//      Increments each Queues totalOverTime.
void overtime(Linked& Customerlist, vector <Queue>& AllLanes);