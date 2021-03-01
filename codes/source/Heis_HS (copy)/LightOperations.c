#include "LightOperations.h"

void Light_Door(){
    if (OpenDoor == true){
        elev_set_door_open_lamp(1);
    } else {
        elev_set_door_open_lamp(0);
    }
}

void Light_clear_floor(){
    int floor = GetFloor();
    if (OpenDoor == true)
        //button = "BTN_" + toString(floor); ???
        elev_set_button_lamp(button, floor, 0);
}
