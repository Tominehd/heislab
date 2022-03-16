#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

#pragma once


static int ordersMatrix[10][2];

//Denne gjør at vi kan hente ut elementene i den globale matrisen i main.
int getMatrixByIndex(int floor, int button);

//Denne funksjonen finnes i elevator og, men lagde den her i tillegg for å unngå at filene trenger å arve fra hverandre
int getFloor(); //testet -M

int checkIfAdded(int f, int b); //testet -M

int addToOrders();//Testet -M

//Returnerer 0 for oppover, 1 for nedover (for å matche ButtonType), 2 for i ro
int getOrderDirection();//Testet -M

//Bare en testfunksjon, virker som den skal
void printOrders();

//Denne sorterer køen, tanker er at den skal kjører hver gang heisen kommer til en ny etasje
int checkOrdersThisFloor();//Testet -M


