// Luke Frazer
// Used educational coding vidoes from Michael Leverington for this assignment

// preprocessor directive
#ifndef STRING_UTILS_H
#define STRING_UTILS_H

// header files
#include "OS_SimDriver.h"
#include "StandardConstants.h"
#include "datatypes.h"

// prototype functions for StringUtils
int compareString(const char *oneStr, const char *otherStr);
void concatenateString(char *destStr, const char *sourceStr);
void copyString(char *destStr, const char *sourceStr);
int findSubString(const char *testStr, const char *searchSubStr);
bool getStringConstrained(FILE *inStream, bool clearLeadingNonPrintable,
                          bool clearLeadingSpace, bool stopAtNonPrintable,
                          char delimiter, char *capturedString);
int getStringLength(const char *testStr);
bool getStringToDelimiter(FILE *inStream, char delimiter, char *capturedString);
bool getStringToLineEnd(FILE *inStream, char *capturedString);
void getSubString(char *destStr, const char *sourceStr, 
                                             int startIndex, int endIndex);
void setStrToLowerCase(char *destStr, const char *sourceStr);
char toLowerCase(char testChar);

#endif // STRING UTILS