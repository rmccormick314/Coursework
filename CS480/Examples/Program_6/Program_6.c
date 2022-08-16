// Header files.
#include "StringUtils.h"

//////////////////////////////////////////////////////////////////////////
// Main Program

/*
Name:                       main
Process:                    Finds the length of a string and displays it.
Function Input/Parameters:  None
Function Output/Parameters: None
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      Result displayed.
Dependencies:               stdio tools
*/
int main()
   {
   // Initialize function/variables
      // Create test strings
      char testString[] = "This is a really cool string!";
      char otherString[ MAX_STR_LEN ];
      char subString[ MAX_STR_LEN ];
      char lowerCaseString[ MAX_STR_LEN ];
      char captureString[ MAX_STR_LEN ];

      // Declare other variables
      int strLen, subStrStart;

      // Display title
         // Function: printf
         printf( "\nString Length Test Program\n" );
         printf( "==========================\n\n" );

   // Conduct string length test
      // Function: getStringLength
      strLen = getStringLength( testString );

   // Display result to user
      // Function: printf
      printf( "The length of string \'%s\' is %d\n\n", testString, strLen );

   // Test copy string function
      // Function: copyString
      copyString( otherString, testString );

   // Display copy test to user
      // Function: printf
      printf( "Copied string is: %s\n\n", otherString );

   // Test concatenate string function
      // Function: concatenateString
      concatenateString( otherString, " I'm pretty sure of it." );

   // Display concatenate test to user
      // Function: printf
      printf( "Concatenated string is: %s\n\n", otherString );

   // Test compare string function for greater than condition
      // Function: compareString
      if ( compareString( "Sally", "Roger" ) > STR_EQ )
         {
           // Display compare/greater than test to user
              // Function: printf
              printf( "\'Sally\' is greater than \'Roger\'\n\n" );
         }

   // Test compare string function for less than condition
      // Function: compareString
      if ( compareString( "Cindi", "Sally" ) < STR_EQ )
      {
        // Display compare/less than test to user
           // Function: printf
           printf( "\'Cindi\' is less than \'Sally\'\n\n" );
      }

   // Test compare string function for equals condition
      // Function: compareString
      if ( compareString( "Mista Cumberbatch", "Mista Cumberbatch" ) == STR_EQ)
      {
        // Display compare/equals test to user
           // Function: printf
           printf( "\'Mista Cumberbatch\' is equal to \'Mista Cumberbatch\'\n\n" );
      }

   // Test get sub string Function
      // Function: getSubString
      getSubString( subString, otherString, 34, 44 );

   // Display get sub string test to user
      // Function: printf
      printf( "Sub string found: %s\n\n", subString );

   // Test Find sub string test to user
      // Function: findSubString
      subStrStart = findSubString( otherString, "pretty sure" );

   // Display find sub string test to user
      // Function: printf
      printf( "Sub string start: %d\n\n", subStrStart );

   // Test for setting string with any upper case letter to lower case
      // Function: setStrToLowerCase
      setStrToLowerCase( lowerCaseString, otherString );

   // Display lower case string result to user
      // Function: printf
      printf( "Lower case string: %s\n\n", lowerCaseString );

   // Test get line to delimiter
      // Function: getStringToDelimiter
      getStringToDelimiter( stdin, '.', captureString );

   // Display get line to delimiter strubg result to user
      // Function: printf
      printf( "Captured to delimiter: %s\n\n", captureString );

   // Test get line to end of line
      // Function: getStringToLineEnd
      getStringToLineEnd( stdin, captureString );

   // Display get line to line end result to user
      // Function: printf
      printf( "Captured to end of line: %s\n\n", captureString );

   // Shut down program
      // Display program end
         // Function: printf
         printf( "\nProgram End\n" );

      // Return program success
      return 0;
   }
