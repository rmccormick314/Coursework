#include "simulator.h"

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
void runSim(ConfigDataType *configPtr, OpCodeType *metaDataMstrPtr)
{
    // Initialize data
        // Pointers to linked lists and working
    ProcessBlockType* headPtrPCB = NULL;
    ProcessBlockType* wkgPCBPtr = NULL;
    FileOutputType* fileHeadPtr = NULL;
    OpCodeType* metaWkgPtr = metaDataMstrPtr;

        // wait time
    int waitTime;

        // Thread variable
    pthread_t thread_id;

        // Log code
    int logToCodeValue = configPtr->logToCode;

    // Start simulator and set working PCB pointer to head of PCB linked list
        // Function: startSimulator
    startSimulator(logToCodeValue, &fileHeadPtr, metaWkgPtr, *configPtr,
                                    &headPtrPCB, metaDataMstrPtr);

    wkgPCBPtr = headPtrPCB;

    // Loop through all metadata until NULL
    while(metaWkgPtr != NULL)
    {
        // Check if current operation is either "app start" or "app end"
        if(compareString(metaWkgPtr->command, "app") == STR_EQ)
        {
            // Print string for either "app start" or "app end" for
            // PROCESS control code
            createOperationOutput(logToCodeValue, *wkgPCBPtr, metaWkgPtr,
                                                        &fileHeadPtr, PROCESS);

            // Change state of PCB from either NEW_STATE or RUNNING_STATE
            changeProcessState(wkgPCBPtr->state, wkgPCBPtr);

            // Print string for state change with code STATE_CHANGE
            createOperationOutput(logToCodeValue, *wkgPCBPtr, metaWkgPtr,
                                                   &fileHeadPtr, STATE_CHANGE);

            // Check if current operation is "app end"
            if(compareString(metaWkgPtr->strArg1, "end") == STR_EQ)
            {
                // Increment to next Process Control Block
                wkgPCBPtr = wkgPCBPtr->nextProcess;
            }
        }
        // Otherwise, check if current operation is in middle of process
        else if(compareString(metaWkgPtr->command, "sys") != STR_EQ)
        {
            // Get operation wait time
            waitTime = getOperationWaitTime(*configPtr, *metaWkgPtr);

            // Display string for start of operation with OPERATION_START code
            createOperationOutput(logToCodeValue, *wkgPCBPtr, metaWkgPtr,
                                                &fileHeadPtr, OPERATION_START);

            // Wait for specified amount of time in separate thread
            pthread_create(&thread_id, NULL, *runTimer, (void *)&waitTime);
            pthread_join(thread_id, NULL);

            // Display string for end of operation through OPERATION_END code
            createOperationOutput(logToCodeValue, *wkgPCBPtr, metaWkgPtr,
                                                  &fileHeadPtr, OPERATION_END);
        }
        // Otherwise check if current operation is system start/end
        else
        {
            // Check if operation is system start
            if(compareString(metaWkgPtr->strArg1, "start") == STR_EQ)
            {
                // Initialize all Process Block States to READY_STATE state
                // from NEW_STATE
                while(wkgPCBPtr != NULL)
                {
                    changeProcessState(NEW_STATE, wkgPCBPtr);

                    // Display state change to READY
                        // Function: createOperationOutput
                    createOperationOutput(logToCodeValue, *wkgPCBPtr,
                                      metaWkgPtr, &fileHeadPtr, STATE_CHANGE);

                    // Increment PCB linked list working pointer
                    wkgPCBPtr = wkgPCBPtr->nextProcess;
                }

                // Reset working pointer for Process Control Block Linked List
                wkgPCBPtr = headPtrPCB;
            }
            // Otherwise, operation is system end
            else
            {
                // Print end messages, dump strings to file if needed and free
                // linked lists
                endSimulator(&headPtrPCB, &fileHeadPtr, *configPtr);
            }
        }

        // Increment metadata pointer
        metaWkgPtr = metaWkgPtr->nextNode;
    }
    // End master loop
}

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
                   ProcessBlockType** headPtrPCB, OpCodeType* metaDataMstrPtr)
{
    // Initialize variables

        // Dummy variable for PCB
    ProcessBlockType* dummyPCB =
                          (ProcessBlockType *)malloc(sizeof(ProcessBlockType));

    // Display simulator run message
    printf("Simulator Run\n");
    printf("-------------\n\n");

    // Create Process Control Block linked list
    *headPtrPCB = createPCBLinkedList(metaDataMstrPtr, *headPtrPCB, configPtr);

    // Print simulator start message
    createOperationOutput(logToCodeValue, *dummyPCB, metaWkgPtr,
                                               fileHeadPtr, SIMULATOR_START);

    // Check if specified print location is File
    if(logToCodeValue == LOGTO_FILE_CODE)
    {
        // Print message stating the program is running
        printf("Simulator running output to file\n\n");
    }

    // Free dummy node
    free(dummyPCB);
}

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
                   ConfigDataType configPtr)
{
    // Initialize variables
    OpCodeType* dummyMetaPtr = (OpCodeType *)malloc(sizeof(OpCodeType));

    char timerString[SMALL_STR_LEN];

    FileOutputType* fileOutputWkgPtr = *fileHeadPtr;

    // Print end of simulation messages
        // Function: createOperationOutput
    createOperationOutput(configPtr.logToCode, **headPtrPCB, dummyMetaPtr,
                                                fileHeadPtr, SYSTEM_STOP);

    createOperationOutput(configPtr.logToCode, **headPtrPCB, dummyMetaPtr,
                                                fileHeadPtr, SIMULATOR_END);

    // Set timer value
        // Function: accessTimer
    accessTimer(STOP_TIMER, timerString);

    // Check if specified to dump to a file
    if(configPtr.logToCode == LOGTO_FILE_CODE ||
                                        configPtr.logToCode == LOGTO_BOTH_CODE)
    {
        // Dump file output string into file
            // Function: dumpFileOutput
        dumpFileOutput(configPtr.logToFileName, fileOutputWkgPtr, configPtr);
    }

    // Free all linked lists and allocated memory
        // Functions: clearPCBLinkedList, clearFileOutputLL, free
    clearPCBLinkedList(*headPtrPCB);
    clearFileOutputLL(*fileHeadPtr);
    free(dummyMetaPtr);
}
