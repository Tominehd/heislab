/**
* @file
* @brief A file with basic functions for the hardware at an elevator
*/

#pragma once

#define N_FLOORS 4

/**
 * @brief enum to define the motor directions whit corresponding numbers
 * -1 represent DIRN_DOWN, 0 represent DIRN_STOP, 1 represent DIRN_UP
 */
typedef enum { 
    DIRN_DOWN   = -1,
    DIRN_STOP   = 0,
    DIRN_UP     = 1
} MotorDirection;


#define N_BUTTONS 3

/**
 * @brief enum to define the buttons whit corresponding numbers
 * 0 represent BUTTON_HALL_UP, 1 represent BUTTON_HALL_DOWN, 2 represent BUTTON_CAB
 */
typedef enum { 
    BUTTON_HALL_UP      = 0,
    BUTTON_HALL_DOWN    = 1,
    BUTTON_CAB          = 2
} ButtonType;

/**
 * @brief Initialize the elevator
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
 * @brief makes the button light up when called with @p value = 1
 * 
 * @param[in] floor where the button is
 * @param[in] button what type of button
 * @param[in] value 1 to turn on the buttonlight, 0 to turn off the buttonlight
 */
void elevio_buttonLamp(int floor, ButtonType button, int value);

/**
 * @brief Turns on the light on the floorpanel
 * 
 * @param[in] floor which light to turn on
 */
void elevio_floorIndicator(int floor);

/**
 * @brief makes the door lamp light up when the door is open
 * 
 * @param[in] value 1 to turn on the lighet, 0 to turn i toff
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
 * @param[in] floor the floor the butten is in
 * @param[in] button type of button
 * @return int, 0 if false and 1 if true
 */
int elevio_callButton(int floor, ButtonType button);

/**
 * @brief Holds track of where the elevator is
 * 
 * @return -1 inbetween floors, 0 i first floor, 1 in second floor, and so on...
 */
int elevio_floorSensor(void);

/**
 * @brief checks if the stop button is being pressed
 * 
 * @return int, return 1 if true
 */
int elevio_stopButton(void);

/**
 * @brief checks if the obstruction lever is down
 * 
 * @return int returns 1 if down
 */
int elevio_obstruction(void);

