// Luke Frazer
// Used educational coding vidoes from Michael Leverington for this assignment

// protect from multiple compiling
#ifndef DATA_TYPES_H
#define DATA_TYPES_H

// header files
#include "OS_SimDriver.h"
#include "StandardConstants.h"

// GLOBAL CONSTANTS - may be used in other files

typedef enum {
    CMD_STR_LEN = 5, 
    IO_ARG_STR_LEN = 5, 
    STR_ARG_LEN = 15
    } OpCodeArrayCapacity;

// five state data structure for processes
typedef enum {
    NEW_STATE,
    READY_STATE,
    RUNNING_STATE,
    BLOCKED_STATE,
    EXIT_STATE
    } ProcessState;

    // command line structure for storing command line switch settings
typedef struct CmdLineDataStruct 
{
    bool programRunFlag;
    bool configDisplayFlag;
    bool mdDisplayFlag;
    bool runSimFlag;

    char fileName[STD_STR_LEN];
} CmdLineData;

// config data structure
typedef struct ConfigDataType
   {
    double version;
    char metaDataFileName[ LARGE_STR_LEN ]; 
    int cpuSchedCode;
    int quantumCycles;
    bool memDisplay;
    int memAvailable;
    int procCycleRate;
    int ioCycleRate;
    int logToCode;
    char logToFileName[ LARGE_STR_LEN ];
   } ConfigDataType;

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


#endif // DATA TYPES