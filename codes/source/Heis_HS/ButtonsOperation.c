#include "ButtonsOperation.h"

void BTN_Stop(){
    if (hardware_read_stop_signal() == 1){
        hardware_command_door_open(HARDWARE_MOVEMENT_STOP);
        if (isInFloor() == true){
            while (hardware_read_stop_signal() == 1){
                hardware_command_door_open(1);
            }
            //DoorOpen();
        }
    }
}