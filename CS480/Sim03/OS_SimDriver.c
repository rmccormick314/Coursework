// Header files
#include "OS_SimDriver.h"

int main( int argc, char **argv )
   {
      // Initialize program

         // Initialize variables
         ConfigDataType *configDataPtr = NULL;
         OpCodeType *metaDataPtr = NULL;
         char errorMessage[ MAX_STR_LEN ];
         CmdLineData cmdLineData;
         bool configUploadSuccess = false;

         // Show title
         // Function: printf
         printf( "\nSimulator Program\n" );
         printf( "=================\n\n" );

      // Process command line, check for program run
      // At least one correct switch and config file name (at end) verified
      // Function: processCmdLine
      if( processCmdLine( argc, argv, &cmdLineData ) )
         {
         // Upload config file and check for success
         // Function: getConfigData
         if( getConfigData( cmdLineData.fileName,
                            &configDataPtr,
                            errorMessage ) )
            {
            // Check config display flag
            if( cmdLineData.configDisplayFlag )
               {
               // Display config data
               // Function: displayConfigData
               displayConfigData( configDataPtr );
               }

            // Set display upload success flag
            configUploadSuccess = true;
            }
         // Otherwise, assume config file upload failure
         else
            {
            // Show error message, end program
            // Function: printf
            printf( "\nConfig Upload Error: %s, program aborted.\n\n",
                     errorMessage );
            }

         // Check for config success and need for metadata
         if( configUploadSuccess &&
             ( cmdLineData.mdDisplayFlag || cmdLineData.runSimFlag ) )
            {
            // Upload metadata file, check for success
            // Function: getMetaData
            if( getMetaData( configDataPtr->metaDataFileName,
                             &metaDataPtr,
                             errorMessage ) )
               {
               // Check metadata display flag
               if( cmdLineData.mdDisplayFlag )
                  {
                  // Display metadata
                  // Function: displayMetaData
                  displayMetaData( metaDataPtr );
                  }

               // Check run simulator flag
               if ( cmdLineData.runSimFlag )
                  {
                  // Run simulator
                  // Function: runSim
                  runSim( configDataPtr, metaDataPtr );
                  }

               }
            // Otherwise, assume metadata upload failure
            else
               {
               // Show error message, end program
               // Function: printf
               printf( "\nMetadata Upload Error: %s, program aborted.\n",
                       errorMessage );
               }
            }
         // End check need for metadata upload

         // Clean up config data as needed
         // Function: clearConfigData
         configDataPtr = clearConfigData( configDataPtr );

         // Clean up metadata as needed
         // Function: clearMetaDataList
         metaDataPtr = clearMetaDataList( metaDataPtr );
         }
      // End check for good command line

      // Otherwise, assume command line failure
      else
         {
         // Show command argument requirements
         // Function: showCommandLineFormat
         showCommandLineFormat();
         }

      // Show program end
      // Function: printf
      printf( "\nSimulator Program End.\n\n" );

      // Return success
      return 0;
   }

/*
Name:                       clearCmdLineStruct
Process:                    Sets command line structure data to defaults:
                            Booleans to false, fileName to empty string.
Function Input/Parameters:  Pointer to command line structure (CmdLineData *)
Function Output/Parameters: Pointer to command line structure (CmdLineData *),
                            with updated members.
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               None
*/
void clearCmdLineStruct( CmdLineData *clDataPtr )
   {
      // Set all struct members to default
      clDataPtr->programRunFlag = false;
      clDataPtr->configDisplayFlag = false;
      clDataPtr->mdDisplayFlag = false;
      clDataPtr->runSimFlag = false;
      clDataPtr->fileName[ 0 ] = NULL_CHAR;

      // Void function - no return
   }

/*
Name:                       processCmdLine
Process:                    Checks for at least two arguments,
                            then sets booleans depending on cmd line switches.
                            These switches can be in any order.
                            Also captures config file name which must be
                            the last argument.
Function Input/Parameters:  Number of arguments (int),
                            Vector of arguments (char **)
Function Output/Parameters: Pointer to command line structure (CmdLineData *)
                            with updated members.
                            Set to default values if failure to capture args.
Function Output/Returned:   Boolean result of argument capture.
                            True if at least one switch and config file name,
                            False otherwise.
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               tbd
*/
bool processCmdLine( int numArgs, char **strVector, CmdLineData *clDataPtr )
   {
      // Initialize function/variables

         // Initialize structure to defaults
         // Function: clearCmdLineStruct
         clearCmdLineStruct( clDataPtr );

         // Initialize success flags to false
         bool atLeastOneSwitchFlag = false;
         bool correctConfigFileFlag = false;

         // Initialize first arg index to one
         int argIndex = 1;

         // Declare other variables
         int fileStrLen, fileStrSubLoc;

      // Must have program name, at least one switch, and config file name (min)
      if ( numArgs >= MIN_NUM_ARGS )
         {
         // Loop across args, starting at 1, and program run flag
         while ( argIndex < numArgs )
            {
            // Check for -dc (display config flag)
            if( compareString( strVector[ argIndex ], "-dc" ) == STR_EQ )
               {
               // Set config display flag
               clDataPtr->configDisplayFlag = true;

               // Set atleast one switch flag
               atLeastOneSwitchFlag = true;
               }

            // Otherwise, check for -dm (display metadata flag)
            else if( compareString( strVector[ argIndex ], "-dm" ) == STR_EQ )
               {
               // Set meta data display flag
               clDataPtr->mdDisplayFlag = true;

               // Set at least one switch flag
               atLeastOneSwitchFlag = true;
               }

            // Otherwise, check for -rs (run simulator flag)
            else if( compareString( strVector[ argIndex ], "-rs" ) == STR_EQ )
               {
               // Set run simulator flag
               clDataPtr->runSimFlag = true;

               // Set at least one switch flag
               atLeastOneSwitchFlag = true;
               }

            // Otherwise, check for filename, ending in .cfg (must be last four)
            else
               {
               // Find lengths to verify file name
               // File name must be last argument, and have ".cnf" extension
               fileStrLen = getStringLength( strVector[ numArgs - 1 ] );
               fileStrSubLoc = findSubString( strVector[ numArgs -1 ],
                                              ".cnf" );
               // Check for file existence and correct file format
               if( fileStrSubLoc != SUBSTRING_NOT_FOUND &&
                   fileStrSubLoc == fileStrLen - LAST_FOUR_LETTERS )
                  {
                  // Set file name to variable
                  copyString( clDataPtr->fileName, strVector[ numArgs - 1 ] );

                  // Set success flag to true
                  correctConfigFileFlag = true;
                  }

               // Otherwise, assume bad config file name
               else
                  {
                  // Reset struct, correct config file flag stays false
                  // Function: clearCmdLineStruct
                  clearCmdLineStruct( clDataPtr );
                  }
               }

            // Update argument index
            argIndex++;
            }
         // End arg loop
         }
      // End test for minimum number of command line arguments

      // Return verification of at least one switch and correct file name
      return atLeastOneSwitchFlag && correctConfigFileFlag;
   }

/*
Name:                       showCommandLineFormat
Process:                    Displays command line format as assistance to user.
Function Input/Parameters:  None
Function Output/Parameters: None
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      Data displayed as specified
Dependencies:               printf
*/
void showCommandLineFormat()
   {
      // Display command line format
      // Function: printf
      printf( "Command Line Format:\n" );
      printf( "   sim_0x [-dc] [-dm] [-rs] <config file name>\n" );
      printf( "   -dc [optional] displays configuration data\n" );
      printf( "   -dm [optional] displays meta data\n" );
      printf( "   -rs [optional] runs simulator\n" );
      printf( "   [Required] config file name\n" );

      // Void function - no return
   }
