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
    if(door->isOpen == false){
        if(elevio_stopButton() == 0){
            printf("Previous motor direction: %d\n", elevator->prevMotorDir);
            printf("Target floor: %d\n", elevator->targetFloor);
            printf("Previous floor: %d\n", elevator->prevFloor);

            if(elevator->currentFloor == elevator->targetFloor && elevator->targetFloor == -1){
                //elevio_motorDirection(DIRN_STOP);
                //elevator->motorDir = DIRN_STOP;
                //printf("HOLD THE DOOR\n");
            }

            if(elevator->currentFloor == elevator->targetFloor && elevator->targetFloor != -1){
                elevio_motorDirection(DIRN_STOP);
                //elevator->motorDir = DIRN_STOP;
                elevator->hasUsedStopButton = false;
            } else if(elevator->currentFloor == -1 && elevator->targetFloor != -1){
                if(elevator->prevMotorDir == DIRN_UP){
                    if(elevator->targetFloor > elevator->prevFloor){
                        elevio_motorDirection(DIRN_UP);
                        //elevator->motorDir = DIRN_UP;
                        elevator->hasMoved = 1;
                    } else if(elevator->targetFloor <= elevator->prevFloor){
                        elevio_motorDirection(DIRN_DOWN);
                        //elevator->motorDir = DIRN_DOWN;
                    }
                } else if(elevator->prevMotorDir == DIRN_DOWN){
                    if(elevator->targetFloor < elevator->prevFloor){
                        elevio_motorDirection(DIRN_DOWN);
                        //elevator->motorDir = DIRN_DOWN;
                    } else if(elevator->targetFloor >= elevator->prevFloor){
                        elevio_motorDirection(DIRN_UP);
                        //elevator->motorDir = DIRN_UP;
                    }
                }
            }    
        } 
        
        if(elevator->isEmptyQueue == 0){
                if(elevator->prevFloor < targetFloor && elevator->currentFloor != -1){
                    elevio_motorDirection(DIRN_UP);
                if(elevator->currentFloor == targetFloor){
                    elevio_motorDirection(DIRN_STOP);
                    }
                    elevator->hasMoved = 1;

            } else if(elevator->prevFloor > targetFloor && elevator->currentFloor != -1){
                elevio_motorDirection(DIRN_DOWN);
                if(elevator->currentFloor == targetFloor){
                    elevio_motorDirection(DIRN_STOP);
                }
                elevator->hasMoved = 1;
            } else if(elevator->currentFloor == targetFloor){
                elevio_motorDirection(DIRN_STOP);
                elevator->lastFloorStopped = elevator->currentFloor;
                elevator->hasMoved = 1;

                if(elevator->hasInitialised){
                    if(elevator->hasMoved == 1 && elevator->currentFloor != -1){
                        door->isOpen = true;
                        elevator->justStopped = true;
                        openDoor(door);
                        elevator->hasMoved = 0;
                    }
                }
                elevator->hasInitialised = true;
                
            }
            } else {
            elevio_motorDirection(DIRN_STOP);
        }
    }
}


/* void moveTo(Elevator* elevator, Door* door, int targetFloor){
    //printf("Current floor: %d\n", elevator->currentFloor);
    if(door->isOpen == false){
        if(elevator->isEmptyQueue == 0){
            if(elevator->hasUsedStopButton == true && elevio_stopButton() == 0){
                if(elevator->currentFloor == elevator->targetFloor && elevator->targetFloor != -1){
                    elevio_motorDirection(DIRN_STOP);
                    //elevator->motorDir = DIRN_STOP;
                } else if(elevator->prevMotorDir == DIRN_UP){
                    elevator->hasUsedStopButton = false;
                    //printf("SHAKLDHAKWDHAWHDØKIWAHØKDHAØIDHWA");
                    if(elevator->currentFloor == elevator->targetFloor){
                        elevio_motorDirection(DIRN_STOP);
                        //elevator->motorDir = DIRN_STOP;
                    } if(elevator->prevFloor > elevator->targetFloor){
                        elevio_motorDirection(DIRN_DOWN);
                        //elevator->motorDir = DIRN_DOWN;
                        elevator->hasMoved = 1;
                    } else if(elevator->prevFloor <= elevator->targetFloor){
                        elevio_motorDirection(DIRN_UP);
                        //printf("gh");
                        //elevator->motorDir = DIRN_UP;
                        elevator->hasMoved = 1;
                    }
                } else if(elevator->prevMotorDir == DIRN_DOWN){
                        elevator->hasUsedStopButton = false;
                        if(elevator->currentFloor == elevator->targetFloor){
                            elevio_motorDirection(DIRN_STOP);
                            //elevator->motorDir = DIRN_STOP;
                        } if(elevator->prevFloor >= elevator->targetFloor){
                            elevio_motorDirection(DIRN_DOWN);
                            //elevator->motorDir = DIRN_DOWN;
                            elevator->hasMoved = 1;
                        } else if(elevator->prevFloor < elevator->targetFloor){
                            elevio_motorDirection(DIRN_UP);
                            //elevator->motorDir = DIRN_UP;
                            elevator->hasMoved = 1;
                        }
                    }
            }
            
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
        } else {
            elevio_motorDirection(DIRN_STOP);
            //elevator->motorDir = DIRN_STOP;
        }
    }

    //nanosleep(&(struct timespec){0, 2000*1000*1000}, NULL);
} */

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
    //SPØRS HVILKEN HEIS VI HAR
    if(elevio_obstruction()){
        openDoor(door);
    }
    /* if(!elevio_obstruction()){
        openDoor(door);
    } */
}

void openWhenStopped(Elevator* elevator, Door* door){
    if(elevio_stopButton() == 1 && elevator->currentFloor != -1){
        openDoor(door);
        door->isOpen = true;
    }
}