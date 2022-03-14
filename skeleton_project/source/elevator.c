#include "elevator.h"

static int lastFloor = 0;

int getCurrentFloor(){
    return elevio_floorSensor();
}


void closeElevatorDoor(){
    elevio_doorOpenLamp(0);
};


void openElevatorDoor(){
    elevio_doorOpenLamp(1);
};


int isAtTargetFloor(int targetFloor){
    if((getCurrentFloor() == targetFloor) ){
        return 1;
    }
    else{
        return 0;
    }
}


void validFloor(){
    while(elevio_floorSensor() ==  -1){
       elevio_motorDirection(DIRN_DOWN);
//       printf("Jeg blir kjørt");
    }
    elevio_motorDirection(DIRN_STOP);
    lastFloor = getCurrentFloor();
    printf("Etter valid floor %d \n", lastFloor);

}


int getLastFloor(){
    int currentFloor = getCurrentFloor();
    if(currentFloor != -1){
        lastFloor  = currentFloor;
        return lastFloor;
    }
    return lastFloor;
}


void elevatorLight(){
    if(getCurrentFloor() == -1 ) {
        elevio_floorIndicator(getLastFloor());
    } else{
        elevio_floorIndicator(getCurrentFloor());
    }
}


void hasReachedTargetFloor(){
    openElevatorDoor();
    elevio_motorDirection(DIRN_STOP);
    printf("Er her");
    elevatorLight();
    struct timespec remaining, request = {3, 500};
    nanosleep(&request, &remaining);

    closeElevatorDoor();
}


void stopElevator(){
    elevio_stopLamp(1);
    if(getCurrentFloor() != -1){
        openElevatorDoor();
    }
}


void driveElevator(int targetFloor, ButtonType b){
    printf("drive elevator");
    if(!(isAtTargetFloor(targetFloor))){

    // Først vil vi sjekke om vi skal opp eller ned
    
    //Floor -1 betyr at den er i en mellom stadie
        printf("Targetfloor: %d \n",targetFloor);
        printf("Floor: %d \n",getCurrentFloor());
        printf("Last floor: %d \n",getLastFloor());


        if (getLastFloor() > targetFloor){
            elevio_motorDirection(DIRN_DOWN);
        }

        else if( getLastFloor() < targetFloor){
            elevio_motorDirection(DIRN_UP);
        }


        if(getCurrentFloor() != -1){
            int ordersHere = checkOrdersThisFloor();
            checkOrdersThisFloor();
            if(ordersHere){
                hasReachedTargetFloor();
            }

        }
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);

        elevatorLight();

        addToOrders();
    }  
    
    printf("!!!!!!!!!!!!!!!!!!!!!");
    if (getCurrentFloor() == targetFloor){
        printf("Target floor er %d\n",targetFloor);
        printf(" vi er i etasje: %d ", getCurrentFloor());
        elevio_motorDirection(DIRN_STOP);
        printf("er her");
        checkOrdersThisFloor();
        hasReachedTargetFloor();
      
    }

    
    

//}
}