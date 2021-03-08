#include "timer.h"

//isTimedOut = 0; 

void door_timer(){
        time_start = time(NULL);
        while (time(NULL) < time_start + TIME_LIMIT)  { //timer med time limit åpå 3 sek
            
            if(hardware_read_obstruction_signal()){
                time_start = time(NULL);
            }
        }
        
        //time_start = time(NULL) + TIME_LIMIT;
        isTimedOut = 1;      
}
int timed_out(){
    return (isTimedOut && time(NULL) > time_start);
}
void reset_timer(){
    isTimedOut = 0;
}
/*
#include <stdio.h> 
#include <sys/time.h>

static double get_wall_time(void){ 
    struct timeval time; 
    gettimeofday(&time, NULL); 
    return (double)time.tv_sec + (double)time.tv_usec * .000001; 
}

static double timerEndTime; 
static int timerActive;

void door_timer(double duration){ 
    timerEndTime = get_wall_time() + duration; timerActive = 1; 
    }

void reset_timer(void){ timerActive = 0; }

int timed_out(void){ 
    return (timerActive && get_wall_time() > timerEndTime); 
}
*/
