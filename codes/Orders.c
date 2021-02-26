#include "Orders.h"

int insideOrders(){
    for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS, i++;){   // Hardware_number_of_floors = 4
        if (hardware_read_order(i, HARDWARE_ORDER_INSIDE) == 1) {
            return i;
        }
    }
}

int outsideOrders(){
    for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS, i++;){   // Hardware_number_of_floors = 4
        if (hardware_read_order(i, HARDWARE_ORDER_UP) == 1) {
            return i, int 1;
        } else if (hardware_read_order(i, HARDWARE_ORDER_DOWN) == 1) {
            return i, int 2;
        }
    }
}

void createQueue(){
    int queue[4][3];
    for (int x = 0; x < 4, x++;){
        for (int y = 0; y < 3, y++;){
            queue[x][y]=0;
    }
}

void placeOrder(){
    
}


