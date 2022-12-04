//protect from multiple compiling
#ifndef OS_SIMDRIVER_H
#define OS_SIMDRIVER_H

//header files
#include <stdio.h>
#include "datatypes.h"
#include "StringUtils.h"
#include "configops.h"
#include "metadataops.h"
#include "simulator.h"

//program constants
typedef enum { MIN_NUM_ARGS = 3, LAST_FOUR_LETTERS = 4 } PRGRM_CONSTANTS;

//Command line struct for storing command line switch settings
typedef struct CmdLineDataStruct
    {
     bool programRunFlag;
     bool configDisplayFlag;
     bool mdDisplayFlag;
     bool runSimFLag;

     char fileName[ STD_STR_LEN ];
    } CmdLineData;

#endif

void clearCmdLineStruct( CmdLineData *clDataPtr );
bool processCmdLine( int numArgs, char**strVector, CmdLineData *clDataPtr );
void showCommandLineFormat();