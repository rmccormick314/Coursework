// Protect from multiple compilations
#ifndef SIMULATOR_H
#define SIMULATOR_H

// Header files
#include <stdio.h>
#include "datatypes.h"

// Function prototypes
void runSim( ConfigDataType *configPtr,
             OpCodeType *metaDataMstrPtr );

#endif // SIMULATOR_H
