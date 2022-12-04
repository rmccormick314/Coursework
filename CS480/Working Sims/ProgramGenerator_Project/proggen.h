// Header file for proggen.c

// Precompiler directive, to eliminate multiple compiles of h file
#ifndef PROGGEN_H
#define PROGGEN_H

// global constants

const int STD_STR_LEN = 45;
const int INPUT_CHANCE = 40;
const int OPTIME_MAX = 10;
const int OPTIME_MIN = 5;
const char NULL_CHAR = '\0';
const char ENDLINE_CHAR[] = "\n";

typedef enum { False, True } Boolean;

// function prototypes

void getNewOp( int percent, char opStr[], Boolean firstOpFlag );
Boolean getOdds( int oddPercent );
int getRandBetween( int low, int high );
int intToString( int value, char valStr[], int index );

#endif // PROGGEN_H


