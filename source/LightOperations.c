#include "LightOperations.h"

void set_current_floor_indicator(){
    int floor = getFloor();
    if (floor >=0){
        hardware_command_floor_indicator_on(floor);
    }
}
void set_floor_light(int floor, HardwareOrder order_type, int on){ // mulig input her helle skal v�re elevator.orders[][] eller bare elevator
    // floor = x i matrix[x][y]
    // down = matrix[x][y]
    //up = matrix[x][y+1]
    hardware_command_order_light(floor, order_type, on);
}
    //pseudo: matrix[floor][dir] = 0;1

