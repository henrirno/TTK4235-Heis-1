#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "hardware.h"
#include <stdio.h>


typedef enum  {
	EB_Idle,
	EB_DoorOpen,
	EB_Moving,
	EB_Initilizing
} ElevatorBehaviour ;

typedef struct {
	ElevatorBehaviour	behaviour;
	HardwareMovement	movement;
	int					floor;
	int					orders[HARDWARE_NUMBER_OF_FLOORS][HARDWARE_NUMBER_OF_BUTTONS];
} Elevator;

void print_elevator_movement(HardwareMovement movement);
void print_orders();
void print_order_type(HardwareOrder order_type);
#endif
