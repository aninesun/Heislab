# include "door.h"
#include <stdbool.h>


void openDoor(){
    nanosleep(&(struct timespec){3, 0}, NULL);
}

void closeDoor(){
    
}

bool isOpen(){
    return false;
}