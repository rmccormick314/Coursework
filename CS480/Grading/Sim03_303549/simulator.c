#include "simulator.h"

void runSim( ConfigDataType *configDataPtr, OpCodeType *metaDataPtr )
	{
		printf("Simulator Run\n");
		printf("-------------\n\n");

		//create pcb structs

		int bufferLen;

		const int MAX_PROCS = 30;

		const char *sysCode = "sys";
		const char *startStr = "start";
		const char *devStr = "dev";

		char outputStringList[MAX_LINES][MAX_STR_LEN]; //= malloc( sizeof( char[MAX_STR_LEN] ) * MAX_LINES );

		char *timeStr = malloc( sizeof(char) * MAX_STR_LEN );
		char *strBuffer = malloc( sizeof(char) * MAX_STR_LEN );

		OpCodeType *currentOpCode = metaDataPtr;
		PCBType *PCBHead = malloc( sizeof( PCBType ) );
		PCBType *currentPCB = PCBHead;
		MemBlockType *memHead = NULL;

		int currPID = 0;

		//must be fixed to have a list of op codes
		//populate pcb list
		while( currentOpCode != NULL )
			{
				currentPCB->opCodes = malloc( sizeof(OpCodeType *) * MAX_PROCS );
				currentPCB->pid = currPID;
				currentPCB->numOpCodes = 0;
				currentPCB->timeRemaining = 0;

				int currOpCodeIndex = 0;

				if(compareString(currentOpCode->command, sysCode) != STR_EQ)
					{
						do
							{
								currentPCB->opCodes[currOpCodeIndex] = currentOpCode;
								currentOpCode->pid = currPID;

								currentPCB->numOpCodes++;
								if( compareString(currentOpCode->command, devStr) == STR_EQ )
									{
										currentPCB->timeRemaining += configDataPtr->ioCycleRate * currentOpCode->intArg2;
									}
								else
									{
										currentPCB->timeRemaining += configDataPtr->proCycleRate * currentOpCode->intArg2;
									}
								currentOpCode = currentOpCode->nextNode;
								currOpCodeIndex++;
							}
						while( currentOpCode->nextNode != NULL && compareString(currentOpCode->strArg1, startStr) != STR_EQ );
						
						currPID++;
						currentPCB->procState = NEW_STATE;
						if( currentOpCode->nextNode != NULL )
							{
								currentPCB->nextPCB = malloc( sizeof( PCBType ) );
								currentPCB = currentPCB->nextPCB;
							}
						currentOpCode = currentOpCode->nextNode;
						currentPCB->nextPCB = NULL;
					}
		
				else
					{
						currentOpCode = currentOpCode->nextNode;
					}
			}

		currentPCB = PCBHead;

		int numLines = 0;
		currPID = 0;
		accessTimer(ZERO_TIMER, timeStr);
		double currTime = 0.0;

		//set all procesess to ready
		while( currentPCB != NULL )
			{
				if( currentPCB->pid == currPID )
					{
						//print set to ready
						currTime = accessTimer( LAP_TIMER, timeStr );
						if( configDataPtr->logToCode == LOGTO_FILE_CODE || configDataPtr->logToCode == LOGTO_BOTH_CODE)
							{
								sprintf( strBuffer, "%f, OS: Process %d set to READY state from NEW state\n", currTime, currPID);
								bufferLen = getStringLength(strBuffer);
								//outputStringList[numLines] = malloc( sizeof(char) * bufferLen );
								copyString(outputStringList[numLines], strBuffer);
								numLines++;
							}
						if( configDataPtr->logToCode == LOGTO_BOTH_CODE || configDataPtr->logToCode == LOGTO_MONITOR_CODE )
							{
								printf("%f, OS: Process %d set to READY state from NEW state\n", currTime, currPID);
							}
						currPID++;
					}
				currentPCB->procState = READY_STATE;
				currentPCB = currentPCB->nextPCB;
			}

		//notify of output
		if( configDataPtr->logToCode == LOGTO_FILE_CODE )
			{
				printf("Sim running, logging to file\n");
			}

		//start sim timer
		PCBType shortJob;

		if( configDataPtr->cpuSchedCode == CPU_SCHED_FCFS_N_CODE )
			{
				currentPCB = PCBHead;
			}
		else if( configDataPtr->cpuSchedCode == CPU_SCHED_SJF_N_CODE )
			{
				shortJob = shortestJob( &PCBHead );
				currentPCB = &shortJob;
			}
		else
			{
				//default to fcfs
				printf( "Unsupported CPU Sched Code. Defaulting to FCFS-N\n");
				configDataPtr->cpuSchedCode = CPU_SCHED_FCFS_N_CODE;
				currentPCB = PCBHead;
			}

		//iterate through all pcbs
		while( currentPCB != NULL )
			{
				bool test = processPCB( currentPCB, timeStr, outputStringList, configDataPtr, &numLines, &memHead );
				if( !test )
					{
						//set process to exit
						if( configDataPtr->logToCode == LOGTO_BOTH_CODE || configDataPtr->logToCode == LOGTO_MONITOR_CODE )
							{
								currTime = accessTimer( LAP_TIMER, timeStr );
								printf("\t%f, OS: Process %d set to EXIT\n", currTime, currentPCB->pid);
							}
					}

				clearMemBlockList( memHead ); //no preemptive, can free all memory;
				memHead = NULL;

				if( configDataPtr->cpuSchedCode == CPU_SCHED_FCFS_N_CODE )
					{
						currentPCB = currentPCB->nextPCB;
					}
				else
					{
						shortJob = shortestJob( &PCBHead );
						currentPCB = &shortJob;
					}
			}
		currTime = accessTimer( STOP_TIMER, timeStr );
		if( configDataPtr->logToCode == LOGTO_BOTH_CODE || configDataPtr->logToCode == LOGTO_FILE_CODE )
			{
				sprintf( strBuffer, "Sim complete, total runtime: %f\n", currTime);
				bufferLen = getStringLength(strBuffer);
				//outputStringList[numLines] = malloc( sizeof(char) * bufferLen );
				copyString(outputStringList[numLines], strBuffer);
				numLines++;
			}
		if( configDataPtr->logToCode == LOGTO_BOTH_CODE || configDataPtr->logToCode == LOGTO_MONITOR_CODE)
			{
				printf( strBuffer, "Sim complete, total runtime: %f", currTime);
			}
		
		//output to file
		if( configDataPtr->logToCode == LOGTO_BOTH_CODE || configDataPtr->logToCode == LOGTO_FILE_CODE )
			{
				bool writeSuccess;
				writeSuccess = writeOutputToFile( numLines, outputStringList,  configDataPtr->logToFileName, configDataPtr );

				if( writeSuccess )
					{
						//process success
						printf( "Output file successfully written, may be found at %s\n", configDataPtr->logToFileName );
					}
				else
					{
						//log error
						printf( "FILE: %s, could not be opened for output\n", configDataPtr->logToFileName );
					}
			}
		
		//notify sim run complete
		clearMetaDataList(metaDataPtr);
		PCBHead = clearPCBList( PCBHead );
		currentPCB = NULL;
		free( timeStr );
		timeStr = NULL;
		free( strBuffer );
		strBuffer = NULL;
		memHead = clearMemBlockList( memHead );

		//int index = 0;
		//while ( index < MAX_LINES )
		//	{
		//		free(outputStringList[index]);
		//		//outputStringList[index] = NULL;
		//		index++;
		//	}
		//free( outputStringList );
		currentOpCode = NULL;
		currentPCB = NULL;
		
	}

bool processPCB( PCBType *currentPCB, char *timeStr, char outputStringList[MAX_LINES][MAX_STR_LEN], ConfigDataType *configDataPtr, int *numLines, MemBlockType **memHead )
	{
		float currTime = 0.0f;
		const char *endString = "end";
		const char *devStr = "dev";
		const char *memStr = "mem";
		const char *allocStr = "allocate";
		char *strBuffer = malloc( sizeof(char) * MAX_STR_LEN );
		int bufferLen = 0;	
				//set pcb to running
		if( configDataPtr->logToCode == LOGTO_BOTH_CODE || configDataPtr->logToCode == LOGTO_MONITOR_CODE )
			{
				//print separator
				printf("\t--------------------------------------------------\n");
				printf( "\t%f: Process %d selected, Time remaining: %dms\n", currTime, currentPCB->pid, currentPCB->timeRemaining );	
				currTime = accessTimer( LAP_TIMER, timeStr );
				if( configDataPtr->logToCode == LOGTO_BOTH_CODE )
					{
						sprintf( strBuffer, "\t%f: Process %d selected, Time remaining: %dms\n", currTime, currentPCB->pid, currentPCB->timeRemaining);
						bufferLen = getStringLength(strBuffer);
						//outputStringList[*numLines] = malloc( sizeof(char) * bufferLen );
						copyString(outputStringList[*numLines], strBuffer);
						(*numLines)++;
					}
				currTime = accessTimer( LAP_TIMER, timeStr );
				printf( "\t%f: OS, Process %d set from READY to RUNNING\n\n", currTime, currentPCB->pid);
				if( configDataPtr->logToCode == LOGTO_BOTH_CODE )
					{
						sprintf( strBuffer, "\t%f: OS, Process %d set from READY to RUNNING\n\n", currTime, currentPCB->pid);
						bufferLen = getStringLength(strBuffer);
						//outputStringList[*numLines] = malloc( sizeof(char) * bufferLen );
						copyString(outputStringList[*numLines], strBuffer);
						(*numLines)++;
					}
				//output state to monitor
			}
		else if (configDataPtr->logToCode == LOGTO_FILE_CODE )
			{
				//add state to outputStringList
				//outputStringList[*numLines] = "\t--------------------------------------------------\n";
				//(*numLines)++;	
				currTime = accessTimer( LAP_TIMER, timeStr );
				sprintf( strBuffer, "\t%f: Process %d selected, Time remaining: %dms\n", currTime, currentPCB->pid, currentPCB->timeRemaining );
				bufferLen = getStringLength(strBuffer);
				//outputStringList[*numLines] = malloc( sizeof(char) * bufferLen );
				copyString(outputStringList[*numLines], strBuffer);
				(*numLines)++;	
				currTime = accessTimer( LAP_TIMER, timeStr );
				sprintf( strBuffer, "\t%f: OS, Process %d set from READY to RUNNING\n\n", currTime, currentPCB->pid);
				bufferLen = getStringLength(strBuffer);
				//outputStringList[*numLines] = malloc( sizeof(char) * bufferLen );
				copyString(outputStringList[*numLines], strBuffer);
				(*numLines)++;	
				currTime = accessTimer( LAP_TIMER, timeStr );
				sprintf( strBuffer, "\t%f: OS, Process %d set from READY to RUNNING\n\n", currTime, currentPCB->pid);
				bufferLen = getStringLength(strBuffer);
				//outputStringList[*numLines] = malloc( sizeof(char) * bufferLen );
				copyString(outputStringList[*numLines], strBuffer);
				(*numLines)++;
			}	
		int opIndex = 0;
		while( opIndex < currentPCB->numOpCodes)
			{
				OpCodeType *inOpCode = currentPCB->opCodes[opIndex];
				currTime = accessTimer( LAP_TIMER, timeStr );	
				if( compareString(inOpCode->strArg1, endString) == STR_EQ )
					{
						//
						if( configDataPtr->logToCode == LOGTO_BOTH_CODE || configDataPtr->logToCode == LOGTO_MONITOR_CODE)
							{
								printf("\t%f, OS: Process %d ended\n", currTime, currentPCB->pid);
							}
						if( configDataPtr->logToCode == LOGTO_BOTH_CODE || configDataPtr->logToCode == LOGTO_FILE_CODE)
							{
								sprintf( strBuffer,"\t%f, OS: Process %d ended\n", currTime, currentPCB->pid);
								bufferLen = getStringLength(strBuffer);
								//outputStringList[*numLines] = malloc( sizeof(char) * bufferLen );
								copyString(outputStringList[*numLines], strBuffer);
								(*numLines)++;
							}
					}
				else
					{
						if( compareString(inOpCode->command, memStr) == STR_EQ )
							{
								if( compareString(inOpCode->strArg1, allocStr ) == STR_EQ )
									{
										if( (*memHead) == NULL )
											{
												(*memHead) = malloc( sizeof( MemBlockType ) );
												(*memHead)->nextBlock = NULL;
												if( inOpCode->intArg3 < configDataPtr->memAvailable )
													{
														(*memHead)->pid = currentPCB->pid;
														(*memHead)->vStart = inOpCode->intArg2;
														(*memHead)->vEnd = inOpCode->intArg2 + inOpCode->intArg3 - 1;
														(*memHead)->pStart = 0;
														(*memHead)->pEnd = inOpCode->intArg3 - 1;
														if( configDataPtr->logToCode == LOGTO_BOTH_CODE || configDataPtr->logToCode == LOGTO_MONITOR_CODE )
															{
																printf( "\tOS: Memory Allocated %d: %d[%d ~ %d]%d\n", currentPCB->pid,
																	(*memHead)->pStart, (*memHead)->vStart, (*memHead)->vEnd, (*memHead)->pEnd );
															}
													}
												else
													{
														if( configDataPtr->logToCode == LOGTO_BOTH_CODE || configDataPtr->logToCode == LOGTO_MONITOR_CODE )
															{
																printf( "OS: Segmentation Fault in process %d\n", currentPCB->pid );
															}
														return false;
													}
											}
										else
											{
												MemBlockType *currBlock = (*memHead);
												while( currBlock->nextBlock != NULL )
													{
														currBlock = currBlock->nextBlock;
													}
												

												if( (currBlock->pEnd + inOpCode->intArg3) >= configDataPtr->memAvailable )
													{
														//seg fault
														if( configDataPtr->logToCode == LOGTO_BOTH_CODE || configDataPtr->logToCode == LOGTO_MONITOR_CODE )
															{
																printf( "OS: Segmentation Fault in process %d\n", currentPCB->pid );
															}
														return false;
													}
												else
													{
														//need to check all pcbs to make sure ther is no virtual block overlap
														MemBlockType *checkBlock = (*memHead);
														int tempVStart = inOpCode->intArg2;
														int tempVEnd = tempVStart + inOpCode->intArg3 - 1;
														while( checkBlock != NULL )
															{
																if( checkBlock->pid == currentPCB->pid )
																	{
																		if( ((checkBlock->vStart <= tempVStart) && (checkBlock->vEnd >= tempVStart)) ||
																			((checkBlock->vStart <= tempVEnd) && (checkBlock->vEnd >= tempVEnd)) )
																			{
																				if( configDataPtr->logToCode == LOGTO_BOTH_CODE || configDataPtr->logToCode == LOGTO_MONITOR_CODE )
																					{
																						printf( "\tSegmentation Fault in process %d\n", currentPCB->pid );
																					}
																				return false;
																			}
																	}
																checkBlock = checkBlock->nextBlock;
															}
														currBlock->nextBlock = malloc( sizeof( MemBlockType ) );
														currBlock->nextBlock->pid = currentPCB->pid;
														currBlock->nextBlock->pStart = currBlock->pEnd + 1;
														currBlock->nextBlock->pEnd = currBlock->pEnd + inOpCode->intArg3;
														currBlock->nextBlock->vStart = tempVStart;
														currBlock->nextBlock->vEnd = tempVEnd;
														currBlock->nextBlock->nextBlock = NULL;

														currBlock = currBlock->nextBlock;

														if( configDataPtr->logToCode == LOGTO_BOTH_CODE || configDataPtr->logToCode == LOGTO_MONITOR_CODE )
															{
																printf( "\tOS: Memory Allocated %d: %d[%d ~ %d]%d\n", currentPCB->pid,
																	currBlock->pStart, currBlock->vStart, currBlock->vEnd, currBlock->pEnd );
															}
													}
											}
									}
								else //access memory
									{
										MemBlockType *currBlock = (*memHead);
										bool flag = false;
										
										while( currBlock != NULL )
											{
												if( currBlock->pid == currentPCB->pid )
													{
														//check for memory to free
														if( (currBlock->vStart <= inOpCode->intArg2) && (currBlock->vEnd >= (inOpCode->intArg2 + 
															inOpCode->intArg3 - 1 )) )
															{
																int vStart = inOpCode->intArg2;
																int vEnd = inOpCode->intArg2 + inOpCode->intArg3 - 1;
																int pStart = currBlock->pStart + (vStart - currBlock->vStart);
																int pEnd = currBlock->pStart + (vEnd - currBlock->vStart);
																printf("\tOS: Memory Access P: %d %d[%d ~ %d]%d\n", currentPCB->pid, pStart, vStart, vEnd, pEnd);
																flag = true;
																//allow for intermediate access
															}
													}
												currBlock = currBlock->nextBlock;
											}
										if( !flag )
											{
												//memory was not freed, segmentation fault occured
												printf( "\tSegmentation Fault in process %d\n", currentPCB->pid );
												return false;
											}
									}
							}
						else
							{
								if( configDataPtr->logToCode == LOGTO_BOTH_CODE || configDataPtr->logToCode == LOGTO_MONITOR_CODE)
									{
										printf("\t%f, Process: %d, %s operation start\n", currTime, currentPCB->pid, inOpCode->command);
									}
								if( configDataPtr->logToCode == LOGTO_BOTH_CODE || configDataPtr->logToCode == LOGTO_FILE_CODE)
									{
										sprintf( strBuffer,"\t%f, Process: %d, %s operation start\n", currTime, currentPCB->pid, inOpCode->command);
										bufferLen = getStringLength(strBuffer);
										//outputStringList[*numLines] = malloc( sizeof(char) * bufferLen );
										copyString(outputStringList[*numLines], strBuffer);
										(*numLines)++;
									}	
								int msec = 0;
								//do pthread here
								if( compareString(inOpCode->command, devStr) == STR_EQ )
									{
										msec = configDataPtr->ioCycleRate * inOpCode->intArg2;
									}
								else
									{
										msec = configDataPtr->proCycleRate * inOpCode->intArg2;
									}
								pthread_t opThread;	
								pthread_create(&opThread, NULL, runOp, (void *)&msec );
								pthread_join(opThread, NULL );	
								if( configDataPtr->logToCode == LOGTO_BOTH_CODE || configDataPtr->logToCode == LOGTO_MONITOR_CODE)
									{
										printf("\t%f, Process: %d, %s operation end\n", currTime, currentPCB->pid, inOpCode->strArg1);
									}
								if( configDataPtr->logToCode == LOGTO_BOTH_CODE || configDataPtr->logToCode == LOGTO_FILE_CODE)
									{
										sprintf( strBuffer,"\t%f, Process: %d, %s operation end\n", currTime, currentPCB->pid, inOpCode->strArg1);
										bufferLen = getStringLength(strBuffer);
										//outputStringList[*numLines] = malloc( sizeof(char) * bufferLen );
										copyString(outputStringList[*numLines], strBuffer);
										(*numLines)++;
									}
							}	
					}
				opIndex++;
			}	
		//set pcb to exit if app end
		currTime = accessTimer( LAP_TIMER, timeStr );
		if( configDataPtr->logToCode == LOGTO_BOTH_CODE || configDataPtr->logToCode == LOGTO_MONITOR_CODE )
			{
				printf( "\t--------------------------------------------------\n" );
				printf( "\t%f, OS: Process %d set to EXIT\n", currTime, currentPCB->pid);
				//output state to monitor
			}
		else if ( configDataPtr->logToCode == LOGTO_BOTH_CODE || configDataPtr->logToCode == LOGTO_FILE_CODE )
			{
				//outputStringList[*numLines] = "\t--------------------------------------------------\n";
				//(*numLines)++;	
				sprintf( strBuffer, "\t%f, OS: Process %d set to EXIT\n", currTime, currentPCB->pid);
				bufferLen = getStringLength(strBuffer);
				//outputStringList[*numLines] = malloc( sizeof(char) * bufferLen );
				copyString(outputStringList[*numLines], strBuffer);
				(*numLines)++;
			}
		free(strBuffer);
		//move to next PCB
		return true;
	}

bool writeOutputToFile(int numLines, char lines[MAX_LINES][MAX_STR_LEN], char *fileName, ConfigDataType *configData )
	{
		const char WRITE_FLAG[] = "w";

		FILE *file = fopen( fileName, WRITE_FLAG );

		//write config data
		char displayString[ STD_STR_LEN ];

		fprintf(file, "Config File Display\n");
        fprintf(file, "-------------------\n");
        fprintf(file, "Version               : %3.2f\n", configData->version );
        fprintf(file, "Program file name     : %s\n", configData->metaDataFileName );
        configCodeToString( configData->cpuSchedCode, displayString );
        fprintf(file, "CPU schedule selection: %s\n", displayString );
        fprintf(file, "Quantum time          : %d\n", configData->quantumCycles );
        fprintf(file, "Memory Display        : " );
        if( configData->memDisplay )
            {
                printf( "On\n" );
            }
        else
            {
                printf( "Off\n" );
            }
        fprintf(file, "Memory Available      : %d\n", configData->memAvailable );
        fprintf(file, "Process cycle rate    : %d\n", configData->proCycleRate );
        fprintf(file, "I/O cycle rate        : %d\n", configData->ioCycleRate );
        configCodeToString( configData->logToCode, displayString );
        fprintf(file, "Log to selection      : %s\n", displayString );
        fprintf(file, "Log file name         : %s\n", configData->logToFileName );
		fprintf(file, "--------------------------------------------\n\n");


		if( file != NULL )
			{
				int index;
				for(index = 0; index < numLines; index++)
					{
						fprintf( file, "%s", lines[index] );
					}
				return true;
			}
		else
			{
				return false;
			}
	}

PCBType *clearPCBList( PCBType *localPtr )
	{
		if( localPtr != NULL )
			{
				clearPCBList( localPtr->nextPCB );

				free(localPtr->opCodes);

				free( localPtr );
				


				localPtr = NULL;
			}
		return NULL;
	}

MemBlockType *clearMemBlockList( MemBlockType *head )
	{
		if( head != NULL )
			{
				clearMemBlockList( head->nextBlock );

				free( head );

				head = NULL;
			}

		return NULL;
	}

PCBType shortestJob( PCBType **head ) 
	{
		PCBType *currShortest = *head;
		PCBType *currPCB = (*head)->nextPCB;

		while( currPCB != NULL ) 
			{
				if( currShortest->timeRemaining > currPCB->timeRemaining )
					{
						currShortest = currPCB;
					}
				currPCB = currPCB->nextPCB;
			}
		PCBType ret;
		ret.opCodes = currShortest->opCodes;
		ret.timeRemaining = currShortest->timeRemaining;
		ret.pid = currShortest->timeRemaining;
		ret.numOpCodes = currShortest->numOpCodes;
		ret.procState = currShortest->procState;

		removePCB( head, currShortest );

		return ret;
	}

PCBType *removePCB( PCBType **head, PCBType *pcb )
	{
		PCBType *tmp = *head;

		if( tmp == pcb )
			{
				(*head) = (*head)->nextPCB;
				free( tmp );
				tmp = NULL;
			}
		else
			{
				while( tmp->nextPCB != NULL )
					{
						if( tmp->nextPCB == pcb )
							{
								PCBType *del = tmp->nextPCB;
								tmp->nextPCB = tmp->nextPCB->nextPCB;
								free(del);
								del = NULL;
								return del;
							}
					}
			}
		return NULL;
	}

bool removeMemBlock( MemBlockType *memBlock, MemBlockType **memHead )
	{
		if( memBlock == (*memHead) )
			{
				MemBlockType *tmp = *memHead;
				(*memHead) = (*memHead)->nextBlock;
				free(tmp);
				tmp = NULL;
				return tmp;
			}
		else
			{
				MemBlockType *currBlock = (*memHead);
				while( currBlock->nextBlock != NULL )
					{
						if(currBlock->nextBlock == memBlock)
							{
								MemBlockType *del = currBlock->nextBlock;
								currBlock->nextBlock = currBlock->nextBlock->nextBlock;
								free(del);
								del = NULL;
								return del;
							}
					}
			}
		return NULL;
	}

void *runOp( void *args )
	{
		int msec = *((int *)args);

		runTimer(msec);

		return NULL;
	}