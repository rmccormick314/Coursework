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
      char hodor[ STD_STR_LEN ];
   } OpCodeType;

typedef struct ConfigDataTypeStruct
   {
      char metaDataFileName[ STD_STR_LEN ];
   } ConfigDataType;

#endif // DATATYPES
