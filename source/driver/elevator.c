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
        elevator->lastFloorStopped = elevator->currentFloor;
    }

    nanosleep(&(struct timespec){0, 2000*1000*1000}, NULL);
}


void doorInit(Door* door){
    door->isOpen = false;
    door->obstruction = false;
    door->startTime = 0;
    door->difference = 3;
}

void openDoor(Elevator* elevator, Door* door){
    int bareEnGang = 0;
    printf("AUGUST \n");
    printf("Motor direction: %d\n", elevator->motorDir);
    printf("Obstruction: %d\n", elevio_obstruction());
    printf("Door open: %d\n", door->isOpen);

    if(elevator->motorDir == DIRN_STOP && elevio_obstruction() == 0){
        printf("musling");
        bareEnGang = 1;
        door->isOpen = true;
        door->startTime = clock();
    }
}

void shouldDoorStayOpen(Elevator* elevator, Door* door){
    if(door->isOpen == true){
        /* if(elevio_obstruction() == 1){
            door->startTime = clock();
        } */
        if((clock() - door->startTime) / CLOCKS_PER_SEC > door->difference){ //blir door->starttime resett hele tiden
            door->isOpen = false;
        }
    }
}

void closeDoor(){
    
}
