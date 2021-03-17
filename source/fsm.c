#include "fsm.h"

static Elevator elevator;

void initialize_elevator() {
    elevator.movement = HARDWARE_MOVEMENT_DOWN;
    elevator.behaviour = Initializing;
    for (int i = 0 ; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        for (int j = 0; j < HARDWARE_NUMBER_OF_BUTTONS; j++){
            elevator.orders[i][j] = 0;
        }
        //clear_all_order_lights();
    }
    
    hardware_command_movement(elevator.movement);
}

void elevator_arriving_floor(int floor){
    elevator.floor = floor;
    elevator.prev_floor = floor;
    hardware_command_floor_indicator_on(elevator.floor);
   
    switch (elevator.behaviour)
    {
    case Moving:
        //print_elevator_movement(elevator.movement);
        printf("Arriving floor: %d\n", floor+1);
        if (should_elevator_stop(elevator) == 1) {
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            hardware_command_door_open(1);

            printf("\nShould stop --> start timer\n");
            start_timer();
            
            //clear_order_light();
            //elevator = clear_elevator_order(elevator);
            
            elevator.behaviour = DoorOpen;
        }
        break;
    case Initializing:
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        printf("Elevator initialized, now Idle\n");
        elevator.behaviour = Idle;
        break;
    default:
        printf("not doing anything smart\n");
        break;
    }
}

void button_press_event(int btn_floor, HardwareOrder order_type) {
    switch (elevator.behaviour) {
    case DoorOpen:  
        printf("door open\n");
        if (elevator.floor == btn_floor) {
            start_timer();
        }
        else {
            elevator.orders[btn_floor][order_type] = 1;
        }
        break;
    case Idle:
        if (elevator.floor == btn_floor) {
            printf("it is on pressed floor\n");
            hardware_command_door_open(1);
            start_timer(); 
            elevator.behaviour = DoorOpen; // her kan den jo sendes til h�ndterer'en av DoorOpen
        }
        else {
            //if (btn_floor != 0 && order_type != 0){
                elevator.orders[btn_floor][order_type] = 1;
            //}
            printf("Floor : %d\n", btn_floor +1);
            printf("Order : ");
            print_order_type(order_type);
            
            printf("\nButton not on floor --> moving to %d\n",btn_floor + 1);
            if (elevator.floor == -1){
                elevator.floor = btn_floor;
                printf("PREV_MOVEMENT:\n");
                print_elevator_movement(elevator.prev_movement);
                switch (elevator.prev_movement)
                {
                case HARDWARE_MOVEMENT_UP:
                    if (btn_floor < elevator.prev_floor || btn_floor == elevator.prev_floor){
                        elevator.movement = HARDWARE_MOVEMENT_DOWN;
                        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
                        break;
                    }else if( btn_floor > elevator.prev_floor ){
                        elevator.movement = HARDWARE_MOVEMENT_UP;
                        //var hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
                        hardware_command_movement(elevator.movement);
                        break;
                    }
                    //elevator.floor = btn_floor -1;
                    break;
                case HARDWARE_MOVEMENT_DOWN:
                    if (btn_floor > elevator.prev_floor || btn_floor == elevator.prev_floor){
                        elevator.movement = HARDWARE_MOVEMENT_UP;
                        hardware_command_movement(elevator.movement);
                        break;
                    }else if( btn_floor < elevator.prev_floor ){
                        elevator.movement = HARDWARE_MOVEMENT_DOWN;
                        hardware_command_movement(elevator.movement);
                        break;
                    }
                    //elevator.floor = btn_floor + 1;
                    break;
                default:
                    break;
                }
            }else {
                elevator.movement = orders_choose_direction(elevator);
                elevator.prev_movement = elevator.movement;
                hardware_command_movement(elevator.movement);
            }
            //printf("Think on floor: %d\n",elevator.floor);
            
            print_orders(elevator);
            /*
            printf("Think on floor: %d\n",elevator.floor);
            if (elevator.floor == -1){
                elevator.floor = elevator.prev_floor;
                if (at_floor() == 0)
                {
                    elevator.floor = elevator.floor -1;
                }
            }
            printf("Fake floor: %d\n",elevator.floor);
            */
            printf("\nCurrent elevator.movement:\n");
            print_elevator_movement(elevator.movement);
            elevator.behaviour = Moving;
            
        }
        break;
    case Moving:
        elevator.orders[btn_floor][order_type] = 1;
        //printf("\nCurrent elevator.behaviour:\n");
        //print_elevator_behaviour(elevator.behaviour);
        //print_orders(elevator);
        break;
    default:
        printf("not doing anything smart with btn\n");
        break;
    }
    if (elevator.orders[btn_floor][order_type] == 1){
        hardware_command_order_light(btn_floor,order_type,1);
    }else {
        hardware_command_order_light(btn_floor,order_type,0);
    }
        
}

void close_door() {
    if (elevator.behaviour == DoorOpen) {
        clear_order_light();
        //print_orders();
        elevator = clear_elevator_order(elevator);
        print_orders();
        elevator.movement = orders_choose_direction(elevator);
        hardware_command_door_open(0);
        hardware_command_movement(elevator.movement);
        printf("closed door\n\n");

        
        if (elevator.movement == HARDWARE_MOVEMENT_STOP) {
            elevator.behaviour = Idle;
        }
        else {
            elevator.behaviour = Moving; 
        }
    }
    
}

void clear_all_order_lights(){
    HardwareOrder order_types[3] = {
        HARDWARE_ORDER_UP,
        HARDWARE_ORDER_INSIDE,
        HARDWARE_ORDER_DOWN
    };

    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int btn = 0; btn < HARDWARE_NUMBER_OF_BUTTONS; btn++){
            hardware_command_order_light(f, order_types[btn], 0);
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

int check_door_open(){
    if (elevator.behaviour == DoorOpen){
        return 1;
    }
    return 0;
}
int at_floor(){
    for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++)
    {
        if (hardware_read_floor_sensor(i) && elevator.floor == i){
            printf("At floor: %d\n",i);
            return 1;
        }
    }
    return 0;
}
void stop_button_pressed(){   
    if (elevator.behaviour == Initializing){
        return;
    }
    clear_all_order_lights();
    elevator = clear_all_orders(elevator);
    elevator.movement = HARDWARE_MOVEMENT_STOP;
    hardware_command_movement(elevator.movement);
    hardware_command_stop_light(1);
    if (at_floor()){
        printf("Door open\n");
        elevator.behaviour = DoorOpen;
        hardware_command_door_open(1);
        start_timer();
        return;
    }
    elevator.floor  = -1;
    elevator.behaviour = Idle;
}

