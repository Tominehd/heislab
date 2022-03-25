#include "elevdrive.h"


int getCurrentFloor(){
    return elevio_floorSensor();
}

void validFloor(){
    
    while(getCurrentFloor() ==  -1){
        elevio_motorDirection(DIRN_DOWN);
    }
    elevio_motorDirection(DIRN_STOP);

    lastFloor = getCurrentFloor();
} 

int isAtTargetFloor(int targetFloor){
    if((getCurrentFloor() == targetFloor) ){
        return 1;
    }
    else{
        return 0;
    }
}


int getLastFloor(){
    int currentFloor = getCurrentFloor();
    if(currentFloor != -1){
        lastFloor  = currentFloor;
        return lastFloor;
    }
    return lastFloor;
}


void hasReachedTargetFloor(){
    
    openElevatorDoor();
    elevio_motorDirection(DIRN_STOP);
    floorLight();
    
    time_t seconds = time(NULL);

    while((time(NULL) - seconds) < 3){
        addToOrders();
        checkOrdersThisFloor();
        

        if(isObstructionButtonPushed()){
            obstruction();
        }
        
        if(isStopButtonPushed()){
            stopElevator();
        }

    }

    closeElevatorDoor();
}


void stopElevator(){
    elevio_motorDirection(DIRN_STOP);
    elevio_stopLamp(1);
    if(getCurrentFloor() != -1){
        openElevatorDoor();
    }
    cleanOrders();

    while(isStopButtonPushed()){
        elevio_stopLamp(1);
        obstruction();
    }

    elevio_stopLamp(0);

    printf("lyset er slått av");
    time_t seconds = time(NULL);

    while((time(NULL) - seconds) < 3){
        addToOrders();
        checkOrdersThisFloor();
        if(isObstructionButtonPushed()){
            obstruction();
        }

    }
    closeElevatorDoor();
}

void obstruction(){
    if(getIsDoorOpen()){

        while(isObstructionButtonPushed()){
            addToOrders();
            checkOrdersThisFloor();
        }

        time_t seconds = time(NULL);

        while((time(NULL) - seconds) < 3){
            addToOrders();
            checkOrdersThisFloor();
        }
        closeElevatorDoor();

    }
} 


void isAtFloor(){
    if(getCurrentFloor() != -1){
        
        int ordersHere = checkOrdersThisFloor(); //1 om det er ordre som skal utføres i denne etasjen, 0 ellers
        checkOrdersThisFloor();

        if(ordersHere){
            hasReachedTargetFloor();
        }
    }
}



void driveElevator(int targetFloor){

    if(!(isAtTargetFloor(targetFloor))){

    //Først vil vi sjekke om vi skal opp eller ned
    //Floor -1 betyr at den er i en mellom stadie

        if (getLastFloor() > targetFloor){
            elevio_motorDirection(DIRN_DOWN);
        }
        else if(getLastFloor() < targetFloor){
            elevio_motorDirection(DIRN_UP);
        }

        //Om heisen er i en etasje ryddes køa med checkOrdersThisFloor
        isAtFloor();

        floorLight();

        addToOrders();
    }  
    
    if (getCurrentFloor() == targetFloor){
        elevio_motorDirection(DIRN_STOP);
        checkOrdersThisFloor();
        hasReachedTargetFloor();
    }

}