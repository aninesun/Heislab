#pragma once

typedef struct Order {
    int fromFloor;
    int toFloor;
} Order;

typedef struct Queue {
    Order queuesystem[10];
    int* firstOrder;
} Queue;

void initializeQueue(Queue q);
void printQueue(int* firstOrder);
void addToQueue(Order o, int* firstOrder);
Order getOrder(Order o);
void removeFromQueue(int* firstOrder);
void removeAll(Queue q);