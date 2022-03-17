/**
 * @file globalvar.h
 * @brief this file contains our global variables
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#pragma once

/**
 * @brief a matrix to keep track of the orders
 * 
 */
static int ordersMatrix[10][2];


/**
 * @brief keeps track of where the elevator is
 * if the elevator is inbetween floors, is lastFloor the last floor the elevator was in
 */
static int lastFloor;

/**
 * @brief keeps track of whether the door is open or not
 * 0 if the door is closes, 1 if it is open
 */
int static isDoorOpen;
