#include "elevator.h"

void elevatorInit(Elevator* elevator){

    while(elevio_floorSensor() != 0){
        elevio_motorDirection(DIRN_DOWN);
    }

    elevio_motorDirection(DIRN_STOP);
}

void setFloor(Elevator* elevator){
    elevator->currentFloor = elevio_floorSensor();
}

void setPrevFloor(Elevator* elevator){
    if(elevator->currentFloor != -1){
        elevator->prevFloor = elevator->currentFloor;
    }
}

void moveTo(Elevator* elevator, int targetFloor){
    printf("Current floor: %d\n", elevator->currentFloor);

    if(elevator->currentFloor < targetFloor && elevator->currentFloor != -1){
        elevio_motorDirection(DIRN_UP);
        if(elevator->currentFloor == targetFloor){
            printf("Riktig etasje");
            elevio_motorDirection(DIRN_STOP);
        }
    } else if(elevator->currentFloor > targetFloor && elevator->currentFloor != -1){
        elevio_motorDirection(DIRN_DOWN);
        if(elevator->currentFloor == targetFloor){
            printf("Riktig etasje");
            elevio_motorDirection(DIRN_STOP);
        }
    } else if(elevator->currentFloor == targetFloor){
        elevio_motorDirection(DIRN_STOP);
    }
}