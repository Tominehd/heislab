#include "orders.h"


static int ordersMatrix[12][2] = {{9,9},
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

int getFloor(){
    int currentFloor = elevio_floorSensor();
    int thisFloor = 0;
    if(currentFloor != -1){
        thisFloor  = currentFloor;
        return thisFloor;
    }
    return thisFloor;
}


int addToOrders(){
    printf ("addToOrders");
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
    int thisFloor = getFloor();
    if (ordersMatrix[0][0] > thisFloor){
        return 0;
    }
    else if (ordersMatrix[0][0] < thisFloor){
        return 1;
    }
    return 3;
}


int checkOrdersThisFloor(){
    int thisFloor = getFloor();
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