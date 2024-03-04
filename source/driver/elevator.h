#pragma once
#include "elevio.h"
#include "door.h"
#include <stdbool.h>
#include <time.h>

typedef struct Door {
    bool isOpen;
    bool obstruction;
    int startTime;
    int difference;
    //struct timespec timer;
} Door;
typedef struct Elevator{
    int currentFloor;
    MotorDirection motorDir;
    int prevFloor;
    bool isMoving;
    Door door;
    int targetFloor;
    int lastFloorStopped;
    int start;
} Elevator;

void setFloor(Elevator* elevator);
void elevatorInit(Elevator* elevator);
void moveTo(Elevator* elevator, int targetFloor);

void doorInit(Door* door);
void openDoor(Elevator* elevator, Door* door);
void shouldDoorStayOpen(Elevator* elevator, Door* door);
void closeDoor();