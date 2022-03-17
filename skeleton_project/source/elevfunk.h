/**
 * @file elevfunk.h
 * @brief this file handels the door, lights and buttons
 * 
 */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <pthread.h>
#include "driver/elevio.h"
#include "globalvar.h"

#pragma once

/**
 * @brief returns the value of isDoorOpen
 * @return isDoorOpen
 */

//Tilhørende get, så vi ikke får matrix problemet <3
int getIsDoorOpen();

/**
 * @brief turns of the doorlight
 * sets isDoorOpen = 0
 */
//Slukker dørlyset
void closeElevatorDoor();

/**
 * @brief turns on the dorlight
 * sets isDoorOpen = 1
 */
//Tenner dørlyset
void openElevatorDoor();

/**
 * @brief turns on the floorpanel light in the floor the elevator is in or was in last
 */
//Skrur på etasjelyset i etasjen heisen er i/ var i sist
void floorLight();

/**
 * @brief turns on the buttonlight
 * 
 * @param floor the floor the button is on
 * @param button type of button
 */
//Skrur på lyset
void buttonLampOn(int floor, int button);

/**
 * @brief turns of the buttonlight
 * 
 * @param floor the floor the button is on
 * @param button type of button
 */
//Skrur av lyset
void buttonLampOff(int floor, int button);

/**
 * @brief checks if the stop button is pushed
 * 
 * @return int, 1 if true
 */
//returnerer 1 om stop blir trykt på. Egentlig for mer lettleste if-setninger.
int isStopButtonPushed();

/**
 * @brief checks if the obstruction lever is down
 * 
 * @return int 1 if true
 */
// returnerer 1 om obstruksjon blir trykt på. 
int isObstructionButtonPushed();

