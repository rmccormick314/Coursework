// Used educational coding vidoes from Michael Leverington for this assignment
// Luke Frazer

// header files
#include "OS_SimDriver.h"

/*
Name: clearConfigData
Process: frees dynamically allocated config data structure
         if it has not already been freed
Fucntion Input/Parameters: pointer to config data structure (ConfigDataType *)
Function Output/Parameters: none
Function Output/Returned: NULL (ConfigDataType *)
Device Input/Keybaord: none
Device Output/Monitor: none
Dependencies: tbd
*/
ConfigDataType *clearConfigData(ConfigDataType *configData)
{
    // check that config data pointer is not null
    if(configData != NULL)
    {
        // free data structure memory 
        free(configData);

        // set config pointer to NULL
        configData = NULL;
        
    }

    // return NULL config Data pointer
    return NULL;
}

/*
Name: configCodeToString
Process: utility function converts configuration code numbers
         to the string they represent
Fucntion Input/Parameters: configuration code (int)
Function Output/Parameters: resulting output string (char *)
Function Output/Returned: none
Device Input/Keybaord: none
Device Output/Monitor: none
Dependencies: copyString
*/
void configCodeToString(int code, char *outString)
{
   // define array with eight items, and short (10) lengths
   char displayStrings[8][10] = 
   {
    "SJF-N", "SRTF-P", 
    "FCFS-P", "RR-P", 
    "FCFS-N", "Monitor", 
    "File", "Both"
    };

   // copy string data to return parameter
   copyString(outString, displayStrings[code]);

}

/*
Name: displayConfigData
Process: screen dump/display of all config data
Fucntion Input/Parameters: pointer to config data structure (ConfigDataType *)
Function Output/Parameters: none
Function Output/Returned: none
Device Input/Keybaord: none
Device Output/Monitor: displayed as specified
Dependencies: tbd
*/
void displayConfigData(ConfigDataType *configData)
{
    // initialize function/vars
    char displayString[STD_STR_LEN];

    // print lines of display for all member values
    printf("Config File Display\n");
    printf("-------------------\n");
    printf("Version                : %3.2f\n", configData->version);
    printf("Program file name      : %s\n", configData->metaDataFileName);
    configCodeToString(configData->cpuSchedCode, displayString);
    printf("CPU schedule selection : %s\n", displayString);
    printf("Quantum time           : %d\n", configData->quantumCycles);
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
Process: driver function for capturing configuration data from a config file
Fucntion Input/Parameters: file name (const char *)
Function Output/Parameters: pointer to config data pointer (ConfigDataType **)
Function Output/Returned: boolean result of data access operation (bool)
Device Input/Keybaord: config data uploaded
Device Output/Monitor: none
Dependencies: copyString, fopen, getStringToDelimiter, compareString, fclose, 
              malloc, free, stripTrailingSpaces, getDataLineCode, fscanf,
              setStrToLowerCase, valueInRange, getCpuSchedCode, getLogToCode
*/
bool getConfigData(const char *fileName, 
                                ConfigDataType **configData, char *endStateMsg)
{
    // initialize function
    
        // set constant number of data lines
        const int NUM_DATA_LINES = 10;

        // set read only constant
        const char READ_ONLY_FLAG[] = "r";

        // create pointer for data input
        ConfigDataType *tempData;

        // declare other variables
        FILE *fileAccessPtr;
        char dataBuffer[MAX_STR_LEN], lowerCaseDataBuffer[MAX_STR_LEN];
        int intData, dataLineCode, lineCtr = 0;
        double doubleData;

    // set endStateMsg to success
    char testMsg[] = "Configuration file upload successful";
    copyString(endStateMsg, testMsg);

    // initialize config data pointer in case of return error
    *configData = NULL;

    // open file
    fileAccessPtr = fopen(fileName, READ_ONLY_FLAG);

    // check for file open failure
    if(fileAccessPtr == NULL)
    {
        // set end state message to config file access error
        char testMsg[] = "Configuration file access error";
        copyString(endStateMsg, testMsg);

        // return file access error
        return false;

    }

    // get first line, check for failure
    if(!getStringToDelimiter(fileAccessPtr, COLON, dataBuffer)
        || compareString(dataBuffer, 
                            "Start Simulator Configuration File") != STR_EQ)
    {
        // close file access
        fclose(fileAccessPtr);

        // set end state message to corrupt leader line error
        copyString(endStateMsg, "Corrupt configuration leader line error");

        // return corrupt file data
        return false;

    }

    // create temporary pointer to config data structure
    tempData = (ConfigDataType *) malloc(sizeof(ConfigDataType));

    // loop to end of config data items
    while(lineCtr < NUM_DATA_LINES)
    {
        // get line leader, check for failure
        if(!getStringToDelimiter(fileAccessPtr, COLON, dataBuffer))
        {
            // free temp struct memory
            free(tempData);

            // close the file access
            fclose(fileAccessPtr);

            // set end state message to line capture failure
            copyString(endStateMsg, 
                            "Configuration data leader line capture error");

            // return incomplete file error
            return false;
            
        }

        // strip trailing spaces of config leader lines
        // for use in other functions
        stripTrailingSpaces(dataBuffer);

        // find the correct data line code number from string
        dataLineCode = getDataLineCode(dataBuffer);

        // check for data line found
        if(dataLineCode != CFG_CORRUPT_PROMPT_ERR)
        {
            // get data value
                
                // check for version number (double value)
                if(dataLineCode == CFG_VERSION_CODE)
                {
                    // get version number
                    fscanf(fileAccessPtr, "%lf", &doubleData);

                }

                // otherwise, check for metaData, file names, 
                //  CPU scheduling names, or memory display settings (strings)
                else if(dataLineCode == CFG_MD_FILE_NAME_CODE
                            || dataLineCode == CFG_LOG_FILE_NAME_CODE
                            || dataLineCode == CFG_CPU_SCHED_CODE
                            || dataLineCode == CFG_LOG_TO_CODE
                            || dataLineCode == CFG_MEM_DISPLAY_CODE)
                {
                    // get string input
                    fscanf(fileAccessPtr, "%s", dataBuffer);

                    // set string to lower case for testing in valueInRange
                    setStrToLowerCase(lowerCaseDataBuffer, dataBuffer);

                }

                // otherwise, assume integer data
                else
                {
                    // get integer input
                    fscanf(fileAccessPtr, "%d", &intData);

                }

            // check for data value in range
            if(valueInRange(dataLineCode, intData, 
                                            doubleData, lowerCaseDataBuffer))
            {
                // assign to data pointer depending on config item
                // (all config line possibilities)
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
                        break;

                    case CFG_QUANT_CYCLES_CODE:

                        tempData->quantumCycles = intData;
                        break;

                    case CFG_MEM_DISPLAY_CODE:

                        tempData->memDisplay
                             = compareString(lowerCaseDataBuffer, "on") == 0;
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

                        tempData->logToCode = getLogToCode(lowerCaseDataBuffer);
                        break;

                    case CFG_LOG_FILE_NAME_CODE:

                        copyString(tempData->logToFileName, dataBuffer);
                        break;
                }
            }

            // otherwise, assume data value not in range
            else
            {
                // free temp struct memory
                free(tempData);

                // close file access
                fclose(fileAccessPtr);

                // set end state message to configuration data out of range
                copyString(endStateMsg, "Configuration item out of range");

                // return data out of range
                return false;

            }
        }

        // otherwise, assume data line not found
        else
        {
            // free temp struct memory
            free(tempData);

            // close the file access
            fclose(fileAccessPtr);

            // set end state message to configuration corrupt prompt error
            copyString(endStateMsg, "Corrupted configuration prompt");

            // return corrupt config file code
            return false;

        }

        // increment line counter
        lineCtr++;

    }
    // end master loop

    // acquire end of sim config string
    if(!getStringToDelimiter(fileAccessPtr, PERIOD, dataBuffer)
    || compareString(dataBuffer, "End Simulator Configuration File") != STR_EQ)
    {
        // free temp struct memory 
        free(tempData);

        // close file access
        fclose(fileAccessPtr);

        // set end state message to corrypt config end line
        copyString(endStateMsg, "Configuration end line capture error");

        // return corrupt file data
        return false;

    }

    // test for "file only" output so memory diagnostics do not display
    tempData->memDisplay = tempData->memDisplay 
                                    && tempData->logToCode != LOGTO_FILE_CODE;

    // assign temporary pointer to parameter return pointer
    *configData = tempData;

    // close file access
    fclose(fileAccessPtr);

    // return no error code
    return true;
}

/*
Name: getCpuSchedCode
Process: converts cpu schedule string to code (all scheduling possibilities)
Fucntion Input/Parameters: lower case code string (const char *)
Function Output/Parameters: none
Function Output/Returned: cpu schedule code (ConfigDataCodes)
Device Input/Keybaord: none
Device Output/Monitor: none
Dependencies: compareString
*/
ConfigDataCodes getCpuSchedCode(const char *lowerCaseCodeStr)
{
    // initialize function/vars

        // set default return to FCFS-N
        ConfigDataCodes returnVal = CPU_SCHED_FCFS_N_CODE;

    // check for SJF-N
    if(compareString(lowerCaseCodeStr, "sjf-n") == STR_EQ)
    {
        // set JSF-N code
        returnVal = CPU_SCHED_SJF_N_CODE;
    }

    // check for SRTF-P
    if(compareString(lowerCaseCodeStr, "srtf-p") == STR_EQ)
    {
        // set SRTF-P code
        returnVal = CPU_SCHED_SRTF_P_CODE;
    }

    // check for FCFS-P
    if(compareString(lowerCaseCodeStr, "fcfs-p") == STR_EQ)
    {
        // set FCFS-P code
        returnVal = CPU_SCHED_FCFS_P_CODE;
    }

    // check for RR-P
    if(compareString(lowerCaseCodeStr, "rr-p") == STR_EQ)
    {
        // set RR-P code
        returnVal = CPU_SCHED_RR_P_CODE;
    }

    // return selected value    
    return returnVal;
}

/*
Name: getDataLineCode
Process: converts leader line string to configuration code value 
         (all config file leader lines)
Fucntion Input/Parameters: config leader line string (const char *)
Function Output/Parameters: none
Function Output/Returned: configuration code value (ConfigCodeMessages)
Device Input/Keybaord: none
Device Output/Monitor: none
Dependencies: compareString
*/
ConfigCodeMessages getDataLineCode(const char *dataBuffer)
{
    // return appropriate code depending on prompt string provided
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

    if(compareString(dataBuffer, "Processor Cycle Time (msec)") == STR_EQ)
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

    // return corrupt leader line error code
    return CFG_CORRUPT_PROMPT_ERR;
}

/*
Name: getLogToCode
Process: converts "log to" text to config data code
         (three log to strings)
Fucntion Input/Parameters: lower case log to string (const char *)
Function Output/Parameters: none
Function Output/Returned: selected code
Device Input/Keybaord: none
Device Output/Monitor: none
Dependencies: compareString
*/
ConfigDataCodes getLogToCode(const char *lowerCaseLogToStr)
{
    // initialize function/vars

        // set default to log to monitor
        ConfigDataCodes returnVal = LOGTO_MONITOR_CODE;

    // check for BOTH
    if(compareString(lowerCaseLogToStr, "both") == STR_EQ)
    {
        // set return value to both code 
        returnVal = LOGTO_BOTH_CODE;
    }

    // check for FILE 
    if(compareString(lowerCaseLogToStr, "file") == STR_EQ)
    {
        // set return value to file code
        returnVal = LOGTO_FILE_CODE;
    
    }

    // return selected code
    return returnVal;
}

/*
Name: stripTrailingSpaces
Process: removes trailing spaces from input config leader lines
Fucntion Input/Parameters: config leader line string (char *)
Function Output/Parameters: updated config leader line string (char *)
Function Output/Returned: none
Device Input/Keybaord: none
Device Output/Monitor: none
Dependencies: getStringLength
*/
void stripTrailingSpaces(char *str)
{
    // initialize index to length of string - 1 to get highest array index 
    int index = getStringLength(str) - 1;

    // loop while space is found at end of string
    while(str[index] == SPACE)
    {
        // set element to NULL_CHAR
        str[index] = NULL_CHAR;

        // decrement index
        index--;
    
    }
    // end loop from end of string
}

/*
Name: valueInRange
Process: checks for config data values in range, including string values
         (all config data values)
Fucntion Input/Parameters: line code number for specific config value (int),
                           integer value, as needed (int),
                           double value, as needed (double)
                           string value, as needed (const char *)
Function Output/Parameters: none
Function Output/Returned: boolean result of range test (bool)
Device Input/Keybaord: none
Device Output/Monitor: none
Dependencies: compareString
*/
bool valueInRange(int lineCode, int intVal, double doubleVal, 
                                                const char *lowerCaseStringVal)
{
    // initialize function/vars

        // set result to true, all tests are to find false
        bool result = true;

    // use line code to identify prompt line
    switch(lineCode)
    {
        // for version code
        case CFG_VERSION_CODE:

            // check if limits of version code are exceeded
            if(doubleVal < 0.00 || doubleVal > 10.00)
            {
                // set boolean result to false
                result = false;

            }

            // break
            break;

        // for cpu scheduling code
        case CFG_CPU_SCHED_CODE:
        
            // check for not finding one of the scheduling strings
            if(compareString(lowerCaseStringVal, "fcfs-n") != STR_EQ
               && compareString(lowerCaseStringVal, "sjf-n") != STR_EQ
               && compareString(lowerCaseStringVal, "srtf-p") != STR_EQ
               && compareString(lowerCaseStringVal, "fcfs-p") != STR_EQ
               && compareString(lowerCaseStringVal, "rr-p") != STR_EQ)
               {
                // set boolean results to false
                result = false;               
                    
               }

            // break
            break;

        // for quantum cycles
        case CFG_QUANT_CYCLES_CODE:

            // check for quantum cycles limits exceeded
            if(intVal < 0 || intVal > 100)
            {
                // set boolean result to false
                result = false;
            
            }

            // break
            break;

        // for memory display
        case CFG_MEM_DISPLAY_CODE: 

            // check for not finding either "on" or "off"
            if(compareString(lowerCaseStringVal, "on") != STR_EQ
               && compareString(lowerCaseStringVal, "off") != STR_EQ)
            {
                // set boolean result to false
                result = false;
            
            }

            // break
            break;

        // for memory available
        case CFG_MEM_AVAILABLE_CODE:

            // check for available limits exceeded 
            if(intVal < 1024 || intVal > 102400)
            {
                // set boolean result to false
                result = false;

            }

            // break
            break;

        // check for process cycles
        case CFG_PROC_CYCLES_CODE:

            // check for process cycles limits exceeded
            if(intVal < 1 || intVal > 100)
            {    
                // set boolean result to false
                result = false;
            
            }

            // break
            break;

        // check for I/O cycles
        case CFG_IO_CYCLES_CODE:

            // check for I/O cycle limits exceeded
            if(intVal < 1 || intVal > 1000)
            {
                // set boolean result to false
                result = false;

            }

            // break
            break;

        // check for log to operation
        case CFG_LOG_TO_CODE:

            // check for not finding on of the log to strings
            if(compareString(lowerCaseStringVal, "both") != STR_EQ
               && compareString(lowerCaseStringVal, "monitor") != STR_EQ
               && compareString(lowerCaseStringVal, "file") != STR_EQ)
            {
                // set boolean result to false
                result = false;
            
            }

            // break
            break;
    }

    // return result of limits analysis
    return result;
}