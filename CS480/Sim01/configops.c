// Header files
#include "configops.h"

// Functions
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
Dependencies:               tbd
*/
ConfigDataType *clearConfigData( ConfigDataType *configData )
   {
      // Stub function

      return NULL; // Temporary stub return
   }

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
void displayConfigData(  ConfigDataType *configData )
   {
      // Stub function

      // Void function, no return
   }

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
Dependencies:               tbd
*/
bool getConfigData( const char *fileName,
                    ConfigDataType ** configData,
                    char *endStateMsg )
   {
      // Stub function

      return false; // Temporary stub return
   }
