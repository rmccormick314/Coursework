#ifndef OS_SIM_DRIVER_H
#define OS_SIM_DRIVER_H

// Header files
#include <stdio.h>

#include "datatypes.h"
#include "stringUtils.h"
#include "configops.h"
#include "metadataops.h"
#include "simulator.h"

// Program constants
typedef enum {MIN_NUM_ARGS = 3, LAST_FOUR_LETTERS = 4} PRGRM_CONSTANTS;

// Command line struct for storing command line switch settings
typedef struct CmdLineDataStruct
{
    bool programRunFlag;
    bool configDisplayFlag;
    bool mdDisplayFlag;
    bool runSimFlag;

    char fileName[STD_STR_LEN];
} CmdLineData;

// ==== Function Prototypes ====

/*
 Name: clearCmdLineStruct
 Process: Sets command line structure data to defaults
          Booleans to false, fileName to empty string
 Function Input/Parameters: pointer to cmomand line structure(CmdLineData*)
 Function Output/Parameters: Pointer to command line structure (CmdLineData *)
                             with updated members
 Fuction Output/Returned: None
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: None
*/
void clearCmdLineStruct(CmdLineData *clDataPtr);

/*
 Name: processCmdLine
 Process: Checks for at least two arguments,
          then sets Booleans depending on command line switches
          which can be in any order,
          also captures config file name which must be the last argument
 Function Input/Parameters: Number of arguments (int),
                            vector of arguments (char **)
 Function Output/Parameters: Pointer to command line structure (CmdLineData *)
                             with updated members,
                             to capture arguments
 Function Output/Returned: Boolean result of argument capture,
                           true if at least one switch and config file name,
                           false otherwise
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: compareString, getStringLength, findSubString, copyString,
               clearCmdLineStruct
*/
bool processCmdLine(int numArgs, char **strVector, CmdLineData *clDataPtr);

/*
 Name: showCommandLineFormat
 Process: Display comand line format as assistance to user
 Function Input/Parameters: None
 Function Output/Parameters: None
 Function Output/Returned: None
 Device Input/Device: None
 Device Output/Monitor: Data displayed as specified
 Dependencies: printf
*/
void showCommandLineFormat();

#endif // OS_SIM_DRIVER_H
