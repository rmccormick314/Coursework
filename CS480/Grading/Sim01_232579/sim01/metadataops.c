#include "metadataops.h"

// locally used constant
const int BAD_ARG_VAL = -1002;

/*
Function Name: addNode
Algorithm: adds op command structure with data to a linked list
Precondition: linked list pointer assigned to null or one op command link,
	      struct pointer assigned to op command struct data
Postcondition: assigns new structure node to beginning of linked list
	       or and of established linked list
Exceptions: none
Notes: none
*/

OpCodeType *addNode(OpCodeType *localPtr, OpCodeType *newNode)
   {

   // check for local pointer assigned to null
   if( localPtr == NULL )
      {
	// access memory for new link/node
	   // function: malloc
	localPtr = (OpCodeType *) malloc(sizeof(OpCodeType));

 	// assign all three values to newly created node
	// assign next pointer to null
	   // function: copyString
	localPtr->pid = newNode->pid;
	copyString( localPtr->command, newNode->command );
	copyString( localPtr->inOutArg, newNode->inOutArg );
	copyString( localPtr->strArg1, newNode->strArg1 );
	localPtr->intArg2 = newNode->intArg2;
	localPtr->intArg3 = newNode->intArg3;
	localPtr->opEndTime = newNode->opEndTime;

	localPtr->nextNode = NULL;

	// return current local pointer
	return localPtr;

	}
    // assume end of list not found yet

    // assign recursive function to current's next link
	// function: addNode
    localPtr->nextNode = addNode( localPtr->nextNode, newNode );

    // return current local pointer
    return localPtr;

   }



/*
Function Name: clearMetaData
Algorithm: recursively iterates through op code linked list,
	   returns memory to OS from the bottom of the list upward
Precondition: linked list, with or without data
Postcondition: all node memory, if any, is returned to OS,
	       return pointer (head) is set to null
Exceptions: none
Notes: none
*/
OpCodeType *clearMetaDataList(OpCodeType *localPtr)
   {

   // check for local pointer not set to null (list not empty)
   if( localPtr != NULL)
      {

      // call recursive function with next pointer
	 // function: clearMetaDataList
      clearMetaDataList(localPtr->nextNode );

      // after recursive call, release memory to OS
	 // functioN: free
      free(localPtr);

      // set local pointer to null
      localPtr = NULL;

      }

   // return null to calling function
   return NULL;  

   }

/*
Function Name: displayMetaData
Algorithm: iterates through op code linked list,
	   displays op code data individually
Precondition: lined list, with or without data
	      (should not be called if no data)
Postcondition: displays all op codes in list
Exceptions: none
Notes: none
*/

void displayMetaData(OpCodeType *localPtr)
   {

    // display title, with underline
 	// function: printf
    printf("Meta-Data File Display\n");
    printf("......................\n\n");

    // loop to end of linked list
    while( localPtr != NULL )
       {
	// print Leader
	   // function: printf
	printf("Op Code: ");

        // print op code pid
	   // function: printf
	printf("/pid: %d", localPtr->pid);

	// print op code command
	   // function: printf
	printf("/cmd: %s", localPtr->command);

	// check for dev op command
	if( compareString( localPtr->command, "dev" ) == STR_EQ )
	   {

	   // print in/out parameter
	      // function: printf
	   printf("/io: %s", localPtr->inOutArg);
	
	   }

	// otherwise assume other than dev
	else
	   {

	   // print NA
	      // function: printf
	   printf("/io: NA");
	   }

	// print first string argument
	   // function: printf
	printf("\n\t /arg1: %s", localPtr->strArg1);

	// print first int argument 
           // function: printf
	printf("/arg 2: %d", localPtr->intArg2);

	// print second int argument
	   // function: printf
	printf("/arg 3: %d", localPtr->intArg3);

	// print op end time
	   // function: printf
	printf("/op end time: %8.6f", localPtr->opEndTime);

	// end line
	   // function: printf
	printf("\n\n");

	// assign local pointer to next node
	localPtr = localPtr->nextNode;

     // end loop across nodes
       }


   }

/*
Function Name: getCommand
Algorithm: gets first three letters of input string to get command
Precondition: provided starting index
Postcondition: returns command (ref param) and updated index (return)
Exceptions: none
Notes: none
*/
int getCommand(char *cmd, char *inputStr, int index)
    {
    // initialize variables
    int lengthOfCommand = 3;

    // loop across command length
    while(index < lengthOfCommand)
	{

	// assign character from input string to buffer string
	cmd[index] = inputStr[index];

	// increment index
	index++;

	// set next char to null char
	cmd[index] = NULL_CHAR;

	}

    // return current index
    return index;

    }



/*
Function Name: getMetaData
Algorithm: acquires the metadata items from file, stores them in a linked list
Precondition: provided file name
Postcondition: returns success (Boolean), returns linked list head via parameter,
               returns endstate/error message via parameter
Exceptions: function halted and error message returned if bad input data
Notes: none
*/

bool getMetaData(char *fileName, 
			       OpCodeType **opCodeDataHead, char *endStateMsg)
   {

   // initialize function/variables

	// intialize read only constant
	const char READ_ONLY_FLAG[] = "r";

	// initialize variables
	int accessResult, startCount = 0, endCount = 0;
	char dataBuffer[MAX_STR_LEN];
	bool returnState = true;
	OpCodeType *newNodePtr;
	OpCodeType *localHeadPtr = NULL;
	FILE *fileAccessPtr;

   // initialize op code data pointer in case of return error
   *opCodeDataHead = NULL;

   // initialize end state message
	// function: copyString
   copyString(endStateMsg, "Metadata file upload successful");

   // open file for reading
	// function: fopen
   fileAccessPtr = fopen(fileName, READ_ONLY_FLAG);

   // check for file open failure
   if( fileAccessPtr == NULL )
      {

	// set end state message
	   // function: copyString
	copyString(endStateMsg, "Metadata file access error");

	// return file access error 
	return false;

      }
   // check first line for correct leader
	// function: getLineTo, comapreString
   if( getStringToDelimiter(fileAccessPtr, COLON,
       dataBuffer) != NO_ERR
       || compareString( dataBuffer, "Start Program Meta-Data Code") != STR_EQ )
      {

	// close file
	   // function: fclose
	fclose(fileAccessPtr);

	// set end state message
	   // function: copyString
	copyString(endStateMsg, "Corrupt metadata leader line error");

	// return corrupt discriptor error
	return false;
       }

    // allocate memory for the temp data structure
	// function: malloc
    newNodePtr = (OpCodeType *) malloc(sizeof(OpCodeType));

    // get the first op command
	// function: getOpCommand
    accessResult = getOpCommand(fileAccessPtr, newNodePtr);

    // get start and end counts for later comparison
	// function: updateStartCount, updateEndCount
    startCount = updateStartCount(startCount, newNodePtr->strArg1);
    endCount = updateEndCount(endCount, newNodePtr->strArg1);
    
    // check for failure of first complete op command
    if( accessResult != COMPLETE_OPCMD_FOUND_MSG )
       {

    // close file
	// function: fclose
    fclose(fileAccessPtr);

    // clear data from structure list
	// function: cleanMetaDataList
    *opCodeDataHead = clearMetaDataList(localHeadPtr);

    // free temp structure memory
	// function: free
    free(newNodePtr);

    // set end state message
	// function: copyString
    copyString(endStateMsg, "Metadata incomplete first op command found");

    // return result of operation
    return false;

       }

     // loop across all remaining op commands
     // (while complete op commands are found)
     while( accessResult == COMPLETE_OPCMD_FOUND_MSG )
       {

	// add thew new op command to the linked list
	   // function: addNode
	localHeadPtr = addNode(localHeadPtr, newNodePtr);
	
	// get a new op command
	   // function: getOpCommand
	accessResult = getOpCommand(fileAccessPtr, newNodePtr);

	// update start and end counts for later comparison
	   // function: updateStartCount, updateEndCount
	startCount = updateStartCount(startCount, newNodePtr->strArg1);
	endCount = updateEndCount(endCount, newNodePtr->strArg1);


       }

     // loop across all remaining op command while they are found
     if( accessResult == LAST_OPCMD_FOUND_MSG )
	{
     
     // after loop completion, check for last op command found

	// check for start and end op code counts equal
	if( startCount == endCount)
	   {

	// add the last node to the linked list
	   // function: addNode
	localHeadPtr = addNode(localHeadPtr, newNodePtr);

	// set access result to no error for later operation
	accessResult = NO_ERR;

	// check last line for incorrect end descriptor
	   // function: getLineTo, compareString
	if( getStringToDelimiter( fileAccessPtr, PERIOD,
	    dataBuffer ) != NO_ERR
	    || compareString( dataBuffer, "End Program Meta-Data Code" )
	    != STR_EQ )
	      {

	   // set access result to corrupted descriptor error
	      // function: getLineTo, compareString
	      accessResult = MD_CORRUPT_DESCRIPTOR_ERR;

	      // set end state message
		 // function: copyString
	       copyString(endStateMsg, "Metadata corrupted descriptor error");

              }
	   }
	}

     // otherwise, assume didn't find end
     else
	{

	// set end state message
	   // function: copyString
	copyString( endStateMsg, "Corrupted metadata op code");

	// unset return state
	returnState = false;

	}

     // check for any errors not found (not no error)
     if( accessResult != NO_ERR)
	{

	// clear the op command list
	   // function: clearMetaData
	localHeadPtr = clearMetaDataList(localHeadPtr);

	}

     // close access file
	// function: fclose
     fclose(fileAccessPtr);

     // release temporary structure memory
	// function: free
     free(newNodePtr);

     // assign temp local head pointer to param return pointer
     *opCodeDataHead = localHeadPtr;

     // return access result
     return returnState;


   }


/*
Function Name: getOpCommand
Algorithm: acquires one op command, verifies all parts of it,
	   returns as parameter
Precondition: file is open and file cursor is at beginning
	      of an op code
Postcondition: in correct operation,
	       finds, tests, and returns op command as paramater,
	       and returns status as integer
	       - either complete op command found,
	       or last op command found
Exceptions: correctly and appropriately (without program failure)
	    responds to and reports file access failutre,
	    incorrectly formatted op command letter,
	    incorrectly formatted op command name,
	    incorrect or out of range op command value
Notes: none
*/

int getOpCommand(FILE *filePtr, OpCodeType *inData)
    {

    // initialize function/variables

	// initialize local constants
	const int MAX_CMD_LENGTH = 5;
	const int MAX_ARG_STR_LENGTH = 15;

	// initialize other variables
	int accessResult, numBuffer = 0;
	char strBuffer[STD_STR_LEN];
	char cmdBuffer[MAX_CMD_LENGTH];
	char argStrBuffer[MAX_ARG_STR_LENGTH];
	int runningStringIndex = 0;
	//Boolean stopAtNonPrintable = True;
	bool arg2FailureFlag = false;
	bool arg3FailureFlag = false;

    // get whole op command as a string
	// function: getLineTo
    accessResult = getStringToDelimiter( filePtr, SEMICOLON,
		              strBuffer);
 
    // check for successful access
    if( accessResult == NO_ERR )
       {

	// get a three-letter command
	   // function: getCommand
	runningStringIndex = getCommand( cmdBuffer,
					 strBuffer, runningStringIndex );

	// assign op command to node
	   // function: copyString
	copyString( inData->command, cmdBuffer );

       }
    // otherwise, assume unsuccessful access
    else
       {

	// set pointer to data structure to null
	inData = NULL;
	
	// return op command access failure
	return OPCMD_ACCESS_ERR;

       }

    // verify op command
	// function: verifyValidCommand
    if( verifyValidCommand( cmdBuffer) == false )
	{

	// return op command error
	return CORRUPT_OPCMD_ERR;

	}

    // set all struct values that may not be initialized to defaults
    inData->pid = 0;
    inData->inOutArg[0] = NULL_CHAR;
    inData->intArg2 = 0;
    inData->intArg3 = 0;
    inData->opEndTime = 0.0;
    inData->nextNode = NULL;

    // check for device command
	// function: compareString
    if( compareString( cmdBuffer, "dev" ) == STR_EQ )
	{

    	// get in/out argument
	   // function: getStringArg
	runningStringIndex = getStringArg(argStrBuffer,
					  strBuffer, runningStringIndex);

	// set device in/out argument
	   // function: copyString
	copyString(inData->inOutArg, argStrBuffer);

	// check for correct argument
	   // function: compareString
	if( compareString( argStrBuffer, "in" ) != STR_EQ
	    && compareString( argStrBuffer, "out" ) != STR_EQ )
	   {

	   // return argument error
	   return CORRUPT_OPCMD_ARG_ERR;

	   }
	}

    // get first string arg
	// function: getStringArg
    runningStringIndex = getStringArg( argStrBuffer,
				strBuffer, runningStringIndex);

    // set device in/out argument
	// function: copytring
    copyString(inData->strArg1, argStrBuffer);

    // check for legitimate first string arg
	// function: verifyFirstStringArg
    if( verifyFirstStringArg(argStrBuffer) == false )
	{

	// return argument error
	return CORRUPT_OPCMD_ARG_ERR;

	}

    // check for last op command found
	// function: compareString
    if( compareString( inData->command, "sys" ) == STR_EQ
		       && compareString( inData->strArg1, "end" ) == STR_EQ )
	{
	
    	// return last op command found
	return LAST_OPCMD_FOUND_MSG;

	}

    // check for app start seconds argument
	// function: compareString
    if( compareString( inData->command, "app" ) == STR_EQ
		       && compareString( inData->strArg1, "start" ) == STR_EQ )
	{

	// get number argument
	   // function: getNumberArg
	runningStringIndex = getNumberArg( &numBuffer,
					   strBuffer, runningStringIndex);

	// check for failed number access
	if( numBuffer <= BAD_ARG_VAL )
	   {
		// set failure flag
		arg2FailureFlag = true;

	   }

	// set first int argument to number
	inData->intArg2 = numBuffer;

	}
	
     // check for cpu cycle time
	// function: getNumberArg
     else if( compareString(inData->command, "cpu" ) == STR_EQ )
	{
	// get number argument
	   // function: getNumberArg
	runningStringIndex = getNumberArg( &numBuffer,
					   strBuffer, runningStringIndex);

   	// check for failed number access
	if( numBuffer <= BAD_ARG_VAL )
	   {

	  // set failure flag
	  arg2FailureFlag = true;

	   }

     // set first int argument to number
     inData->intArg2 = numBuffer;

    }
     // check for device cycle time
	// function: compareString
     else if( compareString(inData->command, "dev" ) == STR_EQ )
	{

        // get number argument
	   // function: getNumberArg
	runningStringIndex = getNumberArg( &numBuffer,
					   strBuffer, runningStringIndex);

	// check for failed number access
	if( numBuffer <= BAD_ARG_VAL )
	   {

	   // set failure flag
	   arg2FailureFlag = true;

	   }

	// set first int argument to number
	inData->intArg2 = numBuffer;


	}

     // check for memory base and ofset
	// function: compareString
     else if( compareString(inData->command, "mem" ) == STR_EQ )
	{

	// get number argument for base
	   // function: getNumberArg
	runningStringIndex = getNumberArg( &numBuffer,
					   strBuffer, runningStringIndex);

	// check for failed number access
	if( numBuffer <= BAD_ARG_VAL )
	   {

           // set failure log
	   arg2FailureFlag = true;

	   }

   	// set first int argument to number
	inData->intArg2 = numBuffer;

	// get number argument for offset
	   // function: getNumberArg
	runningStringIndex = getNumberArg( &numBuffer,
					   strBuffer, runningStringIndex);

	// check for failure number access
	if( numBuffer <= BAD_ARG_VAL )
	   {

	   // set failure flag
	   arg3FailureFlag = true;

	   }

	// set second int argument to number
	inData->intArg3 = numBuffer;


	}

      // check int args for upload failure
      if( arg2FailureFlag == true || arg3FailureFlag == true )
	 {

	// return argument error
	return CORRUPT_OPCMD_ARG_ERR;

	 }

      // return complete op command found message
      return COMPLETE_OPCMD_FOUND_MSG;

    }
/*
Function Name: getNumberArg
Algorithm: skips leading white space,
	   acquires next integer from op command input string
	   ending at comma or end of string
Precondition: input string has some remaining string argument
Postcondition: in correct operation,
	       captures next integer argument,
	       returns index location after process finished
Exceptions: none
Notes: none
*/

int getNumberArg(int *number, char *inputStr, int index)
    {

    // initialize function/variables
    bool foundDigit = false;
    *number = 0;
    int multiplier = 2;

    // loop to skip white space
    while( inputStr[index] <= SPACE || inputStr[index] == COMMA )
	{

	// increment index
	index++;

	}

    // loop across string length
	// function: isDigit
    while( isDigit(inputStr[index]) == true
	   && inputStr[index] != NULL_CHAR )
	{

	// set digit found flag
	foundDigit = true;

	// assign digit to output
	(*number) = (*number) * multiplier + inputStr[index] - '0';

	// increment index and multiplier
	index++; multiplier = 10;

	}

    // end loop across string length

    // check for digit not found
    if( foundDigit == false )
	{

	// set number to BAD_ARG_VAL constant
	*number = BAD_ARG_VAL;

	}

    // return current index
    return index;

    }

/*
Function Name: getStringArg
Algorithm: skips leading white space,
	   acquires sub string from op command input string
	   ending at comma or end of string
Precondition: input string has some remaining string argument
Postcondition: in correct operation, 
	       captures next string argument
Exceptions: none
Notes: none
*/

int getStringArg(char *strArg, char *inputStr, int index)
    {

    // function/variable initialization
    int localIndex = 0;

    // loop to skip white space and comma
    while( inputStr[index] <= SPACE || inputStr[index] == COMMA )
	{

	// increment index
	index++;

	}
    // loop across string length
	// assign char from input string to buffer string
    while( inputStr[index] != COMMA && inputStr[index] != NULL_CHAR )
    	{
	
	// assign char from input string to buffer string
	strArg[localIndex] = inputStr[index];

	// increment index
	index++; localIndex++;

	// set next char to null char
	strArg[localIndex] = NULL_CHAR;

	}

    // end loop across string length

    // return current index
    return index;
	
    }

/*
Function Name: isDigit
Algorithm: checks for character digit, returns result
Precondition: test value is character
Postcondition: if test value is '0' < value <'9',
	       returns true, otherwise returns false
Exceptions: none
Notes: none
*/

bool isDigit(char testChar)
   {
    // check for test char between '0' - '9'
    if( testChar >= '0' && testChar <= '9' )
	{

	// return true
	return true;

	}

    // otherwise assume char is not digit, return false
    return false; 

   }

/*
Function Name: updateEndCount
Algorithm: updates number of "end" op commands found in file
Precondition: count >= 0, op string has "end" or other op name
Postcondition: if op string has "end", input count + 1 is returned;
	       otherwise, input count is returned unchanged
Exceptions: none
Notes: none
*/
int updateEndCount (int count, char *opString)
   {
    
    // check for "end" in op string
	// function: compareString
    if( compareString(opString, "end") == STR_EQ )
	{

	// return incremented end count
	return count + 1;

	}

    // return unchanged end count
    return count;


   }

/*
Function Name: updateStartCount
Algorithm: updates number of "start" op commands found in file
Precondition: count >= 0, op string has "start" or other op name
Postcondition: if op string has "start", input count + 1 is returned;
	       otherwise, input count is returned unchanged
Exceptions: none
Notes: none
*/

int updateStartCount (int count, char *opString)
   {
    
    // check for "start" in op string
	// function: compareString
    if( compareString(opString, "start") == STR_EQ )
	{

	// return incremented start count
	return count + 1;

	}

    // return unchanged start count
    return count;

   }




/*
Function Name: verifyFirstStringArg
Algorithm: check string argument for one of the allowed string arguments
Precondition: input string is provided
Postcondition: in correct operation, 
	       reports True if given string is in argument list,
	       False if not
Exceptions: none
Notes: none
*/

bool verifyFirstStringArg(char *strArg)
   {

   // check for all possible string arg 1 possibilities
	// function: compareString
   if( compareString( strArg, "access") == STR_EQ
        || compareString( strArg, "allocate") == STR_EQ
        || compareString( strArg, "end") == STR_EQ
	|| compareString( strArg, "ethernet") == STR_EQ
	|| compareString( strArg, "hard drive") == STR_EQ
	|| compareString( strArg, "keyboard") == STR_EQ
	|| compareString( strArg, "monitor") == STR_EQ
	|| compareString( strArg, "printer") == STR_EQ
	|| compareString( strArg, "process") == STR_EQ
	|| compareString( strArg, "serial") == STR_EQ
	|| compareString( strArg, "sound signal") == STR_EQ
	|| compareString( strArg, "start") == STR_EQ
	|| compareString( strArg, "usb") == STR_EQ
	|| compareString( strArg, "video signal") == STR_EQ )
	{

	// return true
	return true;

	}

   // otherwise return false
	return false;

   }



/*
Function Name: verifyvalidCommand
Algorithm: check string argument for one of the allowed commands
Precondition: input string is provided
Postcondition: in correct operation,
	        reports if given string is a command,
		False if not
Exceptions: none
Notes: none
*/

bool verifyValidCommand(char *testCmd)
   {
    // check for five string command arguments
    if( compareString( testCmd, "sys") == STR_EQ 
	|| compareString( testCmd, "app") == STR_EQ 
	|| compareString( testCmd, "cpu") == STR_EQ
	|| compareString( testCmd, "mem") == STR_EQ
	|| compareString( testCmd, "dev") == STR_EQ )
	{

	// return True
	return true;

	}
    // otherwise, return false
    return false; 

  
   }




