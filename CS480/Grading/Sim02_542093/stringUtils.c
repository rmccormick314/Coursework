#include <stdio.h>
#include <stdbool.h>

// Header files
#include "stringUtils.h"
#include <stdlib.h>

// Local constants
    // None

// Function implementations

/*
 Name: compareString
 Process: Compares two string with the following results:
          If left string less than right string, returns less than zero
          If left string greater than right string, returns greater than zero
          If left string equals right string, returns zero
          - Equals test includes legnth
 Function Input/Parameters: c-style left and right strings (char *)
 Function Output/Parameters: None
 Function Output/Returned: Result as specified (int)
 Device Input/Keyboard: None
 Device Output/Monitor: None
 Dependencies: getStringLength
*/
int compareString(const char *oneStr, const char *otherStr)
{
    // Initialize function/variables
    int index = 0, difference;

    // Loop to end of shortest string,
    // with overrun protection
    while(oneStr[index] != NULL_CHAR && otherStr[index] != NULL_CHAR
          && index < MAX_STR_LEN)
    {
        // Get difference in characters
        difference = oneStr[index] - otherStr[index];

        // Check for difference between characters
        if(difference != 0)
        {
            // Return difference
            return difference;
        }

        // Increment index
        index++;

    // End loop
    }

    // Return difference in lengths if any
    return getStringLength(oneStr) - getStringLength(otherStr);
}


/*
 Name: concatenateString
 Process: Appends one string onto another
 Function: Input/Parameters: c-style source string (char *)
 Function Output/Parameters: c-style destination string (char *)
 Function Output/Returned: None
 Device Input/Keyboard: None
 Device Output/Monitor: None
 Dependencies: getStringLength
*/
void concatenateString(char *destStr, const char *sourceStr)
{
    // Initialize function/variables
        // Set destination index
            // Function: getStringLength
    int destIndex = getStringLength(destStr);

        // Get source string length
            // Function: getStringLength
    int sourceLength = getStringLength(sourceStr);

        // Create temporary string pointer
    char *tempString;

        // Create other variables
    int index = 0;

    // Copy source string in case of aliasing
        // Function malloc, copyString
    tempString = (char *)malloc(sizeof(char) * (sourceLength + 1));
    copyString(tempString, sourceStr);

    // Loop to end of source string
    while(tempString[index] != NULL_CHAR && destIndex < MAX_STR_LEN)
    {

        // Assign character to end of destination string
        destStr[destIndex] = sourceStr[index];

        // Update indices
        index++;
        destIndex++;

        // Set temporary end of destination string
        destStr[index] = NULL_CHAR;

    // End loop
    }

    // Release memory used for temp string
        // Function: free
    free(tempString);
}

/*
 Name: copyString
 Process: Copied one string into another, overwriting data in the destination string
 Function Input/Parameters: c-style source string (char *)
 Function Output/Parameters: c-style destination string (char *)
 Function Output/Returned: None
 Device Input/Keyboard: None
 Device Output/Monitor: None
 Dependencies: getStringLength
*/
void copyString(char *destStr, const char *sourceStr)
{
    // Initialize function/variables
    int index = 0;

    // Check for source/destination not the same (aliasing)
    if(destStr != sourceStr)
    {
        // Loop to end of source string
        while(sourceStr[index] != NULL_CHAR && index < MAX_STR_LEN)
        {

            // Assign characters to end of destination string
            destStr[index] = sourceStr[index];

            // Update index
            index++;

            // Set temporary end of destination string
            destStr[index] = NULL_CHAR;
        }
        // End loop
    }

}

/*
 Name: findSubString
 Process: Linear search for given substring within another string
 Function Input/Parameters: c-style source test string (char *),
                            c-style source search string (char *)
 Function Output/Parameters: None
 Function Output/Returned: index of found substring,
                           or SUBSTRING_NOT_FOUND constant
                           if string not found
 Device Input/Keybaord: None
 Device Output/Monitor: None
 Dependencies: getStringLength
*/
int findSubString(const char *testStr, const char *searchSubStr)
{
    // Initialize function/variables

        // Initialize test string length
            // Function: getStringLength
    int testStringLength = getStringLength(testStr);

        // Initialize master index - location of sub string start point
    int masterIndex = 0;

        // Initialize other variables
    int searchStrIndex = 0, internalIndex = 0;

    // Loop across test string
    while(masterIndex < testStringLength)
    {
        // Set internal loop index to current test string index
        internalIndex = masterIndex;

        // Set internal search index to zero
        searchStrIndex = 0;

        // Loop to end of test string
        // While test string/sub string characters are the same
        while(internalIndex <= testStringLength &&
                searchSubStr[searchStrIndex] == testStr[internalIndex])
        {
            // Increment test string, substring indices
            internalIndex++;
            searchStrIndex++;

            // Check for end of substring (search completed)
            if(searchSubStr[searchStrIndex] == NULL_CHAR)
            {
                // Return beginning location of sub string
                return masterIndex;
            }

        // End internal comparison loop
        }

        // Increment current beginning location index
        masterIndex++;

    }
    // End loop across test string

    // Assume tests have failed at this point, return SUBSTRING_NOT_FOUND
    return SUBSTRING_NOT_FOUND;
}

/*
 Name: getStringConstrained
 Process: Captures a string from the input stream with various constraints
 Function Input/Parameters: Input stream (FILE *)
                            clears leading non printable (bool),
                            clears leading space (bool),
                            stops at non printable (bool),
                            stops at specified delimiter (char)
                            Note: consumes delimiter
 Function Output/Parameters: String returned (char *)
 Function Output/Returned: Success of operation (bool)
 Device Input/Keyboard: None
 Device Output/Monitor: None
 Dependencies: getStringConstrained
*/
bool getStringConstrained(FILE *inStream,
                          bool clearLeadingNonPrintable,
                          bool clearLeadingSpace,
                          bool stopAtNonPrintable,
                          char delimiter,
                          char *captureString)
{
    // Initialize variables
    int intChar = EOF, index = 0;

    // Initialize output string
    captureString[index] = NULL_CHAR;

    // Capture first value in stream
        // Function: fgetc
    intChar = fgetc(inStream);

    // Loop to clear non printable or space, if indicated
    while((intChar != EOF) &&
                    ((clearLeadingNonPrintable && intChar < (int) SPACE)
                            || (clearLeadingSpace && intChar == (int) SPACE)))
    {
        // Get next character
            // Function: fgetc
        intChar = fgetc(inStream);
    }

    // End clear non printable/space loop

    // Check for end of file found
    if(intChar == EOF)
    {
        // Return failed operation
        return false;
    }

    // Loop to capture input
    while((intChar != EOF && index < MAX_STR_LEN - 1)

    // Continues if not at end of file and max string length not reached

    // AND continues if not printable flag set and characters are printable
    // OR continues if not printable flag not set
        && ((stopAtNonPrintable && intChar >= (int) SPACE) ||
                (!stopAtNonPrintable))

            // AND continues if specified delimiter is not found
        && (intChar != (char)delimiter)
            )
    {
        // Place character in array element
        captureString[index] = (char)intChar;

        // Increment array index
        index++;

        // Set next element to null character/end of c-string
        captureString[index] = NULL_CHAR;

        // Get next character as integer
            // Function: fgetc
        intChar = fgetc(inStream);
    }

    // Return successful operation
    return true;
}

/*
 Name: getStringToDelimiter
 Process: Captures a string from the input stream
          to a specified delimiter;
          Note: consumes delimiter
 Function Input/Parameters: input stream (FILE *)
                            stops at specified delimiter (char)
 Function Output/Parameters: String returned (char *)
 Function Output/Parameters: Success of operation (bool)
 Device Input/Keyboard: None
 Device Output/Monitor: None
 Depenedencies: getStringConstrained
*/
bool getStringToDelimiter(FILE *inStream, char delimiter, char *captureString)
{
    // Call engine function with delimiter
        // Function: getStringConstrained
    return getStringConstrained(
                                inStream,
                                true,
                                true,
                                true,
                                delimiter,
                                captureString
                                );
}

/*
 Name: getStringLength
 Process: Finds the length of a string by counting characters up to the
          NULL_CHAR character
 Function Input/Parameters: c-style string (char *)
 Function Output/Parameters: none
 Function Output/Returned: Length of string
 Device Input/Keyboard: None
 Device Output/Monitor: none
 Dependencies: None
 */
int getStringLength(const char *testStr)
{
    // Initialize function/variables
    int index = 0;

    // Loop to end of string, protect from overflow
    while(index < STD_STR_LEN && testStr[index] != NULL_CHAR)
    {
        // Update index
        index++;
    }
    // End loop

    // Return index/length
    return index;

}

/*
 Name: getStringToLineEnd
 Process: Captures a string from the input stream to the end of the line
 Function Input/Parameters: Input stream (FILE *)
 Function Output/Parameters: String returned (char *)
 Function Output/Returned: Success of operation (bool)
 Device Input/Keyboard: None
 Device Output/Monitor: None
 Dependencies: getStringConstrained
*/
bool getStringToLineEnd(FILE *inStream, char *captureString)
{
    // Call engine function with delimiter
        // Function: getStringConstrained
    return getStringConstrained(
                                inStream,
                                true,
                                true,
                                true,
                                NON_PRINTABLE_CHAR,
                                captureString
                                );
}

/*
 Name: getSubString
 Process: Captures sub string within larger string between two inclusive indices
          Returns empty string if either index is out of range, assumes enough
          memory in destination string
 Function Input/Parameters: c-style source string (char *),
                            start and end indices (int)
 Function Output/Parameters: c-style destination string (char *)
 Function Output/Returned: None
 Device Input/Keyboard: None
 Device Output/Monitor: None
 Dependencies: getStringLength, malloc, copyString, free
*/
void getSubString(char *destStr, const char *sourceStr,
                  int startIndex, int endIndex)
{
    // Initialize function/variables
        // Set length of source string
    int sourceLength = getStringLength(sourceStr);

        // Initialize the destination index to zero
    int destIndex = 0;

        // Initialize source index to start index (parameter)
    int sourceIndex = startIndex;

        // Create pointer for temp string
    char *tempString;

    // Check for indices within limits
    if(sourceIndex <= endIndex && sourceIndex >= 0 && endIndex < sourceLength)
    {

        // Create temporary string
            // Function: malloc, copyString
        tempString = (char *)malloc(sizeof(char) * (sourceLength + 1));
        copyString(destStr, sourceStr);

        // Loop across requested substring (indices)
        while(sourceIndex < endIndex)
        {

            // Assign source character to destination element
            destStr[destIndex] = sourceStr[sourceIndex];

            // Increment indices
            sourceIndex++;
            destIndex++;

            // Set temporary end of destination string
            destStr[destIndex] = NULL_CHAR;

        // End loop
        }

        // Return memory for temporary string
            // Function: free
        free(tempString);
    }
}

/*
 Name: setStrToLowerCase
 Process: Iterates through string, sets any upper case letter
          to lower case; no effect on other letters
 Function Input/Parameters: c-style source string (char *)
 Function Output/Parameters: c-style destination string (char *)
 Function Output/Returned: None
 Device Input/Keyboard: None
 Device Output/Monitor: None
 Dependencies: toLowerCase, getStringLength
*/
void setStrToLowerCase(char *destStr, const char *sourceStr)
{
    // Initialize function/variables

        // Get source string length
            // Function: getStringLength
    int sourceLength = getStringLength(sourceStr);

        // Create temporary string pointer
    char *tempString;

        // Create other variables
    int index = 0;

    // Copy source string in case of aliasing
        // Function: malloc, copyString
    tempString = (char *)malloc(sizeof(char) * (sourceLength + 1));
    copyString(tempString, sourceStr);

    // Loop across source string
    while(index < sourceLength)
    {

        // Set individual character to lower case as needed,
        // assign to destination string
        destStr[index] = toLowerCase(sourceStr[index]);

        // Update index
        index++;

        // Set temporary end of destination string
        destStr[index] = NULL_CHAR;
    }
    // End loop

    // Release memory used for temp string
        // Function: free
    free(tempString);
}

/*
 Name: toLowerCase
 Process: If character is upper case, sets it to lower case;
          otherwise returns character unchanged
 Function Input/Parameters: Test character (char)
 Function Output/Parameters: None
 Function Output/Returned: Character to set to lower case, if appropriate
 Device Input/Keyboard: None
 Device Output/Monitor: None
 Dependencies: None
*/
char toLowerCase(char testChar)
{
    // Check for upper case letter
    if(testChar <= 'Z' && testChar >= 'A')
    {
        // Return lower case letter
        return testChar - 'A' + 'a';
    }

    // Otherwise, assume no upper case letter,
    // return character unchanged
    return testChar;
}
