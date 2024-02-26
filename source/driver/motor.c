#include "motor.h"
#include "elevio.h"
#include "door.h"
#include <stdio.h>

void turnOffMotor(){
    while(elevio_obstruction() == 0){
        elevio_motorDirection(DIRN_STOP);
    }
}
