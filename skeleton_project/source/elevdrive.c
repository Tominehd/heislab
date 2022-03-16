#include "elevdrive.h"

static int lastFloor = 0;



int getCurrentFloor(){
    return elevio_floorSensor();
}

int isStopButtonPushed(){
    return elevio_stopButton();
}

int isObstructionButtonPushed(){
    return elevio_obstruction();
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
//        saveDirection(DIRN_DOWN);
    }
    elevio_motorDirection(DIRN_STOP);
//    saveDirection(DIRN_STOP);

    lastFloor = getCurrentFloor(); //Hvorfor lagrer vi denne? -M Så lastFloor ikke starter på 1
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
    if(getDoorOpen() == 1){
       printf("Jeg blir også kjørt");
        elevio_motorDirection(DIRN_STOP); //Burde være av uansett da. Så vet ikke helt om det er nødvndig <3
    
        openElevatorDoor();
        while(isObstructionButtonPushed()){
          //  printf("Knappen er trykket på");
            addToOrders(); // Må være der så den tar imot ordre. Antar den kan ta imot ordre 
            checkOrdersThisFloor();
        }
        if(!isObstructionButtonPushed()){
                time_t seconds = time(NULL);
            while((time(NULL) - seconds) < 3){
                addToOrders(); // Må være der så den tar imot ordre. 
                checkOrdersThisFloor();
            }
            closeElevatorDoor();
        }
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

        if (getLastFloor() > targetFloor){
            elevio_motorDirection(DIRN_DOWN);
//            saveDirection(DIRN_DOWN); //hehe lurer igjen på hvorfor vi lagrer denne
        }
        else if( getLastFloor() < targetFloor){
            elevio_motorDirection(DIRN_UP);
//            saveDirection(DIRN_UP);
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

        floorLight();

        addToOrders();
    }  
    
    //Tror logikken i denne if-setningen gjør at heisen blir stuck om det går tomt for ordre
    if (getCurrentFloor() == targetFloor){
        elevio_motorDirection(DIRN_STOP);
//        saveDirection(DIRN_STOP);
        checkOrdersThisFloor();
        hasReachedTargetFloor();
    }

}