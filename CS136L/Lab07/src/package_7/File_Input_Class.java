package package_7;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

/**
Formatted file input class

Copyright (c) 2020 by Michael E. Leverington

Code is free for use in whole or in part and may be modified for other
non-commercial use as long as the above copyright statement is included.
*
* @author Michael
*
*/
/*
Rev 0.0: 13 June 2020, Initial creation of file

CLASS USAGE INSTRUCTIONS:

1) This class contains methods that may be used for input and
   output of assignments when text file I/O is needed. 
   The class must be placed under the same package as the class in which
   it will be used. As long as no changes are made to this class, it can
   continue to be used.
      
2) You are provided simple information for all of the methods in a
   standardized format.

   END OF INSTRUCTIONS
*/

public class File_Input_Class
   {
    // constant used for empty string return
    private final String EMPTY_STRING = "";
      
    // constant for highest character (delete), uses UNICODE/ASCII value
    private final char HIGHEST_USABLE_CHAR_INT = 127;
      
    // constant for space character, uses UNICODE/ASCII value
    private final char LOWEST_USABLE_CHAR_INT = 32;
    
    // constant used for dash or minus sign
    private final char MINUS_SIGN = '-';

    // constant used for dash or minus sign
    private final char PLUS_SIGN = '+';

    // constant used for radix point
    private final char RADIX_POINT = '.';

    // constant used for zero character return
    private final char ZERO_CHAR = '0';
    
    // constant used for zero int/double value return
    private final char ZERO_VALUE = 0;
    
    // constant use for identifying end of file marker
    private final int EOF_MARKER = -1;

    // file reader reference
    private FileReader inFile;
    
    // flag indicates file open status
    private boolean openFileFlag;
    
    // flag indicates file open status
    private boolean endOfFileFlag;
    
    /*
    name: constructor - default
    process: sets open file flag to false, no other action
    method input/parameters: none
    method output/parameters: none
    method output/returned: none
    device input/keyboard: none
    device output/monitor: none
    dependencies: none
    */
    public File_Input_Class()
       {
        // set open file flag to false
        openFileFlag = false;
        
        // set end of file flag to false
        endOfFileFlag = false;
       }
    
    /*
    name: checkForEndOfFile
    process: checks to see if end of file flag has been encountered,
             returns true if EOF has been encountered, false otherwise
    method input/parameters: none
    method output/parameters: none
    method output/returned: result of specified test (boolean)
    device input/file: none
    device output/monitor: none
    dependencies: none
    */
    public boolean checkForEndOfFile()
       {
        return endOfFileFlag;
       }

    /*
    name: closeInputFile
    process: closes input file, returns true if successful, false otherwise
    method input/parameters: none
    method output/parameters: none
    method output/returned: none
    device input/file: file closed
    device output/monitor: none
    dependencies: FileReader tools, IOException
    */
    public boolean closeInputFile()
       {
        // sets open file flag to false no matter what the outcome
        openFileFlag = false;
        
        // sets end of file flag to false
        endOfFileFlag = false;
          
        try
           {
            inFile.close();
           }
        
        catch( IOException ioe )
           {
            return false;
           }
        
        return true;
       }
    
    /*
    name: isCharInString
    process: searches given string, reports if given character
             is located within the string
    method input/parameters: test string (String), test character (char)
    method output/parameters: none
    method output/returned: boolean result of specified test
    device input/file: file opened
    device output/monitor: none
    dependencies: String/length, charAt
    */
    private boolean isCharInString( char testChar, String testString )
       {
        int index = 0;
        
        while( index < testString.length() )
           {
            if( testChar == testString.charAt( index ) )
               {
                return true;
               }
            
            index++;
           } 
        
        return false;
       }
    
    /*
    name: getChar
    process: ignores leading unprintable characters,
             captures first printable character
    method input/parameters: none
    method output/parameters: none
    method output/returned: character found if successful, ZERO_CHAR otherwise
    device input/file: character(s) captured from file as needed
    device output/monitor: none
    dependencies: FileReader tools, IOException
    */
    public char getChar()
       {
        int inCharInt = EOF_MARKER;

        if( openFileFlag )
           {
            try
               {
                inCharInt = inFile.read();

                // clear space up to first character
                while( inCharInt != EOF_MARKER 
                                        && inCharInt <= LOWEST_USABLE_CHAR_INT )
                   {
                    inCharInt = inFile.read();
                   }
                
                endOfFileFlag = inCharInt == EOF_MARKER;
               }
       
            catch( IOException ioe )
               {
                // no action here
               }
          
            if( !endOfFileFlag )
               {
                return (char)inCharInt;
               }
           }
        
        return ZERO_CHAR;
       }
      
    /*
    name: getDouble
    process: ignores leading unprintable characters,
             captures first contiguous double value,
             consumes first character after value
    method input/parameters: none
    method output/parameters: none
    method output/returned: double value found if successful, 
                            ZERO_VALUE otherwise
    device input/file: character(s) captured from file as needed
    device output/monitor: none
    dependencies: FileReader tools, IOException
    */
    public double getDouble()
       {
        int inCharInt = EOF_MARKER;
        String strBuffer = EMPTY_STRING;
        double doubleValue = ZERO_VALUE;
        boolean negativeFlag = false;
        boolean digitFound = false;
        boolean firstRadixPointFound = false;
        boolean secondRadixPointFound = false;

        if( openFileFlag )
           {
            try
               {
                inCharInt = inFile.read();

                // clear unprintable characters up to first character
                while( inCharInt != EOF_MARKER && inCharInt <= LOWEST_USABLE_CHAR_INT )
                   {
                    inCharInt = inFile.read();
                   }
           
                endOfFileFlag = inCharInt == EOF_MARKER;
                
                if( !endOfFileFlag && (char)inCharInt == MINUS_SIGN )
                   {
                    negativeFlag = true;
                 
                    inCharInt = inFile.read();
                    
                    endOfFileFlag = inCharInt == EOF_MARKER;
                   }

                else if( !endOfFileFlag && (char)inCharInt == PLUS_SIGN )
                   {
                    inCharInt = inFile.read();
                    
                    endOfFileFlag = inCharInt == EOF_MARKER;
                   }

                while( !endOfFileFlag 
                           && isCharInString( (char)inCharInt, "0123456789." ) 
                                                     && !secondRadixPointFound )
                   {
                    // only allows one radix point
                    if( (char)inCharInt == RADIX_POINT )
                       {                    
                        firstRadixPointFound = true;
                       }

                     strBuffer += (char)( inCharInt );
                
                     if( (char)inCharInt >= '0' && (char)inCharInt <= '9' )
                        {
                         digitFound = true;
                        }

                    inCharInt = inFile.read();
                
                    endOfFileFlag = inCharInt == EOF_MARKER;
                    
                    if( firstRadixPointFound && (char)inCharInt == RADIX_POINT )
                       {
                        secondRadixPointFound = true;
                       }
                   }            
               }
       
            catch( IOException ioe )
               {
                // no action taken here
               }
          
            if( digitFound )
               {
                doubleValue = Double.parseDouble( strBuffer );
                
                if( negativeFlag )
                   {
                    doubleValue *= -1;
                   }
           
                return doubleValue;                
               }       
           }
        
        return ZERO_VALUE;
       }
      
    /*
    name: getInt
    process: ignores leading unprintable characters,
             captures first contiguous integer,
             consumes first character after integer
    method input/parameters: none
    method output/parameters: none
    method output/returned: integer found if successful, ZERO_VALUE otherwise
    device input/file: character(s) captured from file as needed
    device output/monitor: none
    dependencies: FileReader tools, IOException
    */
    public int getInt()
       {
        int inCharInt = EOF_MARKER;
        String strBuffer = EMPTY_STRING;
        int intValue = ZERO_VALUE;
        boolean negativeFlag = false;
        boolean digitFound = false;

        if( openFileFlag )
           {
            try
               {
                inCharInt = inFile.read();

                // clear unprintable characters up to first character
                while( inCharInt != EOF_MARKER 
                                        && inCharInt <= LOWEST_USABLE_CHAR_INT )
                   {
                    inCharInt = inFile.read();
                   }
                            
                endOfFileFlag = inCharInt == EOF_MARKER;

                if( !endOfFileFlag && (char)inCharInt == MINUS_SIGN )
                   {
                    negativeFlag = true;
                
                    inCharInt = inFile.read();
                    
                    endOfFileFlag = inCharInt == EOF_MARKER;
                   }
 
                else if( !endOfFileFlag && (char)inCharInt == PLUS_SIGN )
                   {
                    inCharInt = inFile.read();
                   }

                while( !endOfFileFlag 
                            && isCharInString( (char)inCharInt, "0123456789" ) )
                   {   
                    strBuffer += (char)( inCharInt );
                 
                    digitFound = true;

                    inCharInt = inFile.read();
                    
                    endOfFileFlag = inCharInt == EOF_MARKER;
                   }            
               }
       
            catch( IOException ioe )
               {
                // no action taken here
               }
          
            if( digitFound )
               {
                intValue = Integer.parseInt( strBuffer );

                if( negativeFlag )
                   {
                    intValue *= -1;
                   }
               }
      
           }
        
        return intValue;
       }
      
    /*
    name: getString
    process: ignores leading unprintable characters,
             captures series of characters up to first space
    method input/parameters: none
    method output/parameters: none
    method output/returned: string found if successful, EMPTY_STRING otherwise
    device input/file: character(s) captured from file as needed
    device output/monitor: none
    dependencies: getString with delimiter parameter
    */
    public String getString()
       {
        return getString( (char)LOWEST_USABLE_CHAR_INT );
       }

    /*
    name: getString
    process: ignores leading unprintable characters,
             captures series of characters up to specified delimiter,
    method input/parameters: specified delimiter (char)
    method output/parameters: none
    method output/returned: string found if successful, EMPTY_STRING otherwise
    device input/file: character(s) captured from file as needed
    device output/monitor: none
    dependencies: FileReader tools, IOException
    */
    public String getString( char delimiter )
       {
        int inCharInt = EOF_MARKER;
        String strBuffer = EMPTY_STRING;

        if( openFileFlag )
           {
            try
               {
                inCharInt = inFile.read();

                // clear unprintable characters up to first character
                while( inCharInt != EOF_MARKER 
                                        && inCharInt <= LOWEST_USABLE_CHAR_INT )
                   {
                    inCharInt = inFile.read();
                   }
           
                endOfFileFlag = inCharInt == EOF_MARKER;
                
                while( !endOfFileFlag && inCharInt >= LOWEST_USABLE_CHAR_INT 
                               && inCharInt < HIGHEST_USABLE_CHAR_INT
                                               && (char)inCharInt != delimiter )
                   {   
                    strBuffer += (char)( inCharInt );
                
                    inCharInt = inFile.read();
                    
                    endOfFileFlag = inCharInt == EOF_MARKER;
                   }            
               }
       
            catch( IOException ioe )
               {
                // no action taken here
               }
           }
        
        return strBuffer;
       }

    /*
    name: openInputFile
    process: opens input file, returns true if successful, false otherwise
    method input/parameters: file name (String)
    method output/parameters: none
    method output/returned: none
    device input/file: file opened
    device output/monitor: none
    dependencies: FileReader tools, FileNotFoundException
    */
    public boolean openInputFile( String fileName )
       {
        try
           {
            inFile = new FileReader( fileName );
           }
        
        catch( FileNotFoundException fnfe )
           {
            return false;
           }
           
        openFileFlag = true;
        
        endOfFileFlag = false;
        
        return true;
       }
    
   }