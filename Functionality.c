#include "Functionality.h"
// Ideen er at i main() så har vi en evig while-løkke som hele tiden sjekker sensorenene på etasjene og knappene
// Da trenger vi kun å fokusere på funksjonaliteten her og ikke om det faktisk blir fanget opp --> induksjon



static Elevator elevator;

// vi kjører denne før while(1) - det er basic_state() 
// Når vi går videre til while(1) så sjekker den alle sensorene om den er på en etasje og evt stopper
// Hvis det blir problemer med at ordre kan komme inn før den har nådd etasjen så må vi kanskje gå tilbake til sånn vi hadde det
// Men jeg tror det skal være fikset med button_press_event() case Moving:      - For den skal jo aldri plutselig endre retning mellom to etasjer
void initialize_elevator() {
    elevator.movement = HARDWARE_MOVEMENT_DOWN;
    elevator.behaviour = EB_Moving;
    elevator.floor = getFloor();
    hardware_command_movement(elevator.movement);
}

void elevator_arriving_floor(int floor){
    elevator.floor = floor;
    hardware_command_floor_indicator_on(elevator.floor);
    /*if (floor == HARDWARE_NUMBER_OF_FLOORS || floor == 0){
        elevator.behaviour = EB_Idle;
        elevator.movement = HARDWARE_MOVEMENT_STOP;
        }
    */
    switch (elevator.behaviour)
    {
    case EB_Moving:
        if (should_elevator_stop(elevator)) {
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);
            hardware_command_door_open(1);
            door_timer();
            elevator = clear_current_order(elevator);
            set_floor_light(floor, elevator.orders[floor][HARDWARE_ORDER_DOWN],
                            elevator.orders[floor][HARDWARE_ORDER_UP], 1);    // Kanskje litt lang input her, men det ar kanskje det du mente på labben på mandag?
            elevator.bahaviour = EB_DoorOpen;
        }
        break;
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
            // trenger vi dette her hvis vi har en egen funksjon som fikser når døren lukker seg?
            // trur det er lurt med en egen funksjon som håndterer EB_DoorOpen og den skal lukkes
            elevator.movement = orders_choose_direction(elevator);
            hardware_command_movement(elevator.movement);
            elevator.behaviour = EB_Moving;
        }
    case EB_Idle:
        if (elevator.floor == btn_floor) {
            hardware_command_door_open(1);
            door_timer(); //start_door_timer()
            elevator.behaviour = EB_DoorOpen; // her kan den jo sendes til håndterer'en av EB_DoorOpen
        }
        else {
            elevator.orders[btn_floor][order_type] = 1;
            elevator.movement = orders_choose_direction(elevator);
            hardware_command_movement(elevator.movement);
            elevator.behaviour = EB_Moving;
        }
        break;
    case EB_Moving:
        elevator.orders[btn_floor][order_type] = 1;
        break;
    }
    default:
        break;
        set_floor_light(btn_floor, elevator.orders[floor][order_type], 1); // ikke helt riktig input her, nettoppp derfor den kanskje burde endres
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
}

//må fikse timeren sånn at vi kan sjekke eksternt om den er utgått
// fordi det er jo en del ting som må gjøres da, så greit å gjøre det i en egen funksjon

