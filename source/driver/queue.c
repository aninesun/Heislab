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
    if(elevator->motorDir == DIRN_STOP){
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

void checkQueue(Elevator* elevator, Queue* queue){
    for(int f = 0; f < N_FLOORS; f++){
        for(int b = 0; b < N_BUTTONS; b++){
            if(queue->queuesystem[f][b] == 1){
                /* if(priority->priority[f] > maxPriority || elevator->currentFloor < elevator->targetFloor){
                    maxPriority = priority->priority[f];
                }

                if(priority->priority[f] == maxPriority){
                    elevator->targetFloor = f;
                } */

                /* if (elevator->start == 0){
                    elevator->targetFloor = f;if (elevator->start == 0){
                    elevator->targetFloor = f;
                    elevator->start = 1;
                }
                    elevator->start = 1;
                } */

                if(elevator->motorDir != DIRN_DOWN && elevator->prevFloor < f && b != BUTTON_HALL_DOWN && elevator->targetFloor >= f){
                    elevator->targetFloor = f;
                }
                else if(elevator->motorDir != DIRN_UP && elevator->prevFloor > f && b != BUTTON_HALL_UP && elevator->targetFloor <= f){
                    elevator->targetFloor = f;
                } else if (elevator->motorDir == DIRN_STOP){
                    elevator->targetFloor = f;
                }
            } else {
                elevio_buttonLamp(f, b, 0);
            }
        }
    }
    moveTo(elevator, elevator->targetFloor);

    if(elevator->prevFloor > elevator->targetFloor){
        elevator->motorDir = DIRN_DOWN;
    } else if(elevator->prevFloor < elevator->targetFloor){
        elevator->motorDir = DIRN_UP;
    } else {
        elevator->motorDir = DIRN_STOP;
    }
    printf("Motor direction: %d\n", elevator->motorDir);

}

