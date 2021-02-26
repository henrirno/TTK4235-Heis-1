#include "LightOperations.h"

void Light_Door(){
    if (openDoor()){
        elev_set_door_open_lamp(1);
    } else {
        elev_set_door_open_lamp(0);
    }
}

void Light_clear_floor(){
    int floor = getFloor();
    if (openDoor())
        //button = "BTN_" + toString(floor); ???
        elev_set_button_lamp(button, floor, 0);
}
void set_inside_order_light(int on) {
    int currentFloor = getFloor();

}
