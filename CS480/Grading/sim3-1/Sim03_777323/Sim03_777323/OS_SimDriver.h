// Luke Frazer
// Used educational coding vidoes from Michael Leverington for this assignment

// protect from multiple compiling
#ifndef OS_SIM_DRIVER_H
#define OS_SIM_DRIVER_H

// header files
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "datatypes.h"
#include "StringUtils.h"
#include "configops.h"
#include "metadataops.h"
#include "simulator.h"
#include "StandardConstants.h"

// program constants
typedef enum {MIN_NUM_ARGS = 3, LAST_FOUR_LETTERS = 4} PROGRAM_CONSTANTS;

// prototype functions for OS_SimDriver.c
bool processCmdLine(int numArgs, char **strVector, CmdLineData *clDataPtr); 
void showCommandLineFormat();
void clearCmdLineStruct(CmdLineData *clDataPtr);

#endif // OS SIM DRIVER