#pragma once
#include <stdbool.h>
#include "elevator.h"
#include "door.h"

typedef struct Lights {
    bool lightsOn;
} Lights;

void setStopLight();
void setFloorLight(Elevator* elevator);
void setDoorLight(Door* door);
void setLights(Elevator* elevator);