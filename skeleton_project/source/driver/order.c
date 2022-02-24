#include "order.h"

void printOrders(struct Order* o){
    while( o != NULL){
        printf( " %d", o->floor);
        o = o->next;
    }
}
