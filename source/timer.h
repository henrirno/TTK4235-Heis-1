/**
 * @file
 * @brief Timer for heisdoor.
 */

#ifndef TIMER_H
#define TIMER_H

#include "elevator.h"
#include <time.h>

/**
 * @brief Sette tidsbegrensing paa timer til 3 sekunder.
 */
#define TIME_LIMIT 3

/**
 * @brief Nullstiller tidsvariabelen time_start.
 *
 * @param[in, out] time_start Global tidsreferanse for aa sette timer-tiden.
 */
void reset_timer();

/**
 * @brief Funksjon som definerer tidsvariabelen til timeren.
 *
 * @param[in, out] time_start Global tidsreferanse for aa sette timer-tiden.
 */
void start_timer();

/**
 * @brief Beskriver om tiden til timeren er ute eller ikke.
 *
 * @param[in,out] time_start Global tidsreferanse for aa sette timer-tiden.
 * 
 * @return 1 hvis timeren har gaatt i 3 sekunder (dette prosjektet TIME_LIMIT), og 0 hvis ikke.
 */
int timed_out();

#endif
