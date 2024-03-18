#pragma once
#include "elevio.h"
#include <stdbool.h>
#include <stdio.h>
#include "Door.h"

typedef struct Elevator{
    bool hasInitialised;
    Door door;
    int currentFloor;
    int prevFloor;
    int targetFloor;
    bool justStopped;
    bool isMoving;
    bool hasUsedStopButton;
    bool queueEmpty;
    MotorDirection motorDir;
    MotorDirection prevMotorDir;
} Elevator;

void setFloor(Elevator* elevator);
void elevatorInit(Elevator* elevator);
void moveTo(Elevator* elevator, Door* door);
void timeEnd(Elevator* elevator, Door* door);
void shouldDoorStayOpen(Elevator* elevator, Door* door);
void openWhenStopped(Elevator* elevator, Door* door);