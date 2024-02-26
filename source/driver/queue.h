#pragma once
#include <stdio.h>
#include "elevio.h"

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

Order buttonToOrder(ButtonType button, int floor);
void queueInit(Queue* queue);
void printQueue(Queue* queue);
void addToQueue(Queue* queue, Order* order);
Order getOrder(Order order);
void removeFromQueue(Queue queue);
void removeAll(Queue* queue);