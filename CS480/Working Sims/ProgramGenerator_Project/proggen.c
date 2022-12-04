// header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "proggen.h"

// main program
int main()
   {
    // initialize program

       // initialize variables
       int procPercentage, numOps, numPrograms;
       int progCtr, opCtr;
       char fileName[ STD_STR_LEN ];
       FILE *outFilePtr;
       char opString[ STD_STR_LEN ];
       char tempString[ STD_STR_LEN ];

       // initialize random generator
          // function: srand
       srand( time( NULL ) );

       // show title
          // function: printf
       printf( "Program Meta-Data Creation Program\n\n" );

    // get file name for meta-data file
       // function: printf, scanf
    printf( "Enter file name to use: " );
    scanf( "%s", fileName );

    // get weight of processing
       // function: printf, scanf
    printf( "Enter percentage of processing: " );
    scanf( "%d", &procPercentage );

    // get number of actions
       // function: printf, scanf
    printf( "Enter number of operations per program: " );
    scanf( "%d", &numOps );

    // get number of programs to generate
       // function: printf, scanf
    printf( "Enter number of programs: " );
    scanf( "%d", &numPrograms );

    // open file
       // function: fopen
    outFilePtr = fopen( fileName, "w" );

    // output file description header
       // function: fputs
    fputs( "Start Program Meta-Data Code:\r\n", outFilePtr );

    // set temporary string with string literal
       // function: strcpy
    strcpy( tempString, "sys start\r\n" );

    // output Operating System start
       // function: fputs
    fputs( tempString, outFilePtr );

    // loop across number of programs
    for( progCtr = 0; progCtr < numPrograms; progCtr++ )
       {
        // set temporary string with string literal
           // function: strcpy
        strcpy( tempString, "app start, 0\r\n" );
    
        // show begin of program
           // function: fputs
        fputs( tempString, outFilePtr );

        // get new op, force first item to be input
           // function: getNewOp
        getNewOp( procPercentage, opString, True );

        // loop across number of operations
        for( opCtr = 0; opCtr < numOps; opCtr++ )
           {
            // output new op
               // function: fputs
            fputs( opString, outFilePtr );

            // get new op
            // function: getNewOp
            getNewOp( procPercentage, opString, False );
           }
        // end loop across number of operations

        // set temporary string with string literal
           // function: strcpy
        strcpy( tempString, "app end\r\n" );

        // add end of program
           // function: fputs
        fputs( tempString, outFilePtr );
       }
    // end number of programs loop

    // set temporary string with string literal
       // function: strcpy
    strcpy( tempString, "sys end\r\n" );

    // output end of operating system
       // function: fputs
    fputs( tempString, outFilePtr );

    // output file description header
       // function: fputs
    fputs( "End Program Meta-Data Code.\n\n", outFilePtr );

    // close file
       // function: fclose
    fclose( outFilePtr );

    // shut down program

       // return success
       return 0; 
   }

// supporting function implementations

int getRandBetween( int low, int high )
   {
    // initialize range
    int range = high - low + 1;

    // set random result and return
       // function: rand
    return rand() % range + low;    
   }

Boolean getOdds( int oddPercent )
   {
    // initialize odds
       // function: rand
    int randVal = rand() % 100 + 1;

    // check for odds less than/equal to specification
    if( randVal <= oddPercent )
       {
        // return true
        return True;
       }

    // otherwise, if odds not met, return false
    return False;
   }

void getNewOp( int percent, char opStr[], Boolean firstOpFlag )
   {
    // initialize recursive start index
    int recStartIndex = 0;
    int selectionChance = 25;  // roughly 1 in 7 chance

    // initialize speedFactor to 1, for processor
        // speedFactor makes I/O devices relatively slower than the processor
        // - although not as relatively slow as they would really be
    int speedFactor = 1;

    // declare other variables
    int numCycles;
    char numStr[ STD_STR_LEN ];

    // check for chance of processing
       // function: getOdds
    if( firstOpFlag == False && getOdds( percent ) == True )
       {
        // place a processing action
           // function: strcpy
        strcpy( opStr, "cpu process, " );
       }

    // otherwise, assume some kind of I/O
    else
       {
        // check for first I/O operations, or chance of input operation
             // function: getOdds
        if( firstOpFlag == True 
                           || getOdds( INPUT_CHANCE ) == True ) // input process
           {
            // check for odds of Ethernet
            if( getOdds( selectionChance ) == True )
               {
                // place a keyboard operation
                   // function: strcpy
                strcpy( opStr, "dev in, ethernet, " );

                // 10x slower than processor
                speedFactor = 2;
               }

            // check for odds of hard drive
                // function: getOdds
            if( getOdds( selectionChance ) == True )
               {
                // place a hard drive operation
                   // function: strcpy
                strcpy( opStr, "dev in, hard drive, " );

                // 3x slower than processor
                speedFactor = 3;
               }

            // otherwise, assume keyboard
            else if( getOdds( selectionChance ) == True )
               {
                // place a keyboard operation
                   // function: strcpy
                strcpy( opStr, "dev in, keyboard, " );

                // 10x slower than processor
                speedFactor = 10;
               }

            // otherwise, assume serial
            else if( getOdds( selectionChance ) == True )
               {
                // place a keyboard operation
                   // function: strcpy
                strcpy( opStr, "dev in, serial, " );

                // 10x slower than processor
                speedFactor = 4;
               }

            // otherwise, assume sound signal
            else if( getOdds( selectionChance ) == True )
               {
                // place a keyboard operation
                   // function: strcpy
                strcpy( opStr, "dev in, sound signal, " );

                // 10x slower than processor
                speedFactor = 5;
               }

            // otherwise, assume USB
            else if( getOdds( selectionChance ) == True )
               {
                // place a keyboard operation
                   // function: strcpy
                strcpy( opStr, "dev in, usb, " );

                // 10x slower than processor
                speedFactor = 2;
               }

            // otherwise, assume video signal
            else
               {
                // place a keyboard operation
                   // function: strcpy
                strcpy( opStr, "dev in, video signal, " );

                // 10x slower than processor
                speedFactor = 7;
               }
           }

        // otherwise, assume output operation
        else
           {
            // check for odds of Ethernet
            if( getOdds( selectionChance ) == True )
               {
                // place a keyboard operation
                   // function: strcpy
                strcpy( opStr, "dev out, ethernet, " );

                // 10x slower than processor
                speedFactor = 2;
               }

            // check for odds of hard drive
                // function: getOdds
            if( getOdds( selectionChance ) == True )
               {
                // place a hard drive operation
                   // function: strcpy
                strcpy( opStr, "dev out, hard drive, " );

                // 3x slower than processor
                speedFactor = 3;
               }

            // otherwise, assume keyboard
            else if( getOdds( selectionChance ) == True )
               {
                // place a keyboard operation
                   // function: strcpy
                strcpy( opStr, "dev out, monitor, " );

                // 10x slower than processor
                speedFactor = 10;
               }

            // otherwise, assume serial
            else if( getOdds( selectionChance ) == True )
               {
                // place a keyboard operation
                   // function: strcpy
                strcpy( opStr, "dev out, serial, " );

                // 10x slower than processor
                speedFactor = 4;
               }

            // otherwise, assume sound signal
            else if( getOdds( selectionChance ) == True )
               {
                // place a keyboard operation
                   // function: strcpy
                strcpy( opStr, "dev out, sound signal, " );

                // 10x slower than processor
                speedFactor = 5;
               }

            // otherwise, assume USB
            else if( getOdds( selectionChance ) == True )
               {
                // place a keyboard operation
                   // function: strcpy
                strcpy( opStr, "dev out, usb, " );

                // 10x slower than processor
                speedFactor = 2;
               }

            // otherwise, assume video signal
            else
               {
                // place a keyboard operation
                   // function: strcpy
                strcpy( opStr, "dev out, video signal, " );

                // 10x slower than processor
                speedFactor = 7;
               }
           }
       }

    // find random number of I/O cycles
       // function: getRandBetween
    numCycles = getRandBetween( OPTIME_MIN, OPTIME_MAX ) * speedFactor;

    // set number as string
       // function: intToString
    intToString( numCycles, numStr, recStartIndex );

    // append string number to metadata item, with endlines
       // function: strcat
    strcat( opStr, numStr );

    strcat( opStr, "\r\n" );

   }

int intToString( int value, char valStr[], int index )
   {
    // initialize function, variables
    char digit;

    // check for digits remaining
    if( value > 0 )
       {
        // convert digit to character
        digit = (char) ( value % 10 + '0' );

        // call recursive function to get next digt
           // function: intToString
        index = intToString( value / 10, valStr, index + 1 );
       }

    // otherwise, assume no digits remaining
    else
       {
        // end string with NULL_CHAR
        valStr[ index ] = NULL_CHAR;

        // return uncounted character
        return 0;
       }

    // add character to string
    valStr[ index ] = digit;

    // return updated string length
    return index + 1;
   }


