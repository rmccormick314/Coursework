// Protect from multiple compilations
#ifndef DATATYPES_H
#define DATATYPES_H

#include <stdio.h>
#include <stdbool.h>
#include "StandardConstants.h"

// GLOBAL CONSTANTS - May be used in other files
typedef enum { CMD_STR_LEN = 5,
               IO_ARG_STR_LEN = 5,
               STR_ARG_LEN = 15 } OpCodeArrayCapacity;

// Five state
typedef enum { NEW_STATE,
               READY_STATE,
               RUNNING_STATE,
               BLOCKED_STATE,
               EXIT_STATE } ProcessState;

typedef struct OpCodeTypeStruct
   {
      int pid;
      char command[ STD_STR_LEN ];
      char inOutArg[ STD_STR_LEN ];
      char strArg1[ STD_STR_LEN ];
      int intArg2;
      int intArg3;
      double opEndTime;

      struct OpCodeType* nextNode;
   } OpCodeType;

typedef struct ConfigDataTypeStruct
   {
      char metaDataFileName[ STD_STR_LEN ];
      int cpuSchedCode;
      int ioCycleRate;
      int memAvailable;
      int logToCode;
      char logToFileName[ STD_STR_LEN ];
      bool memDisplay;
      int procCycleRate;
      double version;
      int quantumCycles;
   } ConfigDataType;

#endif // DATATYPES
