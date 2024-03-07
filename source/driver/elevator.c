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

void moveTo(Elevator* elevator, Door* door, int targetFloor){
    //printf("Current floor: %d\n", elevator->currentFloor);
    if(door->isOpen == false){
        if(elevator->currentFloor < targetFloor && elevator->currentFloor != -1){
            elevio_motorDirection(DIRN_UP);
            if(elevator->currentFloor == targetFloor){
                elevio_motorDirection(DIRN_STOP);
            }
            elevator->hasMoved = 1;

        } else if(elevator->currentFloor > targetFloor && elevator->currentFloor != -1){
            elevio_motorDirection(DIRN_DOWN);
            if(elevator->currentFloor == targetFloor){
                elevio_motorDirection(DIRN_STOP);
            }
            elevator->hasMoved = 1;

        } else if(elevator->currentFloor == targetFloor){
            elevio_motorDirection(DIRN_STOP);
            elevator->lastFloorStopped = elevator->currentFloor;

            if(elevator->hasMoved == 1){
                door->isOpen = true;
                elevator->justStopped = true;
                openDoor(door);
                elevator->hasMoved = 0;
            }
        }
    }

    //nanosleep(&(struct timespec){0, 2000*1000*1000}, NULL);
}

void doorInit(Door* door){
    door->isOpen = false;
    door->obstruction = false;
    door->startTime = 0;
}

void openDoor(Door* door){
    door->timer = (int) time(NULL);
}

void timeEnd(Elevator* elevator, Door* door){
    if((time(NULL) - door->timer) <= 3){
        door->isOpen = true;
    } else {
        door->isOpen = false;
        elevator->justStopped = false;
    }
}

void shouldDoorStayOpen(Elevator* elevator, Door* door){
    if(elevator->justStopped && door->isOpen){
        timeEnd(elevator, door);
    }
}

void checkObstruction(Door* door){
    if(!elevio_obstruction()){
        openDoor(&door);
    }
}