#include "order.h"
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>


int getCurrentFloor(){
    int a = 1;
    while (a == 1){
        int floor = elevio_floorSensor();
        if (floor != -1){
            return floor;
        }
    }
}

void startElevator(){
    int a = 1;
    while (a == 1){
        int startFloor = getCurrentFloor();
        if (startFloor == 1){
            elevio_motorDirection(DIRN_STOP);
            a = 0;
        }
        if (startFloor > 1){
            elevio_motorDirection(DIRN_DOWN);
        }
        if (startFloor < 1){
            elevio_motorDirection(DIRN_UP);
        }
    }
}

/**
int queue[12][2];

void initQueue(int array[][]){
    for (int i; i < 12; i++){
        for (int j; j < 2; j++){
            array[i][j] = 0;
        }
    }
}
*/


/**
void addToOrders(){
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            int btnPressed = elevio_callButton(f, b);
            if (btnPressed){
                ordersMatrix[1][1] = f;
            }
        }
    }
}
*/

/**
void addToOrders(int *array[]){
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            int btnPressed = elevio_callButton(f, b);
            if (btnPressed){
                for (int i = 0; i < 12; i++){
                    if (array[i][0] == f && array[i][1] == b){
                        break;
                    }
                }
            }
        }
    }
}
*/