#include "elevdrive.h"


int getCurrentFloor(){
    return elevio_floorSensor();
}

int isAtTargetFloor(int targetFloor){
    if((getCurrentFloor() == targetFloor) ){
        return 1;
    }
    else{
        return 0;
    }
}


void validFloor(){
    
    while(getCurrentFloor() ==  -1){
        elevio_motorDirection(DIRN_DOWN);
    }
    elevio_motorDirection(DIRN_STOP);

    lastFloor = getCurrentFloor();
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
    }

    elevio_stopLamp(0);

    time_t seconds = time(NULL);

        while((time(NULL) - seconds) < 3){
        addToOrders(); // Må være der så den tar imot ordre. 
        checkOrdersThisFloor();

    }
    closeElevatorDoor();
}

void obstruction(){
    if(getIsDoorOpen() == 1){

        while(isObstructionButtonPushed()){
            addToOrders(); // Må være der så den tar imot ordre. Antar den kan ta imot ordre 
            checkOrdersThisFloor();
        }

        time_t seconds = time(NULL);

        while((time(NULL) - seconds) < 3){
            addToOrders(); // Må være der så den tar imot ordre. 
            checkOrdersThisFloor();
        }
        closeElevatorDoor();

    }
} 

void driveElevator(int targetFloor){

    if(!(isAtTargetFloor(targetFloor))){

    //Først vil vi sjekke om vi skal opp eller ned
    //Floor -1 betyr at den er i en mellom stadie

        if (getLastFloor() > targetFloor){
            elevio_motorDirection(DIRN_DOWN);
        }
        else if( getLastFloor() < targetFloor){
            elevio_motorDirection(DIRN_UP);
        }

        //Om heisen er i en etasje ryddes køa med checkOrdersThisFloor
        if(getCurrentFloor() != -1){
            int ordersHere = checkOrdersThisFloor(); //1 om det er ordre som skal utføres i denne etasjen, 0 ellers
            checkOrdersThisFloor(); //trenger denne å kjøres to ganger slik?
            //Om det var ordre som ble ryddet her, kjøres åpne dør rutinen.
            if(ordersHere){
                hasReachedTargetFloor();
            }

        }

        floorLight();

        addToOrders();
    }  
    
    //Tror logikken i denne if-setningen gjør at heisen blir stuck om det går tomt for ordre
    if (getCurrentFloor() == targetFloor){
        elevio_motorDirection(DIRN_STOP);
        checkOrdersThisFloor();
        hasReachedTargetFloor();
    }

}