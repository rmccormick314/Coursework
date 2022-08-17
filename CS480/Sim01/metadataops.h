// Protect from multiple compilations
#ifndef METADATAOPS_H
#define METADATAOPS_H

// Header files
#include <stdio.h>
#include "datatypes.h"

// Function prototypes
OpCodeType *clearMetaDataList( OpCodeType *localPtr );
void displayMetaData( const OpCodeType *localPtr );
bool getMetaData( const char *fileName,
                  OpCodeType **opCodeDataHead,
                  char *endStateMsg );

#endif // METADATAOPS_H
