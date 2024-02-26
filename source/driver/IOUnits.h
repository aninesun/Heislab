#pragma once
#include <stdbool.h>
#include "elevator.h"

typedef struct Lights {
    bool lightsOn;
} Lights;

void setStopLight();
void setFloorLight(Elevator* elevator);
void setLights(Elevator* elevator);