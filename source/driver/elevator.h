#pragma once
#include "elevio.h"
#include "door.h"
#include <stdbool.h>
#include <time.h>
#include <stdio.h>

typedef struct Door {
    bool isOpen;
    bool obstruction;
    int startTime;
    int difference;
    //struct timespec timer;
    int timer;
} Door;
typedef struct Elevator{
    int currentFloor;
    MotorDirection motorDir;
    int prevFloor;
    bool isMoving;
    Door door;
    int targetFloor;
    int lastFloorStopped;
    bool justStopped;
    int hasMoved;
    bool hasUsedStopButton;
    MotorDirection prevMotorDir;
    bool isEmptyQueue;
    bool hasInitialised;
} Elevator;

void setFloor(Elevator* elevator);
void elevatorInit(Elevator* elevator);
void moveTo(Elevator* elevator, Door* door, int targetFloor);

void doorInit(Door* door);
void openDoor(Door* door);
void timeEnd(Elevator* elevator, Door* door);
void shouldDoorStayOpen(Elevator* elevator, Door* door);
void checkObstruction(Door* door);
void openWhenStopped(Elevator* elevator, Door* door);