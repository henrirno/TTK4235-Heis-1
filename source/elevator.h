/**
 * @file
 * @brief Bevegelse- og tilstands-typer for heisen
 */

#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "hardware.h"
#include <stdio.h>

/**
 * @brief Datatype som beskriver tilstanden til heisen.
 *
 * @param Idle Heis står i ro.
 * @param DoorOpen Heisdør er åpen.
 * @param Moving Heisen er i bevegelse.
 * @param Initializing Heisen er initialisers.
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
 * @param[in] movement Heisbevegelse.
 */
void print_elevator_movement(HardwareMovement movement);

/**
 * @brief Printer ut en 4x3 matrise med bestillinger til terminalen.
 * 
 * @param[in] elevator Henter ordren fra heisen.
 */
void print_orders(Elevator elevator);

/**
 * @brief Printer bestillingstypen @p order_type til terminalen.
 *
 * @param[in] order_type 
 */
void print_order_type(HardwareOrder order_type);

/**
 * @brief Printer tilstanden til heisen til terminalen.
 *
 * @param[in] behaviour Heistilstand.
 */
void print_elevator_behaviour(ElevatorBehaviour	behaviour);
#endif
