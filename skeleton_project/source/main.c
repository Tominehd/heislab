#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "order.h"

//Hei! Testing

//Køen. ordersMatrix[i][0] = etasje, ordersMatrix[i][1] = type knapp trykket
int ordersMatrix[12][2] = {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6};


//Sjekker om ordren allerede finnes i ordersMatrix, om ikke legges den til "nederst" i køen
int addToOrders(){
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            int btnPressed = elevio_callButton(f, b);
            if (btnPressed){
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
                        if (ordersMatrix[i][0] == 6 && ordersMatrix[i][1] == 6){
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
    int thisFloor = getCurrentFloor();
    if (ordersMatrix[0][0] > thisFloor){
        return 0;
    }
    else if (ordersMatrix[0][0] < thisFloor){
        return 1;
    }
    else if (ordersMatrix[0][0] == thisFloor){
        return 2;
    }
}


int checkOrdersThisFloor(){
    int thisFloor = getCurrentFloor();
    int ElevDirection = getElevDirection();

    for (int i = 0; i < 12; ++i){
        //tror denne if setningen virker
        if(ordersMatrix[i][0] == thisFloor && (ordersMatrix[i][1] == ElevDirection || ordersMatrix[i][1] == 2)){
            //itererer gjennom ordrene i køen herfra og ned og flytter de et steg opp for å "rydde opp"
            for (int j = (i+1); j < 12; j++){
                ordersMatrix[j-1][0] = ordersMatrix[j][0];
                ordersMatrix[j-1][1] = ordersMatrix[j][1];
            }
            ordersMatrix[11][0] = 6;
            ordersMatrix[11][1] = 6;
        }
    }
}


int main(){
    elevio_init();

    

    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    elevio_motorDirection(DIRN_UP);
    int a = 1;
    while (a == 1){
        if (getCurrentFloor() == 3){
            elevio_motorDirection(DIRN_STOP);
            a = 0;
        }
    }
    startElevator();


    while(1){
        /**
        int floor = elevio_floorSensor();
        printf("floor: %d \n",floor);

        if(floor == 0){
            elevio_motorDirection(DIRN_UP);
        }

        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        }
        */


        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
                
                //if (btnPressed){
                    
                //}
            }
        }

        addToOrders();
        checkOrdersThisFloor();

        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
        
 /**       
        if(elevio_callButton(1,BUTTON_CAB)){
            while(floor != 1){
                if (floor > 1){
                    elevio_motorDirection(DIRN_DOWN);
                }
                else if (floor < 1){
                    elevio_motorDirection(DIRN_UP);
                }
            }
            if (floor == 1){
                elevio_motorDirection(DIRN_STOP);
                //break;
            }
                
        }
 */       
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }
    
    /**
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 4; j++){
            printf("%d", ordersMatrix[i][j]);
        }
    }
    */
    
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
