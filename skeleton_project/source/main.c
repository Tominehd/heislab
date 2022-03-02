#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "fsm.h"

//Hei! Testing



int getCurrentFloor(){
    return elevio_floorSensor();
}

void openElevatorDoor(){
    elevio_doorOpenLamp(1);
};

void closeElevatorDoor(){
    elevio_closeDoorLamp(0);
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
    //nanosleep((const struct timespec[]){{0, 30*00000000L}}, NULL);
}

void driveElevator(int targetFloor, ButtonType b, int lastFloor){

    printf("Blir funksjonen kjørt");


    if(b == BUTTON_CAB){
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
    

        }  
        
        printf("!!!!!!!!!!!!!!!!!!!!!");
         if ( getCurrentFloor() == targetFloor){
                elevio_motorDirection(DIRN_STOP);
                printf("er her");
                hasReachedTargetFloor();
            }

       

    }

}


void valid_floor(){
    while(elevio_floorSensor() ==  -1){
       elevio_motorDirection(DIRN_DOWN);
       printf("Jeg blir kjørt");
    }
    elevio_motorDirection(DIRN_STOP);
}


int lastFloor;

int get_lastFloor(){
    if(getCurrentFloor() != -1){
        int lastFloor = getCurrentFloor();
    }
    
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
        int lastFloor;


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
                    driveElevator(f,b,lastFloor);
                    closeElevatorDoor();
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
