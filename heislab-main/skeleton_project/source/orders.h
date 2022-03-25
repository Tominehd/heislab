/**
 * @file orders.h
 * @brief this file handles the order system of the elevator
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "elevfunk.h"
#include "globalvar.h"

#pragma once

/**
 * @brief Get the Matrix By Index object
 * 
 * @param[in] col col-index
 * @param[in] row row-index
 * 
 * @return int, the stored order value on that index
 */
int getMatrixByIndex(int col, int row);

/**
 * @brief Returns true if the first element of the matrix is an order
 * returns false if not
 */
int getAnyOrders();

/**
 * @brief Get the value of the floor where the elevator is and updates the global variable lastFloor
 *  
 * @return int, the global variable lastFloor with the value of the floor the elevator is on or the last it was on
 */
int ordersGetFloor();

/**
 * @brief Checks if an order alredy exists in ordersMatrix
 * 
 * @param[in] f the floor the order goes to
 * @param[in] b the button pressed
 * 
 * @return int, 0 if the order already exists, 1 if it doesnt exist and should be added
 */
int checkIfToBeAdded(int f, int b);

/**
 * @brief Adds an order to ordersMatrix if checkIfToBeAdded returns 1
 * 
 * @return int, 1 if an order was added to ordersMatrix, 0 if not 
 */
int addToOrders();

/**
 * @brief Finds the direction the elevator is driving
 * based on the top order in ordersMatrix
 * @return int, 0 if the elevator is above the top order, 1 if the elevator is below it and 2 if the elevator is on the same floor
 */
int getOrderDirection();


/**
 * @brief prints orders in ordersMatrix
 */
void printOrders();

/**
 * @brief checks if there are any orders in ordersMatrix for the floor the elevator is on.
 * Deletes the orders for this floor.
 * 
 * @return int, 0 if no orders was deleted, 1 if any was
 */
int checkOrdersThisFloor();

/**
 * @brief deletes all orders in ordersMatrix, and fills if with 9 on all indexes
 */
void cleanOrders();



