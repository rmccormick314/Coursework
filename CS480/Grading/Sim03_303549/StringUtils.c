//header files
#include "StringUtils.h"


/*
Name compareString
*/
int compareString( const char *oneStr, const char *otherStr )
    {
        int diff, index = 0;

        while ( oneStr[ index ] != NULL_CHAR &&
            otherStr[ index ] != NULL_CHAR 
                && index < MAX_STR_LEN)
            {
                diff = oneStr[ index ] - otherStr[ index ];

                if( diff != 0 )
                    {
                        return diff;
                    }

                index++;
            }

            return getStringLength( oneStr ) - getStringLength( otherStr );
    }

/*
Name concatenateString
Process: appends one string onto another
Input: char *
Output: char *
Returned: none
Dep: getStringLength
*/
void concatenateString( char *destStr, const char *sourceStr )
    {
        int destIndex = getStringLength( destStr );

        int sourceStrLen = getStringLength( sourceStr );

        char *tempStr;

        int sourceIndex = 0;

        tempStr = (char *)malloc( sizeof( char ) * (sourceStrLen + 1));
        copyString( tempStr, sourceStr );

        while ( tempStr[ sourceIndex ] != NULL_CHAR && destIndex < MAX_STR_LEN )
            {
                destStr[ destIndex ] = tempStr[ sourceIndex ];

                destIndex++; sourceIndex++;

                destStr[ destIndex ] = NULL_CHAR;
            }

        free( tempStr );
        
    }

/*
Name copyString
Process: copies one string into another
         overwriting data in the destrination string
Function Input/Parameters: c-style source string (char *)
Function Output/Returned: none
Device Input/Keyword: none
Device Output/Monitor: none
Dependencies: getStringLength
*/
void copyString( char *destStr, const char *sourceStr )
    {
        int index = 0;

        if( destStr != sourceStr )
            {
                while ( sourceStr[ index ] != NULL_CHAR && index < MAX_STR_LEN )
                    {
                        destStr[ index ] = sourceStr[ index ];

                        index++;

                        destStr[ index ] = NULL_CHAR;
                    }
                
            }
    }

/*
Name: findSubString
*/
int findSubString( const char *testStr, const char *searchSubStr )
    {
        int testStrLen = getStringLength( testStr );

        int masterIndex = 0;

        int searchIndex, internalIndex;

        while ( masterIndex < testStrLen )
            {
                internalIndex = masterIndex;

                searchIndex = 0;

                while ( internalIndex <= testStrLen 
                        && testStr[ internalIndex ] == searchSubStr[ searchIndex ] )
                    {
                        internalIndex++; searchIndex++;

                        if( searchSubStr[searchIndex ] == NULL_CHAR )
                            {
                                return masterIndex;
                            }
                    }

                masterIndex++;
            }

        return SUBSTRING_NOT_FOUND;
    }

/*
Name: getStringLength
*/
int getStringLength( const char *testStr )
    {
     //initialize function/variables
     int index = 0;

     //loop to the end of string, protect from overflow
     while(index < STD_STR_LEN && testStr[ index ] != NULL_CHAR )
        {
            //update index
            ++index;
        }

     //return index
     return index;
    }

/*
Name: getStringConstarined
*/
bool getStringConstrained(
                          FILE *inStream,
                          bool clearLeadingNonPrintable,
                          bool clearLeadingSpace,
                          bool stopAtNonPrintable,
                          char delimiter,
                          char *capturedString
                         )
    {
        int intChar = EOF, index = 0;

        capturedString[ index ] = NULL_CHAR;

        intChar = fgetc( inStream );

        while(( intChar != EOF )
                && ( ( clearLeadingNonPrintable && intChar < (int)SPACE )
                    || (clearLeadingSpace && intChar == (int)SPACE ) ) 
                )
            {
                intChar = fgetc( inStream );
            }

        if( intChar == EOF )
            {
                return false;
            }

        while ( 
            ( intChar != EOF && index < MAX_STR_LEN - 1)
            && ( ( stopAtNonPrintable && intChar >= (int)SPACE ) 
            || ( !stopAtNonPrintable )
            )

            && ( intChar != (char)delimiter )
         )
            {
                capturedString[ index ] = (char)intChar;

                index++;

                capturedString[ index ] = NULL_CHAR;

                intChar = fgetc( inStream );
            }

        return true;
        
    }

/*
Name: getStringToDelimiter
*/
bool getStringToDelimiter(
                          FILE *inStream,
                          char delimiter,
                          char *capturedString
                         )
    {
        return getStringConstrained(
            inStream,
            true,
            true,
            true,
            delimiter,
            capturedString
        );
    }
/*
Name: getStringToLineEnd
*/
bool getStringToLineEnd(
                        FILE *inStream,
                        char *capturedString
                       )
    {
        return getStringConstrained(
            inStream,
            true,
            true,
            true,
            NON_PRINTABLE_CHAR,
            capturedString
        );
    }

/*
Name: getSubStr
*/
void getSubString( char *destStr, const char *sourceStr,
                    int startIndex, int endIndex )
    {
        int sourceStrLen = getStringLength( sourceStr );

        int destIndex = 0;

        int sourceIndex = startIndex;

        char *tempStr;

        if( startIndex >= 0 && startIndex <= endIndex
            && endIndex < sourceStrLen )
            {
                tempStr = ( char * )malloc( sizeof(char) * (sourceStrLen + 1) );
                copyString( tempStr, sourceStr );

                while( sourceIndex <= endIndex )
                    {
                        destStr[ destIndex ] = tempStr[ sourceIndex ];

                        destIndex++; sourceIndex++;

                        destStr[ destIndex ] = NULL_CHAR;
                    }

                free( tempStr );
            }
    }

/*
Name: setStrToLowerCase
*/
void setStrToLowerCase( char *destStr, const char *sourceStr )
    {
        int sourceStrLen = getStringLength( sourceStr );

        char *tempStr;

        int index = 0;

        tempStr = (char *)malloc( sizeof(char) * (sourceStrLen + 1 ) );
        copyString( tempStr, sourceStr );

        while( tempStr[ index ] != NULL_CHAR && index < MAX_STR_LEN )
            {
                destStr[ index ] = toLowerCase( tempStr[ index ] );

                index++;

                destStr[ index ] = NULL_CHAR;
            }

        free( tempStr );
    }

/*
Name setStrToUpperCase
*/
void setStrToUpperCase( char *destStr, const char *sourceStr )
    {
        int sourceStrLen = getStringLength( sourceStr );

        char *tempStr;

        int index = 0;

        tempStr = (char *)malloc( sizeof(char) * (sourceStrLen + 1 ) );
        copyString( tempStr, sourceStr );

        while( tempStr[ index ] != NULL_CHAR && index < MAX_STR_LEN )
            {
                destStr[ index ] = toUpperCase( tempStr[ index ] );

                index++;

                destStr[ index ] = NULL_CHAR;
            }

        free( tempStr );
    }

/*
Name: toLowerCase
*/
char toLowerCase( char testChar )
    {
        if( testChar >= 'A' && testChar <= 'Z' )
            {
                return testChar - 'A' + 'a';
            }

        return testChar;
    }

/*
Name: toUpperCase
STUB METHOD
*/
char toUpperCase( char testChar )
    {
        return testChar;
    }