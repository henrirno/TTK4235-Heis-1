#include "Sensors.h"

bool isInFloor(){
    while (hardware_read_floor_sensor(1)){
        return true;
    }
}

int GetFloor(){
    int Floorlevel;
    if (isInFloor){
        for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS, i++;){   // Hardware_number_of_floors = 4, så floorlevel er alltid 4?
            Floorlevel = i;                                     // Kanskje vi skal ha en if-setnining med:  int hardware_read_floor_sensor(int floor = i); også return i;
        }
    }
    return Floorlevel;
}