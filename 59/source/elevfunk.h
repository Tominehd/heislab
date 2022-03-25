/**
 * @file elevfunk.h
 * @brief this file handels the door, lights and buttons
 */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>
#include "elevio.h"
#include "globalvar.h"

#pragma once

/**
 * @brief returns the value of isDoorOpen
 * @return isDoorOpen
 */
int getIsDoorOpen();

/**
 * @brief turns of the doorlight
 * sets isDoorOpen = 0
 */
void closeElevatorDoor();

/**
 * @brief turns on the doorlight
 * sets isDoorOpen = 1
 */
void openElevatorDoor();

/**
 * @brief turns on the floorpanel light in the floor the elevator is on or was on last
 */
void floorLight();

/**
 * @brief turns on the buttonlight
 * 
 * @param[in] floor the floor the button is on
 * @param[in] button type of button
 */
void buttonLampOn(int floor, int button);

/**
 * @brief turns of the buttonlight
 * 
 * @param[in] floor the floor the button is on
 * @param[in] button type of button
 */
void buttonLampOff(int floor, int button);

/**
 * @brief checks if the stop button is pushed
 * 
 * @return int, 1 if true
 */
int isStopButtonPushed();

/**
 * @brief checks if the obstruction lever is down
 * 
 * @return int 1 if true
 */
int isObstructionButtonPushed();

