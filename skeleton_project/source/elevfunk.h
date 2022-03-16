//#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>
#include "driver/elevio.h"

#pragma once

//Trenger den som obstruksjon kun blir kjørt når døren er åpen
int static isDoorOpen = 0;

//Tilhørende get, så vi ikke får matrix problemet <3
int getDoorOpen();

//Slukker dørlyset
void closeElevatorDoor();

//Tenner dørlyset
void openElevatorDoor();

//Skrur etasjelyset i etasjen heisen er i/var i sist, virker (er muligens litt treg)
void floorLight();

void buttonLampOn(int floor, int button);

void buttonLampOff(int floor, int button);
