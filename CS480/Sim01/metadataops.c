// Header files
#include "metadataops.h"

// Functions
/*
Name:                       clearMetaDataList
Process:                    Recursively traverses list, frees dynamically
                            allocated nodes.
Function Input/Parameters:  Node op code (const OpCodeType *)
Function Output/Parameters: None
Function Output/Returned:   NULL (OpCodeType *)
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               tbd
*/
OpCodeType *clearMetaDataList( OpCodeType *localPtr )
   {
      // Stub function

      return NULL; // Temporary stub return
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
      // Stub function

      // Void function - no return
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
      // Stub function

      return false; // Temporary stub return
   }
