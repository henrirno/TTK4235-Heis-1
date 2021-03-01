#pragma once
#include "ElevatorDoor.h"
#include "ButtonsOperation.h"
#include "LightOperations.h"

//<<<<<<< HEAD

int queue[4][3];    

int insideOrders();

int outsideOrders();

void executeOrders();

void createMatrix();

void placeOrder();
//=======
void execute_single_order();
void execute_all_orders();

void go_to_floor(int goal_floor);
// string med order: "0,0,0;0,1,0;

//>>>>>>> 1a2fb58a12c9928c15cfc245cd4c241dab994881
