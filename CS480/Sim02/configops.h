// Protect from multiple compilations
#ifndef CONFIGOPS_H
#define CONFIGOPS_H

// HEADER FILES
#include <stdio.h>
#include "datatypes.h"
#include "StandardConstants.h"
#include "StringUtils.h"

// FUNCTION PROTOTYPES
/*
Name:                       clearConfigData
Process:                    Frees all dynamically allocated data in a given
                            config data structure, if it has not already
                            been freed.
Function Input/Parameters:  Pointer to config data structure (ConfigDataType *)
Function Output/Parameters: None
Function Output/Returned:   NULL (ConfigDataType *)
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               free
*/
ConfigDataType *clearConfigData( ConfigDataType *configData );

/*
Name:                       configCodeToString
Process:                    Utility function convers configuration code numbers
                            to the string they represent.
Function Input/Parameters:  Configuration code (int)
Function Output/Parameters: Resulting output string (char *)
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               copyString
*/
void configCodeToString( int code, char *outString );

/*
Name:                       displayConfigData
Process:                    Screen dump/display all config data.
Function Input/Parameters:  Pointer to config data structure (ConfigDataType *)
Function Output/Parameters: None
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      Display config data as specified.
Dependencies:               tbd
*/
void displayConfigData(  ConfigDataType *configData );

/*
Name:                       getConfigData
Process:                    Driver function for capturing configuration data
                            from a config file.
Function Input/Parameters:  File name (const char *)
Function Output/Parameters: Pointer to config data pointer (ConfigDataType **),
                            End/Result state message pointer (char *)
Function Output/Returned:   Boolean result of data access operation (bool)
Device Input/Keyboard:      Config data upload
Device Output/Monitor:      None
Dependencies:               compareString, copyString, fclose, fopen, free,
                            fscanf, getCPUSchedCode, getDataLineCode,
                            getLogToCode, getStringToDelimiter, malloc,
                            setStrToLowerCase, stripTrailingSpaces,
                            valueInRange
*/
bool getConfigData( const char *fileName,
                    ConfigDataType ** configData,
                    char *endStateMsg );

/*
Name:                       getCPUSchedCode
Process:                    Converts CPU schedule string to code
Function Input/Parameters:  Lower case code string (const char *)
Function Output/Parameters: None
Function Output/Returned:   CPU Schedule Code (ConfigDataCodes)
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               compareString
*/
ConfigDataCodes getCPUSchedCode( const char *lowerCaseCodeStr );

/*
Name:                       getDataLineCode
Process:                    Converts leader line string to configuration code
                            value. (All config file leader lines)
Function Input/Parameters:  Config leader line string (const char *)
Function Output/Parameters: None
Function Output/Returned:   Configuration code value (ConfigCodeMessages)
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               compareString
*/
ConfigCodeMessages getDataLineCode( const char *dataBuffer );

/*
Name:                       getLogToCode
Process:                    Converts "log to" text to configuration data code
                            (three log to strings)
Function Input/Parameters:  Lower case log to string (const char *)
Function Output/Parameters: None
Function Output/Returned:   Configuration data code (ConfigDataCodes)
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               compareString
*/
ConfigDataCodes getLogToCode( const char *lowerCaseLogToStr );

/*
Name:                       stripTrailingSpaces
Process:                    Removes trailing spaces from input config leaders
Function Input/Parameters:  Config leader line string (char *)
Function Output/Parameters: Updated config leader line string (char *)
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               getStringLength
*/
void stripTrailingSpaces( char *str );

/*
Name:                       valueInRange
Process:                    Checks for config data values in range,
                            including string values.
Function Input/Parameters:  Line code number for specific config value (int),
                            Integer value, as needed (int),
                            Double value, as needed (double),
                            String value, as needed (const char *)
Function Output/Parameters: None
Function Output/Returned:   Boolean result of range test (bool)
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               compareString
*/
bool valueInRange( int lineCode,
                   int intVal,
                   double doubleVal,
                   const char *lowerCaseStringVal );

#endif // CONFIGOPS_H
