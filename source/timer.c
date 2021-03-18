#include "timer.h"

static time_t time_start = 0;

void start_timer(){
        time_start = time(NULL) + TIME_LIMIT;   
}
int timed_out(){
    if (time(NULL) > time_start && time_start != 0){
        return 1;
    }
    return 0;
}
void reset_timer(){
    time_start = 0;
}
