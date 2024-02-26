#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <stdbool.h>
#include "driver/elevio.h"
#include "driver/IOUnits.h"
#include "driver/queue.h"
#include "driver/motor.h"
#include "driver/order.h"
#include "driver/door.h"
#include "driver/elevator.h"


int main(){
    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    Elevator elevator;
    setFloor(&elevator);
    elevatorInit(&elevator);

    Queue queue;
    queueInit(&queue);
    printQueue(&queue);

    while(1){
        setFloor(&elevator);
        setPrevFloor(&elevator);
        setLights(&elevator);

        moveTo(&elevator, 2);
        

        //Queue testQueue;
        //initializeQueue(testQueue);
        //printQueue(testQueue.firstOrder);

/*      

        /* for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
            }
        } */
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    removeAll(&queue);

    return 0;
}
