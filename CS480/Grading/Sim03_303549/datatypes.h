// protect from multiple compiling
#ifndef DATATYPES_H
#define DATATYPES_H

//include statements
#include <stdio.h>
#include <stdbool.h>
#include "StandardConstants.h"

typedef enum {  CMD_STR_LEN = 5,
                IO_ARG_STR_LEN = 5,
                STR_ARG_LEN = 15
             } OpCodeArrayCapacity;

typedef enum { NEW_STATE,
               READY_STATE,
               RUNNING_STATE,
               BLOCKED_STATE,
               EXIT_STATE
             } ProcessState;


#endif