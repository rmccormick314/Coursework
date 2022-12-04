// Header files.
#include "StandardConstants.h"

// Global constants.

// Function implementations.

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
