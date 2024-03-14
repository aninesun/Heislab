#pragma once
#include <stdbool.h>
#include "elevator.h"
#include "queue.h"
#include "elevio.h"

void setStopLight();
void setFloorLight(Elevator* elevator);
void setDoorLight(Door* door);
void setLights(Elevator* elevator, Door* door);
void checkStopButton(Elevator* elevator, Door* door, Queue* queue);
void checkObstruction(Door* door);