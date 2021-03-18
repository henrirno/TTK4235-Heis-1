/**
 * @file
 * @brief Bestillingsfunskjoner til heisen.
 */

#ifndef ORDERS_H
#define ORDERS_H

#include "elevator.h"
#include "fsm.h"
#include <stdio.h>


/**
* @brief Sjekker om det er ordre i etasjene over den naavaerende etasjen.
*
* @param[in] elevator Heisen brukes som input for aa finne naavaerende etasje, samt sjekke ordre i etasjene over.
*
* @return 1 hvis det er ordre over naavaerende etasje, 0 hvis ikke.
*/
int orders_above(Elevator elevator);

/**
* @brief Sjekker om det er ordre i etasjene under den naavaerende etasjen.
*
* @param[in] elevator Heisen brukes som input for aa finne naavaerende etasje, samt sjekke ordre i etasjene under.
*
* @return 1 hvis det er ordre under naavaerende etasje, 0 hvis ikke.
*/
int orders_below(Elevator elevator);

/**
* @brief En funksjon som bestemmer hvilken retning heisen skal gaa.
*
* @param[in] elevator For aa finne naavaerende bevegelse.
*
* @return HardwareMovement: HARDWARE_MOVEMENT_UP, HARDWARE_MOVEMENT_DOWN eller HARDWARE_MOVEMENT_STOP - avhengig av hvilken retning heisen har og om det er ordre under eller over.
*/
HardwareMovement orders_choose_direction(Elevator elevator);

/**
* @brief En funksjon som bestemmer om heisen skal stoppe. Dette avhenger av hvilken retning heisen har, om det er ordre fra gangen i den retningen eller videre samme retning, eller ordre innenfra til naavaerende etasje.
*
* @param[in] elevator Heisen brukes som input for aa finne naavaerende bevegelse, posisjon og ordre.
*
* @return 1 hvis skal stoppe, 0 hvis ikke.
*/
int should_elevator_stop(Elevator elevator);

/**
* @brief Fjerner alle ordrene og lys i den etasjen heisen er i.
*
* @param[in, out] elevator Heis for aa finne naavaerende etasje og sette ordren her til null.
*
* @return elevator for aa oppdatere ordrene til den globale heisen.
*/
Elevator clear_elevator_order(Elevator elevator);

/**
* @brief Fjerner alle ordrene og tilsvarende lys til heisen.
*
* @param[in, out] elevator For aa kunne sette alle ordrene til heisen til null.
*
* @return elevator for aa oppdatere ordrene til den globale heisen.
*/
Elevator clear_all_orders(Elevator elevator);
#endif