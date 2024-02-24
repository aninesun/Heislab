#pragma once
#include <stdbool.h>

typedef struct Motor {
    bool motorOn;
} Motor;

void turnOffMotor();
void moveToDestination(int floor, int destination);