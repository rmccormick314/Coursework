#ifndef PROCESS_H
#define PROCESS_H

// Include files
#include "StandardConstants.h"
#include "configops.h"
#include "metadataops.h"
#include "SimTimer.h"
#include "datatypes.h"

// ==== Constants ====

typedef enum { IO_BOUND, PROCESS_BOUND } OperationType;

typedef enum { PROCESS,
               STATE_CHANGE,
               OPERATION_START,
               OPERATION_END,
               SIMULATOR_START,
               SIMULATOR_END,
               SYSTEM_STOP } OutputStringType;

// ==== Structs ====

typedef struct ProcessBlockType
{
    int processID;                           // Unique ID for process
    ProcessState state;                      // Current state of the process
    int timeRemaining;                       // Total time process takes to
                                             // complete

    struct ProcessBlockType *nextProcess;    // Next node/process
} ProcessBlockType;

typedef struct FileOutputType
{
    char outputString[STD_STR_LEN];          // String to output to file

    struct FileOutputType *nextString;       // Next node in linked list
} FileOutputType;

// ==== Function Prototypes ====

/*
 Name: addFileOutputNode
 Process: Adds node to file output linked list containing one string
 Function Input/Parameters: String to add to LL (char[STD_STR_LEN]),
                            local pointer (FileOutputType*)
 Function Output/Parameters: None
 Function Output/Returned: None
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: copyString
*/
FileOutputType* addFileOutputNode(char inputString[STD_STR_LEN],
                                                     FileOutputType* localPtr);

/*
 Name: addProcessControlBlock
 Process: Creates a Process Control Block and adds it to the Process Control
          Block Linked List
 Function Input/Parameters: Entire time for a process to complete in ms (int),
                            Process ID (int), current available node in process
                            block linked list (ProcessBlockType *)
 Function Output/Parameters: None
 Function Output/Returned: None
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: malloc
*/
ProcessBlockType* addProcessControlBlock(int processTime, int processID,
                                                   ProcessBlockType* localPtr);

/*
 Name: changeProcessState
 Process: Switches the state in which the current process is in
 Function Input/Parameters: Old state (ProcessState),
                            Current PCB (ProcessBlockType *)
 Function Output/Parameters: None
 Function Output/Returned: None
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: None
*/
void changeProcessState(ProcessState oldState, ProcessBlockType* inputPCB);

/*
 Name: clearFileOutputLL
 Process: Traverses linked list of file output nodes and frees the dynamically
                    allocated memory
 Function Input/Parameters: Local pointer to file output linked list header
                            pointer (FileOutputType*)
 Function Output/Parameters: None
 Function Output/Returned: None
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: getOpType
*/
FileOutputType* clearFileOutputLL(FileOutputType* localPtr);

/*
 Name: clearPCBLinkedList
 Process: Traverses linked list of Process Control Block nodes and frees the
                    dynamically allocated memory
 Function Input/Parameters: Linked List head pointer (ProcessBlockType *)
 Function Output/Parameters: None
 Function Output/Returned: None
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: free
*/
ProcessBlockType* clearPCBLinkedList(ProcessBlockType* localPtr);

/*
 Name: createOperationOutput
 Process: Takes input code specifying what type of formatted string is wanted.
          Then creates the string format and finally, prints the string to the
          screen or adds the string to a linked list for file output,
          or both. If input code is PROCESS, the type of string is then
          decided if the operation is "app start" or "app end"
 Function Input/Parameters: Output destination (Monitor, file or both)
                            (ConfigDataCodes), process control block
                            (ProcessBlockType), current op code block
                            (OpCodeType), working pointer to file output linked
                            list (FileOutputType **), command code specifying
                            output message type (OutputStringType)
 Function Output/Parameters: None
 Function Output/Returned: None
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: accessTimer, sprintf, setStartEndString, setInputOutputString,
               printf, addFileOutputNode
*/
void createOperationOutput(ConfigDataCodes outputDestination,
                           ProcessBlockType currentPCB,
                           OpCodeType* currentOpCode,
                           FileOutputType** fileStringHdPtr,
                           OutputStringType stringOutputType);

/*
 Name: createPCBLinkedList
 Process: Creates a linked list of Process Control Blocks. One for each
          process in the metadata file
 Function Input/Parameters: Pointer to metadata linked list (OpCodeType *),
                         Header pointer to PCB Linked List (ProcessBlockType *),
                         config data struct holding all program specifications
                         (ConfigDataType)
 Function Output/Parameters: None
 Function Output/Returned: None
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: addProcessControlBlock, getOperationWaitTime, compareString
*/
ProcessBlockType* createPCBLinkedList(OpCodeType* metadataPtr,
                 ProcessBlockType* ProcessBlockPtr, ConfigDataType configData);

/*
 Name: dumpFileOutput
 Process: Writes the file output string to file along with creating and writing
          the log files header and footer
 Function Input/Parameters: File name (char*), working pointer to
                            file output linked list (FileOutputType *), config
                            struct holding all program specifications
                            (ConfigDataType)
 Function Output/Parameters: None
 Function Output/Returned: None
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: configCodeToString, fopen, fclose, fputs, sprintf
*/
void dumpFileOutput(char* fileName, FileOutputType* wkgFileStringPtr,
                    ConfigDataType configData);

/*
 Name: getOperationWaitTime
 Process: Calculates how much wait time an op code will require. Decides
          if the op code is I/O or processing bound and adapt
 Function Input/Parameters: Config data block (ConfigDataType), metadata block
                            (OpCodeType)
 Function Output/Parameters: None
 Function Output/Returned: Waiting time in ms for operation to finish (int)
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: getOpType
*/
int getOperationWaitTime(ConfigDataType configData, OpCodeType opCodeBlock);

/*
 Name: getOpType
 Process: Decides if the input op code is I/O or processing bound. And if it's
          I/O bound, returns if it's input or output
 Function Input/Parameters: Operation code to be tested (char *)
 Function Output/Parameters: None
 Function Output/Returned: Result if input operation code is processing,
                           I/O input or I/O output
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: compareString
*/
OperationType getOpType(char* opCode);

/*
 Name: setInputOutputString
 Process: If an operation is IO bound, decides if it's input or output
          and turns it into a string
 Function Input/Parameters: Operation code in/out (char*)
 Function Output/Parameters: None
 Function Output/Returned: String saying "input" or "output" (char*)
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: getOpType
*/
char* setInputOutputString(const char* inOutArg);

/*
 Name: setStartEndString
 Process: Decides if an operation is starting or ending and turns it
          into a string
 Function Input/Parameters: Operation code for start or end (OutputStringType)
 Function Output/Parameters: None
 Function Output/Returned: String saying "start" or "end" (char*)
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: getOpType
*/
char* setStartEndString(OutputStringType outputType);

#endif // PROCESS_H
