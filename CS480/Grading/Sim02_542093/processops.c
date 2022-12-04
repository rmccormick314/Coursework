// Include files
#include "processops.h"

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
                                                      FileOutputType* localPtr)
{
    // Check if localPtr is NULL
    if(localPtr == NULL)
    {
        // Allocate new FileOutputType to localPtr
        localPtr = (FileOutputType *)malloc(sizeof(FileOutputType));

        // Set node string
        copyString(localPtr->outputString, inputString);

        // Set next process to NULL
        localPtr->nextString = NULL;

        // Return localPtr
        return localPtr;
    }

    // Recurse to next node and set to nextString
    localPtr->nextString = addFileOutputNode(inputString, localPtr->nextString);

    // Return localPtr
    return localPtr;
}

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
                                                    ProcessBlockType* localPtr)
{
    // Check if localPtr is NULL
    if(localPtr == NULL)
    {
        // Allocate new ProcessBlockType to localPtr
        localPtr = (ProcessBlockType *)malloc(sizeof(ProcessBlockType));

        // Set processID
        localPtr->processID = processID;

        // Set timeRemaining
        localPtr->timeRemaining = processTime;

        // Set state to NEW
        localPtr->state = NEW_STATE;

        // Set next process to NULL
        localPtr->nextProcess = NULL;

        // Return localPtr
        return localPtr;
    }

    // Recurse to next node and set to nextProcess
    localPtr->nextProcess = addProcessControlBlock(processTime,
                                              processID, localPtr->nextProcess);

    // Return localPtr
    return localPtr;
}

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
void changeProcessState(ProcessState oldState, ProcessBlockType* inputPCB)
{
    // Check if oldState is NEW
    if(oldState == NEW_STATE)
    {
        // Set inputPCB's state to READY
        inputPCB->state = READY_STATE;
    }
    // Otherwise, check is oldState is READY
    else if(oldState == READY_STATE)
    {
        // Set inputPCB's state to RUNNING
        inputPCB->state = RUNNING_STATE;
    }
    // Otherwise, the oldState is RUNNING
    else
    {
        // Set inputPCB's state to EXIT
        inputPCB->state = EXIT_STATE;
    }
}

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
FileOutputType* clearFileOutputLL(FileOutputType* localPtr)
{
    // Check if localPtr is not NULL
    if(localPtr != NULL)
    {
        // Recurse to next node
        clearFileOutputLL(localPtr->nextString);

        // Free current node
            // Function: free
        free(localPtr);

        // Set localPtr to NULL
        localPtr = NULL;
    }

    // Return null
    return NULL;
}

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
ProcessBlockType* clearPCBLinkedList(ProcessBlockType* localPtr)
{
    // Check if localPtr is not NULL
    if(localPtr != NULL)
    {
        // Recurse to next node
        clearPCBLinkedList(localPtr->nextProcess);

        // Free current node
            // Function: free
        free(localPtr);

        // Set localPtr to NULL
        localPtr = NULL;
    }

    // Return null
    return NULL;
}

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
                           OutputStringType stringOutputType)
{
    // Initialize variables

        // Current output string
    char outputString[MAX_STR_LEN];

        // Specification of if OPERATION_* is START or END
    char* operationStartEnd;

        // Current timer value
    char timerString[SMALL_STR_LEN];
    currentOpCode->opEndTime = accessTimer(LAP_TIMER, timerString);

        // ioDirection
    char* ioDirection;

    // Check if outputType is STATE_CHANGE
    if(stringOutputType == STATE_CHANGE)
    {
        // Check if current state is READY
        if(currentPCB.state == READY_STATE)
        {
            // Set output string to format:
            // "<time>, OS: Process <PID> set to <New State> state from
            // <Old State> state\n"
            sprintf(outputString,
                    " %9s, OS: Process %d set to READY state from NEW state\n",
                    timerString, currentPCB.processID);
        }
        // Otherwise, check if current state is EXIT_STATE
        else if(currentPCB.state == EXIT_STATE)
        {
            // Set output string to format:
            // "<time>, OS: Process 0 set to EXIT"
            sprintf(outputString, " %9s, OS: Process %d set to EXIT\n",
                                  timerString, currentPCB.processID);
        }
        // Otherwise, current state is neither EXIT or READY
        else
        {
            // Set output string to:
            // "<time>, OS: Process 0 set from READY to RUNNING"
            sprintf(outputString,
                          " %9s, OS: Process %d set from READY to RUNNING\n\n",
                          timerString, currentPCB.processID);
        }
    }
    // Otherwise, check if outputType is PROCESS
    else if(stringOutputType == PROCESS)
    {
        // Check if process is ending by current state
        if(currentPCB.state == READY_STATE)
        {
            // Set output string to format:
            // "<time>, OS: Process <PID> selected with
            // <time remaining> ms remaining"

            sprintf(outputString,
                  " %9s, OS: Process %d selected with %d ms remaining\n",
                  timerString, currentPCB.processID, currentPCB.timeRemaining);
        }
        // Otherwise, process is starting
        else
        {
            // Set output string to format:
            // "\n<time>, OS: Process <PID> ended"
            sprintf(outputString, "\n %9s, OS: Process %d ended\n",
                                  timerString, currentPCB.processID);
        }
    }
    // Otherwise, check if string type is OPERATION_START or OPERATION_END
    else if(stringOutputType == OPERATION_START ||
                                            stringOutputType == OPERATION_END)
    {
        operationStartEnd = setStartEndString(stringOutputType);

        // Check if operation is IO_BOUND (input or output)
        if(getOpType(currentOpCode->command) == IO_BOUND)
        {
            ioDirection = setInputOutputString(currentOpCode->inOutArg);

            // Set output string to format:
            // "\n<time>, Process: <PID>, <first argument> <input/output>
            // operation <start/end>\n"
            sprintf(outputString, " %9s, Process: %d, %s %s operation %s\n",
                    timerString, currentPCB.processID, currentOpCode->strArg1,
                    ioDirection, operationStartEnd);
        }
        // Otherwise, operation is PROCESS_BOUND
        else
        {
            // Set output string to format:
            // "<time>, Process: <PID>, hard drive input operation <start/end>"
            sprintf(outputString,
                    " %9s, Process: %d, cpu process operation %s\n",
                    timerString, currentPCB.processID, operationStartEnd);
        }
    }
    // Otherwise, check if control code is SIMULATOR_START
    else if(stringOutputType == SIMULATOR_START)
    {
        // Set string of format: "<time>, OS: Simulator start"
        sprintf(outputString, " %9s, OS: Simulator start\n", timerString);
    }
    // Otherwise, check if control code is SIMULATOR_END
    else if(stringOutputType == SIMULATOR_END)
    {
        // Set string of format: "<time>, OS: Simulator end"
        sprintf(outputString, " %9s, OS: Simulation end\n", timerString);
    }
    // Otherwise, check if control code is SYSTEM_STOP
    else
    {
        // Set string of format: "<time>, OS: System stop"
        sprintf(outputString, " %9s, OS: System stop\n", timerString);
    }

    // Check if outputMethod is Monitor or Both
    if(outputDestination == LOGTO_MONITOR_CODE ||
                                          outputDestination == LOGTO_BOTH_CODE)
    {
        // Print output string
        printf(outputString);
    }

    // Check if outputMethod is File or Both
    if(outputDestination == LOGTO_FILE_CODE ||
                                          outputDestination == LOGTO_BOTH_CODE)
    {
        // Add string to file output linked list
        *fileStringHdPtr = addFileOutputNode(outputString, *fileStringHdPtr);
    }
}

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
                 ProcessBlockType* ProcessBlockPtr, ConfigDataType configData)
{
    // Initialize variables
        // Process ID
        // Process time
    int processID = 0, processTime, processWaitTime;

        // Metadata working pointer
    OpCodeType* metadataWkgPtr = metadataPtr;

    // Loop to the end of metadata linked list and excluding sys end
    while(metadataWkgPtr->nextNode != NULL)
    {
        // Check if current operation is "app"
            // Reset process time
        if(compareString(metadataWkgPtr->command, "app") == STR_EQ)
        {
            if(compareString(metadataWkgPtr->strArg1, "start") == STR_EQ)
            {
                // Reset process time
                processTime = 0;
            }

            // Otherwise, check if current op code and first arg is "app end"
            else if(compareString(metadataWkgPtr->strArg1, "end") == STR_EQ)
            {
                // Add process control block
                    // Function: addProcessControlBlock
                ProcessBlockPtr = addProcessControlBlock(processTime,
                                                   processID, ProcessBlockPtr);

                // Increment process ID for next process
                processID++;
            }
        }
        // Otherwise, program is in the middle of a process
        else
        {
            // Get wait time for current process and add to current total
                // Function: getOperationWaitTime
            processWaitTime = getOperationWaitTime(configData, *metadataWkgPtr);

            processTime += processWaitTime;
        }

        // Increment to next node in metadata
        metadataWkgPtr = metadataWkgPtr->nextNode;
    }

    // End loop

    // Return head pointer
    return ProcessBlockPtr;
}

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
 Dependencies: configCodeToString, fopen, fclose, fprintf
*/
void dumpFileOutput(char* fileName, FileOutputType* wkgFileStringPtr,
                    ConfigDataType configData)
{
    // Initialize variables

        // "write" constant for fopen
    const char WRITE_ONLY_FLAG[] = "w";

    char configSchedStr[SMALL_STR_LEN];

        // File access pointer
    FILE *fileAccessPtr;

    // Open specified file
        // Function: fopen
    fileAccessPtr = fopen(fileName, WRITE_ONLY_FLAG);

        // Check if successful
    if(fileAccessPtr != NULL)
    {
        // Set all strings of config data that isn't a string to be added to
        // file header
            // Functions: configCodeToString
        configCodeToString(configData.cpuSchedCode, configSchedStr);

        // Output file header giving important config information
            // Function: fprintf
        fprintf(fileAccessPtr,
                     "\n==================================================\n");
        fprintf(fileAccessPtr, "Simulator Log File Header\n\n");

        fprintf(fileAccessPtr,
                              "File Name                       : %s",
                                          configData.metaDataFileName);
        
        fprintf(fileAccessPtr,
                              "\nCPU Scheduling                  : %s",
                                                       configSchedStr);

        fprintf(fileAccessPtr,
                              "\nQuantum Cycles                  : %d",
                                             configData.quantumCycles);

        fprintf(fileAccessPtr,
                              "\nMemory Available (KB)           : %d",
                                              configData.memAvailable);

        fprintf(fileAccessPtr,
                              "\nProcessor Cycle Rate (ms/cycle) : %d",
                                             configData.procCycleRate);

        fprintf(fileAccessPtr,
                              "\nI/O Cycle Rate (ms/cycle)       : %d",
                                                configData.ioCycleRate);

        fprintf(fileAccessPtr, "\n\n================");
        fprintf(fileAccessPtr, "\nBegin Simulation\n\n");

        // Loop through entire file output linked list
        while(wkgFileStringPtr != NULL)
        {
            // Add current string to file
                // Function: fputs
            fputs(wkgFileStringPtr->outputString, fileAccessPtr);

            wkgFileStringPtr = wkgFileStringPtr->nextString;
        }

        fputs("\nEnd Simulation - Complete\n", fileAccessPtr);
        fputs("=========================", fileAccessPtr);

        // Close file
            // Function: fclose
        fclose(fileAccessPtr);
    }
}

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
int getOperationWaitTime(ConfigDataType configData, OpCodeType opCodeBlock)
{
    // Initialize variables
        // Wait time total
    int waitTime = 0;

    // Check if operation is process bound
        // Function: getOpType
    if(getOpType(opCodeBlock.command) == PROCESS_BOUND)
    {
        // Add to wait time total with the formula:
        // <cpu cycles> * <time per processing cycle>
        waitTime = configData.procCycleRate * opCodeBlock.intArg2;
    }
    // Otherise, operation is IO bound
        // Function: getOpType
    else
    {
        // Add to wait time total with the formula:
        // <cpu cycles> * <time per IO cycle>
        waitTime = configData.ioCycleRate * opCodeBlock.intArg2;
    }
    // Return total wait time
    return waitTime;
}

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
OperationType getOpType(char* opCode)
{
    // Check if the current operation code is processing
        // Function: findSubString
    if(compareString(opCode, "cpu") == STR_EQ)
    {
        // Return PROCESS_BOUND
        return PROCESS_BOUND;
    }
    // Otherwise, operation is IO
    else
    {
        // Return IO_BOUND_INPUT
        return IO_BOUND;
    }
}

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
char* setInputOutputString(const char* inOutArg)
{
    // Initialize variables
        // Input string
    char* inputString = "input";

        // Output string
    char* outputString = "output";

    // Check if inOutArg is "in"
        // Function: compareString
    if(compareString(inOutArg, "in") == STR_EQ)
    {
        // Return "input"
        return inputString;
    }
    // Otherwise, inOutArg is "out"
    else
    {
        // Return "output"
        return outputString;
    }
}

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
char* setStartEndString(OutputStringType outputType)
{
    // Initialize variables
        // Start string
    char* startString = "start";

        // End string
    char* endString = "end";

    // Check if outputType is OPERATION_START
    if(outputType == OPERATION_START)
    {
        // Return "start"
        return startString;
    }
    // Otherwise, outputType is OPERATION_END
    else
    {
        // Return "end"
        return endString;
    }
}
