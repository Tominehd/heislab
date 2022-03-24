/**
 * @file elevdrive.h
 * @brief this file handels the funksjons that get the elevator to drive
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "orders.h"
#include "elevfunk.h"


#pragma once

/**
 * @brief Gets the value for where the elevator is
 * 
 * @return -1 inbetween floors, 0 in first floor, 1 in second floor, and so on...
 */
//Returnerer etasjen heisen er i eller -1 om den er i mellom etasjer
int getCurrentFloor();

/**
 * @brief Checks if the elevator is at targetFloor
 * 
 * @param[in] targetFloor the floor the elevator is going to
 * @return int, 1 if the elevator is at the same floor as @p targetFloor retruns 0 if not
 */
//Returnerer 1 om heisen er i targetFloor, returnerer 0 ellers
int isAtTargetFloor(int targetFloor);

/**
 * @brief makes sure the elevator doesnt start in between floors when initalized
 * The elevator will drive downwars to the nearest valid floor and stop
 */
void validFloor(); 

/**
 * @brief Get the value of the floor the elevator is on
 * 
 * @return int, if the elevator is inbetween floors the elevator return the last floor
 * if the elevators is on a floor, that floor is returned
 */
int getLastFloor();

/**
 * @brief Get the elevator to do everything it should do when it stops on a floor
 * turns on the door light, stops the elevator, wait 3 sec, turns of the door light
 */
//Skrur på dørlyset, holder døren åpen i 3 sekunder, skrur av dørlyset
void hasReachedTargetFloor();

/**
 * @brief Get the elevator to do everything it should do when the stop button is pressed
 * stops the elevator, turnd on the stoplamp, open the door if the elevator is on a valid floor,
 * delets all the orders in ordersMatrix, keeps the door open for three seconds after the button is released
 */
void stopElevator();

/**
 * @brief if the obstruction flip is switched and the door is open, the door stay open
 * if the flip is switched back the door closes after three seconds
 */
void obstruction();

/**
 * @brief calls checkOrdersThisFloor
 * if 
 */
void isAtFloor();


/**
 * @brief calls the other functions together to make the elevator drive as it should
 * 
 * @param targetFloor the floor the elevator is going to (the top order in ordersMatix)
 */
void driveElevator(int targetFloor);
