#include "ElevatorDoor.h"




void door_timer(){
    if (isInFloor()){
        hardware_command_door_open(1);
        time_start = time(NULL);
        while (time(NULL) < time_start + TIME_LIMIT)  { //timer med time limit åpå 3 sek
            
            if(hardware_read_obstruction_signal()){
                time_start = time(NULL);
            }
        }
        hardware_command_door_open(0);
        
    }
}