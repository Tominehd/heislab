#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "fsm.h"
#include "elevdrive.h"
#include "elevfunk.h"
#include "orders.h"

//Hva mer må gjøres?
//Obstruksjon og stoppknapp
//Lys på etasjeknappene -M


int main(){

    elevio_init();
    validFloor();
    stopElevator();
    closeElevatorDoor();

    printf("=== VELKOMMEN TIL HEISLAB! ===\n");
    printf("Press the stop button on the elevator panel to exit\n");  


    while(1){

        addToOrders();   

//Kommentert ut for å teste funksjonene

        if(getMatrixByIndex(0,0) != 9){
            closeElevatorDoor(); //Trenger denne å kjøres her? -M
            driveElevator(getMatrixByIndex(0,0), getMatrixByIndex(0,1));
        }

        //Dette er eneste vi har om obstruksjo og stopp, det må fikses etterhvert -M
        if(isObstructionButtonPushed()){
            obstruction();
        }
        
        if(isStopButtonPushed()){
            stopElevator();
        }

        
    
        //Hva gjør denne? Skal den være her? -M
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

//   printOrders();

    return 0;
}
