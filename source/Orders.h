#ifndef ORDERS_H
#define ORDERS_H

#include "Elevator.h"



int insideOrders();
int orders_above(Elevator elevator);
int orders_below(Elevator elevator);
void go_to_floor(int goal_floor);
HardwareMovement orders_choose_direction(Elevator elevator);
int should_elevator_stop(Elevator e);
Elevator clear_elevator_order(Elevator e);

#endif