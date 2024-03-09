#include "IOUnits.h"

void setStopLight(){
    if(elevio_stopButton()){
        elevio_stopLamp(1);
    } else {
        elevio_stopLamp(0);
    }
}

void setFloorLight(Elevator* elevator){
    elevio_floorIndicator(elevator->prevFloor);
}

void setDoorLight(Door* door){
    if(door->isOpen){
        elevio_doorOpenLamp(1);
    } else {
        elevio_doorOpenLamp(0);
    }
}

void setLights(Elevator* elevator, Door* door){
    setStopLight();
    setFloorLight(elevator);
    setDoorLight(door);
}

void checkStopButton(Elevator* elevator, Door* door, Queue* queue){
    if(elevio_stopButton()){
        elevator->prevMotorDir = elevator->motorDir;
        elevio_motorDirection(DIRN_STOP);
        elevator->motorDir = DIRN_STOP;
        removeAll(queue);
        elevator->hasUsedStopButton = 1;
        elevator->justStopped = 1;

        if(elevator->currentFloor == -1){
            elevator->targetFloor = -1; //burde vi ha denne??
        }

/*         if(!elevio_stopButton()){
            elevio_motorDirection(prevDir);
            printf("Dir %d, \n", prevDir);
        } */
    }
}