#ifndef TIMER_H
#define TIMER_H

#include "Elevator.h"
#include <time.h>

#define TIME_LIMIT 3

static int isTimedOut = 0;
time_t time_start;
//static int timeLength;
//const int TIME_LIMIT = 3;
void reset_timer();
void door_timer();
int timed_out();

#endif