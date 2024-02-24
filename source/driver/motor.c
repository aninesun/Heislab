#include "motor.h"
#include "elevio.h"
#include "door.h"
#include <stdio.h>


void turnOffMotor(){
    while(elevio_obstruction() == 0){
        elevio_motorDirection(DIRN_STOP);
    }
}

void moveToDestination(int fromFloor, int toFloor){
    int floor = elevio_floorSensor();
    
    while(floor != toFloor){
        if(fromFloor < toFloor){
            elevio_motorDirection(DIRN_UP);
        }

        if(fromFloor > toFloor){
            elevio_motorDirection(DIRN_DOWN);
        }

        floor = elevio_floorSensor();
    }
    
    elevio_motorDirection(DIRN_STOP);
}