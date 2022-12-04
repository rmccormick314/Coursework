#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <stdio.h>
#include <stdbool.h>

#include "StandardConstants.h"

int compareString(const char *oneStr, const char *otherStr);
void concatenateString(char *destStr, const char *sourceStr);
void copyString(char *destStr, const char *sourceStr);
int findSubString(const char *testStr, const char *searchSubStr);
bool getStringConstrained(FILE *inStream,
                          bool clearLeadingNonPrintable,
                          bool clearLeadingSpace,
                          bool stopAtNonPrintable,
                          char delimiter,
                          char *capturedString);
int getStringLength(const char *testStr);
bool getStringToDelimiter(FILE *inStream, char delimiter, char *capturedString);
void setStrToLowerCase(char *destStr, const char *sourceStr);
char toLowerCase(char testChar);
bool getStringToLineEnd(FILE *inStream, char *captureString);
void getSubString(char *destStr, const char *sourceStr,
                  int startIndex, int endIndex);

#endif // STRING_UTILS_H
