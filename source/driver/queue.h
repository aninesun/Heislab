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
    int queuesystem [4][3];
    //size_t youngestElement;
} Queue;


void queueInit(Queue* queue);
void printQueue(Queue* queue);
void addToQueue(Queue* queue);
Order getOrder(Order order);
void removeFromQueue(Queue* queue, int floor);
void removeAll(Queue* queue);
void checkQueue(Elevator* elevator, Queue* queue);
void activeOrder(Elevator* elevator);