#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "hardware.h"
#include <stdio.h>

/**
 * @brief Datatype som beskriver tilstanden til heisen.
 *
 * @param Idle @param DoorOpen @param Moving @param Initializing Heisbevegelse.
 */
typedef enum  {
	Idle,
	DoorOpen,
	Moving,
	Initializing
} ElevatorBehaviour ;


/**
 * @brief Konstruerer en struct med heisens bevegelser, etasjer og bestillinger som medlemsvariabler
 *
 * @param behaviour Heistilstand.
 * @param movement Heisbevegelse.
 * @param prev_movement Forrige heisbevegelse.
 * @param floor Nåværende etasje.
 * @param prev_floor Forrige etasje.
 * @param orders 4(etasjer)x3(knapper)-bestillingsmatrise.
 */
typedef struct {
	ElevatorBehaviour	behaviour;
	HardwareMovement	movement;
	HardwareMovement	prev_movement;
	int					floor;
	int					prev_floor;
	int					orders[HARDWARE_NUMBER_OF_FLOORS][HARDWARE_NUMBER_OF_BUTTONS];
} Elevator;

/**
 * @brief Printer heisbevegelsene opp, ned og stopp til terminalen.
 *
 * @param movement Heisbevegelse.
 */
void print_elevator_movement(HardwareMovement movement);

/**
 * @brief Printer ut en 4x3 matrise med bestillinger til terminalen.
 */
void print_orders();

/**
 * @brief Printer mellom bestillingstypene utside-opp, utside-ned og innside-bestilling til terminalen.
 *
 * 
 */
void print_order_type(HardwareOrder order_type);

/**
 * @brief Printer ElevatorBehaviour til terminalen.
 *
 */
void print_elevator_behaviour(ElevatorBehaviour	behaviour);
#endif
