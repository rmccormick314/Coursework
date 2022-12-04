// Header File
#include "configops.h"

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
ConfigDataType *clearConfigData(ConfigDataType *configData)
{
    // Check that config data pointer is not null
    if(configData != NULL)
    {
        // Free data structure memory
            // Function: free
        free(configData);
        // Set config poitner null
    }
    // Set config data pointer to null
    configData = NULL;

    return NULL;
}

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
void configCodeToString(int code, char *outString)
{
    // Define array with eight items, and short (10) lengths
    char displayStrings[8][10] = {"SJF-N", "SRTF-P", "FCFS-P",
                                  "RR-P", "FCFS-N", "Monitor",
                                  "File", "Both"};

    // Copy String to return parameter
        // Function: copyString
    copyString(outString, displayStrings[code]);
}

/*
 Name: displayConfigData
 Process: Screen/dump/display of all config data
 Function Input/Parameters: Pointer to config data structure (ConfigDataType *)
 Function Output/Parameters: None
 Function Output/Returned: None
 Device Input/Device: None
 Device Output/Monitor: Displayed as specified
 Dependencies: configCodeToString, printf
*/
void displayConfigData(ConfigDataType *configData)
{
    // Initialize function/variables
    char displayString[STD_STR_LEN];

    // Print lines of display for all member values
        // Function: printf, codeToString (translates coded items)
    printf("Config File Display\n");
    printf("-------------------\n");
    printf("Version                : %3.2f\n", configData->version);
    printf("Program file name      : %s\n", configData->metaDataFileName);
    configCodeToString(configData->cpuSchedCode, displayString);
    printf("CPU schedule selection : %s\n", displayString);
    printf("Quantum time     |     : %d\n", configData->quantumCycles);
    printf("Memory Display         : ");
    if(configData->memDisplay)
    {
        printf("On\n");
    }
    else
    {
        printf("Off\n");
    }
    printf("Memory Available       : %d\n", configData->memAvailable);
    printf("Process cycle rate     : %d\n", configData->procCycleRate);
    printf("I/O cycle rate         : %d\n", configData->ioCycleRate);
    configCodeToString(configData->logToCode, displayString);
    printf("Log to selection       : %s\n", displayString);
    printf("Log file name          : %s\n\n", configData->logToFileName);
}

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
bool getConfigData(const char *fileName, ConfigDataType **configData, char *endStateMsg)
{
    // Initialize function/variables

        // Set constant number of data lines
    const int NUM_DATA_LINES = 10;

        // Set read only constant
    const char READ_ONLY_FLAG[] = "r";

        // Create pointer for data input
    ConfigDataType *tempData;

        // Declare other variables
    FILE *fileAccessPtr;
    char dataBuffer[MAX_STR_LEN], lowerCaseDataBuffer[MAX_STR_LEN];
    int intData, dataLineCode, lineCtr = 0;
    double doubleData;

    // Set endStateMsg to success
        // Function: copyString
    char testMsg[] = "Configuration file upload successful";
    copyString(endStateMsg, testMsg);

    // Initialize config data pointer in case of return error
    *configData = NULL;

    // Open file
        // fopen
    fileAccessPtr = fopen(fileName, READ_ONLY_FLAG);

    // Check for file open failure
    if(fileAccessPtr == NULL)
    {
        // Set end state message to config file access error
            // Function: copyString
        char testMsg[] = "Configuration file access error";
        copyString(endStateMsg, testMsg);

        // Return file access error
        return false;
    }

    // Get first line, check for failure
        // Function: getStringToDelimiter, compareString
    if(!getStringToDelimiter(fileAccessPtr, COLON, dataBuffer)
        || compareString(dataBuffer,
                             "Start Simulator Configuration File") != STR_EQ)
    {
        // Close file access
            // Function: fclose
        fclose(fileAccessPtr);

        // Set end state message to corrupt leader line error
            // Function: copyString
        copyString(endStateMsg, "Corrupt configuration leader line error");

        // Return corrupt file data
        return false;
    }
    // Create temporary pointer to configuration data structure
        // Function: malloc
    tempData = (ConfigDataType *)malloc(sizeof(ConfigDataType));

    // Loop to end of config data items
    while(lineCtr < NUM_DATA_LINES)
    {
        // Get line leader, check for failure
            // Function: getStringToDelimiter
        if(!getStringToDelimiter(fileAccessPtr, COLON, dataBuffer))
        {
            // Free temp struct memory
                // Function: free
            free(tempData);

            // Close file access
                // Function: fclose
            fclose(fileAccessPtr);

            // Set end state message to line capture failure
            copyString(endStateMsg,
                            "Configuration data leader line capture error");

            // Return incomplete file error
            return false;
        }
        // Strip trailing spaces of config leader lines
        // for use in other functions
            // Function: stripTrailingSpaces
        stripTrailingSpaces(dataBuffer);

        // Find correct data line code number from string
            // Function: getDataLineCode
        dataLineCode = getDataLineCode(dataBuffer);

        // Check for data line found
        if(dataLineCode != CFG_CORRUPT_PROMPT_ERR)
        {
            // Get value

            // Check for version number (double value)
            if(dataLineCode == CFG_VERSION_CODE)
            {
                // Get version number
                    // Function: fscanf
                fscanf(fileAccessPtr, "%lf", &doubleData);
            }
            // Otherwise, check for metaData, file names,
            // CPU Scheduling names, or memory display settings (strings)
            else if(dataLineCode == CFG_MD_FILE_NAME_CODE
                    || dataLineCode == CFG_LOG_FILE_NAME_CODE
                       || dataLineCode == CFG_CPU_SCHED_CODE
                          || dataLineCode == CFG_LOG_TO_CODE
                             || dataLineCode == CFG_MEM_DISPLAY_CODE)
            {
                // Get string input
                    // Function: fscanf
                fscanf(fileAccessPtr, "%s", dataBuffer);

                // Set string to lower case for testing in valueInRange
                    // Function: setStrToLowerCase
                setStrToLowerCase(lowerCaseDataBuffer, dataBuffer);
            }
            // Otherwise, assume integer data
            else
            {
                // Get integer input
                    // Function: fscanf
                fscanf(fileAccessPtr, "%d", &intData);
            }
            // Check for data value in range
                // Function: valueInRange
            if(valueInRange(dataLineCode, intData,
                                            doubleData, lowerCaseDataBuffer))
            {
                // Assign to data pointer depending on config item
                // (all config line possinilities)
                    // Function: copyString, getCPUSchedCode,
                    // compareString, getLogToCode, as needed
                switch(dataLineCode)
                {
                    case CFG_VERSION_CODE:

                        tempData->version = doubleData;
                        break;

                    case CFG_MD_FILE_NAME_CODE:

                        copyString(tempData->metaDataFileName, dataBuffer);
                        break;

                    case CFG_CPU_SCHED_CODE:

                        tempData->cpuSchedCode =
                                        getCpuSchedCode(lowerCaseDataBuffer);

                    case CFG_QUANT_CYCLES_CODE:

                        tempData->quantumCycles = intData;
                        break;

                    case CFG_MEM_DISPLAY_CODE:

                        tempData->memDisplay =
                                compareString(lowerCaseDataBuffer, "on") == 0;
                        break;

                    case CFG_MEM_AVAILABLE_CODE:

                        tempData->memAvailable = intData;
                        break;

                    case CFG_PROC_CYCLES_CODE:

                        tempData->procCycleRate = intData;
                        break;

                    case CFG_IO_CYCLES_CODE:

                        tempData->ioCycleRate = intData;
                        break;

                    case CFG_LOG_TO_CODE:

                        tempData->logToCode =
                                            getLogToCode(lowerCaseDataBuffer);
                        break;

                    case CFG_LOG_FILE_NAME_CODE:

                        copyString(tempData->logToFileName, dataBuffer);
                        break;
                }
            }
            else
            {
            // Otheriwse, assume data value not in range

                // Free temp struct memory
                    // Function: free
                free(tempData);

                // Close file access
                    // Function: fclose
                fclose(fileAccessPtr);

                // Set end state message to configuration data out of range
                    // Function: copyString
                copyString(endStateMsg, "Configuaration item out of range");

                // Return data out of range
                return false;
            }
        }
        else
        {
        // Otherwise, assume data line not found

            // Free temp struct memory
                // Function: free
            free(tempData);

            // Close file access
                // Function: fclose
            fclose(fileAccessPtr);

            // Set end state message to configuratino corrupt prompt error
                // Function: copyString
            copyString(endStateMsg, "Corrupted configuration prompt");

            // Return corrupt config file code
            return false;
        }
        // Increment line counter
        lineCtr++;
    }
    // End master loop

    // Aquire end of sim config string
        // Function: getStringToDelimiter, compareString
    if(!getStringToDelimiter(fileAccessPtr, PERIOD, dataBuffer)
       || compareString(dataBuffer, "End Simulator Configuration File")
                                                                    != STR_EQ)
    {
        // Free temp struct memory
            // Function: free
        free(tempData);
        // Close file access
            // Function: fclose
        fclose(fileAccessPtr);

        // Set end state message to corrupt configuration end line
            // Function: copyString
        copyString(endStateMsg, "Configuration end line capture error");

        // Return corrupt file data
        return false;
    }
    // Test for "File only" output so memory diagnostics do not display
    tempData->memDisplay = tempData->memDisplay
                                && tempData->logToCode != LOGTO_FILE_CODE;

    // Assign temporary pointer to parameter return pointer
    *configData = tempData;

    // Close file access
        // Function: fclose
    fclose(fileAccessPtr);

    // Return no error code
    return true;
}

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
ConfigDataCodes getCpuSchedCode(const char *lowerCaseCodeStr)
{
    // Initialize function/variables

        // Set default return to FCFS-N
    ConfigDataCodes returnVal = CPU_SCHED_FCFS_N_CODE;

    // Check for SJF-N
        // Function: compareString
    if(compareString(lowerCaseCodeStr, "sjf-n") == STR_EQ)
    {
        // Set SJF-N code
        returnVal = CPU_SCHED_SJF_N_CODE;
    }
    // Check for SRTF-P
        // Function: compareString
    if(compareString(lowerCaseCodeStr, "srtf-p") == STR_EQ)
    {
        // Set SRTF-P code
        returnVal = CPU_SCHED_SRTF_P_CODE;
    }
    // Check for FCFS-P
        // Function: compareString
    if(compareString(lowerCaseCodeStr, "fcfs-p") == STR_EQ)
    {
        // Set FCFS-P code
        returnVal = CPU_SCHED_FCFS_P_CODE;
    }
    // Check for RR-P
        // Function: compareString
    if(compareString(lowerCaseCodeStr, "rr-p") == STR_EQ)
    {
        // Set RR-P code
        returnVal = CPU_SCHED_RR_P_CODE;
    }

    // Return the selected value
    return returnVal;
}

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
ConfigCodeMessages getDataLineCode(const char *dataBuffer)
{
    // Return appropriate code depending on prompt string provided
        // Function: compareString
    if(compareString(dataBuffer, "Version/Phase") == STR_EQ)
    {
        return CFG_VERSION_CODE;
    }

    if(compareString(dataBuffer, "File Path") == STR_EQ)
    {
        return CFG_MD_FILE_NAME_CODE;
    }

    if(compareString(dataBuffer, "CPU Scheduling Code") == STR_EQ)
    {
        return CFG_CPU_SCHED_CODE;
    }

    if(compareString(dataBuffer, "Quantum Time (cycles)") == STR_EQ)
    {
        return CFG_QUANT_CYCLES_CODE;
    }

    if(compareString(dataBuffer, "Memory Display (On/Off)") == STR_EQ)
    {
        return CFG_MEM_DISPLAY_CODE;
    }

    if(compareString(dataBuffer, "Memory Available (KB)") == STR_EQ)
    {
        return CFG_MEM_AVAILABLE_CODE;
    }

    if(compareString(dataBuffer, "Processor Cycle Time (msec)")
                                                == STR_EQ)
    {
        return CFG_PROC_CYCLES_CODE;
    }

    if(compareString(dataBuffer, "I/O Cycle Time (msec)") == STR_EQ)
    {
        return CFG_IO_CYCLES_CODE;
    }

    if(compareString(dataBuffer, "Log To") == STR_EQ)
    {
        return CFG_LOG_TO_CODE;
    }

    if(compareString(dataBuffer, "Log File Path") == STR_EQ)
    {
        return CFG_LOG_FILE_NAME_CODE;
    }

    // Return corrupt leader line error code
    return CFG_CORRUPT_PROMPT_ERR;
}

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
ConfigDataCodes getLogToCode(const char *lowerCaseLogToStr)
{
    // Initialize function/variables

        // Set default to log to monitor
    ConfigDataCodes returnVal = LOGTO_MONITOR_CODE;

    // Check for BOTH
        // Function: CompareString
    if(compareString(lowerCaseLogToStr, "both") == STR_EQ)
    {
        // Get return value to both code
        returnVal = LOGTO_BOTH_CODE;
    }
    // Check for FILE
        // Function: compareString
    if(compareString(lowerCaseLogToStr, "file") == STR_EQ)
    {
        // Get return value to file code
        returnVal = LOGTO_FILE_CODE;
    }

    return returnVal;
}

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
void stripTrailingSpaces(char *str)
{

    // Intitialize index to length of string -1 to get highest array index
    int index = getStringLength(str) - 1;

    // Loop while space is found at end of string
    while(str[index] == SPACE)
    {
        // Set element to NULL_CHAR
        str[index] = NULL_CHAR;

        // Decrement index
        index--;
    }
    // End loop from end of string
}


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
                                            const char *lowerCaseStringVal)
{
    // Initialize function/variables

        // Set result to true, all tests are to find false
    bool result = true;

    // Use line code to indentify prompt line
    switch(lineCode)
    {
        // For version code
        case CFG_VERSION_CODE:
            // Check if limits of version code are exceeded
            if(doubleVal < 0.00 || doubleVal > 10.00)
            {
                // Set boolean result to false
                result = false;
            }
            // Break
            break;

        // For cpu scheduling code
        case CFG_CPU_SCHED_CODE:
            // Check for not finding one of the scheduling strings
                // Function: compareString
            if(compareString(lowerCaseStringVal, "fcfs-n") != STR_EQ
               && compareString(lowerCaseStringVal, "sjf-n") != STR_EQ
               && compareString(lowerCaseStringVal, "srtf-p") != STR_EQ
               && compareString(lowerCaseStringVal, "fcfs-p") != STR_EQ
               && compareString(lowerCaseStringVal, "rr-p") != STR_EQ)
            {
                // Set boolean result to false
                result = false;
            }
            // Break
            break;

        // For quantum cycles
        case CFG_QUANT_CYCLES_CODE:
            // Check for quantum cycles limits exceeded
            if(intVal < 0 || intVal > 100)
            {
                // Set boolean result to false
                result = false;
            }
            // Break
            break;

        // For memory display
        case CFG_MEM_DISPLAY_CODE:
            // Check for not finding either "on" or "off"
                // Function: compareString
            if(compareString(lowerCaseStringVal, "on") != STR_EQ
                && compareString(lowerCaseStringVal, "off") != STR_EQ)
            {

                // Set boolean result to false
                result = false;
            }

            // Break
            break;

        // For memory available
        case CFG_MEM_AVAILABLE_CODE:
            // Check for available memory limits exceeded
            if(intVal < 1024 || intVal > 102400)
            {
                // Set boolean result to false
                result = false;
            }

            // Break
            break;
        // Check for process cycles
        case CFG_PROC_CYCLES_CODE:
            // Check for process cycles limits exceeded
            if(intVal < 1 || intVal > 100)
            {
                // Set boolean result to false
                result = false;
            }
            // Break
            break;

        // Check for I/O cycles
        case CFG_IO_CYCLES_CODE:

            // Check for I/O cycles limits exceeded
            if(intVal < 1 || intVal > 1000)
            {
                // Set boolean result to false
                result = false;
            }
            // Break
            break;

        // Check for log to operation
        case CFG_LOG_TO_CODE:
            // Check for not finding one of the log to strings
                // Function: compareString
            if(compareString(lowerCaseStringVal, "both") != STR_EQ
               && compareString(lowerCaseStringVal, "monitor") != STR_EQ
               && compareString(lowerCaseStringVal, "file") != STR_EQ)
            {
                // Set boolean result to false
                result = false;
            }
            // Break
            break;
    }
    // Return result of limits analysis

    return result;
}
