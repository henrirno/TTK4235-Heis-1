#include "Orders.h"

int insideOrders(){
    for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){   // Hardware_number_of_floors = 4
        if (hardware_read_order(i, HARDWARE_ORDER_INSIDE) == 1) {
            return i;
        }
    }
}

int outsideOrders(){
    for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){   // Hardware_number_of_floors = 4
        if (hardware_read_order(i, HARDWARE_ORDER_UP) == 1) {
            return i; //int 1;
        } else if (hardware_read_order(i, HARDWARE_ORDER_DOWN) == 1) {
            return i;//, int 2;
        }
    } 
    return -1;
}

void createMatrix(){
    //int queue[4][3];
    for (int x = 0; x < 4; x++){
        for (int y = 0; y < 3; y++){
            queue[x][y]=0;
            
            }
    }
}
void execute_single_order(){
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
            /* Internal orders */
            if(hardware_read_order(f, HARDWARE_ORDER_INSIDE)){
                go_to_floor(f);
            }
    }
}
void go_to_floor(int goal_floor){
    if (goal_floor < 0 || goal_floor > HARDWARE_NUMBER_OF_FLOORS){
        return;
    }
        while (getFloor() != goal_floor){
            hardware_command_order_light(goal_floor, HARDWARE_ORDER_INSIDE, 1);
            if (getFloor() > goal_floor){
                hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
            } else if (getFloor() < goal_floor && getFloor() != -1){
                hardware_command_movement(HARDWARE_MOVEMENT_UP);
            }
            set_current_floor_indicator();
        }
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        
        hardware_command_order_light(goal_floor, HARDWARE_ORDER_INSIDE, 0);
        clear_floor_light(goal_floor);
        door_timer();
        
        
    }

void placeOrder(){
    
}


