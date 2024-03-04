#include "IOUnits.h"

void setStopLight(){
    if(elevio_stopButton() == 1){
        elevio_stopLamp(1);
    } else {
        elevio_stopLamp(0);
    }
}

void setFloorLight(Elevator* elevator){
    elevio_floorIndicator(elevator->prevFloor);
}

void setDoorLight(Door* door){
    if(door->isOpen == true){
        elevio_doorOpenLamp(1);
    } else {
        elevio_doorOpenLamp(0);
    }
}

void setLights(Elevator* elevator){
    setStopLight();
    setFloorLight(elevator);
    setDoorLight(&elevator->door);
}