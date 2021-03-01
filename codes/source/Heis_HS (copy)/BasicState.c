#include "BasicState.h"

bool Basicstate(){
    bool inBasicState = false;
    while (isInFloor() == false){
        hardware_command_door_open(HARDWARE_MOVEMENT_DOWN);
    }
    inBasicState = true;
    return (inBasicState);
}
