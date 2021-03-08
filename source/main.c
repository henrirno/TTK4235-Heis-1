
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "hardware.h"
/*#include "Orders.h"
#include "Elevator.h"*/
#include "Functionality.h"

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

    //hardware_command_movement(HARDWARE_MOVEMENT_UP);
    //while (!basicState()){}
    initialize_elevator();
    
    while(1){
        //execute_single_order();
        //go_to_floor(outsideOrders());
        
        
        if(hardware_read_stop_signal()){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            break;
        }
        
       
       // sjekker etasjer
        for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++)
        {
            if (hardware_read_floor_sensor(i) == 1){
                elevator_arriving_floor(i);
            }
        }
        if (hardware_read_floor_sensor(0) || hardware_read_floor_sensor(3)){
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        }

        //sjekker knapper
        //static int orders[HARDWARE_NUMBER_OF_FLOORS][HARDWARE_NUMBER_OF_BUTTONS];
        for (int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++)
        {
            for (int btn = 0; btn < HARDWARE_NUMBER_OF_BUTTONS; btn++)
            {   
                if (hardware_read_order(f,order_types[btn])){
                    //printf("floor : %d  button : %d\n",f,btn);
                    button_press_event(f,btn);
                        
                        //orders[f][btn] = 1;
                    }
        }
        }
        

        // SJEKKER TIMEOUT
        if (timed_out()){
            printf("timed out\n");
            close_door();
            reset_timer();
        }
        
        


        /* All buttons must be polled, like this: */
        for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
            if(hardware_read_floor_sensor(f)){
                hardware_command_floor_indicator_on(f);
            }
        }

        /* Lights are set and cleared like this: */
        for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
            /* Internal orders */
            if(hardware_read_order(f, HARDWARE_ORDER_INSIDE)){
                hardware_command_order_light(f, HARDWARE_ORDER_INSIDE, 1);
            }

            /* Orders going up */
            if(hardware_read_order(f, HARDWARE_ORDER_UP)){
                hardware_command_order_light(f, HARDWARE_ORDER_UP, 1);
            }

            /* Orders going down */
            if(hardware_read_order(f, HARDWARE_ORDER_DOWN)){
                hardware_command_order_light(f, HARDWARE_ORDER_DOWN, 1);
            }
        }

        /* Code to clear all lights given the obstruction signal */
        if(hardware_read_obstruction_signal()){
            hardware_command_stop_light(1);
            clear_all_order_lights();
        }
        else{
            hardware_command_stop_light(0);
        }
        
    }

    return 0;
}
