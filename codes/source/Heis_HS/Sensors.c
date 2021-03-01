#include "Sensors.h"

bool isInFloor(){
    while (hardware_read_floor_sensor(1)){
        return true;
    }
}

int GetFloor(){
    int Floorlevel;
    if (isInFloor){
        for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS, i++;){
            Floorlevel = i;
        }
    }
    return Floorlevel;
}