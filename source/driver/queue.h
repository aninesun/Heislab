#pragma once
#include <stdio.h>
#include "elevio.h"
#include "elevator.h"

typedef struct Queue {
    int queuesystem [N_FLOORS][N_BUTTONS];
} Queue;

void queueInit(Queue* queue);
void printQueue(Queue* queue);
void addToQueue(Queue* queue);
void removeFromQueue(Elevator* elevator, Queue* queue, int floor);
void removeAll(Queue* queue);
void checkQueue(Elevator* elevator, Door* door, Queue* queue);
void checkForEmptyQueue(Elevator* elevator, Queue* queue);