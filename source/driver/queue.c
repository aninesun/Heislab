#include "queue.h"
#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>


void initializeQueue(Queue q){
    int orders = malloc(sizeof(int) * 10);
    q.firstOrder = &orders;
    Order a= {.fromFloor = -2, .toFloor = -2};

    for(int i = 0; i < 10; i++){
        q.queuesystem[i] = a;
    }
}

void printQueue(int* firstOrder){
    printf("The queue: ");
    Order o = {(*(firstOrder)), (*(firstOrder+4))};
    printf("%d", o);
    
/*     for(int i = 0; i < 10; i++){
        Order o = {(*(firstOrder + 8*i)), (*(firstOrder+(8*i)+4))};
        printf("Order number: %i", i);
        printf("%d", o);
    } */
}

void destroyQueue(Queue q){
    for(int i = 0; i < 10; i++){
        //free(q.queuesystem[i].); 
    }
}

void addToQueue(Order o, int* firstOrder){
    bool done = false;
    int i = 0;

    while(done == false){
        if(*firstOrder ) 

        done = true;
    }
}

Order getOrder(Order o){
    return o;
}

void removeFromQueue(int* firstOrder) {

}

void removeAll(Queue q){

}