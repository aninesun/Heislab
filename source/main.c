#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <stdbool.h>
#include "driver/elevio.h"
#include "driver/lights.h"
#include "driver/queue.h"
#include "driver/motor.h"
#include "driver/order.h"
#include "driver/door.h"


int main(){
    elevio_init();

    printf("Test\n");
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");
    printf("Test3\n");

    //elevio_motorDirection(DIRN_UP);

    printf("Test2\n");

    MotorDirection prev = DIRN_STOP;
    int prevFloor = 0;

    while(1){
        
        //Queue testQueue;
        //initializeQueue(testQueue);
        //printQueue(testQueue.firstOrder);
/* 

        if(elevio_obstruction() == 0){
            elevio_motorDirection(DIRN_STOP);
        }

        if(elevio_obstruction() == 1){
            if(prev == DIRN_STOP){
                prev = DIRN_STOP;
            }
            elevio_motorDirection(prev);
        } */

        int floor = elevio_floorSensor();
        //printf("Current floor: %d\n", floor);

/*         if(floor != -1){
            prevFloor = floor;
            printf("Current floor: %d\n", floor);
        }

        if(floor == 0){
            elevio_motorDirection(DIRN_UP);
            prev = DIRN_UP;
        }

        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
            prev = DIRN_DOWN;
        } */
    
        //printf("Motor direction: %d\n", elevio_motorDirection());

        moveToDestination(3, 0);
        printf("Hei");
        //moveToDestination(0, 2);
        /* moveToDestination(3, 2);
        moveToDestination(2, 1);
        moveToDestination(1, 0); */

/*      

        int f = 1;
        int b = 1;
        bool hasBeenPressed = false;
        int btnPressed = elevio_callButton(f, b);

        if(btnPressed != 0){
            hasBeenPressed = true;
        }

        elevio_buttonLamp(f, b, btnPressed);

        while(floor != f && hasBeenPressed == true){
            printf("Button pressed: %d\n", btnPressed);
            printf("Current floor: %d\n", prevFloor);
            printf("Destination floor: %d\n", f);
            floor = elevio_floorSensor();
            printf("Current floor: %d\n", prevFloor);
            if(prevFloor < f){
                elevio_motorDirection(DIRN_UP);
                prev = DIRN_UP;
            }
            else if(prevFloor > f){
                elevio_motorDirection(DIRN_DOWN);
                prev = DIRN_DOWN;
            }
            if(floor == f){
                elevio_motorDirection(DIRN_STOP);
                prev = DIRN_STOP;
                hasBeenPressed = false;
            }
        } */


        //printf("Button pressed: %d\n", btnPressed);
        
        /* int array[12];
        int i = 0; */
        /* for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
                if(btnPressed != 0){
                    array[i] = btnPressed;
                    i++;
                }
            }
        } */
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
