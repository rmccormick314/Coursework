#ifndef CONFIG_OPS_H
#define CONFIG_OPS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "stringUtils.h"
#include "datatypes.h"

// ==== Structs ====

typedef struct ConfigDataType
{
    double version;
    char metaDataFileName[ LARGE_STR_LEN ];
    int cpuSchedCode;
    int quantumCycles;
    bool memDisplay;
    int memAvailable;
    int procCycleRate;
    int ioCycleRate;
    int logToCode;
    char logToFileName[ LARGE_STR_LEN ];
} ConfigDataType;

// ==== Function Prototypes ====

/*
 Name: clearConfigData
 Process: Frees dynamically allocated config data structure
          if it has not already been freed
 Function Input/Parameters: Pointer to config data structure (ConfigDataType *)
 Function Output/Parameters: None
 Function Output/Returned: NULL (ConfigDataType *)
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: free
*/
ConfigDataType *clearConfigData(ConfigDataType *configData);

/*
 Name: configCodeToString
 Process: Utility function converts configuration code numbers
          to the string they represent
 Function Input/Parameters: configuration code (int)
 Function Output/Parameters: resulting output string (char *)

 Function Output/Returned: None
 Device Input/Device: None
 Device Output/monitor: None
 Dependencies: copyString
*/
void configCodeToString(int code, char *outString);

/*
 Name: getConfigData
 Process: Driver function for capturing configuration data from a config file
 Function Input/Parameters: File name (const char *)
 Function Output/Parameters: Pointer to ocnfig data pointer (ConfigDataType **),
                             end/result state message pointer (char*)
 Function Output/Returned: Boolean result of data access operation (bool)
 Device Input/File: Confiig data uploaded
 Device Output/Device: None
 Dependencies: compareString, copyString, fclose, fopen, free, fscanf,
               getDataLineCode, getStringToDelimiter, malloc,
               setStrToLowerCase, stripTrailingSpaces, valueInRange
*/
void displayConfigData(ConfigDataType *configData);

/*
 Name: getConfigData
 Process: Driver function for capturing configuration data from a config file
 Function Input/Parameters: File name (const char *)
 Function Output/Parameters: Pointer to ocnfig data pointer (ConfigDataType **),
                             end/result state message pointer (char*)
 Function Output/Returned: Boolean result of data access operation (bool)
 Device Input/File: Confiig data uploaded
 Device Output/Device: None
 Dependencies: TBD
*/
bool getConfigData(const char *fileName, ConfigDataType **configData, char *endStateMsg);

/*
 Name: getCpuSchedCode
 Process: Converts CPU scedule string to code (all scheduling possibilities)
 Function Input/Parameters: Lower case code string (const char *)
 Function OutputParameters: None
 Function Output/Returned: CPU schedule code (ConfigDataCodes)
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: compareString
*/
ConfigDataCodes getCpuSchedCode(const char *lowerCaseCodeStr);

/*
 Name: getDataLineCode
 Process: Converts leader line string to configuration code value
          (all config file leader lines)
 Function Input/Parameters: Config leader line string (const char*)
 Function Output/Parameters: None
 Function Output/Returned: Configuration code value (ConfigCodeMessages)
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: compareString
 */
ConfigCodeMessages getDataLineCode(const char *dataBuffer);

/*
 Name getLogToCode
 Process: Converts "Log to" text to configuration code
          (three log to strings)
 Function Input/Parameters: Lower case log to string (const char *)
 Function Output/Parameters: None
 Function Output/Returned: Configuration data code value (ConfigDataCodes)
 Device Input/Device: None
 Device Ouptut/Device: None
 Dependencies: compareString
*/
ConfigDataCodes getLogToCode(const char *lowerCaseLogToStr);

/*
 Name: stripTrialingSpaces
 Process: Removes trailing spaces from input config leader lines
 Function Input/Parameters: Config leader line string (char *)
 Function Output/Parameters: Updated conig leader line string (char *)
 Function Output/Returned: None
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: getStringLength
*/
void stripTrailingSpaces(char *str);

/*
 Name valueInRange
 Process: Checks for config data values in range, including string values
          (all config data values)
 Function Input/Parameters: Line code number for specific config value (int),
                            integer value, as needed (int),
                            double value, as needed (double),
                            string value, as needed (const char *)
 Function Output/Parameters: None
 Function Output/Returned: Boolean result of range test (bool)
 Device Input/Device: None
 Device Output/Device: None
 Dependencies: compareString
*/
bool valueInRange(int lineCode, int intVal, double doubleVal,
                                            const char *lowerCaseStringVal);


#endif // CONFIG_OPS_H
