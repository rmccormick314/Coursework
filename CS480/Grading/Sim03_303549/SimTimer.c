// Program Information ////////////////////////////////////////////////////////
/**
 * @file SimpleTimer.c
 * 
 * @brief Implementation file for using a timer with micro-second precision
 * 
 * @author Michael Leverington
 *
 * @details Implements member methods for timing
 *
 * @version 3.00 (02 February 2017) Update to simulator timer
            2.00 (13 January 2017) Update to C language
 *          1.00 (11 September 2015)
 *          
 * @Note Requires SimpleTimer.h.
 * 
 */

// Precompiler directives /////////////////////////////////////////////////////

#ifndef SIMTIMER_C
#define SIMTIMER_C

// Header files ///////////////////////////////////////////////////////////////

#include "SimTimer.h"

// Constants  /////////////////////////////////////////////////////////////////
const char RADIX_POINT = '.';

// Function Implementations

double accessTimer( int controlCode, char *timeStr )
   {
    static bool running = false;
    static int startSec = 0, endSec = 0, startUSec = 0, endUSec = 0;
    static int lapSec = 0, lapUSec = 0;
    struct timeval startData, lapData, endData;
    double fpTime = 0.0;

    fpTime = 0.000000000;
    lapSec = 0;
    lapUSec = 0;

    processTime( 0.0, 0.0, 0.0, 0.0, timeStr ); 

    if( controlCode == LAP_TIMER && running )
       {
        gettimeofday( &lapData, NULL );

        lapSec = lapData.tv_sec;
        lapUSec = lapData.tv_usec;

        fpTime = processTime( startSec, lapSec, startUSec, lapUSec, timeStr );
       }

    else if( controlCode == STOP_TIMER && running )
       {
        gettimeofday( &endData, NULL );
        running = false;

        endSec = endData.tv_sec;
        endUSec = endData.tv_usec;

        fpTime = processTime( startSec, endSec, startUSec, endUSec, timeStr );
       }

    else  // assume zero timer
       {
        gettimeofday( &startData, NULL );
        running = true;

        startSec = startData.tv_sec;
        startUSec = startData.tv_usec;
       }

    return fpTime;
   }

double processTime( double startSec, double endSec, 
                           double startUSec, double endUSec, char *timeStr )
   {
    double secDiff = endSec - startSec;
    double uSecDiff = endUSec - startUSec;
    double fpTime;

    if( uSecDiff < 0 )
       {
        uSecDiff = uSecDiff + 1000000;
        secDiff = secDiff - 1;
       }

    fpTime = (double) secDiff + (double) uSecDiff / 1000000;

    //timeToString( secDiff, uSecDiff, timeStr );
    sprintf( timeStr, "%9.6f", fpTime );

    return fpTime;
   }

void runTimer( int milliSeconds )
   {
    struct timeval startTime, endTime;
    int startSec, startUSec, endSec, endUSec;
    int uSecDiff, mSecDiff, secDiff, timeDiff;

    gettimeofday( &startTime, NULL );
 
    startSec = startTime.tv_sec;
    startUSec = startTime.tv_usec;

    timeDiff = 0;

    while( timeDiff < milliSeconds )
       {
        gettimeofday( &endTime, NULL );

        endSec = endTime.tv_sec;
        endUSec = endTime.tv_usec;
        uSecDiff = endUSec - startUSec;

        if( uSecDiff < 0 )
           {
            uSecDiff = uSecDiff + 1000000;

            endSec = endSec - 1;
           }

        mSecDiff = uSecDiff / 1000;
        secDiff = ( endSec - startSec ) * 1000;
        timeDiff = secDiff + mSecDiff;
       }
   }

#endif // ifndef SIMTIMER_C





