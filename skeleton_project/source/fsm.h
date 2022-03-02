#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

typedef enum { 
    INIT,
    WAITING,
    IDLE,
    STOP
} States;

//burde taking order være med her

int returnState();
    
void state_machine();