#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

#pragma once


static int ordersMatrix[12][2];

//Denne funksjonen finnes i elevator og, men lagde den her i tillegg for å unngå at filene trenger å arve fra hverandre
int getFloor();

int addToOrders();

//Returnerer 0 for oppover, 1 for nedover (for å matche ButtonType), 2 for i ro
int getElevDirection();

int checkOrdersThisFloor();
