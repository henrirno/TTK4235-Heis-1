#ifndef ORDERS_H
#define ORDERS_H

#include "elevator.h"
#include "fsm.h"
#include <stdio.h>


/**
* @brief Sjekker om det er ordre i etasjene over den n�v�rende etasjen.
*
* @param[in] elevator Heisen brukes som input for � finne n�v�rende etasje, samt sjekke ordre i etasjene over.
*
* @return 1 hvis det er ordre over n�v�rende etasje, 0 hvis ikke.
*/
int orders_above(Elevator elevator);

/**
* @brief Sjekker om det er ordre i etasjene under den n�v�rende etasjen.
*
* @param[in] elevator Heisen brukes som input for � finne n�v�rende etasje, samt sjekke ordre i etasjene under.
*
* @return 1 hvis det er ordre under n�v�rende etasje, 0 hvis ikke.
*/
int orders_below(Elevator elevator);

/**
* @brief En funksjon som bestemmer hvilken retning heisen skal g�.
*
* @param[in] elevator Heisen brukes som input for � finne n�v�rende bevegelse.
*
* @return HardwareMovement: HARDWARE_MOVEMENT_UP, HARDWARE_MOVEMENT_DOWN eller HARDWARE_MOVEMENT_STOP avhengig av hvilken retning heisen har og om det er ordre under eller over.
*/
HardwareMovement orders_choose_direction(Elevator elevator);

/**
* @brief En funksjon som bestemmer om heisen skal stoppe, avhengig av hvilken retning den har, om det er ordre fra gangen i den retningen eller videre samme retning eller ordre innenfra til den etasjen.
*
* @param[in] elevator Heisen brukes som input for � finne n�v�rende bevegelse, posisjon og ordrene.
*
* @return 1 hvis skal stoppe, 0 hvis ikke.
*/
int should_elevator_stop(Elevator elevator);

/**
* @brief Fjerner alle ordrene og lys i den etasjen heisen er i.
*
* @param[in,out] elevator Heisen brukes som input for � finne n�v�rende etasje og eventuelt sette ordren her til 0.
*
* @return elevator for � oppdatere ordrene til den globale heisen.
*/
Elevator clear_elevator_order(Elevator e);

/**
* @brief Fjerner alle ordrene og tilsvarende lys til heisen.
*
* @param[in, out] elevator Heisen brukes som input for � finne n�v�rende etasje.
*
* @return elevator for � oppdatere ordrene til den globale heisen.
*/
Elevator clear_all_orders(Elevator elevator);
#endif