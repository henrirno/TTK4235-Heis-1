#ifndef FSM_H
#define FSM_H

#include "Orders.h"
#include "timer.h"

#include <stdio.h>

void initialize_elevator();

void elevator_arriving_floor(int floor);

void button_press_event(int btn_floor, HardwareOrder order_type);

void close_door();

void clear_order_light();

int check_door_open();

void stop_button_pressed();

int at_floor();

void clear_all_order_lights();

#endif