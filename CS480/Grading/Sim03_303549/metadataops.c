#include "metadataops.h"

//returns full metadata
bool getMetaData( const char *fileName,
                        OpCodeType **opCodeDataHead, char *endStateMsg )
    {
        int accessResult, startCount = 0, endCount = 0;

        const char READ_ONLY_FLAG[] = "r";

        char dataBuffer[ MAX_STR_LEN ];
        bool returnState = true;
        OpCodeType *newNodePtr;
        OpCodeType *localHeadPtr = NULL;
        FILE *fileAccessPtr;

        *opCodeDataHead = NULL;

        copyString( endStateMsg, "Metadata file upload successful" );

        fileAccessPtr = fopen( fileName, READ_ONLY_FLAG );

        if( fileAccessPtr == NULL )
            {
                copyString( endStateMsg, "Metadata File access error" );
                return false;
            }

        if( !getStringToDelimiter( fileAccessPtr, COLON, dataBuffer )
            || compareString(dataBuffer,
                    "Start Program Meta-Data Code") != STR_EQ )
            {
                fclose(fileAccessPtr);

                copyString( endStateMsg, "Corrupt metadata leader line error" );

                return false;
            }

            newNodePtr = ( OpCodeType * )malloc( sizeof (OpCodeType ) );

            accessResult = getOpCommand( fileAccessPtr, newNodePtr );

            startCount = updateStartCount( startCount, newNodePtr->strArg1 );
            endCount = updateEndCount( endCount, newNodePtr->strArg1 );

            if( accessResult != COMPLETE_OPCMD_FOUND_MSG )
                {
                    fclose( fileAccessPtr );

                    *opCodeDataHead = clearMetaDataList( localHeadPtr );

                    free( newNodePtr );

                    copyString( endStateMsg, "Metadata incomplete first op command found" );

                    return false;
                }

            while ( accessResult == COMPLETE_OPCMD_FOUND_MSG )
            {
                localHeadPtr = addNode( localHeadPtr, newNodePtr );

                accessResult = getOpCommand( fileAccessPtr, newNodePtr );

                startCount = updateStartCount( startCount, newNodePtr->strArg1 );
                endCount = updateEndCount( endCount, newNodePtr->strArg1 );
            }

            if( accessResult == LAST_OPCMD_FOUND_MSG )
                {
                    if( startCount == endCount )
                        {
                            localHeadPtr = addNode( localHeadPtr, newNodePtr );

                            accessResult = NO_ACCESS_ERR;

                            if( !getStringToDelimiter( fileAccessPtr, PERIOD, dataBuffer )
                                || compareString( dataBuffer, "End Program Meta-Data Code" )
                                            != STR_EQ)
                                {
                                    accessResult = MD_CORRUPT_DESCRIPTOR_ERR;

                                    copyString( endStateMsg, "Metadata corrupted descriptor error" );
                                }
                        }

                    else
                        {
                            fclose( fileAccessPtr );

                            *opCodeDataHead = clearMetaDataList ( localHeadPtr );

                            free( newNodePtr );

                            accessResult = UNBALANCED_START_END_ERR;

                            copyString( endStateMsg,
                                "Unbalanced start and end arguments in metadata" );

                            return false;
                        }
                }
            else
                {
                    copyString( endStateMsg, "Corrupted metadata op code" );

                    returnState = false;
                }
            

        if( accessResult != NO_ACCESS_ERR )
            {
                //clear op command list
                localHeadPtr = clearMetaDataList( localHeadPtr );
            }

        fclose( fileAccessPtr );

        free( newNodePtr );

        *opCodeDataHead = localHeadPtr;

        return returnState;

        return false;
    }

//removes all data from metadata
OpCodeType *clearMetaDataList( OpCodeType *localPtr )
    {
        if( localPtr != NULL )
            {
                clearMetaDataList( localPtr->nextNode );

                free( localPtr );

                localPtr = NULL;
            }
        return NULL;
    }

//displays metadata to user
void displayMetaData( const OpCodeType *localPtr )
    {
        printf( "Meta-Data File Display\n" );
        printf( "----------------------\n\n");

        while ( localPtr != NULL )
        {
            printf( "Op Code: " );

            printf( "/pid: %d", localPtr->pid);

            printf("/cmd: %s", localPtr->command);

            if( compareString( localPtr->command, "dev")  ==STR_EQ )
                {
                    printf( "/io: %s", localPtr->inOutArg );
                }
            
            else
                {
                    printf("/io: NA" );
                }
            
            printf( "\n\t /arg 1: %s", localPtr->strArg1 );

            printf( "/arg 2: %d", localPtr->intArg2 );

            printf( "/arg 3: %d", localPtr->intArg3 );

            printf( "/op end time: %8.6f", localPtr->opEndTime);

            printf( "\n\n" );

            localPtr = localPtr->nextNode;
        }
        
    }

//add node to end of opcode linked list
OpCodeType *addNode( OpCodeType *localPtr, OpCodeType *newNode )
    {
        if( localPtr == NULL )
            {
                localPtr = (OpCodeType *)malloc(sizeof( OpCodeType ));

                localPtr->pid = newNode->pid;
                copyString( localPtr->command, newNode->command );
                copyString( localPtr->inOutArg, newNode->inOutArg );
                copyString( localPtr->strArg1, newNode->strArg1 );
                localPtr->intArg2 = newNode->intArg2;
                localPtr->intArg3 = newNode->intArg3;
                localPtr->opEndTime = newNode->opEndTime;

                localPtr->nextNode = NULL;

                return localPtr;
            }

            //assume end of list not yet found
            localPtr->nextNode = addNode( localPtr->nextNode, newNode );

            return localPtr;
    }

//interprets command string input from metadata file
int getCommand( char *cmd, const char *inputStr, int index )
    {
        int lengthOfCommand = 3;

        while ( index < lengthOfCommand )
        {
            cmd[ index ] = inputStr[ index ];

            index++;

            cmd[index] = NULL_CHAR;
        }

        return index;   
    }

//grabs op command from metadata file
OpCodeMessages getOpCommand( FILE *filePtr, OpCodeType *inData )
    {
        const int MAX_CMD_LENGTH = 5;
        const MAX_ARG_STR_LENGTH = 15;

        int numBuffer = 0;
        char strBuffer[ STD_STR_LEN ];
        char cmdBuffer[ MAX_ARG_STR_LENGTH ];
        char argStrBuffer[ MAX_ARG_STR_LENGTH ];
        int runningStringIndex = 0;
        bool arg2FailureFlag = false;
        bool arg3FailureFlag = false;

        if( getStringToDelimiter( filePtr, SEMICOLON, strBuffer ) )
            {
                runningStringIndex = getCommand( cmdBuffer,
                        strBuffer, runningStringIndex );

                copyString( inData->command, cmdBuffer );
            }

        else 
            {
                inData = NULL;

                return OPCMD_ACCESS_ERR;
            }

        if( !verifyValidCommand( cmdBuffer ) )
            {
                return CORRUPT_OPCMD_ERR;
            }

        inData->pid = 0;
        inData->inOutArg[ 0 ] = NULL_CHAR;
        inData->intArg2 = 0;
        inData->intArg3 = 0;
        inData->opEndTime = 0.0;
        inData->nextNode = NULL;

        if( compareString(cmdBuffer, "dev" ) == STR_EQ )
            {
                runningStringIndex = getStringArg( argStrBuffer, 
                        strBuffer, runningStringIndex );

                copyString( inData->inOutArg, argStrBuffer );

                if( compareString(argStrBuffer, "in" ) != STR_EQ &&
                    compareString( argStrBuffer, "out") != STR_EQ )
                    {
                        return CORRUPT_OPCMD_ARG_ERR;
                    }
            }

        runningStringIndex = getStringArg( argStrBuffer, 
                strBuffer, runningStringIndex );

        copyString( inData->strArg1, argStrBuffer );

        if( !verifyFirstStringArg( argStrBuffer ) )
            {
                return CORRUPT_OPCMD_ARG_ERR;
            }


        if( compareString( inData->command, "sys" ) == STR_EQ
            &&compareString( inData->strArg1, "end" ) ==STR_EQ )
            {
                return LAST_OPCMD_FOUND_MSG;
            }

        if( compareString(inData->command, "app") == STR_EQ 
                && compareString(inData->strArg1, "start") == STR_EQ )
                {
                    runningStringIndex = getNumberArg( &numBuffer,
                            strBuffer, runningStringIndex );

                    if( numBuffer <= BAD_ARG_VAL )
                        {
                            arg2FailureFlag = true;
                        }

                    inData->intArg2 = numBuffer;
                }

        else if( compareString( inData->command, "cpu" ) == STR_EQ )
            {
                runningStringIndex = getNumberArg( &numBuffer, 
                        strBuffer, runningStringIndex );

                if( numBuffer <= BAD_ARG_VAL )
                    {
                        arg2FailureFlag = true;
                    }

                inData->intArg2 = numBuffer;
            }

        else if( compareString( inData->command, "dev" ) ==STR_EQ )
            {
                runningStringIndex = getNumberArg( &numBuffer, 
                            strBuffer, runningStringIndex );

                if( numBuffer <= BAD_ARG_VAL )
                    {
                        arg2FailureFlag = true;
                    }

                inData->intArg2 = numBuffer;
            }

        else if( compareString( inData->command, "mem" ) == STR_EQ )
            {
                runningStringIndex = getNumberArg( &numBuffer,
                            strBuffer, runningStringIndex );
                if( numBuffer <= BAD_ARG_VAL )
                    {
                        arg2FailureFlag = true;
                    }

                inData->intArg2 = numBuffer;

                runningStringIndex = getNumberArg( &numBuffer,
                            strBuffer, runningStringIndex );
                
                if( numBuffer <= BAD_ARG_VAL )
                    {
                        arg3FailureFlag = true;
                    }

                inData->intArg3 = numBuffer;
            }

        if( arg2FailureFlag || arg3FailureFlag )
            {
                return CORRUPT_OPCMD_ARG_ERR;
            }

        return COMPLETE_OPCMD_FOUND_MSG;
    }

//pulls number from input
int getNumberArg( int *number, const char *inputStr, int index )
    {
        bool foundDigit = false;
        *number = 0;
        int multiplier = 1;

        while (inputStr[ index ] == SPACE || inputStr[ index ] == COMMA )
            {
                index++;
            }

        while( isDigit(inputStr [ index ] ) == true 
            && inputStr[ index ] != NULL_CHAR )
            {
                (*number) = (*number) * multiplier + inputStr[ index ] - '0';

                foundDigit = true;

                //increment digit and add multiplier
                index++; multiplier = 10;
            }

        if( !foundDigit )
            {
                *number = BAD_ARG_VAL;
            }

        return index;
    }

//grabs string argument from input string
int getStringArg( char *strArg, const char *inputStr, int index )
    {
        int localIndex = 0;

        while( inputStr[ index ] == SPACE || inputStr[ index ] == COMMA )
            {
                index++;
            }

        while ( inputStr[ index ] != COMMA && inputStr[ index ] != NULL_CHAR )
            {
                strArg[ localIndex ] = inputStr[ index ];

                index++; localIndex++;

                strArg[ localIndex ] = NULL_CHAR;
            }

        return index;
        
    }

//tests if character is a digit
bool isDigit( char testChar )
    {
        return ( testChar >= '0' && testChar <= '9' );
    }

//updates the number of times a program has ended
int updateEndCount( int count, const char *opString )
    {
        if( compareString( opString, "end" ) == STR_EQ )
            {
                return count + 1;
            }

        return count;
    }

//updates the number of times an app has started
int updateStartCount( int count, const char *opString )
    {
        if( compareString( opString, "start" ) == STR_EQ )
            {
                return count + 1;
            }
        
        return count;
    }

//ensures valid string argument
bool verifyFirstStringArg( const char *strArg )
    {
        return (compareString (strArg, "access" ) == STR_EQ 
            || compareString( strArg, "allocate" ) == STR_EQ
            || compareString( strArg, "end" ) == STR_EQ
            || compareString( strArg, "ethernet" ) == STR_EQ
            || compareString( strArg, "hard drive" ) == STR_EQ
            || compareString( strArg, "keyboard" ) == STR_EQ
            || compareString( strArg, "monitor" ) == STR_EQ
            || compareString( strArg, "printer" ) == STR_EQ
            || compareString( strArg, "process" ) == STR_EQ
            || compareString( strArg, "serial" ) == STR_EQ
            || compareString( strArg, "sound signal" ) == STR_EQ
            || compareString( strArg, "start" ) == STR_EQ
            || compareString( strArg, "usb" ) == STR_EQ
            || compareString( strArg, "video signal" ) == STR_EQ);
    }

//ensures command is valid
bool verifyValidCommand( char *testCmd )
    {
        return (
            compareString( testCmd, "sys" ) ==STR_EQ
            || compareString( testCmd, "app" ) ==STR_EQ
            || compareString( testCmd, "cpu" ) ==STR_EQ
            || compareString( testCmd, "mem" ) ==STR_EQ
            || compareString( testCmd, "dev" ) ==STR_EQ
        );
    }