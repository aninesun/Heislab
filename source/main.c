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

    Door door;
    doorInit(&door);

    Elevator elevator;
    setFloor(&elevator);
    elevatorInit(&elevator);
    elevator.prevFloor = 0;
    elevator.targetFloor = 0;
    elevator.isEmptyQueue = 0;
    
    elevator.motorDir = DIRN_STOP;
    elevator.door = door;
    elevator.hasMoved = 0;

    Queue queue;
    queueInit(&queue);
    printQueue(&queue);

    int startTime = 0;

    while(1){
        setFloor(&elevator);
        setPrevFloor(&elevator);
        checkStopButton(&elevator, &door, &queue);
        openWhenStopped(&elevator, &door);
        setLights(&elevator, &door);
        addToQueue(&queue);
        printQueue(&queue);
        checkQueue(&elevator, &door, &queue);
        removeFromQueue(&elevator, &queue, elevator.lastFloorStopped);
        shouldDoorStayOpen(&elevator, &door);
        checkObstruction(&door);
        checkForEmptyQueue(&elevator, &queue);
        
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    removeAll(&queue);

    return 0;
}
