#pragma once
#include <time.h>
#include <stdbool.h>

typedef struct Door {
    bool isOpen;
    bool obstruction;
    //struct timespec timer;
} Door;

void openDoor();
void closeDoor();