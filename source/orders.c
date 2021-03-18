#include "orders.h"

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


HardwareMovement orders_choose_direction(Elevator elevator) { 
    
    switch (elevator.movement) {
    case HARDWARE_MOVEMENT_UP:
        if (orders_above(elevator)) {
            return HARDWARE_MOVEMENT_UP;
        }
        else if (orders_below(elevator)) {
            return HARDWARE_MOVEMENT_DOWN;
        }
        printf("was up now -> stop\n");
        return HARDWARE_MOVEMENT_STOP;
        break;
    case HARDWARE_MOVEMENT_DOWN:
        if (orders_below(elevator)) {
            
            return HARDWARE_MOVEMENT_DOWN;
        }
        else if (orders_above(elevator)) {
            return HARDWARE_MOVEMENT_UP;
            
        }
        printf("was down now -> stop\n");
        return HARDWARE_MOVEMENT_STOP;
        break;
    case HARDWARE_MOVEMENT_STOP:
        if (orders_above(elevator)) {
            
            return HARDWARE_MOVEMENT_UP;
        }
        else if (orders_below(elevator)) {
            return HARDWARE_MOVEMENT_DOWN;
            
        }
        printf("was stop now -> stop\n");
        return HARDWARE_MOVEMENT_STOP;
        break;
    default:
        return HARDWARE_MOVEMENT_STOP;
        break;
    }
}
int should_elevator_stop(Elevator elevator) {
    switch (elevator.movement){
    case HARDWARE_MOVEMENT_DOWN:            
        if (elevator.orders[elevator.floor][HARDWARE_ORDER_DOWN] ||  
            elevator.orders[elevator.floor][HARDWARE_ORDER_INSIDE]  ||  
            !orders_below(elevator))
        { 
            return 1;
        }
        else 
        {
            return 0;
        }
        break;              
    case HARDWARE_MOVEMENT_UP:
        if (elevator.orders[elevator.floor][HARDWARE_ORDER_UP] ||  
            elevator.orders[elevator.floor][HARDWARE_ORDER_INSIDE]  ||  
            !orders_above(elevator))
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

Elevator clear_elevator_order(Elevator elevator) {
    elevator.orders[elevator.floor][HARDWARE_ORDER_INSIDE] = 0;
    elevator.orders[elevator.floor][HARDWARE_ORDER_DOWN] = 0;
    elevator.orders[elevator.floor][HARDWARE_ORDER_UP] = 0;

    return elevator;
}

Elevator clear_all_orders(Elevator elevator){
    for (int i = 0 ; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        for (int j = 0; j < HARDWARE_NUMBER_OF_BUTTONS; j++){
            elevator.orders[i][j] = 0;
        }
    }
    return elevator;
}


