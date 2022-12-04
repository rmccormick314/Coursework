// Header files
#include "simulator.h"

// Functions
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
                         int logToCode )
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
      localPtr->nextNode = addLogNode( localPtr->nextNode, newNode, logToCode );

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
                            Log-to config code (int)
Function Output/Parameters: Process Schedule (ProcessScheduleType *)
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               addPCBNode, changePCBstate, clearPCBList, copyString
*/
PCBDataType *buildSchedule( PCBDataType *PCBlistHead,
                            int scheduleCode, char *timer,
                            LogNodeType *logListHead, int logToCode )
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
           changePCBstate( workingPCBptr, READY, timer, logListHead, logToCode );
           // Copy node to schedule
           scheduleHeadPtr = addPCBNode(scheduleHeadPtr, workingPCBptr);
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
         // Set the node to ready state
         changePCBstate( workingPCBptr, READY, timer, logListHead, logToCode );
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
                     char *timer, LogNodeType *logListHead, int logToCode )
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
      addLogNode( logListHead, bufferLogNode, logToCode );

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
             LogNodeType *logListHead, int logToCode )
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

         // Thread for doing IO stuff
         pthread_t ioThread;

      // Build buffer node's log info for PROCESS SELECTED, TIME REMAINING
      accessTimer(LAP_TIMER, timer);
      sprintf(bufferString,
              "   %s, OS: Process %d selected with %d ms remaining\n",
              timer, activePCB->PID, activePCB->timeRemaining );

      copyString( bufferLogNode->logText, bufferString );

      // Add buffer log node to system log list
      addLogNode( logListHead, bufferLogNode, logToCode );

      // PCB is now ready to run
      changePCBstate( activePCB, RUNNING, timer, logListHead, logToCode );

      // Log a newline for formatting consistency
      copyString( bufferLogNode->logText, "\n" );
      addLogNode( logListHead, bufferLogNode, logToCode );

      // While there are commands to run and PCB is running
      while( processDataHead != NULL &&
             activePCB->currentState == (int)RUNNING )
      {
         copyString( opCommand, processDataHead->command );

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
            addLogNode( logListHead, bufferLogNode, logToCode );

            runTimer(processDataHead->runTime);

            // LOGGING
            accessTimer(LAP_TIMER, timer);
            sprintf(bufferString,
                    "   %s, Process: %d, cpu process operation end\n",
                    timer, activePCB->PID );
            copyString( bufferLogNode->logText, bufferString );
            addLogNode( logListHead, bufferLogNode, logToCode );
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
           addLogNode( logListHead, bufferLogNode, logToCode );

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
           addLogNode( logListHead, bufferLogNode, logToCode );
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
           addLogNode( logListHead, bufferLogNode, logToCode );

           // Run process operation for given cycle time
           runTimer(processDataHead->runTime);

           // Get time of operation end
           accessTimer(LAP_TIMER, timer);
           // Print log message to buffer string
           sprintf(bufferString,
                   "   %s, Process: %d, mem %s process operation end\n",
                   timer, activePCB->PID, processDataHead->strArg1 );
           // Copy string buffer string into buffer log node
           copyString( bufferLogNode->logText, bufferString );
           // Add buffer log node to the system log list
           addLogNode( logListHead, bufferLogNode, logToCode );
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
                 "\n   %s, OS: Process %d ended\n\n",
                 timer, activePCB->PID );
         // Copy buffer into log node
         copyString( bufferLogNode->logText, bufferString );
         // Add log node to system log list
         addLogNode( logListHead, bufferLogNode, logToCode );

         // Change PCB to exit state
         changePCBstate( activePCB, EXIT, timer, logListHead, logToCode );
      }

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

         // Variable for system clock
         char systemTimeString[ STD_STR_LEN ];

         // Variables for logging utilities. Current log code (monitor, file, or
         // both), variable for head of all log nodes, working (buffer) log node
         int logToCode = configPtr->logToCode;
         LogNodeType *logListHead = \
                                 (LogNodeType *)malloc( sizeof( LogNodeType ) );
         LogNodeType *bufferLogNode = \
                                 (LogNodeType *)malloc( sizeof( LogNodeType ) );

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
         addLogNode( logListHead, bufferLogNode, logToCode );
         copyString( bufferLogNode->logText, "-------------\n\n");
         addLogNode( logListHead, bufferLogNode, logToCode );

         // Get time of start
         accessTimer( ZERO_TIMER, systemTimeString );

         // Print string buffer
         copyString( bufferLogNode->logText, "   ");
         concatenateString( bufferLogNode->logText, systemTimeString );
         concatenateString( bufferLogNode->logText, ", OS: Simulator Start\n" );
         addLogNode( logListHead, bufferLogNode, logToCode );

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

               // Add new PCB to linked list of PCB
               PCBlistHead = addPCBNode( PCBlistHead, bufferPCB );

               // Reset process op list pointer
               clearPCBList( bufferPCB );
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
                                       logListHead,
                                       logToCode );

      // RUN PROCESSES ------------------------------------------------------>>>

      // Set the running PCB to first in schedule
      runningPCB = PCBscheduleHead;

      while( runningPCB != NULL ) // Gotta change this later
      {
         runPCB( runningPCB, systemTimeString, logListHead, logToCode );
         runningPCB = runningPCB->nextNode;
      }

      // Once all processes are run, system can stop
      copyString( bufferLogNode->logText, "   ");
      concatenateString( bufferLogNode->logText, systemTimeString ); // time
      concatenateString( bufferLogNode->logText, ", OS: System Stop\n" );
      addLogNode( logListHead, bufferLogNode, logToCode );

      // POWER DOWN OS ------------------------------------------------------>>>
      // At this point, the simulator is finished.

      // Get final time
      accessTimer( LAP_TIMER, systemTimeString );

      // Log the end of sim
      copyString( bufferLogNode->logText, "\n   ");
      concatenateString( bufferLogNode->logText, systemTimeString );
      concatenateString( bufferLogNode->logText, ", OS: Simulation End\n" );
      addLogNode( logListHead, bufferLogNode, logToCode );

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
      clearPCBList( PCBlistHead );
      clearPCBList( PCBscheduleHead );

      clearMetaDataList( processHeadPointer );
   }
