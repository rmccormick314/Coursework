#ifndef SIM_H
#define SIM_H

#include "StringUtils.h"
#include <stdlib.h>
#include "StandardConstants.h"
#include <stdio.h>
#include "configops.h"
#include "metadataops.h"
#include "SimTimer.h"
#include <pthread.h>

typedef struct PCBType
	{
		OpCodeType **opCodes;
		int timeRemaining;
		int pid;
		int numOpCodes;
		ProcessState procState;
		struct PCBType *nextPCB;
	} PCBType;

typedef struct MemBlockType
	{
		int pid;
		int vStart;
		int vEnd;
		int pStart;
		int pEnd;
		struct MemBlockType *nextBlock;
	} MemBlockType;

void runSim( ConfigDataType *configDataPtr, OpCodeType *metaDataPtr );
bool writeOutputToFile(int numLines, char lines[MAX_LINES][MAX_STR_LEN], char *fileName, ConfigDataType *configData );
PCBType *clearPCBList( PCBType *PCBListHead );
void *runOp( void *args );
PCBType shortestJob( PCBType **head );
PCBType *removePCB( PCBType **head, PCBType *pcb );
bool processPCB( PCBType *currentPCB, char *timeStr, char outputStringList[MAX_LINES][MAX_STR_LEN], ConfigDataType *configDataPtr, int *numLines, MemBlockType **memHead );
bool removeMemBlock( MemBlockType *memBlock, MemBlockType **memHead);
MemBlockType *clearMemBlockList( MemBlockType *head );

#endif