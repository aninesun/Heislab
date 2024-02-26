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

void setLights(Elevator* elevator){
    setStopLight();
    setFloorLight(&elevator);
}