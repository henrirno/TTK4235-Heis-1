#pragma once
#include "Sensors.h"
#include "LightOperations.h"
#include <time.h>

#define TIME_LIMIT 3
time_t time_start;
//const int TIME_LIMIT = 3;

char elevatorDirection();

void door_timer();