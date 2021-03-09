#include "Elevator.h"


void print_elevator_movement(HardwareMovement movement){
    switch (movement)
    {
    case HARDWARE_MOVEMENT_DOWN:
        printf("HARDWARE_MOVEMENT_DOWN\n");
        break;
    case HARDWARE_MOVEMENT_UP:
        printf("HARDWARE_MOVEMENT_UP\n");
        break;
    case HARDWARE_MOVEMENT_STOP:
        printf("HARDWARE_MOVEMENT_STOP\n");
    }
}
void print_orders(Elevator elevator){
    for (int i = 0 ; i < HARDWARE_NUMBER_OF_FLOORS; i++){
        printf("[");
        for (int j = 0; j < HARDWARE_NUMBER_OF_BUTTONS; j++){
            printf("%d  ",elevator.orders[i][j]);
        }
        printf("]\n");
    }
    printf("\n");
}

void print_order_type(HardwareOrder order_type){
    switch (order_type)
    {
    case HARDWARE_ORDER_DOWN:
        printf("HARDWARE_ORDER_DOWN\n");
        break;
    case HARDWARE_ORDER_INSIDE:
        printf("HARDWARE_ORDER_INSIDE\n");
        break;
    case HARDWARE_ORDER_UP:
        printf("HARDWARE_ORDER_UP\n");
        break;
    }
}

void print_elevator_behaviour(ElevatorBehaviour	behaviour){
    switch (behaviour)
    {
    case EB_DoorOpen:
        printf("EB_DoorOpen\n");
        break;
    case EB_Idle:
        printf("EB_Idle\n");
        break;
    case EB_Moving:
        printf("EB_Moving\n");
        break;
    default:
        break;
    }
}