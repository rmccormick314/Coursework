// Header files
#include "metadataops.h"

// Functions

/*
Name:                       addNode
Process:                    Adds metadata node to linked list recursively,
                            handles empty list condition
Function Input/Parameters:  Pointer to head or next linked node (OpCodeType *),
                            Pointer to new node (OpCodeType *)
Function Output/Parameters: None
Function Output/Returned:   Pointer to previous node, or head (OpCodeType *)
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               copyString, malloc
*/
OpCodeType *addNode( OpCodeType *localPtr, OpCodeType *newNode )
   {
      // Check for local pointer assigned to null
      if( localPtr == NULL )
         {
         // Access memory for new node
         // Function: malloc
         localPtr = (OpCodeType *)malloc( sizeof( OpCodeType ) );

         // Assign all three values to newly created node
         // Assign next pointer to null
         // Function: copyString
         localPtr->pid = newNode->pid;
         copyString( localPtr->command, newNode->command );
         copyString( localPtr->inOutArg, newNode->inOutArg );
         copyString( localPtr->strArg1, newNode->strArg1 );
         localPtr->intArg2 = newNode->intArg2;
         localPtr->intArg3 = newNode->intArg3;
         localPtr->opEndTime = newNode->opEndTime;

         localPtr->nextNode = NULL;

         // Return current local pointer
         return localPtr;
         }

      // Assume end of list not found yet
      // Assign recursive function current node's next link
      // Function: addNode
      localPtr->nextNode = addNode( localPtr->nextNode, newNode );

      // Return current local pointer
      return localPtr;
   }

/*
Name:                       clearMetaDataList
Process:                    Recursively traverses list, frees dynamically
                            allocated nodes.
Function Input/Parameters:  Node op code (const OpCodeType *)
Function Output/Parameters: None
Function Output/Returned:   NULL (OpCodeType *)
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               free
*/
OpCodeType *clearMetaDataList( OpCodeType *localPtr )
   {
      // Check for local pointer not set to null
      if( localPtr != NULL )
         {
         // Call recursive function with next pointer
         // Function: clearMetaDataList
         clearMetaDataList( localPtr->nextNode );

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
Name:                       displayMetaData
Process:                    Screen dump/display all op code files.
Function Input/Parameters:  Pointer to head of op code list (const OpCodeType *)
Function Output/Parameters: None
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      Display config data as specified.
Dependencies:               tbd
*/
void displayMetaData( const OpCodeType *localPtr )
   {
      // Display title, with underline
      // Function: printf
      printf( "Meta-Data File Display\n" );
      printf( "----------------------\n\n" );

      // Loop to end of linked list
      while( localPtr != NULL )
         {
         // Print leader
         // Function: printf
         printf( "Op Code: " );

         // Print op code PID
         // Function: printf
         printf(" /pid: %d", localPtr->pid );

         // Print op code command
         // Function: printf
         printf( "/cmd: %s", localPtr->command );

         // Check for dev op
         if( compareString( localPtr->command, "dev" ) == STR_EQ )
            {
            // Print in/out parameter
            // Function: printf
            printf( "/io: %s", localPtr->inOutArg );
            }

         // Otherwise, assume other than dev
         else
            {
            // Print NA
            // Function: printf
            printf( "/io: NA" );
            }

         // Print first string argument
         // Function: printf
         printf( "\n\t /arg1: %s", localPtr->strArg1 );

         // Print first int argument
         // Function: printf
         printf( "/arg 2: %d", localPtr->intArg2 );

         // Print second int argument
         // Function: printf
         printf( "/arg 3: %d", localPtr->intArg3 );

         // Print op end time
         printf( "/op end time: %8.6f", localPtr->opEndTime );

         // End line
         // Function: printf
         printf( "\n\n" );

         // Assign local pointer to next node
         localPtr = localPtr->nextNode;
         }
   }


/*
Name:                       getCommand
Process:                    Parses three letter command part of op code string
Function Input/Parameters:  Input OP code string (const char *),
                            Starting index (int)
Function Output/Parameters: Parsed command (char *)
Function Output/Returned:   Updated starting index for use by
                            calling function (int)
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               None
*/
int getCommand( char *cmd, const char *inputStr, int index )
   {
      // Initialize function/variables
      int lengthOfCommand = 3;

      // Loop across command length
      while( index < lengthOfCommand )
         {
         // Assign character from input string to buffer string
         cmd[ index ] = inputStr[ index ];

         // Increment index
         index++;

         // Set next character to null character
         cmd[ index ] = NULL_CHAR;
         }

      // Return current index
      return index;
   }

/*
Name:                       getMetaData
Process:                    Main driver function to upload, parse, and store
                            list of op code commands in linked list.
Function Input/Parameters:  File name (const char *)
Function Output/Parameters: Pointer to op code linked list (OpCodeType **),
                            Result message of function state (char *)
Function Output/Returned:   Boolean result of operation (bool)
Device Input/Keyboard:      Op code list uploaded
Device Output/Monitor:      None
Dependencies:               addNode, clearMetaDataList, compareString,
                            copyString, fclose, fopen, free,
                            getStringToDelimiter, malloc, updateStartCount
*/
bool getMetaData( const char *fileName,
                  OpCodeType **opCodeDataHead,
                  char *endStateMsg )
   {
      // Initialize function/variables

         // Initialize read only constant

         // Initialize variables

      // Initialize op code data pointer in case of return error

      // Initialize end state message
      // Function: copyString

      // Open file for reading
      // Function: fopen

      // Check for file open failure

         // Set end state message
         //Function copyString

         // Return file access error

      // Check for first line correct leader
      // getStringToDelimiter, compareString

         // Close file

         // Set end state message
         // Function: copyString

         // Return corrupt descriptor error

      // Allocate memory for the temporary data structure
      // Function: malloc

      // Get the first op command
      // Function: getOpCommand

      // Get start and end counts for later comparison
      // Function: updateStartCount, updateEndCount

      // Check for failure of first complete op command

         // Close file
         // Function: fclose

         // Clear data from structure list
         // Function: clearMetaDataList

         // Free temporary structure memory
         // Function: free

         // Set end state message
         // Function: copyString

         // Return result of operation

      // Loop across all remaining op commands
      // (While complete commands are found)

         // Add the new op command to the linked list
         // Function: addNode

         // Get a new op command
         // Function: getOpCommand

         // Update start and end counts for later comparison
         // Function: updateStartCount, updateEndCount

      // After loop completion, check for last op command found

         // Check start and end op counts are equal

            // Add the last node to the linked list
            // Function: addNode

            // Set access result to no error for later operation

            // Check last line for incorrect end descriptor
            // Function: getStringToDelimiter, compareString

               // Set access result to corrupted descriptor error

               // Set end state message
               // Function: copyString

         // Otherwise, assume start/end counts not equal

            // Close file
            // Function: fclose

            // Clear data from the structure list
            // Function: clearMetaDataList

            // Free temporary structure memory
            // Function: free

            // Set access result to error

            // Set end state message
            // Function: copyString

            // Return result of operation

      // Otherwise, assume didn't find the end

         // Set the end state message
         // Function: copyString

         // Unset return state

      // Check for any errors found (not no error)

         // Clear the op command list
         // Function: clearMetaDataList

      // Close the access file
      // Function: fclose

      // Release temporary structure memory
      // Function: free

      // Assign temporary local head pointer to parameter return pointer

      // Return access result

      return false; // Temporary stub return
   }

/*
Name:                       getOpCommand
Process:                    Acquires one op command line from a previously
                            opened file, parses it, and sets various struct
                            members according to the three letter command.
Function Input/Parameters:  Pointer to open file handle (FILE *)
Function Output/Parameters: Pointer to one op code struct (OpCodeType *)
Function Output/Returned:   Coded result of operation (OpCodeMessages)
Device Input/Keyboard:      Op Code line uploaded
Device Output/Monitor:      None
Dependencies:               compareString, copyString, getCommand, getNumberArg,
                            getStringArg, getStringToDelimiter,
                            verifyFirstStringArg, verifyValidCommand
*/
OpCodeMessages getOpCommand( FILE *filePtr, OpCodeType *inData )
   {
      // Initialize function/variables

         // Initialize local constants

         // Initialize other variables

      // Get whole op command as string, check for successful access
      // Function: getStringToDelimiter

         // Get three-letter command
         // Function: getCommand

         // Assign op command to node
         // Function: copyString

      // Otherwise, assume unsuccessful access

         // Set pointer to data structure to null

         // Return op command access failure

      // Verify op command

         // Return op command error

      // Set all struct values that may not be initialized to default

      // Check for device command

         // Get in/out argument

         // Set device in/out argument

         // Check correct argument

            // Return argument error

      // Get first string arg

      // Set device in/out argument

      // Check for legitimate first string arg

         // Return argument error

      // Check for last op command found

         // Return last op command found message

      // Check for app start seconds argument

         // Get number argument
         // Function: getNumberArg

         // Check for failed number access

            // Set failure flag

         // Set first int argument to number

      // Check for CPU cycle time

         // Get number argument
         // Function: getNumberArg

         // Check for failed access

            // Set failure flag

         // Set first int argument to number

      // Check for device cycle time

         // Get number argument
         // Function: getNumberArg

         // Check for failed number access

            // Set failure flag

         // Set first int argument to number

      // Check for memory base and offset

         // Get number argument for base
         // Function: getNumberArg

         // Check for failed number access

            // Set failure flag

         // Set first int argument to number

         // Get number argument for offset
         // Function: getNumberArg

         // Check for failed number access

            // Set failure flag

         // Set second int argument to number

      // Check int args for upload failure

         // Return corrupt op code command error

      // Return complete op command found message

      return 0; // Temporary return stub
   }

/*
Name:                       getNumberArg
Process:                    Starts at given index, captures and assembles
                            integer argument, and returns as parameter.
Function Input/Parameters:  Input string (const char *),
                            Starting index (int)
Function Output/Parameters: Pointer to captured integer value
Function Output/Returned:   Updated index for next function start
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               isDigit
*/
int getNumberArg( int *number, const char *inputStr, int index )
   {
      // Initialize function/variables

      // Loop to skip white space

         // Increment the index

      // Loop across string length

         // Set digit found flag

         // Assign digit to output

         // Increment index and multiplier

      // Check for digit not found

         // set number to BAD_ARG_VAL, use dereference for pointer

      // Return current index
      return 0; // Temporary stub return
   }

/*
Name:                       getStringArg
Process:                    Starts at given index, captures and assembles
                            string argument, and returns as parameter.
Function Input/Parameters:  Input string (const char *),
                            Starting index (int)
Function Output/Parameters: Pointer to captured string argument (char *)
Function Output/Returned:   Updated index for next function start
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               None
*/
int getStringArg( char *strArg, const char *inputStr, int index )
   {
      // Initialize function/variables

      // Loop to skip white space

         // Increment index

      // Loop across string length

         // Assign character from input string to buffer string

         // Increment index

         // Set next character to null character

      // Return current index

      return 0; // Temporary stub return
   }

/*
Name:                       isDigit
Process:                    Tests character parameter for digit, returns true if
                            it is a digit, false otherwise
Function Input/Parameters:  Test character (char)
Function Output/Parameters: None
Function Output/Returned:   Boolean result of test (bool)
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               None
*/
bool isDigit( char testChar )
   {
      // Check for test character between characters '0' - '9'

         // Return true

      // Otherwise, assume character is not digit, return false
      return false;
   }

/*
Name:                       updateEndCount
Process:                    Manages a count of "end" arguments to be compared at
                            the end of process input
Function Input/Parameters:  Initial count (int),
                            Test string for "end" (const char *)
Function Output/Parameters: None
Function Output/Returned:   Updated count, if "start" string found,
                            otherwise no change
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               compareString
*/
int updateEndCount( int count, const char *opString )
   {
      // Check for "end" in op string
      // Function: compareString

         // Return incremented end count

      // Return unchanged end count
      return 0; // Temporary stub return
   }

/*
Name:                       updateStartCount
Process:                    Manages a count of "start" arguments to be compared
                            at the end of process input
Function Input/Parameters:  Initial count (int),
                            Test string for "start" (const char *)
Function Output/Parameters: None
Function Output/Returned:   Updated count, if "start" string found,
                            otherwise no change
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               compareString
*/
int updateStartCount( int count, const char *opString )
   {
      // Check for "start" in op string
      // Function: compareString

         // Return incremented start count

      // Return unchanged start count
      return 0; // Temporary stub return
   }

/*
Name:                       verifyFirstStringArg
Process:                    Checks for all possible first args in an op command
Function Input/Parameters:  Test string (const char *)
Function Output/Parameters: None
Function Output/Returned:   Boolean result of test (bool)
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               compareString
*/
bool verifyFirstStringArg( const char *strArg )
   {
      // Check for string holding correct first argument
      // Function: compareString

         // Return true

      // Otherwise, assume failure, return false

      return false; // Temporary stub return
   }

/*
Name:                       verifyValidCommand
Process:                    Checks for all possible codes in an op command
Function Input/Parameters:  Test string for command (const char *)
Function Output/Parameters: None
Function Output/Returned:   Boolean result of test (bool)
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               compareString
*/
bool verifyValidCommand( char *testCmd )
   {
      // Check for string holding three-letter op code command
      // Function: compareString

         // Return true

      // Otherwise assume failure, return false
      return false; // Temporary stub return
   }
