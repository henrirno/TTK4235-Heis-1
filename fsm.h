#ifndef FSM_H
#define FSM_H

#include "Orders.h"
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
 * @brief Hvis heisen er i den aktuelle etasjen, så åpner den døren. Hvis den ikke er i etasje legger den inn bestilling: Sjekker om heisen er i bevegelse, og bytter retning hvis forrige bestilling er over og på vei opp eller motsatt. Hvis heis ikke er i bevegelse, starter heisen etter den bestillingen. I tillegg printer den heisbevegelsen til terminalen og skrur på det aktuelle bestillingslyset.
 *
 * @param[in] btn_floor i hvilken etasje knappen ble trykket på.
 * @param[in] order_type forteller type HardwareOrder.
 * @param[out] orders bestillingen registreres i bestillingsmatrisen.
 * @param[out] movement heisbevegelsen er gitt ut i fra bestillingen.
 * @param[out] behavior forteller at heisen nå er i bevegelse.
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
 * @return Returnerer 1 hvis døren er åpen og 0 hvis ikke.
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
 * @brief Sjekker om heisen er i en etasje og returnerer henholdsvis 0 eller 1.
 *
 * @return returnerer 1 hvis heisen er i en etasje og 0 hvis ikke. 
 */
int at_floor();

/**
 * @brief Nullstiller alle bestillingslamper
 *
 * @param * @param[out] orders bestillingsmatrisen.
 */
void clear_all_order_lights();

#endif