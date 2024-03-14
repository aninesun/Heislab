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
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
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

void checkQueue(Elevator* elevator, Door* door, Queue* queue){
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            if(elevator->isEmptyQueue == 1 && elevator->currentFloor == -1 && elevator->hasUsedStopButton == true){ //elevator->isEmptyQueue == 1 && 
                elevator->targetFloor = -1;
            }

            if(queue->queuesystem[f][b] == 1){
                if(elevator->hasUsedStopButton == 0){
                    if(elevator->motorDir != DIRN_DOWN && elevator->prevFloor < f && b != BUTTON_HALL_DOWN && elevator->targetFloor >= f) {
                        elevator->targetFloor = f;
                    }
                    else if(elevator->motorDir != DIRN_UP && elevator->prevFloor > f && b != BUTTON_HALL_UP && elevator->targetFloor <= f){
                        elevator->targetFloor = f;
                    } else if (elevator->motorDir == DIRN_STOP){
                        elevator->targetFloor = f;
                    }
                }
                if(elevator->hasUsedStopButton){
                    if(elevator->motorDir != DIRN_DOWN && elevator->prevFloor <= f && b != BUTTON_HALL_DOWN && (elevator->targetFloor >= f || elevator->targetFloor == -1)){
                        elevator->targetFloor = f;
                    }
                    else if(elevator->motorDir != DIRN_UP && elevator->prevFloor >= f && b != BUTTON_HALL_UP && (elevator->targetFloor <= f || elevator->targetFloor == -1)){
                        elevator->targetFloor = f;
                    } else if (elevator->motorDir == DIRN_STOP){
                        elevator->targetFloor = f;
                    }
                }
                if(elevator->motorDir != DIRN_DOWN && elevator->prevFloor <= f && b != BUTTON_HALL_DOWN && (elevator->targetFloor >= f || elevator->targetFloor == -1)){
                    elevator->targetFloor = f;
                } else if(elevator->motorDir != DIRN_UP && elevator->prevFloor >= f && b != BUTTON_HALL_UP && (elevator->targetFloor <= f || elevator->targetFloor == -1)){
                    elevator->targetFloor = f;
                } else if (elevator->motorDir == DIRN_STOP){
                    elevator->targetFloor = f;
                }
            } else {
                elevio_buttonLamp(f, b, 0);
            }
        }
    }

    moveTo(elevator, door);

    if(elevator->hasUsedStopButton && elevator->currentFloor == -1){
        elevator->motorDir = DIRN_STOP;
    }
    if(elevator->prevFloor > elevator->targetFloor && elevator->targetFloor != -1){
        elevator->motorDir = DIRN_DOWN;
    } else if(elevator->prevFloor < elevator->targetFloor && elevator->targetFloor != -1){
        elevator->motorDir = DIRN_UP;
    } else {
        elevator->motorDir = DIRN_STOP;
    }
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