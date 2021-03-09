#include "fsm.h"

static Elevator elevator;

void initialize_elevator() {
    elevator.movement = HARDWARE_MOVEMENT_DOWN;
    elevator.behaviour = EB_Initilizing;
    for (int i = 0 ; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        for (int j = 0; j < HARDWARE_NUMBER_OF_BUTTONS; j++){
            elevator.orders[i][j] = 0;
            
        }
    }
    hardware_command_movement(elevator.movement);
}

void elevator_arriving_floor(int floor){
    elevator.floor = floor;
    hardware_command_floor_indicator_on(elevator.floor);
   
    switch (elevator.behaviour)
    {
    case EB_Moving:
        //print_elevator_movement(elevator.movement);
        if (should_elevator_stop(elevator) == 1) {
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            hardware_command_door_open(1);

            printf("\nShould stop --> start timer\n");
            start_timer();
            
            clear_order_light();
            elevator = clear_elevator_order(elevator);
            
            elevator.behaviour = EB_DoorOpen;
        }
        break;
    case EB_Initilizing:
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        printf("Elevator initialized, now Idle\n");
        elevator.behaviour = EB_Idle;
        break;
    default:
        printf("not doing anything smart\n");
        break;
    }
}

void button_press_event(int btn_floor, HardwareOrder order_type) {
    switch (elevator.behaviour) {
    case EB_DoorOpen:  
        printf("door open\n");
        if (elevator.floor == btn_floor) {
            start_timer();
        }
        else {
            elevator.orders[btn_floor][order_type] = 1;
            // trenger vi dette her hvis vi har en egen funksjon som fikser n�r d�ren lukker seg?
            // trur det er lurt med en egen funksjon som h�ndterer EB_DoorOpen og den skal lukkes
            //elevator.movement = orders_choose_direction(elevator);
            //hardware_command_movement(elevator.movement);
            //elevator.behaviour = EB_Moving;
        }
        break;
    case EB_Idle:
        if (elevator.floor == btn_floor) {
            printf("it is on pressed floor\n");
            hardware_command_door_open(1);
            start_timer(); 
            elevator.behaviour = EB_DoorOpen; // her kan den jo sendes til h�ndterer'en av EB_DoorOpen
        }
        else {
            
            elevator.orders[btn_floor][order_type] = 1;
            
            printf("Button not on floor --> moving to %d\n",btn_floor);
            elevator.movement = orders_choose_direction(elevator);
            hardware_command_movement(elevator.movement);
            print_orders(elevator);
            printf("\nCurrent elevator.movement:\n");
            print_elevator_movement(elevator.movement);
            elevator.behaviour = EB_Moving;
            
        }
        break;
    case EB_Moving:
        elevator.orders[btn_floor][order_type] = 1;
        print_orders(elevator);
        break;
    default:
        break;
    }
    if (elevator.orders[btn_floor][order_type] == 1){
        hardware_command_order_light(btn_floor,order_type,1);
    }else {
        hardware_command_order_light(btn_floor,order_type,0);
    }
        
}

void close_door() {
    if (elevator.behaviour == EB_DoorOpen) {
        elevator.movement = orders_choose_direction(elevator);
        hardware_command_door_open(0);
        hardware_command_movement(elevator.movement);
        printf("closed door\n\n");
        
        if (elevator.movement == HARDWARE_MOVEMENT_STOP) {
            elevator.behaviour = EB_Idle;
        }
        else {
            elevator.behaviour = EB_Moving; 
        }
    }
    
}

void clear_order_light(){
    HardwareOrder order_types[3] = {
        HARDWARE_ORDER_UP,
        HARDWARE_ORDER_INSIDE,
        HARDWARE_ORDER_DOWN
    };
    for (int btn = 0 ; btn < HARDWARE_NUMBER_OF_BUTTONS; btn++){
        if (elevator.orders[elevator.floor][btn])
        {
            hardware_command_order_light(elevator.floor, order_types[btn], 0);
        }
        
    }
    
}

