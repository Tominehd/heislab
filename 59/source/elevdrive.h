/**
 * @file elevdrive.h
 * @brief this file handels the funksjons that get the elevator to drive
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "elevio.h"
#include "orders.h"
#include "elevfunk.h"


#pragma once

/**
 * @brief Gets the value for where the elevator is
 * 
 * @return -1 inbetween floors, 0 in first floor, 1 in second floor, and so on...
 */
int getCurrentFloor();

/**
 * @brief makes sure the elevator does not start in between floors when initalized
 * The elevator will drive down to the nearest valid floor and stop
 */
void validFloor(); 

/**
 * @brief Checks if the elevator is at targetFloor
 * 
 * @param[in] targetFloor the floor the elevator is going to
 * @return int, 1 if the elevator is at the same floor as @p targetFloor retruns 0 if not
 */
int isAtTargetFloor(int targetFloor);

/**
 * @brief Get the value of the floor the elevator is on
 * 
 * @return int, if the elevator is inbetween floors the last floor the elevator was on is returned
 * if the elevators is on a floor, that floor is returned
 */
int getLastFloor();

/**
 * @brief Get the elevator to do everything it should do when it stops on a floor
 * turns on the door light, stops the elevator, wait 3 sec, turns of the door light
 */
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
 * if it returns 1 (there are orders to this floor), it calls hasReachedTargetFloor
 */
void isAtFloor();


/**
 * @brief calls the other functions together to make the elevator drive as it should
 * 
 * @param[in] targetFloor the floor the elevator is going to (the top order in ordersMatix)
 */
void driveElevator(int targetFloor);
