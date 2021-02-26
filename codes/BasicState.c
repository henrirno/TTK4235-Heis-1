#include "BasicState.h"

bool basicState(){
    while (isInFloor() == false){
        HARDWARE_MOVEMENT_DOWN; 
    }
    if (isInFloor() == true) {
        return true;
    }
    return false;
}

