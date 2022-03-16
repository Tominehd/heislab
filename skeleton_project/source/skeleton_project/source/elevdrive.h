#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "orders.h"
#include "elevfunk.h"

#pragma once


//trenger vi globale variabler her? -M
static int lastFloor;

//Returnerer etasjen heisen er i eller -1 om den er i mellom etasjer
int getCurrentFloor();

//Returnerer 1 om heisen er i targetFloor, returnerer 0 ellers
int isAtTargetFloor(int targetFloor); //Testet -M

//Sørger for at heisen kjører og stopper i nærmeste etasje under seg når den starter
//Lagrer også etasen i den globale variabelen lastFloor (hvorfor det?)
void validFloor(); //Testet -M

//Returnerer forige etasje heisen var i eller den de er i nå
int getLastFloor(); //Tullet når jeg skrev testen, men skal virke

//Skrur på dørlyset, holder døren åpen i 3 sekunder (noe legre?), skrur av dørlyset
//Mens døren er åpen tar ikke heisen i mot ordre. Tror det er her problemet ligger -M
//Funker ellers som den skal -M
void hasReachedTargetFloor();

//Skal tenne stoplampa og åpne døra om heisen er i en etasje
//Syns koden ser god ut, men fikk ikke helt til å teste den -M
//Den er ikke i bruk enda
void stopElevator();

void driveElevator(int targetFloor, ButtonType b);