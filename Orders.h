#pragma once
#include "Elevator.h"
#include "hardware.h"

int insideOrders();
bool orders_above(Elevator elevator);
bool orders_below(Elevator elevator);
void go_to_floor(int goal_floor);
HardwareMovement orders_choose_direction(Elevator elevator);
bool should_elevator_stop(Elevator e);
Elevator clear_current_order(Elevator e);