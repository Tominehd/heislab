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
    closeElevatorDoor();

    while(1){

        addToOrders();   

        if(getAnyOrders()){
            driveElevator(getMatrixByIndex(0,0));
        }
     
        if(isStopButtonPushed()){
            stopElevator();
        }

    }


    return 0;
}
