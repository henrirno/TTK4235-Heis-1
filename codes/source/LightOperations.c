#include "LightOperations.h"

void set_current_floor_indicator(){
    int floor = getFloor();
    if (floor >=0){
        hardware_command_floor_indicator_on(floor);
    }
}
void clear_floor_light(int up, int down, int floor){
    int floor = matrix[0];
    int dir = matrix[1];
    if (dir = 0){
        //go down
    }
    else if (dir = 1) {
        //go up
    }
    }
    //pseudo: matrix[floor][dir] = 0;1
}
