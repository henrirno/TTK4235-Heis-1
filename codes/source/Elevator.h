#pragma once
#include "Orders.h"
#include "hardware.h"

enum ElevatorBehaviour {
	EB_Idle,
	EB_DoorOpen,
	EB_Moving
};

struct Elevator {
	ElevatorBehaviour	behaviour;
	HardwareMovement	movement;
	int					floor;
	int					orders[HARDWARE_NUMBER_OF_FLOORS][HARDWARE_NUMBER_OF_BUTTONS];
	Elevator 
};

