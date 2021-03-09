#include "Orders.h"

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
        printf("no orders below/above -> stop\n");
        return HARDWARE_MOVEMENT_STOP;
        break;
    case HARDWARE_MOVEMENT_DOWN:
        if (orders_below(elevator)) {
            
            return HARDWARE_MOVEMENT_DOWN;
        }
        else if (orders_above(elevator)) {
            return HARDWARE_MOVEMENT_UP;
            
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


