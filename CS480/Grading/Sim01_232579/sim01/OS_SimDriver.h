// Preprocessor directive
#ifndef OS_SIMDRIVER_H
#define OS_SIMDRIVER_H

// header files
#include "dataTypes.h"
#include "metadataops.h"
#include "configops.h"
#include "StringUtils.h"
#include "StandardConstants.h"
#include "simulator.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// program constants
typedef enum {MIN_NUM_ARGS = 3, LAST_FOUR_LETTERS = 4 } PRGRM_CONSTANTS;

typedef struct CmdLineDataStruct
	{
		bool programRunFlag;
		bool configDisplayFlag;
		bool mdDisplayFlag;
		bool runSimFlag;
		char fileName[STD_STR_LEN];
	} CmdLineData;

// function declaration
int main(int argc, char **argv);
void clearCmdLineStruct (CmdLineData *clDataPtr);
bool processCmdLine (int numArgs, char **strVector, CmdLineData *clDataPtr );
void showProgramFormat();

#endif  // OS_SIMDRIVER_H