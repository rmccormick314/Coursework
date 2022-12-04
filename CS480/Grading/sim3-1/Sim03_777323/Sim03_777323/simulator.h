// Luke Frazer
// Used educational coding vidoes from Michael Leverington for this assignment

// protect from multiple compiling
#ifndef SIMULATOR_H
#define SIMULATOR_H

// header files
#include "OS_SimDriver.h"
#include "StandardConstants.h"
#include "datatypes.h"

// create enum constants
typedef enum 
	{
	REGISTER_SIZE = 10,
	OPEN_FILE_SIZE = 10
	} PCBTypeCapacity;

// Process control block data structure
typedef struct PCBType
	{
	int pid;
	ProcessState procState;
	int progCounter;
	int memLimits;
	char cpuRegisters[REGISTER_SIZE];
	char listOpenFiles[OPEN_FILE_SIZE];
	} PCBType;

// memory management unit data structure
typedef struct MMUType
	{
	int memAvailable;
	int* memPtr;
	bool memDisplayLine;
	bool memDisplayOn;
	} MMUType;

// prototype functions for simulator
void runSim(ConfigDataType *configPtr, OpCodeType *metaDataMstrPtr);
PCBType getProcess(char line[], int processID);
OpCodeType getOpCode(char line[]);
bool checkSubString( char* checkString, char* subString);


#endif // SIMULATOR