#include "Functionality.h"
// Ideen er at i main() s� har vi en evig while-l�kke som hele tiden sjekker sensorenene p� etasjene og knappene
// Da trenger vi kun � fokusere p� funksjonaliteten her og ikke om det faktisk blir fanget opp --> induksjon



static Elevator elevator;

// vi kj�rer denne f�r while(1) - det er basic_state() 
// N�r vi g�r videre til while(1) s� sjekker den alle sensorene om den er p� en etasje og evt stopper
// Hvis det blir problemer med at ordre kan komme inn f�r den har n�dd etasjen s� m� vi kanskje g� tilbake til s�nn vi hadde det
// Men jeg tror det skal v�re fikset med button_press_event() case Moving:      - For den skal jo aldri plutselig endre retning mellom to etasjer
void initialize_elevator() {
    elevator.movement = HARDWARE_MOVEMENT_DOWN;
    elevator.behaviour = EB_Initilizing;
    //elevator.floor = getFloor();
    hardware_command_movement(elevator.movement);
}

void elevator_arriving_floor(int floor){
    elevator.floor = floor;
    printf("read floorsensor: %d\n",floor);
    hardware_command_floor_indicator_on(elevator.floor);
    /*if (floor == HARDWARE_NUMBER_OF_FLOORS || floor == 0){
        elevator.behaviour = EB_Idle;
        elevator.movement = HARDWARE_MOVEMENT_STOP;
        }
    */
    switch (elevator.behaviour)
    {
    case EB_Moving:
        if (should_elevator_stop(elevator) == 1) {
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            hardware_command_door_open(1);
            door_timer();
            Elevator temp_elev = clear_elevator_order(elevator);
            elevator = temp_elev;
            //set_floor_light(floor,HARDWARE_ORDER_DOWN, 1);    // Kanskje litt lang input her, men det ar kanskje det du mente p� labben p� mandag?
            //set_floor_light(floor,HARDWARE_ORDER_UP,1);
            elevator.behaviour = EB_DoorOpen;
        }else{
            printf("Didn't think it should stop\n");
        }
        break;
    case EB_Initilizing:
        hardware_command_movement(HARDWARE_MOVEMENT_STOP);
        //elevator = clear_elevator_order(elevator);
        printf("Elevator initialized, now Idle\n");
        elevator.behaviour = EB_Idle;
    default:
        break;
    }
}

void button_press_event(int btn_floor, HardwareOrder order_type) {
    switch (elevator.behaviour) {
    case EB_DoorOpen:  
        if (elevator.floor == btn_floor) {
            door_timer();
        }
        else {
            elevator.orders[btn_floor][order_type] = 1;
            // trenger vi dette her hvis vi har en egen funksjon som fikser n�r d�ren lukker seg?
            // trur det er lurt med en egen funksjon som h�ndterer EB_DoorOpen og den skal lukkes
            //elevator.movement = orders_choose_direction(elevator);
            //hardware_command_movement(elevator.movement);
            //elevator.behaviour = EB_Moving;
        }
    case EB_Idle:
        if (elevator.floor == btn_floor) {
            printf("it is on pressed floor\n");
            hardware_command_door_open(1);
            door_timer(); //start_door_timer()
            elevator.behaviour = EB_DoorOpen; // her kan den jo sendes til h�ndterer'en av EB_DoorOpen
        }
        else {
            elevator.orders[btn_floor][order_type] = 1;
            elevator.movement = orders_choose_direction(elevator);
            hardware_command_movement(elevator.movement);
            elevator.behaviour = EB_Moving;
            printf("Button not on floor --> moving\n to %d",btn_floor);
        }
        break;
    case EB_Moving:
        elevator.orders[btn_floor][order_type] = 1;
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
        /*if (hardware_read_obstruction_signal()) {
            elevator.behaviour = EB_Idle;
            door_timer(); //start_door_timer()
        }
        */
        if (elevator.movement == HARDWARE_MOVEMENT_STOP) {
            elevator.movement = EB_Idle;
        }
        else {
            elevator.movement = EB_Moving; 
        }
    }
    //set_floor_light(elevator.floor, )
}

//m� fikse timeren s�nn at vi kan sjekke eksternt om den er utg�tt
// fordi det er jo en del ting som m� gj�res da, s� greit � gj�re det i en egen funksjon

