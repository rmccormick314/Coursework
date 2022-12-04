// Preprocessor directive
#ifndef STRING_UTILS_H
#define STRING_UTILS_H

// header files
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dataTypes.h"
#include "StandardConstants.h"

// global constants
extern const Boolean IGNORE_LEADING_WS;

// prototypes
int getStringLength(const char *testStr);
void copyString(char *destStr, const char *sourceStr);
bool getStringConstrained(
			  FILE *inStream,
			  bool clearLeadingNonPrintable,
			  bool clearLeadingSpace,
			  bool stopAtNonPrintable,
			  char delimiter,
			  char *capturedString
			 );
char toLowerCase(char testChar);
bool getStringToDelimiter( 
			  FILE *inStream,
			  char delimiter,
			  char *capturedString
			 );

void getSubString(char *destStr, const char *sourceStr,
		  int startIndex, int endIndex);
int findSubString(const char *testStr, const char *searchSubStr);
bool getStringToLineEnd(
			FILE *inStream,
			char *capturedString
		       );

void setStrToLowerCase(char *destStr, const char *sourceStr);
void concatenateString( char *destStr, const char *sourceStr);
int compareString(const char *oneStr, const char *otherStr);
char toLowerCase(char testChar);



#endif // STRING_UTILS_H
