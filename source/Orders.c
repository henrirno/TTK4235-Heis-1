#include "Orders.h"




int insideOrders(){
    for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++){   // Hardware_number_of_floors = 4
        if (hardware_read_order(i, HARDWARE_ORDER_INSIDE) == 1) {
            return i;
        }
    }
}

int orders_above(Elevator elevator){
    for (int floor = elevator.floor + 1; floor < HARDWARE_NUMBER_OF_FLOORS; floor++) {
        for (int btn = 0; btn < HARDWARE_NUMBER_OF_BUTTONS; btn++) {
            if (elevator.orders[floor][btn] == 1) {
                return 1;
            }
        }
    }
    return 0;
}

int orders_below(Elevator elevator) {
    for (int floor = 0; floor < elevator.floor; floor++) {
        for (int btn = 0; btn < HARDWARE_NUMBER_OF_BUTTONS; btn++) {
            if (elevator.orders[floor][btn] == 1) {
                return 1;
            }
        }
    }
    return 0;
}
/*
        if (hardware_read_order(i, HARDWARE_ORDER_UP) == 1) {
            return i; //int 1;
        } else if (hardware_read_order(i, HARDWARE_ORDER_DOWN) == 1) {
            return i;//, int 2;
        }
    } 
    return -1;

*/



void execute_single_order(){
    /*
    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
            /* Internal orders 
            if(hardware_read_order(f, HARDWARE_ORDER_INSIDE)){
                go_to_floor(f);
            }
    }
*/}
/*

void go_to_floor(int goal_floor){
    if (goal_floor < 0 || goal_floor > HARDWARE_NUMBER_OF_FLOORS){
        return;
    }
        while (getFloor() != goal_floor){
            hardware_command_order_light(goal_floor, HARDWARE_ORDER_INSIDE, 1);
            if (getFloor() > goal_floor){
                hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
            } else if (getFloor() < goal_floor && getFloor() != -1){
                hardware_command_movement(HARDWARE_MOVEMENT_UP);
            }
            set_current_floor_indicator();
        }
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        
        hardware_command_order_light(goal_floor, HARDWARE_ORDER_INSIDE, 0);
        clear_floor_light(goal_floor);
        door_timer();
        
        
}*/



//  choose_direction()

HardwareMovement orders_choose_direction(Elevator elevator) { 
    switch (elevator.movement) {
    case HARDWARE_MOVEMENT_UP:
        if (orders_above(elevator)) {
            return HARDWARE_MOVEMENT_UP;
        }
        else if (orders_below(elevator)) {
            return HARDWARE_MOVEMENT_DOWN;
        }
        printf("no orders below/above -> stop\n");
        return HARDWARE_MOVEMENT_STOP;
        break;
    case HARDWARE_MOVEMENT_DOWN:
        if (orders_above(elevator)) {
            
            return HARDWARE_MOVEMENT_UP;
        }
        else if (orders_below(elevator)) {
            return HARDWARE_MOVEMENT_DOWN;
            
        }
        return HARDWARE_MOVEMENT_STOP;
        break;
    case HARDWARE_MOVEMENT_STOP:
        if (orders_above(elevator)) {
            
            return HARDWARE_MOVEMENT_UP;
        }
        else if (orders_below(elevator)) {
            return HARDWARE_MOVEMENT_DOWN;
            
        }
        return HARDWARE_MOVEMENT_STOP;
        break;
    default:
        printf("was and is stop\n");
        return HARDWARE_MOVEMENT_STOP;
        break;
    }
}
int should_elevator_stop(Elevator e) {
    
    
    switch (e.movement){
    case HARDWARE_MOVEMENT_DOWN:            // HARDWARE_ORDER_DOWN = 2 // hvis den skal ned p� denne etasje eller //  noen har bestilt inne i heise her eller//   det ikke er noen ordre lengre ned
        if (e.orders[e.floor][HARDWARE_ORDER_DOWN] ||  
            e.orders[e.floor][HARDWARE_ORDER_INSIDE]  ||  
            !orders_below(e))
        { 
            return 1;
        }
        else 
        {
            return 0;
        }
        break;              
    case HARDWARE_MOVEMENT_UP:
        if (e.orders[e.floor][HARDWARE_ORDER_UP] ||  
            e.orders[e.floor][HARDWARE_ORDER_INSIDE]  ||  
            !orders_above(e))
        {                        
            return 1;
        }
        else
        {
            return 0;
        }  
        break; 
            
    case HARDWARE_MOVEMENT_STOP:
        return 1;
        break;
    default:
        return 0;
        break;
    }
}

Elevator clear_elevator_order(Elevator e) {
    e.orders[e.floor][HARDWARE_ORDER_INSIDE] = 0;
    switch (e.movement)
    {
    case HARDWARE_MOVEMENT_DOWN:
        e.orders[e.floor][HARDWARE_ORDER_DOWN] = 0;
        hardware_command_order_light(e.floor,HARDWARE_ORDER_DOWN,0);
        break;
    case HARDWARE_MOVEMENT_UP:
        e.orders[e.floor][HARDWARE_ORDER_UP] = 0;
        hardware_command_order_light(e.floor,HARDWARE_ORDER_UP,0);
        break;
    case HARDWARE_MOVEMENT_STOP:
        e.orders[e.floor][HARDWARE_ORDER_DOWN] = 0;
        e.orders[e.floor][HARDWARE_MOVEMENT_UP] = 0;
        hardware_command_order_light(e.floor,HARDWARE_ORDER_UP,0);
        hardware_command_order_light(e.floor,HARDWARE_ORDER_DOWN,0);
        break;
    default:
        break;
    }
    return e;
}


