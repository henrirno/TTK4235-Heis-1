#include "BasicState.h"

bool basicState(){
    hardware_command_movement(HARDWARE_MOVEMENT_UP);
        /*for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){
            if (hardware_read_floor_sensor(i) == 1){
                hardware_command_movement(HARDWARE_MOVEMENT_STOP);
                return true;
            }
        */
    if (getFloor() >= 0 ){
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        return true;       
        }
    return false;
}

void orderTest(){
    if (hardware_read_order(1, HARDWARE_ORDER_INSIDE) == 1) {
        while (getFloor() != 1){
            if (getFloor() > 1){
                hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
            } else if (getFloor() < 1 && getFloor() != -1){
                hardware_command_movement(HARDWARE_MOVEMENT_UP);
            }
        }
        hardware_command_movement(HARDWARE_MOVEMENT_STOP); 
    }
}
    
    

