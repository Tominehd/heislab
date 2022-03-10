#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

#pragma once


int ordersMatrix[12][2] = {{9,9},
                           {9,9},
                           {9,9},
                           {9,9},
                           {9,9},
                           {9,9},
                           {9,9},
                           {9,9},
                           {9,9},
                           {9,9},
                           {9,9},
                           {9,9}};


int addToOrders();

int checkOrdersThisFloor();
