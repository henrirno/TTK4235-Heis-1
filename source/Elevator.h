#ifndef ELEVATOR_H
#define ELEVATOR_H
//#include "Orders.h"
#include "hardware.h"


typedef enum  {
	EB_Idle,
	EB_DoorOpen,
	EB_Moving
} ElevatorBehaviour ;

typedef struct {
	ElevatorBehaviour	behaviour;
	HardwareMovement	movement;
	int					floor;
	int					orders[HARDWARE_NUMBER_OF_FLOORS][HARDWARE_NUMBER_OF_BUTTONS];
} Elevator;

#endif
