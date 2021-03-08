#include "timer.h"

//isTimedOut = 0; 

void door_timer(){
        /*time_start = time(NULL);
        while (time(NULL) < time_start + TIME_LIMIT)  { //timer med time limit åpå 3 sek
            
            if(hardware_read_obstruction_signal()){
                time_start = time(NULL);
            }
        }
        */
        time_start = time(NULL) + TIME_LIMIT;
        isTimedOut = 1;      
}
int timed_out(){
    return (isTimedOut && time(NULL) > time_start);
}
void reset_timer(){
    isTimedOut = 0;
}