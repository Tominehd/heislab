#pragma once

#include "driver/elevio.h"

//Matrise inspirert av simulatormatrisa, tanken er at om en knapp er trykket skal den tilsvarende plassen endres til 1.


//Henter ut etasje uten -1 i mellom etasjene
int getCurrentFloor();

//Får heisen til å kjøre til 2.etasje og stoppe der
void startElevator();

//void initQueue(int array[][]);

//void addToOrders();

