// Protect from multiple compilations
#ifndef CONFIGOPS_H
#define CONFIGOPS_H

// Header files
#include <stdio.h>
#include "datatypes.h"

// Function prototypes
ConfigDataType *clearConfigData( ConfigDataType *configData );
void displayConfigData(  ConfigDataType *configData );
bool getConfigData( const char *fileName,
                    ConfigDataType ** configData,
                    char *endStateMsg );

#endif // CONFIGOPS_H
