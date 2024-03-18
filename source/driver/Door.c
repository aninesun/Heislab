#include "Door.h"

void doorInit(Door* door){
    door->isOpen = false;
}

void openDoor(Door* door){
    door->timer = (int) time(NULL);
}
