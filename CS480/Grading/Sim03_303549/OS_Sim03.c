//header files
#include "OS_Sim03.h"

int main( int argc, char **argv )
    {
     //Initialize program
    
        ConfigDataType *configDataPtr = NULL;
        OpCodeType *metaDataPtr = NULL;
        char errorMessage[ MAX_STR_LEN ];
        CmdLineData *cmdLineData = malloc( sizeof ( CmdLineData ) );
        bool configUploadSuccess = false;

        //initialize variables

        //show title
        printf( "\nSimulator program\n" );
        printf( "=================\n\n" );

    //process command line, check for program run
    //at least one correct switch...
        if( processCmdLine( argc, argv, cmdLineData ) )
            {
        //upload cfg file, check for success
                if( getConfigData( cmdLineData->fileName,
                        &configDataPtr, errorMessage ) )
                    {
            //check config display flag
                        if( cmdLineData->configDisplayFlag )
                            {
                // display config data
                                displayConfigData( configDataPtr );
                            }

        //set config upload success flag
                        configUploadSuccess = true;
                    }
                else
                    {
                        printf( "\nConfig Upload Error %s, program aborted\n\n",
                                    errorMessage);
                    }

                if( configUploadSuccess 
                        && ( cmdLineData->mdDisplayFlag || cmdLineData->runSimFLag) )
                    {
                        if( getMetaData (configDataPtr->metaDataFileName,
                                &metaDataPtr, errorMessage ) )
                            {
                                if( cmdLineData->mdDisplayFlag )
                                    {
                                        displayMetaData( metaDataPtr );
                                    }
                                if( cmdLineData->runSimFLag )
                                    {
                                        runSim( configDataPtr, metaDataPtr );
                                    }
                            }
                        else
                            {
                                printf( "\nMetadata Upload Error: %s, program aborted\n",
                                        errorMessage);
                            }
                    }

                configDataPtr = clearConfigData( configDataPtr );

                if( !cmdLineData->runSimFLag )
                    {
                        metaDataPtr = clearMetaDataList( metaDataPtr );
                    }

                free(cmdLineData);
        }
        else
            {
                showCommandLineFormat();
            }

        printf( "\nSimulator Program End.\n\n" );
        return 0;
    }

void clearCmdLineStruct( CmdLineData *clDataPtr )
    {
        clDataPtr->programRunFlag = false;
        clDataPtr->configDisplayFlag = false;
        clDataPtr->mdDisplayFlag = false;
        clDataPtr->runSimFLag = false;
        clDataPtr->fileName[ 0 ] = NULL_CHAR;
    }

bool processCmdLine( int numArgs, char **strVector, CmdLineData *clDataPtr )
    {
        clearCmdLineStruct( clDataPtr );

        bool atLeastOneSwitchFlag = false;
        bool correctConfigFileFlag = false;

        int argIndex = 1;

        int fileStrLen, fileStrSubLoc;

        if( numArgs >= MIN_NUM_ARGS )
            {
                while( argIndex < numArgs )
                    {
                        if( compareString(strVector[ argIndex ], "-dc" ) == STR_EQ )
                            {
                                clDataPtr->configDisplayFlag = true;

                                atLeastOneSwitchFlag = true;
                            }
                        else if( compareString(strVector[ argIndex ], "-dm" ) ==STR_EQ )
                            {
                                clDataPtr->mdDisplayFlag = true;

                                atLeastOneSwitchFlag = true;
                            }
                        else if( compareString(strVector[ argIndex ], "-rs" ) ==STR_EQ )
                            {
                                clDataPtr->runSimFLag = true;

                                atLeastOneSwitchFlag = true;
                            }

                        else
                            {
                                fileStrLen = getStringLength( strVector[ argIndex ] );
                                fileStrSubLoc
                                    = findSubString( strVector[ argIndex ], ".cnf" );

                                
                                if( fileStrSubLoc != SUBSTRING_NOT_FOUND 
                                        && fileStrSubLoc == fileStrLen - LAST_FOUR_LETTERS )
                                    {
                                        copyString( clDataPtr->fileName, strVector[ argIndex ] );

                                        correctConfigFileFlag = true;
                                    }
                            }
                        argIndex++;
                    }
            }

            else
                {
                    clearCmdLineStruct( clDataPtr );
                }
        return atLeastOneSwitchFlag && correctConfigFileFlag;
    }

void showCommandLineFormat()
    {
        printf( "Command Line Format:\n");
        printf( "       sim_0x [-dc] [-dm] [-rs] config file name>\n" );
        printf( "       -dc [optional] displays configuration dat\n" );
        printf( "       -dm [optional] diplays meta data\n" );
        printf( "       -rs [optional] runs sumulator\n" );
        printf( "       required config file name\n" );
    }