#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

#pragma once


static int ordersMatrix[10][2];

int getMatrixByIndex(int floor, int button);

//Denne funksjonen finnes i elevator og, men lagde den her i tillegg for å unngå at filene trenger å arve fra hverandre
int getFloor();

int checkIfAlreadyAdded(int f, int b);

int addToOrders();

//Returnerer 0 for oppover, 1 for nedover (for å matche ButtonType), 2 for i ro
int getOrderDirection();

void printOrders();

int checkOrdersThisFloor();


