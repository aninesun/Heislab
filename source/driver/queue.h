#pragma once
#include <stdio.h>
#include "elevio.h"
#include "elevator.h"

typedef struct Order {
    int fromFloor;
    int toFloor;
    ButtonType button;
    //MotorDirection direction;
} Order;

typedef struct Queue {
    int queuesystem [N_FLOORS][N_BUTTONS];
    //size_t youngestElement;
} Queue;

/* typedef struct FloorPriority {
    int priority [N_FLOORS];
} FloorPriority; */

void queueInit(Queue* queue);
void printQueue(Queue* queue);
void addToQueue(Queue* queue);
Order getOrder(Order order);
void removeFromQueue(Elevator* elevator, Queue* queue, int floor);
void removeAll(Queue* queue);
void checkQueue(Elevator* elevator, Queue* queue);