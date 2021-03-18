
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

int main(){
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
    
    printf("=== Heis gruppe 43 ===\n");
    printf("    Have fun :D\n\n");

    
    initialize_elevator();
    int prev_floor_local = -1;
    clear_all_order_lights();
    
    while(1){
       
       // SJEKK ETASJER
        for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++)
        {
            int floor = hardware_read_floor_sensor(i);
            if (floor == 1 && prev_floor_local != i){
                prev_floor_local = i;
                elevator_arriving_floor(i);
            }
        }
        //SJEKK KNAPPER
        static int orders[HARDWARE_NUMBER_OF_FLOORS][HARDWARE_NUMBER_OF_BUTTONS];
            
        for (int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++)
        {
                
            for (int btn = 0; btn < HARDWARE_NUMBER_OF_BUTTONS; btn++)
            {   
                int btn_event = hardware_read_order(f,order_types[btn]);
                if (btn_event && orders[f][btn] != 1){
                    button_press_event(f,btn);
                    orders[f][btn] = 1;
                }
            }
                
        }
        // STOPP HAANDTERING
        int is_stop_button_pressed = 0;
        while (hardware_read_stop_signal()){
            if (!is_stop_button_pressed)
            {
                printf("!   STOP    !\n");
            }
                
            stop_button_pressed();
            is_stop_button_pressed = 1;
        }
            
        if (is_stop_button_pressed){
            hardware_command_stop_light(0);
            prev_floor_local = -1;
                
            for (int i = 0 ; i < HARDWARE_NUMBER_OF_FLOORS; i++){
                for (int j = 0; j < HARDWARE_NUMBER_OF_BUTTONS; j++){
                    orders[i][j] = 0;
                }
            }
        }
        
        if(hardware_read_obstruction_signal() && check_door_open()){
            start_timer();
        }
        // SJEKK TIMER
        if (timed_out()){
            printf("timed out\n");
            close_door();
            reset_timer();

            // CLEAR LOCAL VARIABLE
            for (int i = 0 ; i < HARDWARE_NUMBER_OF_FLOORS; i++){
                for (int j = 0; j < HARDWARE_NUMBER_OF_BUTTONS; j++){
                    orders[i][j] = 0;
                }
            }
            
        }
        
    }

    return 0;
}
