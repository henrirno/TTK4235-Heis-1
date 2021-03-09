
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
#include "fsm.h"

HardwareOrder order_types[3] = {
        HARDWARE_ORDER_UP,
        HARDWARE_ORDER_INSIDE,
        HARDWARE_ORDER_DOWN
    };

static void clear_all_order_lights(){

    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int i = 0; i < 3; i++){
            HardwareOrder type = order_types[i];
            hardware_command_order_light(f, type, 0);
        }
    }
}


int main(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n\n");

    
    initialize_elevator();
    int prev_floor = -1;
    
    while(1){
       
        /*
        clear_all_order_lights();
        if(hardware_read_stop_signal()){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            break;
        }
        */
        
       
       // sjekker etasjer
        for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++)
        {
            int floor = hardware_read_floor_sensor(i);
            if (floor == 1 && prev_floor != i){
                prev_floor = i;
                elevator_arriving_floor(i);
            }
        }
        

        //sjekker knapper
        static int orders[HARDWARE_NUMBER_OF_FLOORS][HARDWARE_NUMBER_OF_BUTTONS];
        for (int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++)
        {
            for (int btn = 0; btn < HARDWARE_NUMBER_OF_BUTTONS; btn++)
            {   
                if (hardware_read_order(f,order_types[btn]) && orders[f][btn] != 1){
                    printf("Floor: %d  \nButton: ",f);
                    print_order_type(order_types[btn]);
                    printf("\n");
                    button_press_event(f,btn);
                        
                        orders[f][btn] = 1;
                    }
            }
        }
        
        if(hardware_read_obstruction_signal()){
            start_timer();
        }
        // SJEKKER TIMEOUT
        if (timed_out()){
            printf("timed out\n");
            close_door();
            reset_timer();
        }
        
    }

    return 0;
}
