// Protect from multiple compilations
#ifndef SIMULATOR_H
#define SIMULATOR_H

// Header files
#include <stdio.h>
#include "datatypes.h"

// Function prototypes
/*
Name:                       runSim
Process:                    Primary simulation driver.
Function Input/Parameters:  Configuration data (ConfigDataType *),
                            Metadata (OpCodeType *)
Function Output/Parameters: None
Function Output/Returned:   None
Device Input/Keyboard:      None
Device Output/Monitor:      None
Dependencies:               tbd
*/
void runSim( ConfigDataType *configPtr,
             OpCodeType *metaDataMstrPtr );

#endif // SIMULATOR_H
