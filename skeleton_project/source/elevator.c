#include "elevator.h"
#include "orders.h"


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


void valid_floor(){
    while(elevio_floorSensor() ==  -1){
       elevio_motorDirection(DIRN_DOWN);
       printf("Jeg blir kjørt");
    }
    elevio_motorDirection(DIRN_STOP);
    lastFloor = getCurrentFloor();
    printf("Etter valid floor %d \n", lastFloor);

}


int get_lastFloor(){
    int currentFloor = getCurrentFloor();
    if(currentFloor != -1){
        lastFloor  = currentFloor;
        return lastFloor;
    }
    return lastFloor;
}


void elevatorLight(){
    if(getCurrentFloor() == -1 ) {
        elevio_floorIndicator(get_lastFloor());
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


//Returnerer 0 for oppover, 1 for nedover (for å matche ButtonType), 2 for i ro
int getElevDirection(){
    int thisFloor = get_lastFloor();
    if (ordersMatrix[0][0] > thisFloor){
        return 0;
    }
    else if (ordersMatrix[0][0] < thisFloor){
        return 1;
    }
    return 3;
}


void driveElevator(int targetFloor, ButtonType b){

    while(!(isAtTargetFloor(targetFloor))){

    // Først vil vi sjekke om vi skal opp eller ned
    
    //Floor -1 betyr at den er i en mellom stadie
        printf("Targetfloor: %d \n",targetFloor);
        printf("Floor: %d \n",getCurrentFloor());
        printf("Last floor: %d \n",get_lastFloor());


        if (get_lastFloor() > targetFloor){
            elevio_motorDirection(DIRN_DOWN);
        }

        else if( get_lastFloor() < targetFloor){
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
        elevio_motorDirection(DIRN_STOP);
        printf("er her");
        checkOrdersThisFloor();
        hasReachedTargetFloor();
      
    }

    
    

//}
}