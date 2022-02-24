#pragma once

#include "elevio.h"


#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>


struct Order {
    int floor;
    ButtonType upOrDown;
    struct Order* next;
};
 

void printOrders(struct Order* o);
