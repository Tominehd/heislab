 #include "fsm.h"

int returnState();
    
    /**
void state_machine(){

    States currentState = INIT;

    while(1){

        lightUpButtons();

        switch(elevatorState){
            case INIT:
                printf("=== VELKOMMEN TIL HEISLAB! ===\n");
                validFloor();

                
                break;

            case WAITING:
            case IDLE:
            case STOP:
                printf("Stoppknappen er trykket på");
                stopElevator(); // Får også knappen til å lyse og åpner dørene
                clearOrders();
                clearLights()
                


            case OBSTRUCTION:
                
        }

          nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }
      

}

*/