#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "elevdrive.h"
#include "elevfunk.h"
#include "orders.h"


int main(){

    elevio_init();
    validFloor();
    elevio_motorDirection(DIRN_STOP);
    closeElevatorDoor();

    while(1){

        addToOrders();   

        if(anyOrders()){
            driveElevator(getMatrixByIndex(0,0));
        }
     
        if(isStopButtonPushed()){
            stopElevator();
        }

    }


    return 0;
}
