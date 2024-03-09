#include "queue.h"
#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>

void queueInit(Queue* queue){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            queue->queuesystem[i][j] = 0;
        }
    }
}

void printQueue(Queue* queue){
    for(int i = 0; i < 4; i++){ //4 floors
        for(int j = 0; j < 3; j++){ //3 buttons
            printf("%d ", queue->queuesystem[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void addToQueue(Queue* queue){
    for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                if(btnPressed == 1){
                    queue->queuesystem[f][b] = 1;
                    elevio_buttonLamp(f, b, btnPressed);
                }
            }
        }
    //queue->queuesystem[order->toFloor][order->button] = 1;
}

void removeFromQueue(Elevator* elevator, Queue* queue, int floor){
    if(elevator->motorDir == DIRN_STOP && elevator->currentFloor != -1){
        for(int b = 0; b < N_BUTTONS; b++){
            queue->queuesystem[floor][b] = 0;
        }
    }
}

void removeAll(Queue* queue){
    for(int i = 0; i < 4; i++){

        for(int j = 0; j < 3; j++){
            queue->queuesystem[i][j] = 0;
        }
    }
}

Order getOrder(Order order){
    return order;
}

void checkQueue(Elevator* elevator, Door* door, Queue* queue){
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            if(elevator->isEmptyQueue == 1 && elevator->currentFloor == -1 && elevator->hasUsedStopButton){
                elevator->targetFloor = -1;
                //elevio_motorDirection(DIRN_STOP);
            }
            
            //printf("Verdi på knapp %d \n", queue->queuesystem[f][b]);
            //printf("Kø er tom: %d\n", elevator->isEmptyQueue);

            if(queue->queuesystem[f][b] == 1){
                if(elevator->motorDir != DIRN_DOWN && elevator->prevFloor < f && b != BUTTON_HALL_DOWN && elevator->targetFloor >= f){
                    elevator->targetFloor = f;
                }
                else if(elevator->motorDir != DIRN_UP && elevator->prevFloor > f && b != BUTTON_HALL_UP && elevator->targetFloor <= f){
                    elevator->targetFloor = f;
                } else if (elevator->motorDir == DIRN_STOP){
                    elevator->targetFloor = f;
                    //printf("WÆÆÆÆÆÆÆÆÆÆÆÆÆÆÆÆÆÆÆÆÆÆÆÆÆÆÆÆÆ \n");
                    //printf("f: %d \n", f);
                }  else {
                    //printf("ingenting skjedde \n");
                }
            } else {
                elevio_buttonLamp(f, b, 0);
            }
        }
    }

    //printf("current floor: %d \n", elevator->currentFloor);
    //printf("prevFloor %d \n", elevator->prevFloor);
    //printf("target %d \n", elevator->targetFloor);
    
    moveTo(elevator, door, elevator->targetFloor);

    if(elevator->hasUsedStopButton && elevator->currentFloor == -1){
        elevator->motorDir = DIRN_STOP;
    }
    if(elevator->prevFloor > elevator->targetFloor){ //elevator->currentFloor != -1
        elevator->motorDir = DIRN_DOWN;
    } else if(elevator->prevFloor < elevator->targetFloor){ //elevator->currentFloor != -1
        elevator->motorDir = DIRN_UP;
    } else {
        elevator->motorDir = DIRN_STOP;
    }

    //elevator->prevMotorDir = elevator->motorDir;

    /* if(elevator->motorDir == DIRN_UP && elevator->prevFloor < elevator->targetFloor){
        elevator->motorDir = DIRN_UP;
    } else if (elevator->motorDir == DIRN_UP && elevator->prevFloor >= elevator->targetFloor){
        elevator->motorDir = DIRN_DOWN;
    } else if (elevator->motorDir == DIRN_DOWN && elevator->prevFloor > elevator->targetFloor){
        elevator->motorDir = DIRN_DOWN;
    } else if (elevator->motorDir == DIRN_DOWN && elevator->prevFloor <= elevator->targetFloor){
        elevator->motorDir = DIRN_UP;
    } */
}

void checkForEmptyQueue(Elevator* elevator, Queue* queue){
    bool queueIsEmpty = 1;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            if(queue->queuesystem[i][j] != 0){
                queueIsEmpty = 0;
            }    
        }
    }

    elevator->isEmptyQueue = queueIsEmpty;
}
