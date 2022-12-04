// header files
#include "OS_SimDriver.h"

int main(int argc, char **argv)
    {
    // initialize program

      // initialize variables
      bool configUploadFlag = false;
      char errorMessage[ MAX_STR_LEN ];
      ConfigDataType *configDataPtr = NULL;
      OpCodeType *metaDataPtr = NULL;
      CmdLineData cmdLineData;

      // show title
        // function: printf
      printf( "\nSimulator Program\n" );
      printf( "=================\n\n");

      // process command lne, check for program run
      // at least one correct switch and config file name (at end) verified
        // function: processCmdLine
        if (processCmdLine(argc, argv, &cmdLineData))
            {
              // upload config file, check for success
                // funtion: getConfigData
           if(getConfigData(cmdLineData.fileName,
                                                 &configDataPtr, errorMessage))
              {

              // check config display flag
                // function: displayConfigData
              if (cmdLineData.configDisplayFlag)
                {
                 // display config data
                  //function: displayConfigData
                  displayConfigData(configDataPtr);
                }

                // set config upload sucess flag
                configUploadFlag = true;

              }
             // otherwise, assume config file upload failure
             else 
               {
                   // show error message, end program
                     // function: printf
                   printf( "\nConfig Upload Error: %s, program aborted\n\n",
                                                              errorMessage );

               }

               // check for config success and need for metadata
               if(configUploadFlag && (cmdLineData.mdDisplayFlag
               || cmdLineData.runSimFlag))
                {
                    // upload meta data file, check for success
                     // function: getMetaData
                    if( getMetaData( configDataPtr->metaDataFileName,
                                            &metaDataPtr, errorMessage ))
                      {
                        // check meta data display flag
                        if(cmdLineData.mdDisplayFlag)
                        {
                            // display meta data
                              // function: displayMetaData
                              displayMetaData(metaDataPtr);
                        }
                        // check run sim flag
                        if (cmdLineData.runSimFlag)
                        {
                            runSim(configDataPtr, metaDataPtr);
                        }

                      }

                  // otherwise, assume meta data upload failure
                  else
                  {
                      // show error message, end program
                        // function: printf
                      printf( "\nConfig Upload Error: %s, program aborted\n\n",
                                                           errorMessage );
                  }

                }
                // end check for metadata upload

                // clean up metadata as needed
                    // function: clearConfigData
                configDataPtr = clearConfigData(configDataPtr);

                // clean up metaData as needed
                    // function: clearMetaData   
                metaDataPtr = clearMetaDataList(metaDataPtr);
            }

            // end check for good command line

            // otherwise, assume command line failure
            else 
            {
                // show command argument requirementrs
                    // function: showProgramFormat
                showProgramFormat();
            }

      // show program end
        // fucntion: printf
      printf( "\nSimulator Program End.\n\n" );

      // return success
      return 0;

    
  }
/*
Name: clearCmdLineStruct
Process: sets command line structure data to defaults
         booleans to false, fileName to empty string
Method input/parameters: pointer to command line structure (cmdLineData *)
Method output/parameters: pointer to command line structure (CmdLineData *)
                          with updated members
Method output/returned: none
Device input/keyboard: none
Device output/monitor: none
Dependencies: none
*/

void clearCmdLineStruct (CmdLineData *clDataPtr)
  {
      // set all struct members to default
      clDataPtr->programRunFlag = false;
      clDataPtr->configDisplayFlag = false;
      clDataPtr->mdDisplayFlag = false;
      clDataPtr->runSimFlag = false;
      clDataPtr->fileName[0] = NULL_CHAR;

      // void function, no return
      
  }
  
/*
Name: processCmdLine
Process: checks for at least two arguments, then sets
         Booleans depending on command line switches
         which can be in any order, also captures
         config file name which must be last argument
Method input/parameters: number of arguments (int)
                         vector of arguments (char **)
Method output/parameters: pointer to command line structure (CmdLineData *)
                          with updated members, set to default values
                          if failure to caprute arguments
Method output/returned: Boolean result of argument capture,
                        true if at least one switch and config file name,
                        false otherwise
Device input/keyboard: none
Device output/monitor: none
Dependencies: none
*/

bool processCmdLine (int numArgs, char **strVector, CmdLineData *clDataPtr )
    {

    // initialize functions/variables

    // initialize structure to defaults
        // function: clearCmdLineStruct
     clearCmdLineStruct(clDataPtr);
    // initialize success flags to false
    bool atLeastOneSwitchFlag = false;
    bool correctConfigFileFlag = false;

    // initialize first arg index to one
    int argIndex = 1;
    
    // declare other variables
    int fileStrLen, fileStrSubLoc;

    // must have prog name, at lease one switch, and config file name, minimum
    if (numArgs >= MIN_NUM_ARGS )
        {
            // loop across args (starting at 1) and program run flag
            while(argIndex < numArgs)
            {
            // check for dc
            if (compareString(strVector[argIndex], "-dc") == STR_EQ)
                {
            // set config display flag
            clDataPtr->configDisplayFlag = true;

            // set at least one switch flag
            atLeastOneSwitchFlag = true;

                }
            // otherwise, check for dm
            else if (compareString(strVector[argIndex], "-dm") == STR_EQ)
                {
            // set config display flag
            clDataPtr->mdDisplayFlag = true;

            // set at least one switch flag
            atLeastOneSwitchFlag = true;

                }


                // otherwise, check for rs
            else if (compareString(strVector[argIndex], "-rs") == STR_EQ)
                {
            // set config display flag
            clDataPtr->runSimFlag = true;

            // set at least one switch flag
            atLeastOneSwitchFlag = true;

                }
            // otherwise, check for file name, ending in .cfg
            // must be last four
            else
                {
                    // find lengths to verify file Name
                    // file name must be last arg, and have .cnf extension
                    fileStrLen = getStringLength(strVector[numArgs - 1]);
                    fileStrSubLoc =
                                    findSubString(strVector[numArgs - 1], ".cnf");

                    // verify string found and correct Format for config file name
                    if(fileStrSubLoc != SUBSTRING_NOT_FOUND
                                    && fileStrSubLoc == fileStrLen - LAST_FOUR_LETTERS)
                        {
                            // set file name to variable
                            copyString( clDataPtr->fileName, strVector[numArgs - 1]);

                            // set success flag to true
                            correctConfigFileFlag = true;
                        }
                    // otherwise assume bad cnfig file Name
                    else
                        {
                            // reset struct, correct config file flag stays false
                                // function: clearStruct
                            clearCmdLineStruct(clDataPtr);

                        }

                }
                // update arg index
                argIndex++;

            }
            // end arg loop
        }
        // end test for min num of command line arguments

        // return verification of at least one switch and correct file name
        return atLeastOneSwitchFlag && correctConfigFileFlag;
    }






/*
Name: showProgramFormat
Process: displays command line argument requirements for this program
Method input/parameters: none
Method output/parameters: none
Method output/returned: none
Device input/keyboard: none
Device output/monitor: intstructions provided as specified
Dependencies: none
*/

void showProgramFormat()
  {
    // print out command line argument instructions
        // function: printf
    printf( "Program Format:\n" );
    printf( "     sim_01 [-dc] [-dm] [-rs] configops.c\n" );
    printf( "     -dc [optional] displays configuration data\n" );
    printf( "     -dm [optional] displays meta date\n" );
    printf( "     -rs [optional] runs simulator\n" );
    printf( "     required config file name\n" );
  }
	