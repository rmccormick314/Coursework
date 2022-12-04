// DEFINE IF NOT ALREADY DEFINED -------------------------------------------->>>
#ifndef SIMULATOR_H
#define SIMULATOR_H

// HEADER FILES ------------------------------------------------------------->>>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "datatypes.h"
#include "StringUtils.h"
#include "metadataops.h"
#include "simtimer.h"

// SIMULATOR DATA STRUCTURES ------------------------------------------------>>>
// Process Control Block struct
typedef struct PCBDataTypeStruct
   {
      int PID;                                // PCB/Process ID number
      ProcessState currentState;              // Process state
      char currentStateString[ STD_STR_LEN ]; // State of PCB as string

      int totalRunTime;                       // Total time process will take
      int timeRemaining;                      // Time remaining on process

      OpCodeType* startingCommand;            // First command to run
      OpCodeType* nextCommand;                // Next command to run

      bool waitingOnInterrupt;                // Is this PCB waiting for thread

      struct PCBDataTypeStruct* nextNode;     // next PCB block
   } PCBDataType;

// Memory node data struct
typedef struct MemTableEntryTypeStruct
   {
      int ProcessHolder;                         // Owner of mem node
      int memorySize;                            // Size of memory in node

      int logicalAddressStart;
      int logicalAddressEnd;

      int physicalAddressStart;
      int physicalAddressEnd;

      struct MemTableEntryTypeStruct* nextNode;  // Next node in list
   } MemTableEntryType;

// Interrupt controller data struct
typedef struct InterruptControllerStruct
   {
      bool processesWaiting [ 256 ];     // Processes with threads running
      bool processesComplete [ 256 ];    // Processes with threads completed
      char processOps[ 256 ][ 64 ];    // Commands being run for each process
      char processIOArgs[256][64];
   } InterruptController;

// Interrupt argument struct for threads
typedef struct InterruptArgStruct
   {
      int PID;
      int runTime;
      char operation[ STD_STR_LEN ];
      char ioarg[ IO_ARG_STR_LEN ];
   } InterruptArgType;

// Scheduling codes
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

// FUNCTION PROTOTYPES ------------------------------------------------------>>>
/*
Name:                       accessMemory
Process:                    Attempts to access a stored memory location
Function Input/Parameters:  Head of memory list (MemTableEntryType *),
                            Process holding the memory (int),
                            Start of memory location to access (int),
                            Offset of memory to access (int)
Function Output/Parameters: None
Function Output/Returned:   Success code; 0=success, 2=seg fault (int)
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               None
*/
int accessMemory( MemTableEntryType *memHead, int processHolder,
                  int memStart, int offset );

/*
Name:                       addLogNode
Process:                    Recursively adds a log line to a list of logs
Function Input/Parameters:  Head node for linked list (LogDataType *),
                            Pointer to new log node to add (LogDataType *)
Function Output/Parameters: Updated log node List Head Pointer (LogDataType *)
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               addLogNode, copyString, malloc, printf
*/
LogNodeType *addLogNode( LogNodeType *localPtr,
                         LogNodeType *newNode );

/*
Name:                       addMemNode
Process:                    Recursively adds a memory node to a list of mem
Function Input/Parameters:  Head node for linked list (MemTableEntryType *),
                            Pointer to new mem node to add (MemTableEntryType *)
Function Output/Parameters: Updated mem List Head Pointer (MemTableEntryType *)
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               addMemNode, malloc
*/
MemTableEntryType *addMemNode( MemTableEntryType *localPtr,
                               MemTableEntryType *newNode );

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
Name:                       allocateMemory
Process:                    Attempts to allocate memory for a process at the
                            desired location, with the desired size.
Function Input/Parameters:  Head of memory linked list (MemTableEntryType *),
                            Logical start of desired memory (int),
                            Logical end of desired memory (int),
                            Head of log node linked list (logListHead *),
                            Amount of memory available to sim (int),
                            Process making the allocation request (int)
Function Output/Parameters: Allocation succes code (int)
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               addMemNode, free, malloc
*/
int allocateMemory( MemTableEntryType *memHead, int logStart, int logEnd,
                    LogNodeType *logListHead, int memAvailable,
                    int ProcessHolder );

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
Function Output/Parameters: Process Schedule (ProcessScheduleType *)
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               addPCBNode, changePCBstate, clearPCBList, copyString
*/
PCBDataType *buildSchedule( PCBDataType *PCBlistHead,
                           int scheduleCode, char *timer,
                           LogNodeType *logListHead );

/*
Name:                       changePCBstate
Process:                    Takes in a PCB and state, changes the PCB to the
                            new state, and logs the result.
Function Input/Parameters:  Pointer to PCB (PCBDataType *),
                            Process state to change to (ProcessState),
                            System Timer pointer (char *),
                            Head of system log list (LogNodeType *),
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
                     LogNodeType *logListHead );

/*
Name:                       checkForInterrupt
Process:                    Checks system interrupt controller to see if there
                            is a thread waiting.
Function Input/Parameters:  None
Function Output/Parameters: None
Function Output/Returned:   Interrupt waiting value (bool)
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               None
*/
bool checkForInterrupt( void );

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
Name:                       clearProcessMemory
Process:                    Clears all memory for a given process
Function Input/Parameters:  PCB to clear the memory for (PCBDataType *),
                            Head of memory linked list (MemTableEntryType *)
Function Output/Parameters: None
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               free
*/
void *clearProcessMemory( PCBDataType *PCBpointer,
                          MemTableEntryType *memHead );

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
Name:                       getInterruptPID
Process:                    Gets the PID of the block calling an interrupt
Function Input/Parameters:  None
Function Output/Parameters: None
Function Output/Returned:   PID number of calling block (int)
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               None
*/
int getInterruptPID( void );

/*
Name:                       initializeMemory
Process:                    Initializes the first node in sys memory linked list
Function Input/Parameters:  Memory node to log (memNode *),
                            Head of system log list (logListHead *),
                            Amount of available memory (int),
Function Output/Parameters: None
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               addLogNode, copyString, free, malloc, sprintf
*/
MemTableEntryType *initializeMemory( MemTableEntryType *memHead,
                                     LogNodeType *logListHead,
                                     int memAvailable );

/*
Name:                       logMemoryEntry
Process:                    Logs a given memory table entry
Function Input/Parameters:  Memory node to log (memNode *),
                            Head of system log list (logListHead *),
Function Output/Parameters: None
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               addLogNode, copyString, free, malloc, sprintf
*/
void logMemoryEntry( MemTableEntryType *memNode,
                     LogNodeType *logListHead );

/*
Name:                       nukeAllMemory
Process:                    Deletes all simulator memory
Function Input/Parameters:  Head of memory linked list (MemTableEntryType *)
Function Output/Parameters: None
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               free, nukeAllMemory
*/
MemTableEntryType *nukeAllMemory( MemTableEntryType *memNode );

/*
Name:                       removePCBNode
Process:                    Deletes a PCB node from a list of PCB nodes
Function Input/Parameters:  Head of PCB linked list (PCBDataType *),
                            PCB node to be deleted (PCBDataType *)
Function Output/Parameters: None
Function Output/Returned:   Exit code (int)
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               free
*/
PCBDataType *removePCBNode(PCBDataType *head, PCBDataType *key);

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
void *runInOutOp( void *IOArgs );

/*
Name:                       runPCB
Process:                    Runs the processes associated with the PCB
Function Input/Parameters:  Pointer to PCB to be run (PCBDataType *),
                            System Timer pointer (char *),
                            Pointer to head of system log list (LogNodeType *),
                            Head of memory list (MemTableEntryType *)
Function Output/Parameters: None
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               accessTimer, addLogNode, changePCBstate,
                            concatenateString, copyString,
                            malloc, runTimer, sprintf
*/
void runPCB( PCBDataType *activePCB, char *timer,
             LogNodeType *logListHead, MemTableEntryType *memHead );

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

/*
Name:                       showMem
Process:                    Displays the system memory
Function Input/Parameters:  Head of memory linked list (MemTableEntryType *),
                            Head of log linked list (LogNodeType *),
                            Message to display with memory (char *)
Function Output/Parameters: None
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               addLogNode, copyString, free, logMemoryEntry,
                            sprintf
*/
void showMem( MemTableEntryType *memHead, LogNodeType *logListHead,
              char *displayMessage );

/*
Name:                       sortSJF
Process:                    Sorts a linked list of PCB nodes into SJF
Function Input/Parameters:  Head node for linked list of process commands
Function Output/Parameters: Head of PCB node list (PCBDataType)
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               swapPCBNode
*/
void sortSJF( PCBDataType *headNode );

/*
Name:                       swapPCBNode
Process:                    Swaps two given PCB nodes in place
Function Input/Parameters:  First node to swap (PCBDataType *),
                            Second node to swap (PCBDataType *)
Function Output/Parameters: None
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               copyString
*/
void swapPCBNode( PCBDataType *nodeOne, PCBDataType *nodeTwo );

#endif // SIMULATOR_H
