// HEADER FILES ------------------------------------------------------------->>>
#include "simulator.h"

// GLOBAL SYSTEM VARIABLES -------------------------------------------------->>>
int logToCode = 0;      // Log to File, Monitor, or Both
bool memDisplay;        // On or off
int memAvailable;       // True false

// may god forgive me for creating this abomination

// FUNCTIONS ---------------------------------------------------------------->>>
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
                  int memStart, int offset )
   {
      // Initialize variables
         // Read head for scanning over the memory nodes
         MemTableEntryType *memReadHead = memHead;

         // Int for holding success code
         int success = 2; // defaults to seg fault error

      // While there is still memory to read
      while( memReadHead != NULL )
      {
         // Check if this mem entry is owned by requester
         if( memReadHead->ProcessHolder == processHolder )
         {
            // If it is, and the memory is within the range we are searching
            if( memReadHead->logicalAddressStart <= memStart &&
                (memStart + offset) <= memReadHead->logicalAddressEnd )
            {
               // Set successful request
               success = 0;
            }
         }
         // Move to next node
         memReadHead = memReadHead->nextNode;
      }
      // Return success code
      return success;
   }

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
                         LogNodeType *newNode )
   {
      // Check for local pointer assigned to null
      if( localPtr == NULL )
         {
            // Access memory for new node
            // Function: malloc
            localPtr = (LogNodeType *)malloc( sizeof( LogNodeType ) + 1 );

            // Assign all three values to newly created node
            // Assign next pointer to null
            copyString( localPtr->logText, newNode->logText );
            //localPtr->nextNode = NULL;

            // If logging to monitor, print output now
            if( logToCode == LOGTO_MONITOR_CODE ||
                logToCode == LOGTO_BOTH_CODE )
            {
               printf("%s", localPtr->logText );
            }

            // Set end of list to null
            localPtr->nextNode = NULL;

            // Return current local pointer
            return localPtr;
         }

      // Assume end of list not found yet
      // Assign recursive function current node's next link
      // Function: addLogNode
      localPtr->nextNode = addLogNode( localPtr->nextNode, newNode );

      // Return current local pointer
      return localPtr;
   }

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
                               MemTableEntryType *newNode )
   {
      // Check for local pointer assigned to null
      if( localPtr == NULL )
         {
         // Access memory for new node
         // Function: malloc
         localPtr = (MemTableEntryType *) \
                                       malloc( sizeof( MemTableEntryType ) + 1);

         // Assign new node values into memory node
         localPtr->ProcessHolder = newNode->ProcessHolder;
         localPtr->memorySize = newNode->memorySize;
         localPtr->logicalAddressStart = newNode->logicalAddressStart;
         localPtr->logicalAddressEnd = newNode->logicalAddressEnd;
         localPtr->physicalAddressStart = newNode->physicalAddressStart;
         localPtr->physicalAddressEnd = newNode->physicalAddressEnd;

         // Next node will be end of list, null
         localPtr->nextNode = NULL;

         // Return current local pointer
         return localPtr;
         }

      // Assume end of list not found yet
      // Assign recursive function current node's next link
      // Function: addPCBNode
      localPtr->nextNode = addMemNode( localPtr->nextNode, newNode );

      // Return current local pointer
      return localPtr;
  }

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
PCBDataType *addPCBNode( PCBDataType *localPtr, PCBDataType *newNode )
   {
      // Check for local pointer assigned to null
      if( localPtr == NULL )
         {
         // Access memory for new node
         // Function: malloc
         localPtr = (PCBDataType *)malloc( sizeof( PCBDataType ) + 1);

         // Assign new node values into PCB node
         localPtr->PID = newNode->PID;
         localPtr->currentState = newNode->currentState;
         localPtr->totalRunTime = newNode->totalRunTime;
         localPtr->timeRemaining = newNode->timeRemaining;
         localPtr->startingCommand = newNode->startingCommand;
         localPtr->nextCommand = newNode->nextCommand;

         // Next node will be end of list, null
         localPtr->nextNode = NULL;

         // Return current local pointer
         return localPtr;
         }

      // Assume end of list not found yet
      // Assign recursive function current node's next link
      // Function: addPCBNode
      localPtr->nextNode = addPCBNode( localPtr->nextNode, newNode );

      // Return current local pointer
      return localPtr;
   }

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
                    int ProcessHolder )
   {
      // Initialize variables
         // Buffer node for logging
         LogNodeType *bufferLogNode = \
                                 (LogNodeType *)malloc( sizeof( LogNodeType ) );

         // Buffer mem node for scanning/working
         MemTableEntryType *bufferMemNode;

         // Success value
         int success = 0; // 0 = success; 1 = logical fail; 2 = physical failure

         // Physical memory start
         int phyStart = 0;
         int memChunkSize = logEnd - logStart;
         int phyEnd = memChunkSize;

      bufferMemNode = memHead;

      if( phyEnd <= memAvailable-1 && logStart >= 0 )
      {
         // While mem node not empty
         while( bufferMemNode->nextNode != NULL )
         {
            phyStart = bufferMemNode->nextNode->physicalAddressEnd+1;
            phyEnd = phyStart + memChunkSize;
            success=0;
            // If node is not in the 'empty space' section
            if( bufferMemNode->ProcessHolder != -1 && phyStart < phyEnd );
            {
               // check that mem doesn't overlap
               if( phyStart > bufferMemNode->nextNode->physicalAddressEnd  &&
                   phyEnd < memAvailable )
               {
                  // check that logi addresses dont overlap in same process
                  if( ProcessHolder == bufferMemNode->nextNode->ProcessHolder )
                  {
                     // Sorry for these terrible statements
                     // Check if logStart or logEnd are within already allocated
                     // memory range
                     if( ((bufferMemNode->nextNode->logicalAddressEnd \
                            > logStart) && (logStart > \
                               bufferMemNode->nextNode->logicalAddressStart)) ||
                         ((bufferMemNode->nextNode->logicalAddressEnd \
                           > logEnd) && (logEnd > \
                             bufferMemNode->nextNode->logicalAddressStart))
                        )
                     {
                        success = 1;
                     }
                     // If they do, return code for this
                     else
                     {
                        success = 0;
                     }
                  } // end check for logic address overlap
               } // end check for physical address overlap
               else
               {
                  // If there is a physical address overlap, return special code
                  success = 2;
               }
            } // end check for unique node with real memory
            // Set physical address start to latest node in list
            //phyStart = bufferMemNode->physicalAddressEnd+1;
            // Move to next node
            bufferMemNode = bufferMemNode->nextNode;
         }
         // At the end, set buffer node to NULL end of list
         bufferMemNode = bufferMemNode->nextNode;
      }

      // If checks pass, make node
      if( success == 0 )
      {
         // Allocate the memory
         MemTableEntryType *newMemNode = \
                          (MemTableEntryType *)malloc( sizeof( LogNodeType ) );

         // Assign new node all values
         newMemNode->logicalAddressStart = logStart;
         newMemNode->logicalAddressEnd = logEnd;
         newMemNode->physicalAddressStart = phyStart;
         newMemNode->physicalAddressEnd = phyEnd;
         newMemNode->ProcessHolder = ProcessHolder;
         newMemNode->memorySize = memChunkSize;
         newMemNode->nextNode = NULL;

         // Add this node to the list
         addMemNode( memHead, newMemNode );

         memHead->physicalAddressStart = phyEnd+1;

         // Free the new node
         free( newMemNode ); // adding to list generates a new one automatically
      }

      // If checks fail, cancel node
      if( success != 0 )
      {
         bufferMemNode = NULL;
         free( bufferMemNode );
      }

      // Free log buffer memory
      free( bufferLogNode );

      // Return success value
      return success;
   }

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
                       char *timer )
   {
      // Initialize variables
         // Create the new PCB to be returned
         PCBDataType *newPCB = (PCBDataType *)malloc( sizeof( PCBDataType ) );

         // Create a variable to store total run time of PCB
         int totalRunTime = 0;

      // Set PCB variables
      newPCB->PID = processDataHead->pid;
      newPCB->currentState = NEW;

      // Check that first command is app start, move to first real command
      if( compareString( processDataHead->strArg1, "start" ) == 0 )
      {
         // Pull next commands
         newPCB->startingCommand = processDataHead->nextNode;
         newPCB->nextCommand = processDataHead->nextNode;
      }

      // Calculate total runtime for PCB based on number and type of operations
      // Loop forward until next node command is app end
      while( processDataHead != NULL )
      {
         // If current command is an IO operation
         if ( compareString( processDataHead->command, "dev" ) == 0 )
         {
            // Increment IO operations counter
            totalRunTime = totalRunTime + \
                                       (ioCycleRate * processDataHead->intArg2);

            // Set time into instruction
            processDataHead->runTime = ioCycleRate * processDataHead->intArg2;
         }
         // If current command is a CPU operation
         if ( compareString( processDataHead->command, "cpu" ) == 0 )
         {
            // Increment CPU operation counter
            totalRunTime = totalRunTime + \
                                      (CPUcycleRate * processDataHead->intArg2);

            // Set time into instruction
            processDataHead->runTime = CPUcycleRate * processDataHead->intArg2;
         }
         // If current command is a MEM operation
         if ( compareString( processDataHead->command, "mem" ) == 0 )
         {
            // Set time into instruction
            processDataHead->runTime = 0;
         }
         // Move to next node
         processDataHead = processDataHead->nextNode;

      }

      // Set total run time and total time remaining into PCB
      newPCB->totalRunTime = totalRunTime;
      newPCB->timeRemaining = totalRunTime;

      // Give new PCB back to requester
      return newPCB;
   }

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
                            LogNodeType *logListHead )
   {
      // Initialize variables
         // Create head of schedule list as PCB node
         PCBDataType *scheduleHeadPtr = NULL;

         // Create a buffer node for holding working PCB
         PCBDataType *workingPCBptr = NULL;

      // First Come First Serve Schedule
      if( scheduleCode == (int)CPU_SCHED_FCFS_N_CODE )
      {
           // PCB list comes in as FCFS

           // Set buffer node to list head
           workingPCBptr = PCBlistHead;

           // Iterate over nodes
           while( workingPCBptr != NULL )
           {
              // Set the node to ready state
              //changePCBstate( workingPCBptr, READY, timer, logListHead );
              // Copy node to schedule
              scheduleHeadPtr = addPCBNode(scheduleHeadPtr, workingPCBptr);
              // Go to next node
              workingPCBptr = workingPCBptr->nextNode;
           }
      }

      // Shortest Job First - Non Preemptive
      if( scheduleCode == (int)CPU_SCHED_SJF_N_CODE )
      {
         // Set buffer node to list head
         workingPCBptr = PCBlistHead;

         // Sort the list
         sortSJF( workingPCBptr );

         // Load final return variable
         scheduleHeadPtr = workingPCBptr;

         // Loop through list and set all blocks to ready state
         while( workingPCBptr != NULL )
         {
            // Go to next node
            workingPCBptr = workingPCBptr->nextNode;
         }

      }

      // If not a recognized schedule, default to FCFS-N
      else
      {
         workingPCBptr = PCBlistHead;

         // Run the FCFS scheduling loop
         while( workingPCBptr != NULL )
         {
            // Copy node to schedule
            scheduleHeadPtr = addPCBNode(scheduleHeadPtr, workingPCBptr);
            // Go to next node
            workingPCBptr = workingPCBptr->nextNode;
         }
      }

      // Return
      return scheduleHeadPtr;
}

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
                     char *timer, LogNodeType *logListHead )
   {
      // Initialize variables
         // Array of strings for each state
         const char* stateStrings[] = {"NEW",
                                       "READY",
                                       "RUNNING",
                                       "BLOCKED",
                                       "EXIT" };

         // Buffer log node for writing to log
         LogNodeType *bufferLogNode = \
                                 (LogNodeType *)malloc( sizeof( LogNodeType ) );

         // Buffer string to store old state once changed
         char localStateStr[ STD_STR_LEN ];

         // Buffer string for use in logging
         char bufferString[ MAX_STR_LEN ];

      // Copy the old state to the buffer string
      copyString(localStateStr, stateStrings[ PCBpointer->currentState ]);

      // Copy the new state into the PCB (as a string for future ease)
      copyString(PCBpointer->currentStateString, stateStrings[ newState ]);

      // Directly set new PCB state using given state type
      PCBpointer->currentState = newState;

      accessTimer(LAP_TIMER, timer);
      sprintf(bufferString,
              "   %s, OS: Process %d set to %s from %s state\n",
              timer, PCBpointer->PID, stateStrings[newState], localStateStr);
      copyString( bufferLogNode->logText, bufferString );
      addLogNode( logListHead, bufferLogNode );

      // free the thing
      free( bufferLogNode );
   }

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
PCBDataType *clearPCBList( PCBDataType *localPtr )
   {
      // Check for local pointer not set to null
      //clearMetaDataList( localPtr->startingCommand );
      if( localPtr != NULL )
         {
         // Call recursive function with next pointer
         // Function: clearMetaDataList
         clearPCBList( localPtr->nextNode );

         // After call, return memory to OS
         // Function: free
         free( localPtr );

         // Set given pointer to NULL
         localPtr = NULL;
         }

      // Return NULL to calling function
      return NULL;
   }

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
                          MemTableEntryType *memHead )
   {
      // Initialize variables
         // Buffer node for temp mem head
         MemTableEntryType *memBufferNode = memHead;

         // Buffer node for actual mem work
         MemTableEntryType *memWorkingNode = memHead;

         // Buffer node for holding previous mem node
         MemTableEntryType *memPreviousWorkingNode = NULL;

         // Process ID of process being cleared
         int processValue = PCBpointer->PID;

      // While working mem node is not null
      while ( memWorkingNode )
      {
         // If working node is owned by process holder
         if ( memWorkingNode->ProcessHolder == processValue )
         {
             // Cut the node out
             memPreviousWorkingNode->nextNode = memWorkingNode->nextNode;
             free( memWorkingNode );
         }
         // Otherwise
         else
         {
             // Update previous node
             memPreviousWorkingNode = memWorkingNode;
         }
         // Move to next node
         memWorkingNode = memWorkingNode->nextNode;
       }
       memHead->physicalAddressStart = 0;
       return memBufferNode;
   }

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
LogNodeType *clearLogList( LogNodeType *localPtr )
   {
      // Check for local pointer not set to null
      if( localPtr != NULL )
         {
         // Call recursive function with next pointer
         // Function: clearMetaDataList
         clearLogList( localPtr->nextNode );

         // After call, return memory to OS
         // Function: free
         free( localPtr );

         // Set given pointer to NULL
         localPtr = NULL;
         }

      // Return NULL to calling function
      return NULL;
   }

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
void dumpLogs( LogNodeType *logListHead, char *logFileName )
   {
      // Initialize variables
         // Variable for holding temp (working) log node
         LogNodeType *bufferLogNode = NULL;

         // Pointer to log file
         FILE *logFile;

      // Open log file
      logFile = fopen( logFileName, "w+");

      // Set log node read head to start of log list
      bufferLogNode = logListHead;

      // Loop over all log nodes while not null
      while( bufferLogNode != NULL )
      {
         // Print the log node text to file
         fprintf( logFile, bufferLogNode->logText );

         // Move to next node
         bufferLogNode = bufferLogNode->nextNode;
      }

      // Close the file once done writing
      fclose( logFile );
   }

/*
Name:                       initializeMemory
Process:                    Initializes the first node in sys memory linked list
Function Input/Parameters:  Memory node to log (memNode *),
                            Head of system log list (logListHead *),
                            Log-to code (int),
                            Amount of available memory (int),
                            Mem display switch (bool)
Function Output/Parameters: None
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               addLogNode, copyString, free, malloc, sprintf
*/
MemTableEntryType *initializeMemory( MemTableEntryType *memHead,
                                     LogNodeType *logListHead,
                                     int memAvailable )
   {
      // Initialize variables
         // Buffer log node
         LogNodeType *bufferLogNode = \
                                 (LogNodeType *)malloc( sizeof( LogNodeType ) );

         // Buffer string
         char bufferString[ MAX_STR_LEN ];

      // Set initial memory values
      memHead->ProcessHolder = -1;
      memHead->memorySize = memAvailable;
      memHead->logicalAddressStart = 0;
      memHead->logicalAddressEnd = 0;
      memHead->physicalAddressStart = 0;
      memHead->physicalAddressEnd = memAvailable - 1;
      memHead->nextNode = NULL;

      // If mem display is turned on, log this operation
      if( memDisplay )
      {
         // Padding
         sprintf( bufferString,
                "    -----------------------------------------------------\n" );
         copyString( bufferLogNode->logText, bufferString );
         addLogNode( logListHead, bufferLogNode );

         // Specific message for this operation (only shown once)
         sprintf( bufferString,
                "    After memory initialization:\n" );
         copyString( bufferLogNode->logText, bufferString );
         addLogNode( logListHead, bufferLogNode );

         // Log the actual table entry
         logMemoryEntry( memHead, logListHead );

         // Padding
         sprintf( bufferString,
                "    -----------------------------------------------------\n" );
         copyString( bufferLogNode->logText, bufferString );
         addLogNode( logListHead, bufferLogNode );
      }

      // Free buffer node
      free( bufferLogNode );

      // Return initialized mem head
      return memHead;
   }

/*
Name:                       logMemoryEntry
Process:                    Logs a given memory table entry
Function Input/Parameters:  Memory node to log (memNode *),
                            Head of system log list (logListHead *),
                            Log-to code (int)
                            Mem display switch (bool)
Function Output/Parameters: None
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               addLogNode, copyString, free, malloc, sprintf
*/
void logMemoryEntry( MemTableEntryType *memNode,
                     LogNodeType *logListHead )
   {
      // Initialize variables
         // Buffer log node
         LogNodeType *bufferLogNode = \
                                 (LogNodeType *)malloc( sizeof( LogNodeType ) );

         // Buffer string
         char bufferString[ MAX_STR_LEN ];

      // Only log if the memory display config is set
      if( memDisplay )
      {
         // If unused process holder, print as such
         if( memNode->ProcessHolder == -1 )
         {
            sprintf( bufferString,
                   "    %d [ Open, P#: x, %d-%d ] %d\n",
                   memNode->physicalAddressStart,
                   memNode->logicalAddressStart,
                   memNode->logicalAddressEnd,
                   memNode->physicalAddressEnd );
            copyString( bufferLogNode->logText, bufferString );
            addLogNode( logListHead, bufferLogNode );
         }

         // Otherwise, process holder must be an actual process
         else
         {
           sprintf( bufferString,
                  "    %d [ Used, P#: %d, %d-%d ] %d\n",
                  memNode->physicalAddressStart,
                  memNode->ProcessHolder,
                  memNode->logicalAddressStart,
                  memNode->logicalAddressEnd,
                  memNode->physicalAddressEnd );
           copyString( bufferLogNode->logText, bufferString );
           addLogNode( logListHead, bufferLogNode );
         }
      }

      // Free buffer node
      free( bufferLogNode );
   }

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
MemTableEntryType *nukeAllMemory( MemTableEntryType *memNode )
   {
     // Check for local pointer not set to null
     if( memNode != NULL )
        {
        // Call recursive function with next pointer
        // Function: clearMetaDataList
        nukeAllMemory( memNode->nextNode );

        // After call, return memory to OS
        // Function: free
        free( memNode );

        // Set given pointer to NULL
        memNode = NULL;
        }

     // Return NULL to calling function
     return NULL;
   }

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
void *runInOutOp( void *runTime )
   {
      // Initialize variables
      int *cycletime;

      // Cast input var to int pointer
      cycletime = (int *) runTime;

      // Run timer with referenced var ...
      runTimer( *cycletime );

      // Return something I guess
      return((void *) 0); //hate this language
   }

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
             LogNodeType *logListHead, MemTableEntryType *memHead )
   {
      // Initialize variables
         // Process Data Head - reads commands on PCB one by one
         OpCodeType *processDataHead;
         processDataHead = activePCB->startingCommand;

         // Buffer node for logging
         LogNodeType *bufferLogNode = \
                                 (LogNodeType *)malloc( sizeof( LogNodeType ) );

         // Buffer string for holding current process operation command
         char opCommand[ CMD_STR_LEN ];

         // Buffer string for logging
         char bufferString[ MAX_STR_LEN ];
         char errorMessage[ MAX_STR_LEN ];
         char memMessage[ MAX_STR_LEN ];

         // Thread for doing IO stuff
         pthread_t ioThread;

         // Success var for mem ops
         int memSuccess;

      // Build buffer node's log info for PROCESS SELECTED, TIME REMAINING
      accessTimer(LAP_TIMER, timer);
      sprintf(bufferString,
              "   %s, OS: Process %d selected with %d ms remaining\n",
              timer, activePCB->PID, activePCB->timeRemaining );

      copyString( bufferLogNode->logText, bufferString );

      // Add buffer log node to system log list
      addLogNode( logListHead, bufferLogNode );

      // PCB is now ready to run
      changePCBstate( activePCB, RUNNING, timer, logListHead );

      // Log a newline for formatting consistency
      copyString( bufferLogNode->logText, "\n" );
      addLogNode( logListHead, bufferLogNode );

      // While there are commands to run and PCB is running
      while( processDataHead != NULL &&
             activePCB->currentState == (int)RUNNING )
      {
         copyString( opCommand, processDataHead->command );
         copyString( errorMessage, " " );

         // IF THE CURRENT OP IS CPU ---------------------------------------->>>
         if( compareString( opCommand, "cpu" ) == 0 )
         {
            // Get time
            accessTimer(LAP_TIMER, timer);
            // LOGGING
            sprintf(bufferString,
                    "   %s, Process: %d, cpu process operation start\n",
                    timer, activePCB->PID );
            copyString( bufferLogNode->logText, bufferString );
            addLogNode( logListHead, bufferLogNode );

            runTimer(processDataHead->runTime);

            // LOGGING
            accessTimer(LAP_TIMER, timer);
            sprintf(bufferString,
                    "   %s, Process: %d, cpu process operation end\n",
                    timer, activePCB->PID );
            copyString( bufferLogNode->logText, bufferString );
            addLogNode( logListHead, bufferLogNode );
         }

         // IF THE CURRENT OP IS DEV ---------------------------------------->>>
         if( compareString( opCommand, "dev" ) == 0)
         {
           // LOGGING
           accessTimer(LAP_TIMER, timer);
           sprintf(bufferString,
                   "   %s, Process: %d, %s %s process operation start\n",
                   timer, activePCB->PID, processDataHead->strArg1,
                   processDataHead->inOutArg );
           copyString( bufferLogNode->logText, bufferString );
           addLogNode( logListHead, bufferLogNode );

           int *ioRunTime = &processDataHead->runTime;

           // Do in/out thread
           pthread_create( &ioThread, NULL, &runInOutOp,
                           (void *) ioRunTime );

           pthread_join( ioThread, NULL );

           // LOGGING THE OPERATION
           accessTimer(LAP_TIMER, timer);
           sprintf(bufferString,
                   "   %s, Process: %d, %s %s process operation end\n",
                   timer, activePCB->PID, processDataHead->strArg1,
                   processDataHead->inOutArg );
           copyString( bufferLogNode->logText, bufferString );
           addLogNode( logListHead, bufferLogNode );
         }

         // IF CURRENT OP IS MEM -------------------------------------------->>>
         if( compareString( opCommand, "mem" ) == 0)
         {
           // Get time of operation start
           accessTimer(LAP_TIMER, timer);

           sprintf(bufferString,
                   "   %s, Process: %d, mem %s request (%d, %d)\n",
                   timer, activePCB->PID, processDataHead->strArg1,
                   processDataHead->intArg2, processDataHead->intArg3 );
           copyString( bufferLogNode->logText, bufferString );
           addLogNode( logListHead, bufferLogNode );

           // Check if it is allocate or access request
           // If allocate request
           if( compareString(processDataHead->strArg1, "allocate" ) == 0 )
           {
              // Attempt to allocate memory
              // error code 0=success, 1=logical failure, 2=physical failure
              memSuccess = allocateMemory( memHead, // Head of memory list
                                           processDataHead->intArg2, //log start
                                           processDataHead->intArg2 + \
                                           processDataHead->intArg3 - 1, // end
                                           logListHead,
                                           memAvailable,
                                           activePCB->PID );
           }
           if( compareString(processDataHead->strArg1, "access" ) == 0 )
           {
              memSuccess = accessMemory( memHead,
                                         activePCB->PID,
                                         processDataHead->intArg2,
                                         processDataHead->intArg3 );
           }

           // If access request
              // Attempt to access memory
              // error code 0=success, 1=doesn't exist, 2=out of bounds

           // Get time of operation end
           accessTimer(LAP_TIMER, timer);

           // Decide if given operation failed or not
           if( memSuccess != 0 )
           {
              processDataHead->nextNode = NULL;
              sprintf( memMessage,
                       "    After %s failure\n", processDataHead->strArg1 );
              showMem( memHead, logListHead, memMessage );

              // Print log message to buffer string
              sprintf(bufferString,
                      "   %s, Process: %d, failed mem %s request\n",
                      timer, activePCB->PID, processDataHead->strArg1 );
              // Copy string buffer string into buffer log node
              copyString( bufferLogNode->logText, bufferString );
              // Add buffer log node to the system log list
              addLogNode( logListHead, bufferLogNode );
              copyString(errorMessage, " Segmentation fault, ");

           }
           else
           {
              sprintf( memMessage,
                       "    After %s success\n", processDataHead->strArg1 );
              showMem( memHead, logListHead, memMessage );
              // Print log message to buffer string
              sprintf(bufferString,
                      "   %s, Process: %d, successful mem %s request\n",
                      timer, activePCB->PID, processDataHead->strArg1 );
              // Copy string buffer string into buffer log node
              copyString( bufferLogNode->logText, bufferString );
              // Add buffer log node to the system log list
              addLogNode( logListHead, bufferLogNode );
           }
         }
         processDataHead = processDataHead->nextNode;
      }

      // If there are no more commands to run
      if( processDataHead == NULL )
      {
         // Get time of process end
         accessTimer(LAP_TIMER, timer);
         // Print log to buffer
         sprintf(bufferString,
                 "\n   %s, OS:%sProcess %d ended\n\n",
                 timer, errorMessage, activePCB->PID );
         // Copy buffer into log node
         copyString( bufferLogNode->logText, bufferString );
         // Add log node to system log list
         addLogNode( logListHead, bufferLogNode );


      }

      clearProcessMemory( activePCB, memHead );
      if( memDisplay )
      {
         sprintf( memMessage,
                  "    After clear process %d success\n", activePCB->PID );
         showMem( memHead, logListHead, memMessage );
      }
      // Change PCB to exit state
      changePCBstate( activePCB, EXIT, timer, logListHead );

      // Free the buffer log node
      free( bufferLogNode );
   }

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
             OpCodeType *metaDataMstrPtr )
   {
      // INITIALIZE VARIABLES ------------------------------------------------->

         // VARIABLES FOR PROCESSES & CONTROL ------------------------------->>>
         // Variable for holding current OpCodeType node
         // Function: malloc
         OpCodeType *currentOp = metaDataMstrPtr;

         //Build a list for storing process control blocks as they are finished

         // Variable for holding copies of current node members
         char currentOpCommand[ CMD_STR_LEN ];
         char currentOpStringArg[ STR_ARG_LEN ];

         // Create variable to hold number of total processes
         int processCounter = 0; // Counter for assigning PID numbers

         // Create buffer variable to act as the head of the operations list
         // for a given PCB
         OpCodeType *processHeadPointer = NULL;

         // Variables for working (buffer) PCB, head of PCB list, and currently
         // running PCB
         PCBDataType *bufferPCB = NULL;
         PCBDataType *PCBlistHead = NULL;
         PCBDataType *runningPCB = NULL;

         // Variable to hold the schedule
         PCBDataType *PCBscheduleHead;

         // Variable to hold system memory table
         MemTableEntryType *sysMemHead = \
                     (MemTableEntryType *)malloc( sizeof( MemTableEntryType ) );

         // Variable for system clock
         char systemTimeString[ STD_STR_LEN ];
         char bufferString[ STD_STR_LEN ];

         // Variables for logging utilities. Current log code (monitor, file, or
         // both), variable for head of all log nodes, working (buffer) log node
         LogNodeType *logListHead = \
                                 (LogNodeType *)malloc( sizeof( LogNodeType ) );
         LogNodeType *bufferLogNode = \
                                 (LogNodeType *)malloc( sizeof( LogNodeType ) );

         // Set the global vars
         logToCode = configPtr->logToCode;
         memDisplay = configPtr->memDisplay;

      // BEGIN SIMULATOR ------------------------------------------------------>
      // Get the first command
      copyString( currentOpCommand, currentOp->command );
      copyString( currentOpStringArg, currentOp->strArg1 );

      // START UP OS -------------------------------------------------------->>>
      if( logToCode == (int)LOGTO_FILE_CODE )
      {
         printf( "OS running in log to file mode...\n\n" );
      }

      // First command should be system start
      if( compareString( currentOpCommand, "sys" ) == 0 &&
          compareString( currentOpStringArg, "start" ) == 0 )
      {

         copyString( bufferLogNode->logText, "\nSimulator Start\n");
         addLogNode( logListHead, bufferLogNode );
         copyString( bufferLogNode->logText, "---------------\n\n");
         addLogNode( logListHead, bufferLogNode );

         // Get time of start
         accessTimer( ZERO_TIMER, systemTimeString );

         // Print string buffer
         copyString( bufferLogNode->logText, "   ");
         concatenateString( bufferLogNode->logText, systemTimeString );
         concatenateString( bufferLogNode->logText, ", OS: Simulator Start\n" );
         addLogNode( logListHead, bufferLogNode );

         // Move to first op command in data list
         currentOp = currentOp->nextNode;
      }

      // BUILD PROCESS CONTROL BLOCKS --------------------------------------->>>
      // Loop over all ops in metadata, building individual processes lists
      while( currentOp != NULL ) // go until end of data file
      {
         currentOp->pid = processCounter; // set PID (default unassigned)

         // Copy commands and string args for checking
         copyString( currentOpCommand, currentOp->command );
         copyString( currentOpStringArg, currentOp->strArg1 );

         // If not at app or sys, we must be in an app
         // Make sure sys end isn't added to something by mistake
         if( compareString( currentOpCommand, "app" ) != 0 &&
             compareString( currentOpCommand, "sys" ) != 0 )
         {
            // Add current operation to process command list
            processHeadPointer = addNode( processHeadPointer, currentOp );
         }

         // Check if current operation is creating or ending an app
         // Function: compareString
         if( compareString(currentOpCommand, "app") == 0 )
         {
            // If creating an app, we start building a new process chain
            if( compareString(currentOpStringArg, "start" ) == 0 )
            {
               // Add new operation to head of the process ops list
               processHeadPointer = addNode( processHeadPointer, currentOp );
            }

            // If ending an app, create a new PCB and reset pointer
            if( compareString(currentOpStringArg, "end" ) == 0 )
            {
               // Increase PID count
               processCounter = processCounter + 1;

               // Build the process control block
               // Function: buildPCB
               bufferPCB = buildPCB( processHeadPointer,
                                     configPtr->procCycleRate,
                                     configPtr->ioCycleRate,
                                     systemTimeString );

               changePCBstate( bufferPCB, READY,
                               systemTimeString, logListHead );

               // Add new PCB to linked list of PCB
               PCBlistHead = addPCBNode( PCBlistHead, bufferPCB );

               // Reset process op list pointer
               clearPCBList( bufferPCB );
               free(processHeadPointer);
               processHeadPointer = NULL;
            }
         }

         // Move to next operation node
         currentOp = currentOp->nextNode;
      }

      // SCHEDULE PROCESSES ------------------------------------------------->>>

      // Build schedule out from config code
      PCBscheduleHead = buildSchedule( PCBlistHead,
                                       configPtr->cpuSchedCode,
                                       systemTimeString,
                                       logListHead );

      // INITIALIZE MEMORY -------------------------------------------------->>>

      memAvailable = configPtr->memAvailable; // global var
      sysMemHead = initializeMemory( sysMemHead,
                                     logListHead,
                                     configPtr->memAvailable );

      // RUN PROCESSES ------------------------------------------------------>>>

      // Set the running PCB to first in schedule
      runningPCB = PCBscheduleHead;

      while( runningPCB != NULL ) // Gotta change this later
      {
         runPCB( runningPCB, systemTimeString, logListHead, sysMemHead );
         clearMetaDataList( runningPCB->startingCommand );
         runningPCB = runningPCB->nextNode;
      }

      // Once all processes are run, system can stop
      copyString( bufferLogNode->logText, "   ");
      concatenateString( bufferLogNode->logText, systemTimeString ); // time
      concatenateString( bufferLogNode->logText, ", OS: System Stop\n" );
      addLogNode( logListHead, bufferLogNode );

      // NUKE SIM MEMORY ---------------------------------------------------->>>
      nukeAllMemory( sysMemHead );
      if( memDisplay )
      {
        sprintf( bufferString,
               "    -----------------------------------------------------\n" );
        copyString( bufferLogNode->logText, bufferString );
        addLogNode( logListHead, bufferLogNode );
        sprintf( bufferString,
               "    After clear all process success\n" );
        copyString( bufferLogNode->logText, bufferString );
        addLogNode( logListHead, bufferLogNode );
        sprintf( bufferString,
               "    No memory configured\n" );
        copyString( bufferLogNode->logText, bufferString );
        addLogNode( logListHead, bufferLogNode );
        sprintf( bufferString,
               "    -----------------------------------------------------\n" );
        copyString( bufferLogNode->logText, bufferString );
        addLogNode( logListHead, bufferLogNode );
      }

      // POWER DOWN OS ------------------------------------------------------>>>
      // At this point, the simulator is finished.

      // Get final time
      accessTimer( LAP_TIMER, systemTimeString );

      // Log the end of sim
      copyString( bufferLogNode->logText, "\n   ");
      concatenateString( bufferLogNode->logText, systemTimeString );
      concatenateString( bufferLogNode->logText, ", OS: Simulation End\n" );
      addLogNode( logListHead, bufferLogNode );

      // DUMP LOG IF THING NECESSARY ---------------------------------------->>>

      if( logToCode == LOGTO_BOTH_CODE ||
          logToCode == LOGTO_FILE_CODE )
      {
         dumpLogs( logListHead, configPtr->logToFileName );
      }

      // FREE THE MEMORY ---------------------------------------------------->>>

      clearLogList( logListHead );
      clearLogList( bufferLogNode );

      clearPCBList( runningPCB );
      clearPCBList( PCBscheduleHead );

      clearMetaDataList( processHeadPointer );
      free( processHeadPointer );
   }

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
              char *displayMessage )
   {
      // Initialize vars
         // Buffer node for traversing mem table
         MemTableEntryType *bufferNode = memHead;

         // Buffer log node
         LogNodeType *bufferLogNode = \
                                 (LogNodeType *)malloc( sizeof( LogNodeType ) );

         // Buffer string
         char bufferString[ MAX_STR_LEN ];

      if( memDisplay )
      {
         sprintf( bufferString,
                "    -----------------------------------------------------\n" );
         copyString( bufferLogNode->logText, bufferString );
         addLogNode( logListHead, bufferLogNode );

         copyString( bufferLogNode->logText, displayMessage );
         addLogNode( logListHead, bufferLogNode );
         while( bufferNode != NULL )
            {
               logMemoryEntry( bufferNode, logListHead );
               bufferNode = bufferNode->nextNode;
            }
         sprintf( bufferString,
                "    -----------------------------------------------------\n" );
         copyString( bufferLogNode->logText, bufferString );
         addLogNode( logListHead, bufferLogNode );
      }

      free( bufferLogNode );
   }

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
void sortSJF( PCBDataType *headNode )
   {
      // Initialize variables
         // Ghetto int bool for checking if a swap has occurred
         int swapBool;

         // Buffer node for holding working piece
         PCBDataType *bufferNode;

         // Buffer node for holding piece after working piece
         PCBDataType *nextBufferNode = NULL;

      do // We have to check atleast once that things are in right spot
      {
         // Set swappBool to false
         swapBool = 0;
         // Initialize the buffer node
         bufferNode = headNode;

         while (bufferNode->nextNode != nextBufferNode)
            {
               if ( bufferNode->totalRunTime > \
                    bufferNode->nextNode->totalRunTime )
               {
                  swapPCBNode( bufferNode, bufferNode->nextNode );
                  swapBool = 1;
               }
               bufferNode = bufferNode->nextNode;
            }
            nextBufferNode = bufferNode;
      }
      while( swapBool );
   }

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
void swapPCBNode( PCBDataType *nodeOne, PCBDataType *nodeTwo )
   {
      // Create temporary variables to hold the contents of PCB node one
      int tempPID = nodeOne->PID;
      ProcessState tempState = nodeOne->currentState;
      char tempCurrentStateString[ STD_STR_LEN ];
      copyString(tempCurrentStateString, nodeOne->currentStateString);
      int tempTotalRunTime = nodeOne->totalRunTime;
      int tempTimeRemaining = nodeOne->timeRemaining;
      OpCodeType* tempStartingCommand = nodeOne->startingCommand;
      OpCodeType* tempNextCommand = nodeOne->nextCommand;

      // Copy variables from node two into node one
      nodeOne->PID = nodeTwo->PID;
      nodeOne->currentState = nodeTwo->currentState;
      copyString(nodeOne->currentStateString, nodeTwo->currentStateString);
      nodeOne->totalRunTime = nodeTwo->totalRunTime;
      nodeOne->timeRemaining = nodeTwo->timeRemaining;
      nodeOne->startingCommand = nodeTwo->startingCommand;
      nodeOne->nextCommand = nodeTwo->nextCommand;

      // Copy temp variables back into node two
      nodeTwo->PID = tempPID;
      nodeTwo->currentState = tempState;
      copyString(nodeTwo->currentStateString, tempCurrentStateString);
      nodeTwo->totalRunTime = tempTotalRunTime;
      nodeTwo->timeRemaining = tempTimeRemaining;
      nodeTwo->startingCommand = tempStartingCommand;
      nodeTwo->nextCommand = tempNextCommand;
   }
