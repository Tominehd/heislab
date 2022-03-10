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

//Køen. ordersMatrix[i][0] = etasje, ordersMatrix[i][1] = type knapp trykket
int ordersMatrix[12][2] = {{9,9},
                           {9,9},
                           {9,9},
                           {9,9},
                           {9,9},
                           {9,9},
                           {9,9},
                           {9,9},
                           {9,9},
                           {9,9},
                           {9,9},
                           {9,9}};


int lastFloor = 0;

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

int addToOrders(){
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            int btnPressed = elevio_callButton(f, b);
            elevio_buttonLamp(f, b, btnPressed);
            if (btnPressed){
                //printf("registert at knapp er trykket på");
                //Sjekker før om denne ordren allerede er lagt til
                for (int i = 0; i < 12; i++){
                    for (int j = 0; j < 2; j++){
                        if (ordersMatrix[i][0] == f && ordersMatrix[i][1] == b){
                            return 0; //returnerer 0 om orderen er lagt til og går ut av funksjonen
                        }
                    }
                }
                //Om orederen ikke finnes allrede legges den til den første linja i matrisa som ikke inneholder en ordre ({6,6})
                for (int i = 0; i < 12; i++){
                    for (int j = 0; j < 2; j++){
                        if (ordersMatrix[i][0] == 9 && ordersMatrix[i][1] == 9){
                            ordersMatrix[i][0] = f;
                            ordersMatrix[i][1] = b;
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 1; //Bare for at noe skal returneres uansett
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


int checkOrdersThisFloor(){
    int thisFloor = get_lastFloor();
    int ElevDirection = getElevDirection();
    int anyOrders = 0; //Forblir 0 om det ikke er noen ordre i denne etasjen, blir 1 om det er det

    for (int i = 0; i < 12; ++i){
        //tror denne if setningen virker
        if(ordersMatrix[i][0] == thisFloor && (ordersMatrix[i][1] == ElevDirection || ElevDirection == 3 || ordersMatrix[i][1] == 2)){
            //itererer gjennom ordrene i køen herfra og ned og flytter de et steg opp for å "rydde opp"
            for (int j = (i+1); j < 12; j++){
                ordersMatrix[j-1][0] = ordersMatrix[j][0];
                ordersMatrix[j-1][1] = ordersMatrix[j][1];
            }
            ordersMatrix[11][0] = 9;
            ordersMatrix[11][1] = 9;
            anyOrders = 1;
        }
    }

    for (int i = 0; i < 12; i++){
        for (int j = 0; j < 2; j++){
            int a = ordersMatrix[i][j];
            printf(" %d ", a);
            printf("%d", i);
            printf("%d", j);
        }
    printf("\n");
    }

    return anyOrders;
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



int main(){
    elevio_init();

    //orders_start();
    
    printf("=== VELKOMMEN TIL HEISLAB! ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    //elevio_motorDirection(DIRN_UP);   

    
    valid_floor();

    while(1){

        int floor = elevio_floorSensor();
        

//        if(floor != -1){
//            printf("floor: %d \n",floor); }

        if(floor == 0){
            elevio_motorDirection(DIRN_STOP);
        }

        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_STOP);
        }

       
        addToOrders();
        if(ordersMatrix[0][0] != 9){
            closeElevatorDoor();
            driveElevator(ordersMatrix[0][0], ordersMatrix[0][1]);
        }

        /**
        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
                if(btnPressed){
                    printf("Knapp er trykket på, ønsker å dra til: %d \n",f);
                    closeElevatorDoor();
                    addToOrders();
                    driveElevator(f,b,lastFloor);
                }
            }
        }

        
        */

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

    for (int i = 0; i < 12; i++){
        for (int j = 0; j < 2; j++){
            int a = ordersMatrix[i][j];
            printf(" %d ", a);
            printf("%d", i);
            printf("%d", j);
        }
    printf("\n");
    }   

    return 0;
}
