#include "elevator.h"

static int lastFloor = 0;

void saveDirection(MotorDirection m){
    dir = m;
}

MotorDirection getMotorDirection(){
    return dir;
}

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
    
    while(getCurrentFloor() ==  -1){
        elevio_motorDirection(DIRN_DOWN);
        saveDirection(DIRN_DOWN);
    }
    elevio_motorDirection(DIRN_STOP);
    saveDirection(DIRN_STOP);

    lastFloor = getCurrentFloor(); //Hvorfor lagrer vi denne? -M
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
    if(getCurrentFloor() == -1){
        elevio_floorIndicator(getLastFloor());
    } 
    else{
        elevio_floorIndicator(getCurrentFloor());
    }
}


void hasReachedTargetFloor(){
    
    openElevatorDoor();
    elevio_motorDirection(DIRN_STOP);
    elevatorLight();
    
    time_t seconds = time(NULL);

    while((time(NULL) - seconds) < 3){
        addToOrders();
        //stop
        //obstruct
        //keepsLights
    }

    //struct timespec remaining, request = {3, 500};
    //nanosleep(&request, &remaining);

    closeElevatorDoor();
}

//Denne brukes ikke til noe enda
void stopElevator(){
    elevio_stopLamp(1);
    if(getCurrentFloor() != -1){
        openElevatorDoor();
    }
}


void driveElevator(int targetFloor, ButtonType b){

/** //Denne if setningen gjør vel ingenting?
    if(elevio_floorSensor()== -1){
    }
*/

    if(!(isAtTargetFloor(targetFloor))){

    //Først vil vi sjekke om vi skal opp eller ned
    //Floor -1 betyr at den er i en mellom stadie
        
        printf("Targetfloor %d", targetFloor);
        printf("Lastfloor %d", getLastFloor());
        printf("Floor %d", getFloor());
        printf("Current floor %d", getCurrentFloor());

        if (getLastFloor() > targetFloor){
            elevio_motorDirection(DIRN_DOWN);
            saveDirection(DIRN_DOWN); //hehe lurer igjen på hvorfor vi lagrer denne
        }
        else if( getLastFloor() < targetFloor){
            elevio_motorDirection(DIRN_UP);
            saveDirection(DIRN_UP);
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
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);

        elevatorLight();

        addToOrders();
    }  
    
    //Tror logikken i denne if-setningen gjør at heisen blir stuck om det går tomt for ordre
    printOrders();
    if (getCurrentFloor() == targetFloor){
        checkOrdersThisFloor();
        saveDirection(DIRN_STOP);
        hasReachedTargetFloor();
    }

}