#pragma once
#include "elevio.h"
#include <stdbool.h>

typedef struct Elevator{
    int currentFloor;
    MotorDirection motorDir;
    int prevFloor;
    bool isMoving;
    bool doorOpen;
    int targetFloor;
} Elevator;

void setFloor(Elevator* elevator);
void elevatorInit(Elevator* elevator);
void moveTo(Elevator* elevator, int targetFloor);