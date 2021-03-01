#include "ElevatorDoor.h"

bool OpenDoor(){
    /*
    if (GetFloor() == orderedFloor && OrderedDir == ElevatorMovement){
        return true;
    } else {
        return false;
    }
    */
}

void OpenCloseDoor(){
    if (OpenDoor == true){
        while (time(NULL) < TIME_LIMIT)  { //timer med time limit åpå 3 sek
            hardware_command_door_open(1);
        }
        hardware_command_door_open(0);
    }
}