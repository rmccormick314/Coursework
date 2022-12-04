#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <stdio.h>
#include <stdbool.h>
#include "StandardConstants.h"

// GLOBAL CONSTANTS - May be used in other files
typedef enum { CMD_STR_LEN = 4,
               IO_ARG_STR_LEN = 4,
               STR_ARG_LEN = 13 } OpCodeArrayCapacity;

    // Five state data structure for processes
typedef enum { NEW_STATE,
               READY_STATE,
               RUNNING_STATE,
               BLOCKED_STATE,
               EXIT_STATE } ProcessState;

    // Config message codes
typedef enum { CFG_FILE_ACCESS_ERR,
               CFG_CORRUPT_DESCRIPTOR_ERR,
               CFG_DATA_OUT_OF_RANGE_ERR,
               CFG_CORRUPT_PROMPT_ERR,
               CFG_VERSION_CODE,
               CFG_MD_FILE_NAME_CODE,
               CFG_CPU_SCHED_CODE,
               CFG_QUANT_CYCLES_CODE,
               CFG_MEM_DISPLAY_CODE,
               CFG_MEM_AVAILABLE_CODE,
               CFG_PROC_CYCLES_CODE,
               CFG_IO_CYCLES_CODE,
               CFG_LOG_TO_CODE,
               CFG_LOG_FILE_NAME_CODE } ConfigCodeMessages;

    // Config data codes
typedef enum { CPU_SCHED_SJF_N_CODE,
               CPU_SCHED_SRTF_P_CODE,
               CPU_SCHED_FCFS_P_CODE,
               CPU_SCHED_RR_P_CODE,
               CPU_SCHED_FCFS_N_CODE,
               LOGTO_MONITOR_CODE,
               LOGTO_FILE_CODE,
               LOGTO_BOTH_CODE,
               NON_PREEMPTIVE_CODE,
               PREEMPTIVE_CODE } ConfigDataCodes;

#endif // DATA_TYPES_H
