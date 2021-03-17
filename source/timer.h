/**
 * @file
 * @brief Timer for heisdøren.
 */

#ifndef TIMER_H
#define TIMER_H

#include "elevator.h"
#include <time.h>

/**
 * @brief Sette tidsbegrensing på timer til 3 sekunder
 */
#define TIME_LIMIT 3

/**
 * @brief Nullstiller tidsvariabelen time_start
 *
 * @param[out] time_start Global tidsreferanse for å sette timer-tiden
 */
void reset_timer();

/**
 * @brief Funksjon som definerer tidsvariabelen til timeren
 *
 * @param[out] time_start Global tidsreferanse for å sette timer-tiden
 */
void start_timer();

/**
 * @brief Beskriver om tiden til timeren er ute eller ikke
 *
 * @param[out] time_start Global tidsreferanse for å sette timer-tiden
 * 
 * @return 0 hvis timeren har gått i 3 sekunder (dette prosjektet TIME_LIMET), og 1 ellers
 */
int timed_out();

#endif