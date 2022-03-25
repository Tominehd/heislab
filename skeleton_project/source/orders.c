#include "orders.h"



int getMatrixByIndex(int col, int row){
    return ordersMatrix[col][row];
}


int getAnyOrders(){
    return getMatrixByIndex(0,0) != 9; 
}

int ordersGetFloor(){
    int currentFloor = elevio_floorSensor();
    if(currentFloor != -1){
        lastFloor  = currentFloor;
        return lastFloor;
    }
    return lastFloor;
}


int checkIfToBeAdded(int f, int b){
    for (int i = 0; i < 10; i++){
        if (ordersMatrix[i][0] == f && ordersMatrix[i][1] == b){
            return 0; //returnerer 0 om orderen er lagt til og går ut av funksjonen
        }
    }
    return 1;
}


int addToOrders(){
    //itterer gjennom alle knappene:
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            
            //Sjekker om knappen er trykket på:
            int btnPressed = elevio_callButton(f, b);
            
            //Sjekker om ordren allerede er lagt til:
            if (btnPressed && checkIfToBeAdded(f,b)){
                buttonLampOn(f, b);
                //Om orederen ikke finnes allrede legges den til den første linja i matrisa som ikke inneholder en ordre ({9,9})
                for (int i = 0; i < 10; i++){
                    if (ordersMatrix[i][0] == 9 && ordersMatrix[i][1] == 9){
                        ordersMatrix[i][0] = f;
                        ordersMatrix[i][1] = b;
                        return 1;
                    }
                    
                }
            }
        }
    }
    return 0;
}


//Returnerer 0, 1 og 2 for å matche ButtonType
int getOrderDirection(){
    int thisFloor = ordersGetFloor();
    if (ordersMatrix[0][0] > thisFloor){
        return 0;
    }
    else if (ordersMatrix[0][0] < thisFloor){
        return 1;
    }
    return 2;
}


void printOrders(){
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 2; j++){
            int a = ordersMatrix[i][j];
            printf(" %d ", a);
        }
        printf("\n");
    }
}

int checkOrdersThisFloor(){
    int thisFloor = ordersGetFloor();
    int orderDirection = getOrderDirection();
    int anyOrders = 0;

    for (int i = 0; i < 10; ++i){
        //Itterere gjennom ordrene og sjekker om den skal fjernes i denne etasjen
        if(ordersMatrix[i][0] == thisFloor && (ordersMatrix[i][1] == orderDirection ||  ordersMatrix[i][1] == 2 || orderDirection == 2)){
            buttonLampOff(getMatrixByIndex(i,0), getMatrixByIndex(i,1));
            //itererer gjennom ordrene i køen herfra og ned og flytter de et steg opp for å "rydde opp"
            for (int j = (i+1); j < 10; j++){
                ordersMatrix[j-1][0] = ordersMatrix[j][0];
                ordersMatrix[j-1][1] = ordersMatrix[j][1];
            }
            ordersMatrix[9][0] = 9;
            ordersMatrix[9][1] = 9;
            anyOrders = 1;
        }
    }

    return anyOrders;
}

void cleanOrders(){
    for (int i = 0; i < 10; i++){
                ordersMatrix[i][0] = 9;
                ordersMatrix[i][1] = 9;
            }
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            buttonLampOff(f,b); //Slår av alle lysene
        }
    }
    floorLight(); //Slår på lyset i etasjen man er i
}