// Header files.
#include <stdio.h>
#include "StandardConstants.h"

// Global constants.

// Function prototypes.

/*
Name:                       getStringLength
Process:                    Finds the length of a string by
                            counting characters up to the NULL_CHAR character.
Function Input/Parameters:  C-Style string (char *).
Function Output/Parameters: None
Function Output/Returned:   Length of string.
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               None
*/
int getStringLength ( const char *testStr )
   {
   // Initialize function/variables.
   int index = 0;

   // Loop to end of string, preventing overflow.
   while ( index < STD_STR_LEN && testStr[ index ] != NULL_CHAR )
      {
      // Update index.
      index++;
      }

   // End Loop.

   // Return index/length.
   return index;
   }

// Main program.

/*
Name:                       main
Process:                    Finds the length of a string and displays it.
Function Input/Parameters:  None
Function Output/Parameters: None
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      Result displayed.
Dependencies:               stdio tools.
*/
int main()
   {
   // Initialize function/variables.
      // Create a test string.
      char testString[] = "This is a test string.";

      // Declare other variables.
      int strLen;      

      // Display title.
         // Function: printf
         printf( "\nString Length Test Program\n" );
         printf( "==========================\n\n" );

   // Conduct string length test.
      // Function: getStringLength
      strLen = getStringLength( testString );

   // Display result to user.
      // Function: printf
      printf( "The length of string \"%s\" is %d\n\n", testString, strLen );

   // Shut down program.
      // Display program end.
         // Function: printf
         printf( "\nProgram End\n" );

      // Return program success.
      return 0;

   }
