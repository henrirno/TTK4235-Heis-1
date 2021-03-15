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
 * @param[out] time_start global tidsreferanse for å sette timer-tiden
 */
void elevator_arriving_floor(int floor);

/**
 * @brief Nullstiller tidsvariabelen time_start
 *
 * @param[out] time_start global tidsreferanse for å sette timer-tiden
 */
void button_press_event(int btn_floor, HardwareOrder order_type);

/**
 * @brief Nullstiller tidsvariabelen time_start
 *
 * @param[out] time_start global tidsreferanse for å sette timer-tiden
 */
void close_door();

/**
 * @brief Nullstiller tidsvariabelen time_start
 *
 * @param[out] time_start global tidsreferanse for å sette timer-tiden
 */
void clear_order_light();

/**
 * @brief Nullstiller tidsvariabelen time_start
 *
 * @param[out] time_start global tidsreferanse for å sette timer-tiden
 */
int check_door_open();

/**
 * @brief Nullstiller tidsvariabelen time_start
 *
 * @param[out] time_start global tidsreferanse for å sette timer-tiden
 */
void stop_button_pressed();

/**
 * @brief Nullstiller tidsvariabelen time_start
 *
 * @param[out] time_start global tidsreferanse for å sette timer-tiden
 */
int at_floor();

/**
 * @brief Nullstiller tidsvariabelen time_start
 *
 * @param[out] time_start global tidsreferanse for å sette timer-tiden
 */
void clear_all_order_lights();

#endif