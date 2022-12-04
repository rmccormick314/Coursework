// Preprocessor directive
#ifndef STRING_UTILS_H
#define STRING_UTILS_H

// Header files
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "StandardConstants.h"

// FUNCTION PROTOTYPES
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
int compareString( const char *leftStr, const char *rightStr );

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
void concatenateString( char *destStr, const char *sourceStr );

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
void copyString( char *destStr, const char *sourceStr );

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
int findSubString( const char *testStr, const char *searchSubStr );

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
                       );

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
int getStringLength( const char *testStr );

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
                       );

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
                      );

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
                  int startIndex, int endIndex );

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
void setStrToLowerCase( char *destStr, const char *sourceStr );

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
int toLowerCase( char testChar );

#endif // STRING_UTILS_H
