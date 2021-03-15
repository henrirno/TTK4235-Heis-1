#ifndef ORDERS_H
#define ORDERS_H

#include "elevator.h"
#include "fsm.h"
#include <stdio.h>




int orders_above(Elevator elevator);
int orders_below(Elevator elevator);

HardwareMovement orders_choose_direction(Elevator elevator);
int should_elevator_stop(Elevator elevator);
Elevator clear_elevator_order(Elevator elevator);
Elevator clear_all_orders(Elevator elevator);

#endif