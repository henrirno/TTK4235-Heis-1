#include "Orders.h"

int orders_above(Elevator elevator){
    // HER ER FEILEN MED STOPP KNAPPEN: elevator.floor = -1
    //  Har stoppet og må finne ut hvor den er-ish
    /*
    if (elevator.floor == -1){
        elevator.floor = elevator.prev_floor;
    }
    */
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
    //elev.floor = 2
    // elevator.orders[0][0] = 1 ...
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
        printf("was and is stop\n");
        return HARDWARE_MOVEMENT_STOP;
        break;
    }
}
int should_elevator_stop(Elevator elevator) {
    switch (elevator.movement){
    case HARDWARE_MOVEMENT_DOWN:            // HARDWARE_ORDER_DOWN = 2 // hvis den skal ned p� denne etasje eller //  noen har bestilt inne i heise her eller//   det ikke er noen ordre lengre ned
        if (elevator.orders[elevator.floor][HARDWARE_ORDER_DOWN] ||  
            elevator.orders[elevator.floor][HARDWARE_ORDER_INSIDE]  ||  
            !orders_below(elevator))
        { 
            //print_orders(elevator);
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
    switch (elevator.movement)
    {
    case HARDWARE_MOVEMENT_DOWN:
        elevator.orders[elevator.floor][HARDWARE_ORDER_DOWN] = 0;
        elevator.orders[elevator.floor][HARDWARE_ORDER_UP] = 0;
        hardware_command_order_light(elevator.floor,HARDWARE_ORDER_DOWN,0);
        hardware_command_order_light(elevator.floor,HARDWARE_ORDER_UP,0);
        break;
    case HARDWARE_MOVEMENT_UP:
        elevator.orders[elevator.floor][HARDWARE_ORDER_UP] = 0;
        elevator.orders[elevator.floor][HARDWARE_ORDER_DOWN] = 0;
        hardware_command_order_light(elevator.floor,HARDWARE_ORDER_UP,0);
        hardware_command_order_light(elevator.floor,HARDWARE_ORDER_DOWN,0);
        break;
    case HARDWARE_MOVEMENT_STOP:
        elevator.orders[elevator.floor][HARDWARE_ORDER_DOWN] = 0;
        elevator.orders[elevator.floor][HARDWARE_MOVEMENT_UP] = 0;
        hardware_command_order_light(elevator.floor,HARDWARE_ORDER_UP,0);
        hardware_command_order_light(elevator.floor,HARDWARE_ORDER_DOWN,0);
        break;
    default:
        break;
    }
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


