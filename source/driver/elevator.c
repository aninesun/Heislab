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

void moveTo(Elevator* elevator, Door* door){
    if(door->isOpen == false){
        if(elevio_stopButton() == 0){
            if(elevator->currentFloor == elevator->targetFloor && elevator->targetFloor != -1){
                elevio_motorDirection(DIRN_STOP);
                elevator->hasUsedStopButton = false;
            } else if(elevator->currentFloor == -1 && elevator->targetFloor != -1){
                if(elevator->prevMotorDir == DIRN_UP){
                    if(elevator->targetFloor > elevator->prevFloor){
                        elevio_motorDirection(DIRN_UP);
                    } else if(elevator->targetFloor <= elevator->prevFloor){
                        elevio_motorDirection(DIRN_DOWN);
                    }
                } else if(elevator->prevMotorDir == DIRN_DOWN){
                    if(elevator->targetFloor < elevator->prevFloor){
                        elevio_motorDirection(DIRN_DOWN);
                    } else if(elevator->targetFloor >= elevator->prevFloor){
                        elevio_motorDirection(DIRN_UP);
                    }
                }
            }    
        } 
        
        if(elevator->queueEmpty == 0){
            if(elevator->prevFloor < elevator->targetFloor && elevator->currentFloor != -1){
                elevio_motorDirection(DIRN_UP);
                if(elevator->currentFloor == elevator->targetFloor){
                    elevio_motorDirection(DIRN_STOP);
                }
            } else if(elevator->prevFloor > elevator->targetFloor && elevator->currentFloor != -1){
                elevio_motorDirection(DIRN_DOWN);
                if(elevator->currentFloor == elevator->targetFloor){
                    elevio_motorDirection(DIRN_STOP);
                }
            } else if(elevator->currentFloor == elevator->targetFloor){
                elevio_motorDirection(DIRN_STOP);                
                if(elevator->hasInitialised && elevator->currentFloor != -1){
                    door->isOpen = true;
                    elevator->justStopped = true;
                    openDoor(door);
                }
                elevator->hasInitialised = true;
            }
        } else {
            elevio_motorDirection(DIRN_STOP);
        }
    }
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

void openWhenStopped(Elevator* elevator, Door* door){
    if(elevio_stopButton() == 1 && elevator->currentFloor != -1){
        openDoor(door);
        door->isOpen = true;
    }
}