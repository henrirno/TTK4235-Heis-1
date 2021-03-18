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
 * @brief Heisen gjøres klart til bruk ved å gå til nærmeste underetasje og deretter nullstille bestillingsmatrisen.
 *
 * @param[out] movement heisbevegelsen blir satt med retning ned.
 * @param[out] behavior heisen blir satt 
 */
void initialize_elevator();

/**
 * @brief Stopper heisen på etasje og åpner dør, eller hvis inititialized stopper den heisen og setter Elevator Behaviour til idle.
 *
 * @param[in] floor forteller hvilken etasje heisen er i
 * @param[out] behavior behaviour settes til DoorOpen eller Idle avhengig av casen til heisen
 */
void elevator_arriving_floor(int floor);

/**
 * @brief Forklar hovedfunksjonaliteten til funksjonen og ikke hva den gjør i detalj.
 Haandterer knappetrykk for alle heisens tilstander. Legger til ordre til etasje @p btn_floor av type @order_type i köen. Setter retning til heisen hvis den staar i ro. Funksjonen bestemmer ogsaa retning hvis stoppknapp har blitt trykket, ved hjelp av @p elevator.prev_floor og @p elevator.prev_movement
 *
 * @param[in] btn_floor Hvilken etasje knappen ble trykket på.
 * @param[in] order_type Forteller type HardwareOrder.
 * @param[in] elevator.prev_floor Heisens tidligere etasje.
 * @param[in] elevator.prev_movement Heisens tidligere bevegelse.
 * @param[out] elevator.orders Bestillingen registreres i bestillingsmatrisen.
 * @param[out] elevator.movement Heisbevegelsen blir satt ut ifra bestillingen.
 * @param[out] elevator.behavior Tilstanden til heisen.
 */
void button_press_event(int btn_floor, HardwareOrder order_type);

/**
 * @brief Lukker døren, skrur av den aktuelle bestillingslampen og nullstiller bestillingen.
 *
 * @param[out] movement heisbevegelsen er gitt ut i fra bestillingen.
 * @param[out] behavior forteller om heisen er i Idle, bevegelse eller om døren åpnes.
 */
void close_door();

/**
 * @brief Skrur av bestillingslampe spesifisert på bestillingstype. 
 *
 * @param[out] time_start global tidsreferanse for å sette timer-tiden
 */
void clear_order_light();

/**
 * @brief Sjekker om døren er åpen og returnerer henholdsvis 0 eller 1. 
 *
 * @return 1 hvis døren er åpen og 0 hvis ikke.
 */
int check_door_open();

/**
 * @brief Hvis stopp-knappen holdes inne blir alle bestillinger og bestillingslys nullstilt og heisen står stille i nåværende posisjon frem til knappen ikke holdes inne. Setter også nåværende etasje til -1, så heisen er uavhengig av tidligere bevegelser når stopp-knappen ikke lenger trykkes inne.
 *
 * @param[out] behaviour forteller om heisens tilstand
 * @param[out] floor nåværende etasje
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