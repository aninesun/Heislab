#pragma once
#include <time.h>
#include <stdbool.h>

typedef struct Door {
    bool isOpen;
    int timer;
} Door;

void doorInit(Door* door);
void openDoor(Door* door);