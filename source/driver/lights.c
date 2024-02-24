#include "lights.h"

void setStopLight(){
    if(elevio_obstruction()){
        elevio_stopLamp(1);
    } else {
        elevio_stopLamp(0);
    }
}