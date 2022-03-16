#include "elevfunk.h"

void closeElevatorDoor(){
    elevio_doorOpenLamp(0);
};


void openElevatorDoor(){
    elevio_doorOpenLamp(1);
};


void elevatorLight(){
    if(getCurrentFloor() == -1){
        elevio_floorIndicator(getLastFloor());
    } 
    else{
        elevio_floorIndicator(getCurrentFloor());
    }
}

void buttonLampOn(int floor, ButtonType button){
    elevio_buttonLamp(floor, button, 1);
}

void buttonLampOff(int floor, ButtonType button){
    elevio_buttonLamp(floor, button, 0);
}