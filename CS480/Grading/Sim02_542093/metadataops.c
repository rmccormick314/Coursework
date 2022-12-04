#include "metadataops.h"

/*
 Name: addNode
 Process: Adds metadata node to linked list recursively,
          handles empty list condition
 Function Input/Parameters: Pointer to head or next linked node (OpCodeType *),
                            pointer to new node (OpCodeType *)
 Function Output/Parameters: None
 Function Output/Returned: Pointer to previous node, or head node (OpCodeType *)
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: copyString, malloc
*/
OpCodeType *addNode(OpCodeType *localPtr, OpCodeType *newNode)
{
    // Check for local pointer assigned to null
    if(localPtr == NULL)
    {
        // Access memory for new link/node
            // Function: malloc
        localPtr = (OpCodeType *)malloc(sizeof(OpCodeType));

        // Assign all three values to newly created node
        // Assign next pointer to null
            // Function: copyString
        localPtr->pid = newNode->pid;
        copyString(localPtr->command, newNode->command);
        copyString(localPtr->inOutArg, newNode->inOutArg);
        copyString(localPtr->strArg1, newNode->strArg1);
        localPtr->intArg2 = newNode->intArg2;
        localPtr->intArg3 = newNode->intArg3;
        localPtr->opEndTime = newNode->opEndTime;

        localPtr->nextNode = NULL;

        // Return current local pointer
        return localPtr;
    }
    // Assume end of list not found yet
    // Assign recursive function to current's next link
        // Function: addNode
    localPtr->nextNode = addNode(localPtr->nextNode, newNode);

    // Return current local pointer
    return localPtr;
}

/*
 Name: clearMetaDataList
 Process: Recursively traverses list, frees dynamically allocated nodes
 Function Input/Parameters: Node op code (const OpCodeType *)
 Function Output/Parameters: None
 Function Output/Returned: NULL (OpCodeType *)
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: clearMetaDataList, free
*/
OpCodeType *clearMetaDataList(OpCodeType *localPtr)
{

    // Check for local pointer not set to null (list not empty)
    if(localPtr != NULL)
    {
        // Call recursive function with next pointer
            // Function: clearMetaDataList
        clearMetaDataList(localPtr->nextNode);

        // After recursive call, release memory to OS
            // Function: free
        free(localPtr);

        // Set given pointer to NULL
        localPtr = NULL;
    }
    // Return null to calling function
    return NULL;
}

/*
 Name: displayMetaData
 Process: Data dump/display all op code items
 Function Input/Parameters: Pointer to head
                            of op code/metadata list (const OpCodeType *)
 Function Output/Parameters: None
 Function Output/Returned: None
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: None
*/
void displayMetaData(const OpCodeType *localPtr)
{
    // Display title, with underline
        // Function: printf
    printf("Meta-Data File Display\n");
    printf("----------------------\n\n");

    // Loop to end of linked list
    while(localPtr != NULL)
    {
        // Print leader
            // Function: printf
        printf("Op code: ");
        // Print op code pid
            // Function: printf
        printf("/pid: %d", localPtr->pid);

        // Print op code command
            // Function: printf
        printf("/cmd: %s", localPtr->command);

        // Check for dev op
        if(compareString(localPtr->command, "dev") == STR_EQ)
        {
            // Print in/out parameter
                // Function: printf
            printf("/io: %s", localPtr->inOutArg);
        }
        // Otherwise assume other than dev
        else
        {
            // Print NA
                // Function: printf
            printf("/io: NA");
        }
        // Print first string arugment
            // Function: printf
        printf("\n\t /arg1: %s", localPtr->strArg1);

        // Print first int argument
            // Function: printf
        printf("/arg2 %d", localPtr->intArg2);

        // Print second int argument
            // Function: printf
        printf("/arg 3: %d", localPtr->intArg3);

        // Print op end time
        printf("/op end time: %8.6f", localPtr->opEndTime);

        // End line
            // Function: printf
        printf("\n\n");

        // Assign local pointer to next node
        localPtr = localPtr->nextNode;
    }
}

/*
 Name: getCommand
 Process: Parses three letter command part of op code string
 Function Input/Parameters: Input op code string (const char *),
                            starting index (int)
 Function Output/Parameters: Parsed command (char *)
 Function Output/Returned: Updated starting index for use
                           by calling function (int)
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: None
*/
int getCommand(char *cmd, const char *inputStr, int index)
{
    // Initialize variables
    int lengthOfCommand = 3;

    // Loop across command length
    while(index < lengthOfCommand)
    {
        // Assign character from input string to buffer string
        cmd[index] = inputStr[index];

        // Increment index
        index++;

        // Set next character to null character
        cmd[index] = NULL_CHAR;
    }

    // Return current index
    return index;
}

/*
 Name: getMetaData
 Process: Main driver function to upload, parse, and store list
          of op code commands in a linked list
 Function Input/Parameters: File name (const char *)
 Function Output/Parameters: Pointer
                             to op code linked list head pointer (OpCodeType *)
                             result message of function state
                             after completion (char *)
 Function Output/Returned: Boolean result of operation (bool)
 Device Input/File: op code list uploaded
 Device Output/Device: None
 Dependencies: CopyString, fopen, getStringToDelimiter,
               compareString, fclose, malloc, getOpCommand,
               updateStartCount, updateEndCount,
               clearMetaDataList, free, addNode
*/
bool getMetaData(const char *fileName, OpCodeType **opCodeDataHead, char *endStateMsg)
{
    // Initialize function/variables

        // Initialize read only constant
    const char READ_ONLY_FLAG[] = "r";
    
        // Initialize variables
    int accessResult, startCount = 0, endCount = 0;
    char dataBuffer[MAX_STR_LEN];
    bool returnState = true;
    OpCodeType *newNodePtr;
    OpCodeType *localHeadPtr = NULL;
    FILE *fileAccessPtr;

    // Initialize op code data pointer in case of return error
    *opCodeDataHead = NULL;

    // Initialize end state message
        // Function: copyString
    copyString(endStateMsg, "Metadata file upload successful");

    // Open file for reading
        // Function: fopen
    fileAccessPtr = fopen(fileName, READ_ONLY_FLAG);

    // Check for file open failure
    if(fileAccessPtr == NULL)
    {
        // Set end state message
            // Function: copyString
        copyString(endStateMsg, "Metadata file access error");

        // Return file access error
        return false;
    }

    // Check first line for correct leader
        // Functions: getStringToDelimiter, compareString

    if(!getStringToDelimiter(fileAccessPtr, COLON, dataBuffer)
        || compareString(dataBuffer, "Start Program Meta-Data Code") != STR_EQ)
    {
        // Close file
            // Function: fclose
        fclose(fileAccessPtr);

        // Set end state message
            // Function: copyString
        copyString(endStateMsg, "Corrupt metadata leader line error");

        // Return corrupt descriptor error
        return false;
    }
    // Allocate memory for temporary data structure
        // Function: malloc
    newNodePtr = (OpCodeType *)malloc(sizeof(OpCodeType));

    // Get the first op command
        // Function: getOpCommand
    accessResult = getOpCommand(fileAccessPtr, newNodePtr);

    // Get start and end counts for later comparison
        // Function: updateStartCount, updateEndCount
    startCount = updateStartCount(startCount, newNodePtr->strArg1);
    endCount = updateEndCount(endCount, newNodePtr->strArg1);

    // Check for failure of first complete op command
    if(accessResult != COMPLETE_OPCMD_FOUND_MSG)
    {
        // Close file
            // Function: fclose
        fclose(fileAccessPtr);

        // Clear data from the structure list
            // Function: clearMetaDataList
        *opCodeDataHead = clearMetaDataList(localHeadPtr);

        // Free temporary structure memory
            // Function: free
        free(newNodePtr);

        // Set end state message
            // Function: copyString
        copyString(endStateMsg, "Metadata incomplete first op command found");

        // Return result of operation
        return false;
    }

    // Loop across all remaining op commands
    //   (while complete op commands are found)

    while(accessResult == COMPLETE_OPCMD_FOUND_MSG)
    {
        // Add the new op command to the linked list
            // Function: addNode
        localHeadPtr = addNode(localHeadPtr, newNodePtr);

        // Get new op command
            // Function: getOpCommand
        accessResult = getOpCommand(fileAccessPtr, newNodePtr);

        // Update start and end counts for later comparison
            // Function: updateStartCount, updateEndCount
        startCount = updateStartCount(startCount, newNodePtr->strArg1);
        endCount = updateEndCount(endCount, newNodePtr->strArg1);
    }

    // After loop completion, check for last op command found
    if(accessResult == LAST_OPCMD_FOUND_MSG)
    {
        // Check for start and end op code counts equal
        if(startCount == endCount)
        {
            // Add the last node to the linked list
                // Function: addNode
            localHeadPtr = addNode(localHeadPtr, newNodePtr);

            // Set access result to no error for later operation
            accessResult = NO_ACCESS_ERR;

            // Check last line for incorrect end descriptor
                // Function: getStringToDelimiter, compareString
            if(!getStringToDelimiter(fileAccessPtr, PERIOD, dataBuffer)
               || compareString(dataBuffer, "End Program Meta-Data Code") != STR_EQ)
            {
                // Set access result to corrupted descriptor error
                accessResult = MD_CORRUPT_DESCRIPTOR_ERR;

                // Set end state message
                    // Function: copyString
                copyString(endStateMsg, "Metadata corrupted descriptor error");
            }
        }
        // Otherwise, assume start/end counts not equal
        else
        {
            // Close file
            // Function: fclose
            fclose(fileAccessPtr);

            // Clear data from the structure list
            // Function: clearMetaDataList
            *opCodeDataHead = clearMetaDataList(localHeadPtr);

            // Free temporary structure memory
            // Function: free
            free(newNodePtr);

            // Set access result to error
            accessResult = UNBALANCED_START_END_ERR;

            // Set end state message
            // Function: copyString
            copyString(endStateMsg,
                       "Unbalanced start and end arguments in metadata");

            // Return result of operation
            return false;
        }
    }
    // Otherwise, assume didn't find end
    else
    {
        // Set end state message
            // Function: copyString
        copyString(endStateMsg, "Corrupted metadata op code");

        // Unset return state
        returnState = false;

    }
    // Check for any errors found (not no error)
    if(accessResult != NO_ACCESS_ERR)
    {
        // Clear the op command list
            // Function: clearMetaDataList
        localHeadPtr = clearMetaDataList(localHeadPtr);

        returnState = false;
    }
    // Close access file
        // Function: fclose
    fclose(fileAccessPtr);

    // Release temporary structure memory
        // Function: free
    free(newNodePtr);

    // Assign temporary local head pointer to parameter return pointer
    *opCodeDataHead = localHeadPtr;

    // Return access result
    return returnState;
}

/*
 Name: getNumberArg
 Process: Starts at given index, captures and assembles integer argument,
          and returns as parameter
 Function Input/Parameters: Input string (const char *), starting index (int)
 Function Output/Parameters: Pointer to captured integer value
 Function Output/Returned: Updated index for next function start
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: isDigit
*/
int getNumberArg(int *number, const char *inputStr, int index)
{
    // Initialize function/variables
    bool foundDigit = false;
    *number = 0;
    int multiplier = 1;

    // Loop to skip white space
    while(inputStr[index] <= SPACE || inputStr[index] == COMMA)
    {
        // Increment the index
        index++;
    }

    // Loop across string length
    while(isDigit(inputStr[index]) == true &&
                                    inputStr[index] != NULL_CHAR)
    {
        // Set digit found flag
        foundDigit = true;

        // Assign digit to output
        (*number) = (*number) * multiplier + inputStr[index] - '0';

        // Increment index and multiplier
        index++;
        multiplier = 10;
    }

    // Check for digit not found
    if(!foundDigit)
    {
        // Set number to BAD_ARG_VAL, use dereference for pointer
        *number = BAD_ARG_VAL;
    }

    // Return current index
    return index;
}

/*
 Name: isDigit
 Process: Tests character parameter for digit, returns true if is digit,
          false otherwise
 Function Input/Parameters: Test character (char)
 Function Output/Parameters: None
 Function Output/Returned: Boolean result of test (bool)
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: None
*/
bool isDigit(char testChar)
{
    // Check for test character between characters '0' - '9'
    return (testChar >= '0' && testChar <= '9');
}

/*
 Name: getOpCommand
 Process: Acquires one op command line from previously opened file,
          parses it, and sets various struct members according
          to the three letter command
 Function Input/Parameters: piotner to open file handle (FILE *)
 Function Output/Parameters: Pointer to one op code struct (OpCodeType *)
 Function Output/Returned: Coded result of operation (OpCodeMessages)
 Device Input/File: Opcode line uploaded
 Device Output/Device: None
 Dependencies: getStringToDelimiter, getCommand, copyString, verifyValidCommand,
               compareString, getStringArg, verifyFirstStringArg, getNumberArg
*/
OpCodeMessages getOpCommand(FILE *filePtr, OpCodeType *inData)
{
    // Initialize function/variables

        // Initialize local constants
    const int MAX_CMD_LENGTH = 5;
    const int MAX_ARG_STR_LENGTH = 15;

        // Initialize other variables
    int numBuffer = 0;
    char strBuffer[STD_STR_LEN];
    char cmdBuffer[MAX_CMD_LENGTH];
    char argStrBuffer[MAX_ARG_STR_LENGTH];
    int runningStringIndex = 0;
    bool arg2FailureFlag = false;
    bool arg3FailureFlag = false;

    // Get whole op command as string, check for successful access
        // Function: getStringToDelimiter
    if(getStringToDelimiter(filePtr, SEMICOLON, strBuffer))
    {

        // Get three-letter command
            // Function: getCommand
        runningStringIndex = getCommand(cmdBuffer,
                                            strBuffer, runningStringIndex);

        // Assign op command to node
            // Function: copyString
        copyString(inData->command, cmdBuffer);
    }
    // Otherwise, assume unsuccessful access
    else
    {
        // Set pointer to data structure to null
        inData = NULL;

        // Return op command access failure
        return OPCMD_ACCESS_ERR;
    }
    // Verify op command
    if(!verifyValidCommand(cmdBuffer))
    {
        // Return op command error
        return CORRUPT_OPCMD_ERR;
    }

    // Set all struct values that may not be initialized to defaults
    inData->pid = 0;
    inData->inOutArg[0] = NULL_CHAR;
    inData->intArg2 = 0;
    inData->intArg3 = 0;
    inData->opEndTime = 0.0;
    inData->nextNode = NULL;

    // Check for device command
    if(compareString(cmdBuffer, "dev") == STR_EQ)
    {
        // Get in/out argument
        runningStringIndex = getStringArg(argStrBuffer,
                                          strBuffer, runningStringIndex);

        // Set device in/out argument
        copyString(inData->inOutArg, argStrBuffer);

        // Check correct argument
        if(compareString(argStrBuffer, "in") != STR_EQ
           && compareString(argStrBuffer, "out") != STR_EQ)
        {
            // Return argument error
            return CORRUPT_OPCMD_ARG_ERR;
        }
    }

    // Get first string arg
    runningStringIndex = getStringArg(argStrBuffer,
                                      strBuffer, runningStringIndex);

    // Set device in/out argument
    copyString(inData->strArg1, argStrBuffer);

    // Check for legitimate first string arg
    if(!verifyFirstStringArg(argStrBuffer))
    {
        // Return argument error
        return CORRUPT_OPCMD_ARG_ERR;
    }

    // Check for last op command found
    if(compareString(inData->command, "sys") == STR_EQ
                        && compareString(inData->strArg1, "end") == STR_EQ)
    {
        // Return last op command found message
        return LAST_OPCMD_FOUND_MSG;
    }

    // Check for app start seconds argument
    if(compareString(inData->command, "app") == STR_EQ
                        && compareString(inData->strArg1, "start") == STR_EQ)
    {

        // Get number argument
            // Function: getNumberArg
        runningStringIndex = getNumberArg(&numBuffer,
                                          strBuffer, runningStringIndex);

        // Check for failed number access
        if(numBuffer <= BAD_ARG_VAL)
        {
            // Set failure flag
            arg2FailureFlag = true;
        }

        // Set first int argument to number
        inData->intArg2 = numBuffer;
    }

    // Check for cpu cycle time
    else if(compareString(inData->command, "cpu") == STR_EQ)
    {
        // Get number argument
            // Function: getNumberArg
        runningStringIndex = getNumberArg(&numBuffer,
                                          strBuffer, runningStringIndex);

        // Check for failed number access
        if(numBuffer <= BAD_ARG_VAL)
        {
            // Set failure flag
            arg2FailureFlag = true;
        }

        // Set first int argument to number
        inData->intArg2 = numBuffer;
    }

    // Check for device cycle time
    else if(compareString(inData->command, "dev") == STR_EQ)
    {

        // Get number argument
            // Function: getNumberArg
        runningStringIndex = getNumberArg(&numBuffer,
                                          strBuffer, runningStringIndex);

        // Check for failed number access
        if(numBuffer <= BAD_ARG_VAL)
        {
            // Set failure flag
            arg2FailureFlag = true;
        }

        // Set first int argument to number
        inData->intArg2 = numBuffer;
    }

    // Check for memory base and offset
    else if(compareString(inData->command, "mem") == STR_EQ)
    {
        // Get number argument for base
            // Function: getNumberArg
        runningStringIndex = getNumberArg(&numBuffer,
                                          strBuffer, runningStringIndex);

        // Check for failed number access
        if(numBuffer <= BAD_ARG_VAL)
        {
            // Set failure flag
            arg2FailureFlag = true;
        }
        // Set first int argument to number
        inData->intArg2 = numBuffer;

        // Get number argument to for offset
            // Function: getNumberArg
        runningStringIndex = getNumberArg(&numBuffer,
                                          strBuffer, runningStringIndex);

        // Check for failed number access
        if(numBuffer <= BAD_ARG_VAL)
        {
            // Set failure
            arg3FailureFlag = true;
        }

        // Set second int argument to number
        inData->intArg3 = numBuffer;
    }
    // Check int args for upload failure
    if(arg2FailureFlag || arg3FailureFlag)
    {
        // Return corrupt op command error error
        return CORRUPT_OPCMD_ARG_ERR;
    }

    // Return complete op command found message
    return COMPLETE_OPCMD_FOUND_MSG;
}

/*
 Name: getStringArg
 Process: Starts at given index, captures and assembles string argument,
          and returns as parameter
 Function Input/Parameters: Input string (const char *), starting index (int)
 Function Output/Parameters: Pointer to captured string argument (char *)
 Function Output/Returned: Updated index for next function start
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: None
*/
int getStringArg(char *strArg, const char *inputStr, int index)
{
    // Intialize function/variables
    int localIndex = 0;

    // Loop to skip white space
    while(inputStr[index] <= SPACE || inputStr[index] == COMMA)
    {
        // Increment index
        index++;
    }

    // Loop across string length
    while(inputStr[index] != COMMA && inputStr[index] != NULL_CHAR)
    {
        // Assign character from input string to buffer string
        strArg[localIndex] = inputStr[index];

        // Increment index
        localIndex++;
        index++;

        // Set next character to null character
        strArg[localIndex] = NULL_CHAR;
    }

    // Return current index
    return index;
}

/*
 Name: updateEndCount
 Process: Manages count of "end" arguments to be compared at end
          of process input
 Function Input/Parameters: Initial count (int),
                            test string for "end" (const char *)
 Function Output/Parameters: None
 Function Output/Returned: Updated count, if "end" string found,
                           otherwise no change
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: compareString
*/
int updateEndCount(int count, const char *opString)
{
    // Check for "end" in op string
        // Function: compareString
    if(compareString(opString, "end") == STR_EQ)
    {
        // Return incremented end count
        return count + 1;
    }

    // Return unchanged end count
    return count;
}

/*
 Name: updateStartCount
 Process: Manages count of "start" arguments to be compared at end
          of process input
 Function Input/Parameters: Initial count (int),
                            test string for "start" (const char *)
 Function Output/Parameters: None
 Function Output/Retruned: Updated count, if "start" string found,
                           otherwise no change
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: compareString
*/
int updateStartCount(int count, const char *opString)
{
    // Check for "start" in op string
        // Function: compareString
    if(compareString(opString, "start") == STR_EQ)
    {
        // Return incremented end count
        return count + 1;
    }

    // Return unchanged end count
    return count;
}

/*
 Name: verifyFirstStringArg
 Process: Checks for all possibilities of first argument string of op command
 Function Input/Parameters: Test string (const char *)
 Function Output/Parameters: None
 Function Ouput/Returned: Boolean result of test (bool)
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: compareString
*/
bool verifyFirstStringArg(const char *strArg)
{
    // Check for string holding correct first argument
        // Function: compareString

    return (compareString(strArg, "access") == STR_EQ
        ||  compareString(strArg, "allocate") == STR_EQ
        ||  compareString(strArg, "end") == STR_EQ
        ||  compareString(strArg, "ethernet") == STR_EQ
        ||  compareString(strArg, "hard drive") == STR_EQ
        ||  compareString(strArg, "keyboard") == STR_EQ
        ||  compareString(strArg, "monitor") == STR_EQ
        ||  compareString(strArg, "printer") == STR_EQ
        ||  compareString(strArg, "process") == STR_EQ
        ||  compareString(strArg, "serial") == STR_EQ
        ||  compareString(strArg, "sound signal") == STR_EQ
        ||  compareString(strArg, "start") == STR_EQ
        ||  compareString(strArg, "usb") == STR_EQ
        ||  compareString(strArg, "video signal") == STR_EQ);
}

/*
 Name: verifyValidCommand
 Process: Checks for all possibilities of three-letter op code commands
 Function Input/Parameters: Test string for command (const char *)
 Function Output/Parameters: None
 Function Output/Returned: Boolean result of test (bool)
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: compareString
*/
bool verifyValidCommand(char *testCmd)
{
    // Check for string holding three-letter op code command
        // Function: compareString

    return (compareString(testCmd, "sys") == STR_EQ
        ||  compareString(testCmd, "app") == STR_EQ
        ||  compareString(testCmd, "cpu") == STR_EQ
        ||  compareString(testCmd, "mem") == STR_EQ
        ||  compareString(testCmd, "dev") == STR_EQ);
}
