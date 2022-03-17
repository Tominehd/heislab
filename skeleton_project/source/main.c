#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "elevdrive.h"
#include "elevfunk.h"
#include "orders.h"

//Hva mer må gjøres?
//Obstruksjon og stoppknapp
//Lys på etasjeknappene -M


int main(){

    elevio_init();
    validFloor();
    elevio_motorDirection(DIRN_STOP);
    closeElevatorDoor();

    printf("=== VELKOMMEN TIL HEISLAB! ===\n");
    printf("Press the stop button on the elevator panel to exit\n");  


    while(1){

        addToOrders();   

        if(getMatrixByIndex(0,0) != 9){
            driveElevator(getMatrixByIndex(0,0));
        }

        if(isObstructionButtonPushed()){
            obstruction();
        }
        
        if(isStopButtonPushed()){
            stopElevator();
        }

    }


    return 0;
}
