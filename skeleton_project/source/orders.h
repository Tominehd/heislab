/**
 * @file orders.h
 * @brief this file handles the order system of the elevator
 * 
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
 * @param col[in] col index
 * @param row[in] row index
 * @return int the stored order value on that index
 */
//Denne gjør at vi kan hente ut elementene i den globale matrisen i main.
int getMatrixByIndex(int col, int row);

/**
 * @brief Get the value of the floor the elevator is on
 * 
 * @return int, the floor the elevator is on or the last it was on
 */
//Denne funksjonen finnes i elevator og, men lagde den her i tillegg for å unngå at filene trenger å arve fra hverandre
int getFloor();

/**
 * @brief Checks if a order is alredy exists in orderMatrix
 * 
 * @param f floor the order goes to
 * @param b button pressed
 * @return int, 0 if the order alredy exist, 1 if it should be added
 */
int checkIfToBeAdded(int f, int b);

/**
 * @brief Adds an order to orderMatrix if checkIfToBeAdded returns 1
 * 
 * @return int, 1 if an order was added to orderMatrix, 0 if not 
 */
int addToOrders();

/**
 * @brief Finds the direction the elevator is driving
 * based on the top order in orderMatrix
 * @return int, 0 if the elevator is abow the top order, 1 if the elevator is below it and 2 if the elevator is in the same floor
 */
//Returnerer 0 for oppover, 1 for nedover (for å matche ButtonType), 2 for i ro
int getOrderDirection();//Testet -M

/**
 * @brief prints orderMatrix
 */
//Bare en testfunksjon, virker som den skal
void printOrders();

/**
 * @brief checks if there is any orders in orderMatrix for the floor the elevator is on.
 * Deletes the orders for this floor.
 * 
 * @return int, 0 if no orders was deleted, 1 if any was
 */
//Denne sorterer køen, tanker er at den skal kjører hver gang heisen kommer til en ny etasje
int checkOrdersThisFloor();//Testet -M

/**
 * @brief delets all orders in oderMatrix, and fils if with 9 on all index
 */
//Fjerner alle ordre fra matrisen med å fylle den med 9 9
void cleanOrders();


