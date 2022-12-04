// Used educational coding vidoes from Michael Leverington for this assignment
// Luke Frazer

// header files
#include "OS_SimDriver.h"

// local constants

    // none

// function implementations


/*
Name: compareString
Process: compares two strings with the following results: 
         if left string less than right string, returns less than zero
         if left string greater than right string, returns greater than zero
         if left string equals right string, returns zero
         - equals test includes length
Fucntion Input/Parameters: c-style left and right strings (char *)
Function Output/Parameters: none
Function Output/Returned: results as specified (int)
Device Input/Keybaord: none
Device Output/Monitor: none
Dependencies: getStringLength
*/
int compareString(const char *oneStr, const char *otherStr)
{
    // initialize vars
    int diff, index = 0;

    // loop to end of shortest string, 
    // with overrun protection
    while( oneStr[index] != NULL_CHAR && index < MAX_STR_LEN)
    {
        // get difference in chars
        diff = oneStr[index] - otherStr[index];

        // check for difference between chars
        if(diff != 0)
        {
            // return difference
            return diff;
        }

        // increment index
        index++;
    } 
    // end loop

    // return difference in lengths, if any
    return getStringLength(oneStr) - getStringLength(otherStr);
}

/*
Name: concatenateString
Process: appends one string onto another
Fucntion Input/Parameters: c-style string (char *)
Function Output/Parameters: c-style destination string (char *)
Function Output/Returned: none
Device Input/Keybaord: none
Device Output/Monitor: none
Dependencies: getStringLength
*/
void concatenateString(char *destStr, const char *sourceStr)
{
    // initialize vars

        // set dest index
        int destIndex = getStringLength(destStr);

        // get source string length
        int sourceStrLen = getStringLength(sourceStr);

        // create temp string pointer
        char *tempStr;

        // create other vars
        int sourceIndex = 0;

    // copy source string in case of aliasing
    tempStr = (char *)malloc(sizeof(sourceStrLen + 1));
    copyString(tempStr, sourceStr);

    // loop to end of source string
    while(tempStr[sourceIndex] != NULL_CHAR && destIndex < MAX_STR_LEN)
    {
        // assign chars to end of dest string
        destStr[destIndex] = tempStr[sourceIndex];

        // update indices
        destIndex++; sourceIndex++;

        // set temp end of dest string
        destStr[destIndex] = NULL_CHAR;
    }
    // end loop

    // release memory used for temp string
    free(tempStr);
}

/*
Name: copyString
Process: copies one string into another, 
         overwriting data in the destination string
Fucntion Input/Parameters: c-style string (char *)
Function Output/Parameters: c-style destination string (char *)
Function Output/Returned: none
Device Input/Keybaord: none
Device Output/Monitor: none
Dependencies: getStringLength
*/
void copyString(char *destStr, const char *sourceStr)
{
    // initialize vars
    int index = 0;

    // check for source and dest not the same (aliasing)
    if(destStr != sourceStr)
    {

        // loop to end of source string
        while(sourceStr[index] != NULL_CHAR && index < MAX_STR_LEN)
        {
            // assign chars to end of dest string
            destStr[index] = sourceStr[index];

            // update index
            index++;

            // set temp end of dest string
            destStr[index] = NULL_CHAR;
        }
        // end loop
    }
    // no return required
}

/*
Name: findSubString
Process: linear search for given substring within another string
Fucntion Input/Parameters: c-style source test string (char *), 
                           c-style source search string (char *)
Function Output/Parameters: none
Function Output/Returned: index of found substring, or
                          SUBSTRING_NOT_FOUND constant if string not found
Device Input/Keybaord: none
Device Output/Monitor: none
Dependencies: getStringLength
*/
int findSubString(const char *testStr, const char *searchSubStr)
{
    // initialize vars

        // initialize test string length
        int testStrLen = getStringLength(testStr);

        // initialize master index
        int masterIndex = 0;

        // initialize other variables
        int searchIndex, internalIndex;

    // loop acroos test string
    while(masterIndex < testStrLen)
    {
        // set internal loop index to current test string index
        internalIndex = masterIndex;

        // set internal search index to zero
        searchIndex = 0;

        // loop to end of test string
        // while test string/sub string chars are the same
        while(internalIndex <= testStrLen && 
                            testStr[internalIndex] == searchSubStr[searchIndex])
        {
            // increment test string, substring indices
            internalIndex++; searchIndex++;
            
            // check for end of substring (search completed)
            if(searchSubStr[searchIndex] == NULL_CHAR)
            {
                // return beginning location of sub string
                return masterIndex;

            }
        }
        // end internal loop

        // increment current beginning location index
        masterIndex++;

    }
    // end loop across test string

    // assume test have failed at this point, return SUBSTRING_NOT_FOUND
    return SUBSTRING_NOT_FOUND;
}

/*
Name: getStringConstrained
Process: captures a string from the input stream with various constraints
Fucntion Input/Parameters: input stream (FILE *),
                           clears leading non printable (bool),
                           clears leading space (bool),
                           stops at non printable (bool),
                           stops at specified delimiter (char),
                           Note: consumes delimiter
Function Output/Parameters: string returned (char *)
Function Output/Returned: success of operation (bool)
Device Input/Keybaord: none
Device Output/Monitor: none
Dependencies: fgetc
*/
bool getStringConstrained(FILE *inStream, bool clearLeadingNonPrintable,
                          bool clearLeadingSpace, bool stopAtNonPrintable,
                          char delimiter, char *capturedString) 
{
    // initialize vars
    int intChar = EOF, index = 0;

    // initialize output string
    capturedString[index] = NULL_CHAR;

    // capture first value in stream
    intChar = fgetc(inStream);

    // loop to clear not printable or space, if indicated
    while((intChar != EOF) && ((clearLeadingNonPrintable && 
    intChar < (int)SPACE) || (clearLeadingSpace && intChar == (int)SPACE)))
    {
        // get next character
        intChar = fgetc(inStream);

    }
    // end clar non printable loop

    // check for end of file found
    if(intChar == EOF)
    {
        // return failed operation
        return false;

    }
    // loop to captured input
    while(

        // continues if not at EOF and max string length not reached
        (intChar != EOF && index < MAX_STR_LEN - 1)

        // AND
        // continues if not printable flag set and chars are printable
        //  OR continues if not printable flag not found
        && ((stopAtNonPrintable && intChar >= (int)SPACE)
                                                    || (!stopAtNonPrintable))

        // AND 
        // continues if specified delimiter is not found
        && (intChar != (char)delimiter)
    )
    {
        // place character in array element
        capturedString[index] = (char)intChar;

        // increment array index
        index++;

        // set next element to null char
        capturedString[index] = NULL_CHAR;

        // get next char as integer
        intChar = fgetc(inStream);

    }   
    // end loop

    // return successful operation
    return true;
}

/*
Name: getStringLength
Process: finds the length of a string by counting chars up to NULL_CHAR char
Fucntion Input/Parameters: c-style string (char *)
Function Output/Parameters: none
Function Output/Returned: len of string
Device Input/Keybaord: none
Device Output/Monitor: none
Dependencies: none
*/
int getStringLength(const char *testStr) 
{
    // initialize vars
    int index = 0;

    // loop to end of string, protect from overflow
    while( index < STD_STR_LEN && testStr[index] != NULL_CHAR)
    {
        // update index
        index++;

    }
    // end loop

    // return index/length
    return index;
}

/*
Name: getStringToDelimiter
Process: captures a string from the input stream
         to a specified delimiter
         Note: consumes delimiter
Fucntion Input/Parameters: input stream (FILE *)
                           stops at specified delimiter (char)
Function Output/Parameters: string returned (char *)
Function Output/Returned: success of operation (bool)
Device Input/Keybaord: none
Device Output/Monitor: none
Dependencies: getStringConstrained
*/
bool getStringToDelimiter(FILE *inStream, char delimiter, char *capturedString) 
{
    // call engine function with delimiter
    return getStringConstrained( 
        inStream, 
        true,
        true, 
        true, 
        delimiter, 
        capturedString
        );

}

/*
Name: getStringToLineEnd
Process: captures a string from the input stream to the end of line
Fucntion Input/Parameters: input stream (FILE *)
Function Output/Parameters: string returned (char *)
Function Output/Returned: success of operation
Device Input/Keybaord: none
Device Output/Monitor: none
Dependencies: fgetc
*/
bool getStringToLineEnd(FILE *inStream, char *capturedString) 
{
    // call engine function with delimiter
    return getStringConstrained( 
        inStream, 
        true,
        true, 
        true, 
        NON_PRINTABLE_CHAR, 
        capturedString
        );
}

/*
Name: getSubString
Process: captures sub string within larger string
         between two inclusive indices.
         returns empty string if either index is out of range,
         assums enoguh memory in destination string
Fucntion Input/Parameters: c-style source string (char *), 
                           start and end indices (int)
Function Output/Parameters: c-style destination string (char *)
Function Output/Returned: none
Device Input/Keybaord: none
Device Output/Monitor: none
Dependencies: getStringLength, malloc, copyString, free
*/
void getSubString(char *destStr, const char *sourceStr, 
                 int startIndex, int endIndex) 
{
    // initialize vars

        // set length of source string
        int sourceStrLen = getStringLength(sourceStr);

        // initialize dest index to zero
        int destIndex = 0;

        // initialize source index to start index
        int sourceIndex = startIndex;

        // create pointer for temp string
        char *tempStr;

    // check for indices within limits
    if(startIndex >= 0 && startIndex <= endIndex && endIndex < sourceStrLen)
    {
        // create temp string
        tempStr = (char *)malloc(sourceStrLen + 1);
        copyString(tempStr, sourceStr);

        // loop across requested substring
        while(sourceIndex <= endIndex)
        {
            // assign source char to dest element
            destStr[destIndex] = tempStr[sourceIndex];

            // increment indices
            destIndex++; sourceIndex++;

            // set temp end of dest string
            destStr[destIndex] = NULL_CHAR;

        }
        // end loop

        // return memory for temp string
        free(tempStr);
    }
    // end loop
}

/*
Name: setStrToLowerCase
Process: iterates through string, sets any upper case letter
         to lower case; no effect on other letters
Fucntion Input/Parameters: c-style source string (char *)
Function Output/Parameters: c-style destination string (char *)
Function Output/Returned: none
Device Input/Keybaord: none
Device Output/Monitor: none
Dependencies: toLowerCase
*/
void setStrToLowerCase(char *destStr, const char *sourceStr)
{
    // initialize vars

        // get source string length
        int sourceStrLen = getStringLength(sourceStr);

        // create temp string pointer
        char *tempStr;

        // create other vars
        int index = 0;

    // copy source string in case of aliasing
    tempStr = (char *)malloc(sizeof(sourceStrLen + 1));
    copyString(tempStr, sourceStr);

    // loop across source string
    while(tempStr[index] != NULL_CHAR && index < MAX_STR_LEN)
    {
        // set individual cahrs to lower case as needed,
        // assign to dest string
        destStr[index] = toLowerCase(tempStr[index]);

        // update index
        index++;

        // set temp end of dest string
        destStr[index] = NULL_CHAR;

    }
    // no return

    // release memory used for temp string
    free(tempStr);
}

/*
Name: toLowerCase
Process: if character is upper case, set to lower case;
         otherwise, return character unchanged
Fucntion Input/Parameters: test char (char)
Function Output/Parameters: none
Function Output/Returned: character to set to lower case, if needed
Device Input/Keybaord: none
Device Output/Monitor: none
Dependencies: none
*/
char toLowerCase(char testChar)
{
    // check for upper case letter
    if(testChar >= 'A' && testChar <= 'Z')
    {
        // return lower case letter
        return testChar - 'A' + 'a';
    
    }

    // otherwise, assume no upper case letter,
    // return char unchanged
    return testChar;
}