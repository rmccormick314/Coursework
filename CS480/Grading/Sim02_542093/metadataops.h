#ifndef META_OPS_H
#define META_OPS_H

// Header Files
#include "datatypes.h"
#include "stringUtils.h"
#include "configops.h"

// Constants
typedef enum {BAD_ARG_VAL = -1,
              NO_ACCESS_ERR,
              MD_FILE_ACCESS_ERR,
              MD_CORRUPT_DESCRIPTOR_ERR,
              OPCMD_ACCESS_ERR,
              CORRUPT_OPCMD_ERR,
              CORRUPT_OPCMD_ARG_ERR,
              UNBALANCED_START_END_ERR,
              COMPLETE_OPCMD_FOUND_MSG,
              LAST_OPCMD_FOUND_MSG} OpCodeMessages;

// ==== Structs ====

typedef struct OpCodeType
{
    int pid;                          // pid, added when PCB is created
    char command[ CMD_STR_LEN ];      // three letter command quantity
    char inOutArg[ IO_ARG_STR_LEN ];  // for device in/out
    char strArg1[ STR_ARG_LEN ];      // arg 1 descriptor, up to 12 chars
    int intArg2;                      // cycles or memory, assumes 4 byte int
    int intArg3;                      // memory, assumes 4 byte int
                                      //   also non/premption indicator
    double opEndTime;                 // size of time string returned from accessTimer
    struct OpCodeType *nextNode;      // pointer to next node as needed
} OpCodeType;

// ==== Function Prototypes ====

/*
 Name: addNode
 Process: Adds metadata node to linked list recursively,
          handles empty list condition
 Function Input/Parameters: Pointer to head or next linked node (OpCodeType *),
                            pointer to new node (OpCodeType *)
 Function Output/Parameters: None
 Function Output/Returned: Pointer to previous node, or head node (OpCodeType *)
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: copyString, malloc
*/
OpCodeType *addNode(OpCodeType *localPtr, OpCodeType *newNode);

/*
 Name: clearMetaDataList
 Process: Recursively traverses list, frees dynamically allocated nodes
 Function Input/Parameters: Node op code (const OpCodeType *)
 Function Output/Parameters: None
 Function Output/Returned: NULL (OpCodeType *)
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: clearMetaDataList, free
*/
OpCodeType *clearMetaDataList(OpCodeType *localPtr);

/*
 Name: displayMetaData
 Process: Data dump/display all op code items
 Function Input/Parameters: Pointer to head
                            of op code/metadata list (const OpCodeType *)
 Function Output/Parameters: None
 Function Output/Returned: None
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: None
*/
void displayMetaData(const OpCodeType *localPtr);

/*
 Name: getCommand
 Process: Parses three letter command part of op code string
 Function Input/Parameters: Input op code string (const char *),
                            starting index (int)
 Function Output/Parameters: Parsed command (char *)
 Function Output/Returned: Updated starting index for use
                           by calling function (int)
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: None
*/
int getCommand(char *cmd, const char *inputStr, int index);

/*
 Name: getMetaData
 Process: Main driver function to upload, parse, and store list
          of op code commands in a linked list
 Function Input/Parameters: File name (const char *)
 Function Output/Parameters: Pointer
                             to op code linked list head pointer (OpCodeType *)
                             result message of function state
                             after completion (char *)
 Function Output/Returned: Boolean result of operation (bool)
 Device Input/File: op code list uploaded
 Device Output/Device: None
 Dependencies: CopyString, fopen, getStringToDelimiter,
               compareString, fclose, malloc, getOpCommand,
               updateStartCount, updateEndCount,
               clearMetaDataList, free, addNode
*/
bool getMetaData(const char *fileName, OpCodeType **opCodeDataHead, char *endStateMsg);

/*
 Name: getNumberArg
 Process: Starts at given index, captures and assembles integer argument,
          and returns as parameter
 Function Input/Parameters: Input string (const char *), starting index (int)
 Function Output/Parameters: Pointer to captured integer value
 Function Output/Returned: Updated index for next function start
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: isDigit
*/
int getNumberArg(int *number, const char *inputStr, int index);

/*
 Name: isDigit
 Process: Tests character parameter for digit, returns true if is digit,
          false otherwise
 Function Input/Parameters: Test character (char)
 Function Output/Parameters: None
 Function Output/Returned: Boolean result of test (bool)
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: None
*/
bool isDigit(char testChar);

/*
 Name: getOpCommand
 Process: Acquires one op command line from previously opened file,
          parses it, and sets various struct members according
          to the three letter command
 Function Input/Parameters: piotner to open file handle (FILE *)
 Function Output/Parameters: Pointer to one op code struct (OpCodeType *)
 Function Output/Returned: Coded result of operation (OpCodeMessages)
 Device Input/File: Opcode line uploaded
 Device Output/Device: None
 Dependencies: getStringToDelimiter, getCommand, copyString, verifyValidCommand,
               compareString, getStringArg, verifyFirstStringArg, getNumberArg
*/
OpCodeMessages getOpCommand(FILE *filePtr, OpCodeType *inData);

/*
 Name: getStringArg
 Process: Starts at given index, captures and assembles string argument,
          and returns as parameter
 Function Input/Parameters: Input string (const char *), starting index (int)
 Function Output/Parameters: Pointer to captured string argument (char *)
 Function Output/Returned: Updated index for next function start
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: None
*/
int getStringArg(char *strArg, const char *inputStr, int index);

/*
 Name: updateEndCount
 Process: Manages count of "end" arguments to be compared at end
          of process input
 Function Input/Parameters: Initial count (int),
                            test string for "end" (const char *)
 Function Output/Parameters: None
 Function Output/Returned: Updated count, if "end" string found,
                           otherwise no change
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: compareString
*/
int updateEndCount(int count, const char *opString);

/*
 Name: updateStartCount
 Process: Manages count of "start" arguments to be compared at end
          of process input
 Function Input/Parameters: Initial count (int),
                            test string for "start" (const char *)
 Function Output/Parameters: None
 Function Output/Retruned: Updated count, if "start" string found,
                           otherwise no change
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: compareString
*/
int updateStartCount(int count, const char *opString);

/*
 Name: verifyFirstStringArg
 Process: Checks for all possibilities of first argument string of op command
 Function Input/Parameters: Test string (const char *)
 Function Output/Parameters: None
 Function Ouput/Returned: Boolean result of test (bool)
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: compareString
*/
bool verifyFirstStringArg(const char *strArg);

/*
 Name: verifyValidCommand
 Process: Checks for all possibilities of three-letter op code commands
 Function Input/Parameters: Test string for command (const char *)
 Function Output/Parameters: None
 Function Output/Returned: Boolean result of test (bool)
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: compareString
*/
bool verifyValidCommand(char *testCmd);


#endif // META_OPS_H
