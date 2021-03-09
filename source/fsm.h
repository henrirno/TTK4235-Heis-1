#ifndef FUNCTIONALITY_H
#define FUNCTIONALITY_H

#include "Orders.h"
#include "timer.h"
#include <stdio.h>

void initialize_elevator();

void elevator_arriving_floor(int floor);

void button_press_event(int btn_floor, HardwareOrder order_type);

void close_door();

void clear_order_light();


#endif