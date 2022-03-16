#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>
#include "driver/elevio.h"

#pragma once

//Slukker dørlyset
void closeElevatorDoor();

//Tenner dørlyset
void openElevatorDoor();

//Skrur etasjelyset i etasjen heisen er i/var i sist, virker (er muligens litt treg)
void elevatorLight();

void buttonLampOn(int floor, ButtonType button);

void buttonLampOff(int floor, ButtonType button);
