// Protect from multiple compilations
#ifndef OS_SIM_DRIVER_H
#define OS_SIM_DRIVER_H

// Header files
#include <stdio.h>
#include "datatypes.h"
#include "StringUtils.h"
#include "metadataops.h"
#include "simulator.h"
#include "configops.h"

// Program constants
typedef enum { MIN_NUM_ARGS = 3, LAST_FOUR_LETTERS = 4 } PRGRM_CONSTANTS;

// Command Line structure for storing command line switch settings
typedef struct CmdLineDataStruct
   {
      bool programRunFlag;
      bool configDisplayFlag;
      bool mdDisplayFlag;
      bool runSimFlag;

      char fileName[ STD_STR_LEN ];
   } CmdLineData;

// FUNCTION PROTOTYPES
/*
Name:                       clearCmdLineStruct
Process:                    Sets command line structure data to defaults:
                            Booleans to false, fileName to empty string.
Function Input/Parameters:  Pointer to command line structure (CmdLineData *)
Function Output/Parameters: Pointer to command line structure (CmdLineData *),
                            with updated members.
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               None
*/
void clearCmdLineStruct( CmdLineData *clDataPtr );

/*
Name:                       processCmdLine
Process:                    Checks for at least two arguments,
                            then sets booleans depending on cmd line switches.
                            These switches can be in any order.
                            Also captures config file name which must be
                            the last argument.
Function Input/Parameters:  Number of arguments (int),
                            Vector of arguments (char **)
Function Output/Parameters: Pointer to command line structure (CmdLineData *)
                            with updated members.
                            Set to default values if failure to capture args.
Function Output/Returned:   Boolean result of argument capture.
                            True if at least one switch and config file name,
                            False otherwise.
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               tbd
*/
bool processCmdLine( int numArgs, char **strVector, CmdLineData *clDataPtr );

/*
Name:                       showCommandLineFormat
Process:                    Displays command line format as assistance to user.
Function Input/Parameters:  None
Function Output/Parameters: None
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      Data displayed as specified
Dependencies:               printf
*/
void showCommandLineFormat();

#endif // OS_SimDriver
