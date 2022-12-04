// Program Information ////////////////////////////////////////////////////////
/**
 * @file SimpleTimer.h
 *
 * @brief Header file for micro-second precision timer
 * 
 * @author Michael Leverington
 * 
 * @details Specifies all member methods of the SimpleTimer
 *
 * @version 2.00 (13 January 2017)
 *          1.00 (11 September 2015)
 *
 * @Note None
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef SIMTIMER_H
#define SIMTIMER_H

// Header files ///////////////////////////////////////////////////////////////

#include <sys/time.h>
#include <string.h>
#include <math.h>
#include "StringUtils.h"
#include "StandardConstants.h"

// Global Constants  //////////////////////////////////////////////////////////

typedef enum { ZERO_TIMER, LAP_TIMER, STOP_TIMER } TimerControlCodes;

// Function Prototype  /////////////////////////////////////////////////////////

void runTimer( int milliSeconds );
double accessTimer( int controlCode, char *timeStr );
double processTime( double startSec, double endSec, 
                           double startUSec, double endUSec, char *timeStr );

#endif // ifndef SIMTIMER_H

