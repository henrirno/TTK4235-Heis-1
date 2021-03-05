#pragma once
#include "Elevator.h"

void initialize_elevator();

void elevator_arriving_floor(int floor);
void button_press_event(int btn_floor, HardwareOrder order_type);
void close_door();