#include "Sensors.h"

bool isInFloor(){
    if (getFloor()) {
        return true;
    }
    return false;
}

int getFloor(){
        for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS, i++;){   // Hardware_number_of_floors = 4
            if (hardware_read_floor_sensor(i) == 1) {
                return i;
            }
        }
        return 0;
}