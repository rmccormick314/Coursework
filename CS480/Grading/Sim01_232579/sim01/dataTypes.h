#ifndef DATATYPES_H
#define DATATYPES_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


// GLOBAL CONSTANTS - may be used in other files
typedef enum { False, True } Boolean;

// config data structure
typedef struct ConfigDataType
   {
	double version;
	char metaDataFileName[100];
	int cpuSchedCode;
	int quantumCycles;
	bool memDisplay;
	int memAvailable;
	int procCycleRate;
	int ioCycleRate;
	int logToCode;
	char logToFileName[100];

   } ConfigDataType;

typedef struct OpCodeType
   {
	int pid;					// pid, added when PCB is created
	char command[5];			// three letter command quantity
	char inOutArg[5];			// for device in/out
	char strArg1[15];			// arg 1 descriptor, up to 12 chars
	int intArg2;				// cycles or memory, assumes 4 byte int
	int intArg3;				// memory, assumes 4 byte int
								//   also non/premption indicator
	double opEndTime;			// size of time string returned from accessTimer
	struct OpCodeType *nextNode;
								 // pointer to next node as needed
   } OpCodeType;

typedef enum 
   {
	CMD_STR_LEN = 5,
	IO_ARG_STR_LEN = 5,
	STR_ARG_LEN = 15
   } OpCodeArrayCapacity;





	

	 
	   

		

#endif // DATATYPES_H