#include "elevfunk.h"

int getIsDoorOpen(){
    return isDoorOpen;
}

void closeElevatorDoor(){
    isDoorOpen = 0;
    elevio_doorOpenLamp(0);
};


void openElevatorDoor(){
    isDoorOpen = 1;
    elevio_doorOpenLamp(1);
};


void floorLight(){
    if(getCurrentFloor() == -1){
        elevio_floorIndicator(getLastFloor());
    } 
    else{
        elevio_floorIndicator(getCurrentFloor());
    }
}


void buttonLampOn(int floor, int button){
    elevio_buttonLamp(floor, button, 1);
}

void buttonLampOff(int floor, int button){
    elevio_buttonLamp(floor, button, 0);
}

int isStopButtonPushed(){
    return elevio_stopButton();
}

int isObstructionButtonPushed(){
    return elevio_obstruction();
}
