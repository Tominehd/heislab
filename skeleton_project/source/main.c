#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "fsm.h"

//Hei! Testing

//Hva mer må gjøres

// Obstruksjon og stoppknapp
// Klare å ta imot ordere mellom etasjer
// Få en ordning som sorterer koden

int orders[4][4] = {
    {0,0,0,0},
    {1,0,0,0},
    {2,0,0,0},
    {3,0,0,0}
};


int lastFloor = 0;

int getCurrentFloor(){
    return elevio_floorSensor();
}



void openElevatorDoor(){
    elevio_doorOpenLamp(1);
};

void closeElevatorDoor(){
    elevio_doorOpenLamp(0);
};


int isAtTargetFloor(int targetFloor){
    if((getCurrentFloor() == targetFloor) ){
        return 1;
    }
    else{
        return 0;
    }
}

void hasReachedTargetFloor(){
        openElevatorDoor();
        elevio_motorDirection(DIRN_STOP);
        printf("Er her");

        struct timespec remaining, request = {3, 500};
        int response = nanosleep(&request, &remaining);

        closeElevatorDoor();
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
        printf("Etter last floor %d \n", lastFloor);
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

void stopElevator(){
    elevio_stopLamp(1);
    if(getCurrentFloor() != -1){
        openElevatorDoor();
    }
}

void driveElevator(int targetFloor, ButtonType b, int lastFloor){

    printf("Blir funksjonen kjørt");

    //if(b == BUTTON_CAB){
        printf("Knappen er cab");


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

            nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    
            elevatorLight();
        }  
        
        printf("!!!!!!!!!!!!!!!!!!!!!");
         if ( getCurrentFloor() == targetFloor){
                elevio_motorDirection(DIRN_STOP);
                printf("er her");
                hasReachedTargetFloor();

                elevatorLight();
            }

        
     

    //}

}



int main(){
    elevio_init();

    //orders_start();
    
    printf("=== VELKOMMEN TIL HEISLAB! ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    //elevio_motorDirection(DIRN_UP);   

    
    valid_floor();

    while(1){
        int floor = elevio_floorSensor();
        

        if(floor != -1){
            printf("floor: %d \n",floor); }

        if(floor == 0){
            elevio_motorDirection(DIRN_STOP);
        }

        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_STOP);
        }


        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
                if(btnPressed){
                    printf("Knapp er trykket på, ønsker å dra til: %d \n",f);
                    closeElevatorDoor();

                    driveElevator(f,b,lastFloor);
                }
            }
        }
        

        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
        
        

        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }


    return 0;
}
