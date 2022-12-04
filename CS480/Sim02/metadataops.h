// Protect from multiple compilations
#ifndef METADATAOPS_H
#define METADATAOPS_H

// HEADER FILES
#include <stdio.h>
#include "datatypes.h"
#include "StandardConstants.h"
#include "StringUtils.h"

// FUNCTION PROTOTYPES
/*
Name:                       addNode
Process:                    Adds metadata node to linked list recursively,
                            handles empty list condition
Function Input/Parameters:  Pointer to head or next linked node (OpCodeType *),
                            Pointer to new node (OpCodeType *)
Function Output/Parameters: None
Function Output/Returned:   Pointer to previous node, or head (OpCodeType *)
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               copyString, malloc
*/
OpCodeType *addNode( OpCodeType *localPtr, OpCodeType *newNode );

/*
Name:                       clearMetaDataList
Process:                    Recursively traverses list, frees dynamically
                            allocated nodes.
Function Input/Parameters:  Node op code (const OpCodeType *)
Function Output/Parameters: None
Function Output/Returned:   NULL (OpCodeType *)
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               free
*/
OpCodeType *clearMetaDataList( OpCodeType *localPtr );

/*
Name:                       displayMetaData
Process:                    Screen dump/display all op code files.
Function Input/Parameters:  Pointer to head of op code list (const OpCodeType *)
Function Output/Parameters: None
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      Display config data as specified.
Dependencies:               compareString, printf
*/
void displayMetaData( const OpCodeType *localPtr );

/*
Name:                       getCommand
Process:                    Parses three letter command part of op code string
Function Input/Parameters:  Input OP code string (const char *),
                            Starting index (int)
Function Output/Parameters: Parsed command (char *)
Function Output/Returned:   Updated starting index for use by
                            calling function (int)
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               None
*/
int getCommand( char *cmd, const char *inputStr, int index );

/*
Name:                       getMetaData
Process:                    Main driver function to upload, parse, and store
                            list of op code commands in linked list.
Function Input/Parameters:  File name (const char *)
Function Output/Parameters: Pointer to op code linked list (OpCodeType **),
                            Result message of function state (char *)
Function Output/Returned:   Boolean result of operation (bool)
Device Input/Keyboard:      Op code list uploaded
Device Output/Monitor:      None
Dependencies:               addNode, clearMetaDataList, compareString,
                            copyString, fclose, fopen, free,
                            getStringToDelimiter, malloc, updateStartCount
*/
bool getMetaData( const char *fileName,
                  OpCodeType **opCodeDataHead,
                  char *endStateMsg );

/*
Name:                       getOpCommand
Process:                    Acquires one op command line from a previously
                            opened file, parses it, and sets various struct
                            members according to the three letter command.
Function Input/Parameters:  Pointer to open file handle (FILE *)
Function Output/Parameters: Pointer to one op code struct (OpCodeType *)
Function Output/Returned:   Coded result of operation (OpCodeMessages)
Device Input/Keyboard:      Op Code line uploaded
Device Output/Monitor:      None
Dependencies:               compareString, copyString, getCommand, getNumberArg,
                            getStringArg, getStringToDelimiter,
                            verifyFirstStringArg, verifyValidCommand
*/
OpCodeMessages getOpCommand( FILE *filePtr, OpCodeType *inData );

/*
Name:                       getNumberArg
Process:                    Starts at given index, captures and assembles
                            integer argument, and returns as parameter.
Function Input/Parameters:  Input string (const char *),
                            Starting index (int)
Function Output/Parameters: Pointer to captured integer value
Function Output/Returned:   Updated index for next function start
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               isDigit
*/
int getNumberArg( int *number, const char *inputStr, int index );

/*
Name:                       getStringArg
Process:                    Starts at given index, captures and assembles
                            string argument, and returns as parameter.
Function Input/Parameters:  Input string (const char *),
                            Starting index (int)
Function Output/Parameters: Pointer to captured string argument (char *)
Function Output/Returned:   Updated index for next function start
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               None
*/
int getStringArg( char *strArg, const char *inputStr, int index );

/*
Name:                       isDigit
Process:                    Tests character parameter for digit, returns true if
                            it is a digit, false otherwise
Function Input/Parameters:  Test character (char)
Function Output/Parameters: None
Function Output/Returned:   Boolean result of test (bool)
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               None
*/
bool isDigit( char testChar );

/*
Name:                       updateEndCount
Process:                    Manages a count of "end" arguments to be compared at
                            the end of process input
Function Input/Parameters:  Initial count (int),
                            Test string for "end" (const char *)
Function Output/Parameters: None
Function Output/Returned:   Updated count, if "start" string found,
                            otherwise no change
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               compareString
*/
int updateEndCount( int count, const char *opString );

/*
Name:                       updateStartCount
Process:                    Manages a count of "start" arguments to be compared
                            at the end of process input
Function Input/Parameters:  Initial count (int),
                            Test string for "start" (const char *)
Function Output/Parameters: None
Function Output/Returned:   Updated count, if "start" string found,
                            otherwise no change
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               compareString
*/
int updateStartCount( int count, const char *opString );

/*
Name:                       verifyFirstStringArg
Process:                    Checks for all possible first args in an op command
Function Input/Parameters:  Test string (const char *)
Function Output/Parameters: None
Function Output/Returned:   Boolean result of test (bool)
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               compareString
*/
bool verifyFirstStringArg( const char *strArg );

/*
Name:                       verifyValidCommand
Process:                    Checks for all possible codes in an op command
Function Input/Parameters:  Test string for command (const char *)
Function Output/Parameters: None
Function Output/Returned:   Boolean result of test (bool)
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               compareString
*/
bool verifyValidCommand( char *testCmd );

#endif // METADATAOPS_H
