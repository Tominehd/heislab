#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"

#pragma once

int lastFloor = 0;


int getCurrentFloor();

void closeElevatorDoor();

void openElevatorDoor();

int isAtTargetFloor(int targetFloor);

void valid_floor();

int get_lastFloor();

void elevatorLight();

void hasReachedTargetFloor();

void stopElevator();

//Returnerer 0 for oppover, 1 for nedover (for å matche ButtonType), 2 for i ro
int getElevDirection();

void driveElevator(int targetFloor, ButtonType b);