#pragma once
#include "elevio.h"
#include <stdbool.h>
#include <time.h>
#include <stdio.h>

typedef struct Door {
    bool isOpen;
    int timer;
} Door;
typedef struct Elevator{
    bool hasInitialised;
    Door door;
    int currentFloor;
    int prevFloor;
    int targetFloor;
    int lastFloorStopped;
    bool justStopped;
    bool isMoving;
    int hasMoved;
    bool hasUsedStopButton;
    bool isEmptyQueue;
    MotorDirection motorDir;
    MotorDirection prevMotorDir;
} Elevator;

void setFloor(Elevator* elevator);
void elevatorInit(Elevator* elevator);
void moveTo(Elevator* elevator, Door* door);

void doorInit(Door* door);
void openDoor(Door* door);
void timeEnd(Elevator* elevator, Door* door);
void shouldDoorStayOpen(Elevator* elevator, Door* door);
void checkObstruction(Door* door);
void openWhenStopped(Elevator* elevator, Door* door);