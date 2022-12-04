// Header files.
#include "StringUtils.h"

// Global constants.
   // None

// Function implementations.
/*
Name:                       compareString
Process:                    Compares two strings with the following results:
                            - If left string less than right string, returns
                              less than zero.
                            - If left string greater than right string, returns
                              greater than zero.
                            - If left string equals right string, returns zero.
Function Input/Parameters:  C-Style left and right strings (char *).
Function Output/Parameters: None
Function Output/Returned:   Result as specified (int)
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               getStringLength
*/
int compareString( const char *leftStr, const char *rightStr )
   {
      // Initialize function/variables
      int diff, index = 0;

      // Loop to end of shortest string, with overrun protection.
      while( leftStr[ index ] != NULL_CHAR &&
             rightStr[ index ] != NULL_CHAR &&
             index < MAX_STR_LEN )
         {
            // Get difference in characters
            diff = leftStr[ index ] - rightStr[ index ];

            // Check for difference between characters
            if ( diff != 0 )
            {
               // Return difference
               return diff;
            }

            // Increment index
            index++;
         }
         // End loop

      // Return difference in lengths, if any
         // Function: getStringLength
         return ( getStringLength( leftStr ) - getStringLength( rightStr ) );
   }

/*
Name:                       concatenateString
Process:                    Appends one string to another.
Function Input/Parameters:  C-Style source string (char *).
Function Output/Parameters: C-Style destination string (char *).
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               getStringLength
*/
void concatenateString( char *destStr, const char *sourceStr )
   {
      // Initialize function/variables
         // Set destination index
            // Function: getStringLength
            int destIndex = getStringLength( destStr );

         // Get source string length
            // Function: getStringLength
            int sourceStrLen = getStringLength( sourceStr );

         // Create temporary string pointer
         char *tempStr;

         // Create other variables
         int sourceIndex = 0;

      // Copy source string in case of aliasing
         // Function: malloc, copyString
         tempStr = (char *)malloc( sizeof( sourceStrLen + 1 ) );
         copyString( tempStr, sourceStr );

      // Loop to end of source string
      while( tempStr[ sourceIndex ] != NULL_CHAR &&
             destIndex < MAX_STR_LEN )
         {
           // Assign characters to end of destination string
           destStr[ destIndex ] = tempStr[ sourceIndex ];

           // Update indicies
           destIndex++;
           sourceIndex++;

           // Set temporary end of destination string
           destStr[ destIndex ] = NULL_CHAR;
         }
      // End loop

      // Release memory used for temp string
         // Function: free
         free( tempStr );

      // No return required
   }

/*
Name:                       copyString
Process:                    Copies one string into another,
                            overwriting data in the destination string.
Function Input/Parameters:  C-Style source string (char *).
Function Output/Parameters: C-Style destination string (char *).
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               getStringLength
*/
void copyString( char *destStr, const char *sourceStr )
   {
      // Initialize function
      int index = 0;

      // Check for source/destination not the same (aliasing)
      if ( destStr != sourceStr )
      {
         // Loop to end of source string
         while( sourceStr[ index ] != NULL_CHAR &&
                index < MAX_STR_LEN )
         {
            // Assign characters to end of destination string
            destStr[ index ] = sourceStr[ index ];

            // Update index
            index++;

            // Set temporary end of destination string
            destStr[ index ] = NULL_CHAR;
         }
         // End loop
      }

      // No return required.
   }

/*
Name:                       findSubString
Process:                    Linear search for a given substring within
                            another string.
Function Input/Parameters:  C-Style source test string (char *),
                            C-Style source search string (char *).
Function Output/Parameters: None
Function Output/Returned:   Index of found substring, or SUBSTRING_NOT_FOUND
                            constant if string not found.
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               getStringLength
*/
int findSubString( const char *testStr, const char *searchSubStr )
   {
      // Initialize function/variables
         // Initialize test string length
            // Function: getStringLength
            int testStrLen = getStringLength( testStr );

         // Initialize master index - location of sub string start point
         int masterIndex = 0;

         // Initialize other variables
         int searchIndex, internalIndex;

      // Loop across test string
      while( masterIndex < testStrLen )
      {
         // Set internal loop index to current string index
         internalIndex = masterIndex;

         // Set internal search index to zero
         searchIndex = 0;

         // Loop to end of test string
         // While test string/sub string characters are the same
         while( internalIndex <= testStrLen &&
                testStr[ internalIndex ] == searchSubStr[ searchIndex ] )
         {
            // Increment test string, substring indices
            internalIndex++;
            searchIndex++;

            // Check for end of substring (search completed)
            if( searchSubStr[ searchIndex ] == NULL_CHAR )
            {
               // Return beginning location of sub string
               return masterIndex;
            }
         }
         // End internal comparison loop

         // Increment current beginning location index
         masterIndex++;
      }
      // End loop across test string

      // Assume test has failed at this point, return SUBSTRING_NOT_FOUND
      return SUBSTRING_NOT_FOUND;

   }

/*
Name:                       getStringConstrained
Process:                    Captures a string from the input stream with
                            various constraints.
Function Input/Parameters:  Input stream (FILE *),
                            Clears leading non printable (bool),
                            Clears leading space (bool),
                            Stops at non-printable (bool),
                            Stops at specified delimiter (char)
                            Note: Consumes delimiter
Function Output/Parameters: C-Style string returned (char *).
Function Output/Returned:   Success of operation (bool).
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               fgetc
*/
bool getStringConstrained(
                         FILE *inStream,
                         bool clearLeadingNonPrintable,
                         bool clearLeadingSpace,
                         bool stopAtNonPrintable,
                         char delimiter,
                         char *capturedString
                        )
   {
      // Initialize variables
      int intChar = EOF, index = 0;

      // Initialize output string
      capturedString[ index ] = NULL_CHAR;

      // Capture first value in stream
         // Function: fgetc
         intChar = fgetc( inStream );

      // Loop to clear non-printable or space, if indicated
      while( ( intChar != EOF) &&
              ( ( clearLeadingNonPrintable  && intChar < (int)SPACE ) ||
                ( clearLeadingSpace && intChar == (int)SPACE ) )
           )
         {
            // Get next character
              // Function: fgetc
              intChar = fgetc( inStream );
         }
      // End clear non-printable/space loop

      // Check for end of file found
      if ( intChar == EOF )
      {
         // Return failed operation
         return false;
      }

      // Loop to capture input
      while(
            // Continues if not at end of file and max string length not reached
            ( intChar != EOF && index < MAX_STR_LEN - 1 )

            // AND
            // Continues if not-printable flag is set and characters are printable
            //    OR continues if non-printable flag not set
            && ( ( stopAtNonPrintable && intChar >= (int)SPACE )
                   || ( !stopAtNonPrintable ) )

            // AND
            // Continues if specified delimiter is not found
            && ( intChar != (char)delimiter )
           )
         {
            // Place character into array element
            capturedString[ index ] = (char)intChar;

            // Increment array index
            index++;

            // Set next element to null character / end of c-string
            capturedString[ index ] = NULL_CHAR;

            // Get next character as integer
               // Function: fgetc
               intChar = fgetc( inStream );
         }
         // End loop

      // Return successful operation
      return true;
   }

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
int getStringLength( const char *testStr )
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

/*
Name:                       getStringToDelimiter
Process:                    Captures a string from the input stream to a
                            specified delimiter.
                            Note: consumes delimiter.
Function Input/Parameters:  Input stream (FILE *),
                            Stops at specified delimiter (char).
Function Output/Parameters: C-Style string returned (char *).
Function Output/Returned:   Success of operation (bool).
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               getStringConstrained
*/
bool getStringToDelimiter(
                          FILE *inStream,
                          char delimiter,
                          char *capturedString
                         )
   {
      // Call engine function with delimiter
         // Function: getStringConstrained
         return getStringConstrained(
           inStream,        // File stream pointer
           true,            // Clears leading non-printable characters
           true,            // bool clearLeadingSpace
           true,            // Stops at non-printable
           delimiter,       // Stops at delimiter
           capturedString   // Returns string
         );
   }

/*
Name:                       getStringToLineEnd
Process:                    Captures a string from the input stream to
                            the end of the line.
Function Input/Parameters:  Input stream (FILE *)
Function Output/Parameters: C-Style string returned (char *).
Function Output/Returned:   Success of operation (bool).
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               getStringConstrained
*/
bool getStringToLineEnd(
                         FILE *inStream,
                         char *capturedString
                        )
   {
      // Call engine function with specified constraints
         // Function: getStringConstrained
         return getStringConstrained(
           inStream,            // File stream pointer
           true,                // Clears leading non-printable characters
           true,                // bool clearLeadingSpace
           true,                // Stops at non-printable
           NON_PRINTABLE_CHAR,  // Non-printable delimiter
           capturedString       // Returns string
         );
   }

/*
Name:                       getSubString
Process:                    Captures a sub string within larger string,
                            between two inclusive indicies.
                            - Returns empty string if either index is
                              out of range.
                            - Assumes enough memory in destination string.
Function Input/Parameters:  C-Style source string (char *),
                            start and end indicies (int).
Function Output/Parameters: C-Style destination string (char *).
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               getStringLength, malloc, copyString, free
*/
void getSubString( char *destStr, const char *sourceStr,
                  int startIndex, int endIndex )
   {
      // Initialize function/variables
         // Set length of source string
            // Function: getStringLength
            int sourceStrLen = getStringLength( sourceStr );

         // Initialize the destination index to zero
         int destIndex = 0;

         // Initialize the source index to start index (parameter)
         int sourceIndex = startIndex;

         // Create pointer for temp string
         char *tempStr;

      // Check for indices within limits
      if ( startIndex >= 0 &&
           startIndex <= endIndex &&
           endIndex < sourceStrLen )
         {
            // Create temporary string
               // Function: malloc, copyString
               tempStr = (char *)malloc( sourceStrLen + 1 );
               copyString( tempStr, sourceStr );

            // Loop across requested substring (indices)
            while( sourceIndex <= endIndex )
               {
                  // Assign source character to destination element
                  destStr[ destIndex ] = tempStr[ sourceIndex ];

                  // Increment indices
                  destIndex++;
                  sourceIndex++;

                  // Set temporary end of destination string
                  destStr[ destIndex ] = NULL_CHAR;
               }
            // End loop

            // Return memory to OS for destination string
               // Function: free
               free( tempStr );
         }

      // No return required.
   }

/*
Name:                       setStrToLowerCase
Process:                    Iterates through string, setting any upper case
                            letter to lower case; no effect on other letters.
Function Input/Parameters:  C-Style source string (char *).
Function Output/Parameters: C-Style destination string (char *).
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               toLowerCase
*/
void setStrToLowerCase( char *destStr, const char *sourceStr )
   {
      // Initialize function/variables
         // Get source string length
            // Function: getStringLength
            int sourceStrLen = getStringLength( sourceStr );

         // Create temporary string pointer
         char *tempStr = NULL;

         // Create other variables
         int index = 0;

      // Copy source string in case of aliasing
         // Function: malloc, copyString
         // Note: extra memory is allocated to fix valgrind errors
         tempStr = (char *)malloc( (char)sizeof( sourceStrLen ) +
                                   (char)sizeof( NULL_CHAR ) * 3 );
         copyString( tempStr, sourceStr );

      // Loop across source string
      while ( tempStr[ index ] != NULL_CHAR &&
              index < MAX_STR_LEN )
         {
            // Set individual character to lower case as needed,
            // Assign to destination string
            destStr[ index ] = toLowerCase( tempStr[ index ] );

            // Update index
            index++;

            // Set temporary end of destination string
            destStr[ index ] = NULL_CHAR;
         }
      // End loop

      // Release memory used for temp string
         // Function: free
         free( tempStr );

      // No return required
   }

/*
Name:                       toLowerCase
Process:                    If character is upper case, change it to lower case;
                            otherwise returns character unchanged.
Function Input/Parameters:  Test character (char)
Function Output/Parameters: None
Function Output/Returned:   Character to set to lower case, if appropriate.
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               None
*/
int toLowerCase( char testChar )
   {
      // Check for upper case letter
      if ( testChar >= 'A' && testChar <= 'Z' )
      {
         // Return lower case letter
         return testChar - 'A' + 'a';
      }

      // Otherwise, assume no upper case letter
      // Return character unchanged
      return testChar;
   }
