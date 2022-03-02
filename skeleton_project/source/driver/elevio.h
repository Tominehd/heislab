/**
* @file
* @brief A file with basic functions for the hardware at an elevator
*/

#pragma once

#define N_FLOORS 4

/**
 * @brief 
 * 
 */
typedef enum { 
    DIRN_DOWN   = -1,
    DIRN_STOP   = 0,
    DIRN_UP     = 1
} MotorDirection;


#define N_BUTTONS 3

//Skal denne dokumenteres?
typedef enum { 
    BUTTON_HALL_UP      = 0,
    BUTTON_HALL_DOWN    = 1,
    BUTTON_CAB          = 2
} ButtonType;

/**
 * @brief Initialize "suff"-what?
 * 
 */
void elevio_init(void);

/**
 * @brief Sets the motor direction
 * 
 * @param[in] dirn An Enum where -1 means down, 0 stop and 1 up
 */
void elevio_motorDirection(MotorDirection dirn);
/**
 * @brief makes the button light up when pressed
 * 
 * @param[in] floor 
 * @param[in] button 
 * @param[in] value 
 */
void elevio_buttonLamp(int floor, ButtonType button, int value);
/**
 * @brief indicates which floor the elevator is on
 * 
 * @param[in] floor 
 */
void elevio_floorIndicator(int floor);
/**
 * @brief makes the door lamp light up when the door is open
 * 
 * @param[in] value 
 */
void elevio_doorOpenLamp(int value);
/**
 * @brief Turn on the stop lamp
 * 
 * @param[in] value 1 if turn on, 0 if turn off
 */
void elevio_stopLamp(int value);

/**
 * @brief Checks if a button is being pushed
 * 
 * @param[in] floor 
 * @param[in] button 
 * @return int, 0 if false and 1 if true
 */
int elevio_callButton(int floor, ButtonType button);
/**
 * @brief Holds track of which floor the elevtor is on
 * 
 * @return an int that indicates the floor
 */
int elevio_floorSensor(void);
/**
 * @brief checks if the stop button is being pressed
 * 
 * @return int, rturn 1 if true?
 */
int elevio_stopButton(void);
int elevio_obstruction(void);

