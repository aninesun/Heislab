#include "queue.h"
#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>

void queueInit(Queue* queue){
    int queue[4][3] = {0};
}

void printQueue(Queue* queue){
    for(int i = 0; i < 4; i++){ //4 floors
        for(int j = 0; j < 3; j++){ //3 buttons
            printf("%d ", queue->queuesystem[i][j]);
        }
        printf("\n");
    }
}

void addToQueue(Queue* queue, Order* order){
    queue->queuesystem[order->toFloor][order->button] = 1;
}

void removeFromQueue(Queue* queue, Order* order){
    queue->queuesystem[order->toFloor][order->button] = 0;
}

void removeAll(Queue* queue){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 3; j++){
            queue->queuesystem[i][j] = 0;
        }
    }
}

Order buttonToOrder(ButtonType button, int floor){
    Order order;
    //HVA SKAL HER? Få inn en knapp og gjøre om til order, men hvordan skal order struct se ut?
    return order;
}

Order getOrder(Order order){
    return order;
}