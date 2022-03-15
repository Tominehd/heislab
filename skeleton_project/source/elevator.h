#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "orders.h"

#pragma once


//Er denne globae variabelen nødvendig?
static int lastFloor;

MotorDirection dir;

void saveDirection(MotorDirection m);

MotorDirection getMotorDirection();

int getCurrentFloor();

void closeElevatorDoor();

void openElevatorDoor();

int isAtTargetFloor(int targetFloor);

void validFloor();

int getLastFloor();

void elevatorLight();

void hasReachedTargetFloor();

void stopElevator();

void driveElevator(int targetFloor, ButtonType b);