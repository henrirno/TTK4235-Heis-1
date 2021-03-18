/**
 * @file
 * @brief Koden til tilstandsmaskinen til heisen.
 */

#ifndef FSM_H
#define FSM_H

#include "orders.h"
#include "timer.h"

#include <stdio.h>

/**
 * @brief Heisen gjøres klart til bruk ved aa gaa til nærmeste underetasje og deretter nullstille bestillingsmatrisen.
 *
 * @param[out] movement Heisbevegelsen blir satt med retning ned.
 * @param[out] behavior Heisen blir satt 
 */
void initialize_elevator();

/**
 * @brief Stopper heisen paa etasje og aapner door, eller hvis inititialized stopper den heisen og setter ElevatorBehaviour til Idle.
 *
 * @param[in] floor Forteller hvilken etasje heisen er i
 * @param[out] behavior Behaviour settes til DoorOpen eller Idle avhengig av casen til heisen
 */
void elevator_arriving_floor(int floor);

/**
 * @brief Haandterer knappetrykk for alle heisens tilstander. Legger til ordre til etasje @p btn_floor av type @order_type i köen. Setter retning til heisen hvis den staar i ro. Funksjonen bestemmer ogsaa retning hvis stoppknapp har blitt trykket, ved hjelp av @p elevator.prev_floor og @p elevator.prev_movement
 *
 * @param[in] btn_floor Hvilken etasje knappen ble trykket paa.
 * @param[in] order_type Forteller type HardwareOrder.
 * @param[in, out] elevator Henter og eventuelt endrer heisens tilstand
 */
void button_press_event(int btn_floor, HardwareOrder order_type);

/**
 * @brief Lukker door, skrur av den aktuelle bestillingslampen og nullstiller bestillingen.
 *
 * @param[out] elevator Endrer heisbevegelsen oppförsel og bevegelse.

 */
void close_door();

/**
 * @brief Skrur av bestillingslampe spesifisert paa bestillingstype. 
 *
 * @param[out] time_start Global tidsreferanse for aa sette timer-tiden
 */
void clear_order_light();

/**
 * @brief Sjekker om door er aapen og returnerer henholdsvis 0 eller 1. 
 *
 * @return 1 hvis door er aapen og 0 hvis ikke.
 */
int check_door_open();

/**
 * @brief Hvis stopp-knappen holdes inne blir alle bestillinger og bestillingslys nullstilt og heisen staar stille i naavaerende posisjon frem til knappen ikke holdes inne.
 *
 * @param[out] elevator Endrer heisbevegelsen oppförsel og etasje.
 */
void stop_button_pressed();

/**
 * @brief Sjekker om heisen faktisk er i en etasjen den tror den er i.
 *
 * @return 1 hvis heisen er i en etasjen, 0 hvis ikke. 
 */
int at_floor();

/**
 * @brief Nullstiller alle bestillingslamper
 *
 * @param * @param[out] orders bestillingsmatrisen.
 */
void clear_all_order_lights();

#endif