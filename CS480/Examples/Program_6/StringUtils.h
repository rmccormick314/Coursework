// Preprocessor directive
#ifndef STRING_UTILS_H
#define STRING_UTILS_H

// Header files
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "StandardConstants.h"

// Prototypes
int compareString( const char *leftStr, const char *rightStr );
void concatenateString( char *destStr, const char *sourceStr );
void copyString( char *destStr, const char *sourceStr );
int findSubString( const char *testStr, const char *searchSubStr );
bool getStringConstrained(
                         FILE *inStream,
                         bool clearLeadingNonPrintable,
                         bool clearLeadingSpace,
                         bool stopAtNonPrintable,
                         char delimiter,
                         char *capturedString
                       );
bool getStringToDelimiter(
                         FILE *inStream,
                         char delimiter,
                         char *capturedString
                       );
int getStringLength( const char *testStr );
bool getStringToLineEnd(
                        FILE *inStream,
                        char *capturedString
                      );
void getSubString( char *destStr, const char *sourceStr,
                  int startIndex, int endIndex );
void setStrToLowerCase( char *destStr, const char *sourceStr );
int toLowerCase( char testChar );

#endif // STRING_UTILS_H
