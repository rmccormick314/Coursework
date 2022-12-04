// Protect from multiple compilations
#ifndef SIMULATOR_H
#define SIMULATOR_H

// Header files
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "datatypes.h"
#include "StringUtils.h"
#include "metadataops.h"
#include "simtimer.h"

// Simulator data structures
typedef struct PCBDataTypeStruct // Process Control Block data struct
   {
      int PID;                    // PCB/Process ID number
      ProcessState currentState;  // Process state
      char currentStateString[ STD_STR_LEN ];

      int totalRunTime;           // Total time process will take
      int timeRemaining;

      OpCodeType* startingCommand;     // Next command to run
      OpCodeType* nextCommand;

      struct PCBDataTypeStruct* nextNode;     // next PCB block
   } PCBDataType;

typedef struct PCBNodeTypeStruct
   {
      PCBDataType* PCB;
      struct PCBNodeTypeStruct* nextNode;
   } PCBNodeType;

typedef struct MemTableEntryTypeStruct
   {
      int ProcessHolder;
      int MemStartLocation;
      int MemSize;
   } MemTableEntryType;

typedef enum
   {
      SJF_N_CODE,
      SRTF_P_CODE,
      FCFS_P_CODE,
      RR_P_CODE,
      FCFS_N_CODE,
   } ScheduleCode;

// Logging data structures
typedef struct LogNodeTypeStruct
  {
     char logText[ 256 ];
     struct LogNodeTypeStruct* nextNode;
  } LogNodeType;

// Function prototypes
/*
Name:                       addLogNode
Process:                    Recursively adds a log line to a list of logs
Function Input/Parameters:  Head node for linked list (LogDataType *)
Function Output/Parameters: Log node List Head Pointer (LogDataType *),
                            Pointer to new log node to add (LogDataType *),
                            Log-to code (int)
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               addLogNode, copyString, malloc, printf
*/
LogNodeType *addLogNode( LogNodeType *localPtr,
                         LogNodeType *newNode,
                         int logToCode );

/*
Name:                       addPCBNode
Process:                    Recursively adds a PCB to a list of PCB
Function Input/Parameters:  Head node for linked list (PCBDataType *),
                            New PCB Node to add (PCBDataType *)
Function Output/Parameters: PCB Pointer to list head (PCBDataType *)
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               addPCBNode, malloc
*/
PCBDataType *addPCBNode( PCBDataType *localPtr, PCBDataType *newNode );

/*
Name:                       buildPCB
Process:                    Builds a PCB from head node of operations
Function Input/Parameters:  Head node for linked list of process commands
                            (OpCodeType *),
                            CPU Cycle Time (int),
                            IO Cycle Time (int),
                            System timer pointer (char *)
Function Output/Parameters: Pointer to new PCB (PCBDataType *)
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               clearMetaDataList, compareString, malloc, sizeof
*/
PCBDataType *buildPCB( OpCodeType *processDataHead,
                       int CPUcycleRate,
                       int ioCycleRate,
                       char *timer );

/*
Name:                       buildSchedule
Process:                    Takes in a list of Process Control Blocks and builds
                            a schedule.
Function Input/Parameters:  PCB linked list header node (PCBNodeType *),
                            Schedule Config Data (ConfigDataType),
                            Timer Pointer (char *),
                            Log list head (LogNodeType *),
                            Log-to config code (int)
Function Output/Parameters: Process Schedule (ProcessScheduleType *)
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               addPCBNode, changePCBstate, clearPCBList, copyString
*/
PCBDataType *buildSchedule( PCBDataType *PCBlistHead,
                           int scheduleCode, char *timer,
                           LogNodeType *logListHead, int logToCode );

/*
Name:                       changePCBstate
Process:                    Takes in a PCB and state, changes the PCB to the
                            new state, and logs the result.
Function Input/Parameters:  Pointer to PCB (PCBDataType *),
                            Process state to change to (ProcessState),
                            System Timer pointer (char *),
                            Head of system log list (LogNodeType *),
                            Log-to config code (int)
Function Output/Parameters: None
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               accessTimer, addLogNode, concatenateString,
                            copyString, intToCharArray, malloc
*/
void changePCBstate( PCBDataType *PCBpointer,
                     ProcessState newState,
                     char *timer,
                     LogNodeType *logListHead,
                     int logToCode );

/*
Name:                       clearPCBList
Process:                    Clears a linked list of PCB nodes recursively
Function Input/Parameters:  PCB list head pointer (PCBNodeType *)
Function Output/Parameters: None
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               clearPCBList, free
*/
PCBDataType *clearPCBList( PCBDataType *localPtr );

/*
Name:                       clearLogList
Process:                    Clears a linked list of log nodes recursively
Function Input/Parameters:  Log list head pointer (LogNodeType *)
Function Output/Parameters: None
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               clearLogList, free
*/
LogNodeType *clearLogList( LogNodeType *localPtr );

/*
Name:                       dumpLogs
Process:                    Dumps all logs to a given file
Function Input/Parameters:  Head of linked list of log entries (LogNodeType *),
                            Name of log file (char *)
Function Output/Parameters: None
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               fclose, fopen, fprintf
*/
void dumpLogs( LogNodeType *logListHead, char *logFileName );

/*
Name:                       runInOutOp
Process:                    Function for running I/O op as seperate thread
Function Input/Parameters:  Time to run I/O thread for (int)
Function Output/Parameters: None
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               runTimer
*/
void *runInOutOp( void *runTime );

/*
Name:                       runPCB
Process:                    Runs the processes associated with the PCB
Function Input/Parameters:  Pointer to PCB to be run (PCBDataType *),
                            System Timer pointer (char *),
                            Pointer to head of system log list (LogNodeType *),
                            Log-to config code (int)
Function Output/Parameters: None
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               accessTimer, addLogNode, changePCBstate,
                            concatenateString, copyString,
                            malloc, runTimer, sprintf
*/
void runPCB( PCBDataType *activePCB, char *timer,
             LogNodeType *logListHead, int logToCode );

/*
Name:                       runSim
Process:                    Primary simulation driver.
Function Input/Parameters:  Configuration data (ConfigDataType *),
                            Metadata (OpCodeType *)
Function Output/Parameters: None
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               accessTimer, addLogNode, addNode, addPCBNode,
                            buildPCB, buildSchedule, compareString,
                            concatenateString, copyString, dumpLogs,
                            malloc, printf
*/
void runSim( ConfigDataType *configPtr,
             OpCodeType *metaDataMstrPtr );

#endif // SIMULATOR_H
