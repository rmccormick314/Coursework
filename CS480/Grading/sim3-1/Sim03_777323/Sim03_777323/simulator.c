// Used educational coding vidoes from Michael Leverington for this assignment
// Luke Frazer

// header files
#include "OS_SimDriver.h"
#include "string.h"
#include "simtimer.h"
#include "simtimer.c"

/*
Name: runSim
Process: primary simulator driver
Function Input/Parameters: configuration data (ConfigDataType *)
                           metadata (OpCodeType *)
Function Output/Parameters: none
Function Output/Returned: none
Device Input/Keybaord: none
Device Output/Monitor: none
Dependencies: tbd
*/
void runSim(ConfigDataType *configPtr, OpCodeType *metaDataMstrPtr)
{
	// initialize variables
	bool monitor = false;
	bool file, isDev, isApp, isStart, isEnd, isSys;	
	bool assignBoth = false;
	bool logTo = false;
	bool isProcess;
	char line[MAX_LINE_LENGTH];
	char time[MAX_STR_LEN];
	int cpuSched;
	int pidCounter = 0;
	double getTime;
	PCBType currentProcess;
	MMUType memory;
	OpCodeType opCode;
	ProcessState state;
	FILE *configFile, *metadataFile, *fptr;

	// open the config file
	configFile = fopen("config.cnf", "r");

	// get start time
	getTime = accessTimer(ZERO_TIMER, time);

	// get the available memory from the config file
	memory.memAvailable = configPtr->memAvailable;
	
	// loop through each line
	while(fgets(line, MAX_LINE_LENGTH, configFile))
	{
		// set pointer result of Log To substring check
		logTo = checkSubString(line, "Log To");

		// set pointer result of mem display flag to substring check
		memory.memDisplayLine = checkSubString(line, "Memory Display");
		
		// check how to log
		if(logTo)
		{
			// check for if it is monitor or file
			monitor = checkSubString(line, "Monitor");
			file = checkSubString(line, "File");

			// check if it is both
			assignBoth = checkSubString(line, "Both");

			// if it is both, assign both monitor and file
			if(assignBoth)
			{
				monitor = true;
				file = true;
			}
		}

		// check if memory display is needed
		if(memory.memDisplayLine)
		{
			// checks for memory display
			memory.memDisplayOn = checkSubString(line, ": On");
		}

		// reset flags
		logTo = false;
		memory.memDisplayLine = false;
	}

	// close the config file
	fclose(configFile);

	// check if outputting solely to file
	if(file && !monitor)
	{		

		// display message of outputting to file
		printf("Outputting to the following file after all operations are complete: \n\n");
		puts(configPtr->logToFileName);

	}	

	// open the metadata
	metadataFile = fopen(configPtr->metaDataFileName, "r");

	// get the scheduling type
	cpuSched = configPtr->cpuSchedCode;

	// check for SJF scheduling
	if(cpuSched == CPU_SCHED_SJF_N_CODE)
	{
		// check for monitor
		if(monitor)
		{
			// print the schedule
			printf("Running with SJF-N Scheduling\n\n");
		}
	}

	// otherwise, default to FCFS-N
	else
	{
		// check for monitor
		if(monitor)
		{
			// print the schedule
			printf("Running with FCFS-N Scheduling\n\n");
		}

	}

	// loop through the metadata to process
	while(fgets(line, MAX_LINE_LENGTH, metadataFile))
	{

		// set flag for process
		isProcess = checkSubString(line, "process");

		// check if the line is a process
		if(isProcess)
		{
			// allocate memory for the process
			memory.memPtr = (int*)malloc(sizeof(memory.memAvailable - MEM_OFFSET));

			// check if there was an error allocating memory
			if(memory.memPtr == NULL_CHAR)
			{

				// check for monitoring to terminal
				if(monitor)
				{
					// get current time
					getTime = accessTimer(LAP_TIMER, time);

					// print the time 
					printf("%f, ", getTime);
					
					// print the error
					printf("Memory Allocation Error\n");
				}
			
			}

			// increment the pid counter
			pidCounter += 1;

			// get the process and assign to process variable
			currentProcess = getProcess(line, pidCounter);

			// set the states
			state = NEW_STATE;
			state = READY_STATE;
			state = RUNNING_STATE;

				// check for monitor
				if(monitor && state != NULL_CHAR)
				{
					// get current time
					getTime = accessTimer(LAP_TIMER, time);

					// print the time 
					printf("%f, ", getTime);
					
					// print to the screen the process data
					printf("Process: %i set to READY from NEW state\n\n", currentProcess.pid);

					// get current time
					getTime = accessTimer(LAP_TIMER, time);

					// print the time 
					printf("%f, ", getTime);
					
					// print to the screen the process data
					printf("Process: %i set to RUNNING from READY state\n\n", currentProcess.pid);

				}

			// reset the isProcess flag
			isProcess = false;

			// free the memory
			free(memory.memPtr);
		}

		// get the opcode and assign to opcode variable
		opCode = getOpCode(line);
			
		// check for monitor output
		if(monitor)
		{
			// set the flags for op code
			isApp 	= checkSubString(opCode.command, "app");
			isDev 	= checkSubString(opCode.command, "dev");
			isSys 	= checkSubString(opCode.command, "sys");
			isStart = checkSubString(opCode.strArg1, "start");
			isEnd 	= checkSubString(opCode.strArg1, "end");

			// check if its an app
			if(isApp)
			{
				// check if its starting
				if(isStart)
				{
					// get current time
					getTime = accessTimer(LAP_TIMER, time);

					// print the time 
					printf("%f, ", getTime);

					printf("Starting Application...\n\n");
				}
					
				// check if its ending
				else if(isEnd)
				{
					printf("Ending Application...\n\n");

					if(memory.memDisplayOn)
					{
						printf("--------------------------------------------------\n");
						printf("After clear process %i success\n", currentProcess.pid);
						printf("0 [ Open, P#: x, 0-0 ] %i\n", memory.memAvailable - MEM_OFFSET);
						printf("--------------------------------------------------\n\n");
					}
				}
			}
	
			// check if its a system
			else if(isSys)
			{

				// check if its starting
				if(isStart)
				{
					// get current time
					getTime = accessTimer(ZERO_TIMER, time);

					// print the time 
					printf("%f\n", getTime);

					printf("--------STARTING SYSTEM--------\n\n");

				}

				// check if its ending
				else if(isEnd)
				{
					// get current time
					getTime = accessTimer(STOP_TIMER, time);

					// print the time 
					printf("%f\n", getTime);

					printf("--------ENDING SYSTEM--------\n\n");
				}
			}

			// check if its a dev command
			else if(isDev)
			{

				// get current time
				getTime = accessTimer(LAP_TIMER, time);

				// print the time 
				printf("%f, ", getTime);

				// print to the screen the opcode data
				printf("OpCode: ");
				fputs(opCode.command, stdout);
				printf(" ");
				fputs(opCode.inOutArg, stdout);
				printf("\n\n");
			}
		}
	}

	// open the logging file
	fptr = fopen(configPtr->logToFileName, "w");

	// write to the file
	fwrite("logging... \n", 1, sizeof("logging... \n"), fptr);

	// close the file pointer
	fclose(fptr);
}

/*
Name: getProcess
Process: retrieves the process ID from the metadatafile
Function Input/Parameters: metadata (OpCodeType *)
						   process ID to be assigned to the process
Function Output/Parameters: none
Function Output/Returned: The process ID
Device Input/Keybaord: none
Device Output/Monitor: none
Dependencies: tbd
*/
PCBType getProcess(char line[], int processID)
{
	// initialzie the PCB object
	PCBType processStuff;
	
	// set the process ID
	processStuff.pid = processID;

	// return the PCB Object
	return processStuff;
}

/*
Name: getOpCode
Process: retrieves the OpCode from the metadata file
Function Input/Parameters: metadata (OpCodeType *)
Function Output/Parameters: none
Function Output/Returned: The OpCode for process
Device Input/Keybaord: none
Device Output/Monitor: none
Dependencies: tbd
*/
OpCodeType getOpCode(char line[])
{
	// initialize variables
	bool devIn, devOut, appStart, appEnd, sysStart, sysEnd;
	OpCodeType opCode;

	// set flags for each opcode 
	devIn =    checkSubString(line, "dev in");
	devOut =   checkSubString(line, "dev out");
	appStart = checkSubString(line, "app start");
	appEnd =   checkSubString(line, "app end");
	sysStart = checkSubString(line, "sys start");
	sysEnd =   checkSubString(line, "sys end");

	// check for the dev in flag
	if(devIn)
	{
		// save the command and argument
		copyString(opCode.command, "dev");
		copyString(opCode.inOutArg, "in");
	}
	
	// check for the dev out flag
	else if(devOut)
	{
		// save the command and argument
		copyString(opCode.command, "dev");
		copyString(opCode.inOutArg, "out");
	}
	
	// check for the app start flag
	else if(appStart)
	{
		// save the command and argument
		copyString(opCode.command, "app");
		copyString(opCode.strArg1, "start");
	}

	// check for the app end flag
	else if(appEnd)
	{
		// save the command and argument
		copyString(opCode.command, "app");
		copyString(opCode.strArg1, "end");
	}

	// check for the sys start flag
	else if(sysStart)
	{
		// save the command and argument
		copyString(opCode.command, "sys");
		copyString(opCode.strArg1, "start");
	}

	// check for the sys end flag
	else if(sysEnd)
	{
		// save the command and argument
		copyString(opCode.command, "sys");
		copyString(opCode.strArg1, "end");
	}

	return opCode;
}

/*
Name: checkSubString
Process: checks if the specified string is in another string
Function Input/Parameters: String to check and substring (char[])
Function Output/Parameters: none
Function Output/Returned: True or false of if a substring is in the string
Device Input/Keybaord: none
Device Output/Monitor: none
Dependencies: none
*/
bool checkSubString( char checkString[], char subString[])
{
	// initialize variables

	// create check string index
	int checkIndex;

	// create substring index
	int subStringIndex;

	// set substring in string flag to false to start
	bool containsSubString = false;

	// loop through the check string
	for(checkIndex = 0; checkString[checkIndex] != '\0'; checkIndex++)
	{
		containsSubString = false;

		for(subStringIndex = 0; subString[subStringIndex] != '\0'; subStringIndex++)
		{
			if(checkString[checkIndex + subStringIndex] != subString[subStringIndex])
			{
				containsSubString = false;
				break;
			}

			containsSubString = true;

		}
		
		if(containsSubString)
		{
			break;
		}
	}

	// return the flag
	return containsSubString;

}




