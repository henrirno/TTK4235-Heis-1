#ifndef TIMER_H
#define TIMER_H

#include "Elevator.h"
#include <time.h>

#define TIME_LIMIT 3

void reset_timer();
void start_timer();
int timed_out();

#endif