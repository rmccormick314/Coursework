#ifndef SIMULATOR_H
#define SIMULATOR_H

// Includes
#include <pthread.h>

#include "configops.h"
#include "metadataops.h"
#include "SimTimer.h"
#include "processops.h"

// ==== Function Prototypes ====

/*
 Name: runSim
 Process: Primary simulation driver
 Function Input/Parameters: Configuration data (ConfigDataType *),
                            metadata (OpCodeType *)
 Function Output/Parameters: None
 Function Output/Returned: None
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: startSimulator, compareString, createOperationOutput,
               changeProcessState, getOperationWaitTime, pthread_create,
               pthread_join, endSimulator
*/
void runSim(ConfigDataType *configPtr, OpCodeType *metaDataMstrPtr);

/*
 Name: startSimulator
 Process: Starts simulator by printing start strings and creating a
          process control block linked list
 Function Input/Parameters: log to code value (int), pointer to head pointer to
                            file linked list (FileOutputType**), working pointer
                            of meta data linked list (OpCodeType*), config data
                            (ConfigDataType), pointer to head pointer of PCB
                            linked list (ProcessBlockType**), head pointer to
                            metadata linked list (OpCodeType*)
 Function Output/Parameters: None
 Function Output/Returned: None
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: createPCBLinkedList, createOperationOutput, accessTimer, printf
*/
void startSimulator(int logToCodeValue, FileOutputType** fileHeadPtr,
                   OpCodeType* metaWkgPtr, ConfigDataType configPtr,
                   ProcessBlockType** headPtrPCB, OpCodeType* metaDataMstrPtr);

/*
 Name: endSimultator
 Process: When called, ending messages are shown, file output is dumped if
          specified and linked lists are freed
 Function Input/Parameters: Head pointer to process control block linked list
                            (ProcessBlockType**), head pointer to file output
                            linked list (FileOutputType**), config pointer
                            (ConfigDataType)
 Function Output/Parameters: None
 Function Output/Returned: None
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: createOperationOutput, accessTimer, dumpFileOutput,
               clearPCBLinkedList, clearFileOutputLL
*/
void endSimulator(ProcessBlockType** headPtrPCB, FileOutputType** fileHeadPtr,
                   ConfigDataType configPtr);

#endif // SIMULATOR_H
