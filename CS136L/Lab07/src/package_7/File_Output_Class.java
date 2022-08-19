package package_7;

import java.io.FileWriter;
import java.io.IOException;

/**
Formatted file output class

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

1) This class contains methods that may be used for file output of data
   when text file I/O is needed. The class must be placed under the same 
   package as the class in which it will be used. As long as no changes 
   are made to this class, it can continue to be used.
      
2) Users are provided simple information for all of the methods in a
   standardized format.

   END OF INSTRUCTIONS
*/

public class File_Output_Class
   {
    // constant used for empty string return
    private final String EMPTY_STRING = "";      

    // constant radix point for use in double formatting
    private final int RADIX_POINT = '.';
    
    // file reader reference
    private FileWriter outFile;
      
    // flag indicates file open status
    private boolean openFileFlag;
    
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
      public File_Output_Class()
         {
          // set open file flag to false
          openFileFlag = false;
         }
      
      /*
      name: charToInt
      process: converts character value to equivalent integer value (private)
      method input/parameters: value to be converted (char)
      method output/parameters: none
      method output/returned: converted value (int)
      device input/keyboard: none
      device output/monitor: none
      dependencies: none
      */
      private int charToInt( char inChar )
         {
          return (int)( inChar - '0' );
         }
      
    /*
    name: closeOutputFile
    process: closes output file, returns true if successful, false otherwise
    method input/parameters: none
    method output/parameters: none
    method output/returned: none
    device input/file: file closed
    device output/monitor: none
    dependencies: FileWriter tools, IOException
    */
    public boolean closeOutputFile()
       {
        // sets open file flag to false no matter what the outcome
        openFileFlag = false;
            
        try
           {
            writeEndline();
            
            outFile.flush();
            outFile.close();
           }
          
        catch( IOException ioe )
           {
            return false;
           }
          
        return true;
       }
      
    /*
    name: formatDouble
    process: formats double value with specified precision, converts to string
    method input/parameters: double doubleVal
                             integer precision
                             (number of digits to the right of the radix point)
    method output/parameters: none
    method output/returned: the value with the correct precision as a String
    device input/keyboard: none
    device output/monitor: none
    dependencies: none
    */
    public String formatDouble( double doubleVal, int precision )
       {
        final double ROUND_REFERENCE = 0.45;
        final int MAX_DOUBLE_DIGITS = 20;
        double fractionPart;
        int nonFractionPart, fractionDigit, numberLength, carryBit = 0;
        int precisionIndex, index, lowIndex, highIndex, tempVal;
        char temp;
        char[] tempArr, digitStr = new char[ MAX_DOUBLE_DIGITS ];
        boolean negativeFlag = false;
        
        String outStr = "";
        
        // set negative flag as needed
        if( doubleVal < 0 )
           {
            doubleVal *= -1;
            
            negativeFlag = true;
           }
        
        // find fractional and non fractional parts
        nonFractionPart = (int)doubleVal;
        
        fractionPart = doubleVal - nonFractionPart;
        
        // capture non fraction part digits
        index = 0;
        
        while( nonFractionPart > 0 )
           {
            digitStr[ index ] = intToChar( nonFractionPart % 10 );
            
            nonFractionPart /= 10;
            
            index++;
           }
        
        // reverse digits
        lowIndex = 0;
        highIndex = index - 1;
        
        while( lowIndex < highIndex )
           {
            temp = digitStr[ lowIndex ];
            
            digitStr[ lowIndex ] = digitStr[ highIndex ];
            
            digitStr[ highIndex ] = temp;
            
            lowIndex++; highIndex--;
           }
        
        // set radix point
        digitStr[ index ] = RADIX_POINT;        
        index++;
        
        // set fractional digits        
        precisionIndex = 0;
        
        while( index < MAX_DOUBLE_DIGITS && precisionIndex < precision )
           {
            fractionDigit = (int)( fractionPart * 10 );
            
            digitStr[ index ] = intToChar( fractionDigit );
            
            fractionPart *= 10;
            
            fractionPart -= fractionDigit;
            
            index++; precisionIndex++;
           }
        
        numberLength = index;

        // resolve rounding as needed
        if( fractionPart > ROUND_REFERENCE )
           {
            index--;
            
            carryBit = 1;
            
            while( index >= 0 && carryBit == 1 )
               {
                if( digitStr[ index ] == RADIX_POINT )
                   {
                    index--;
                   }
                
                tempVal = charToInt( digitStr[ index ] );
                    
                tempVal++;
                    
                digitStr[ index ] = intToChar( tempVal % 10 );
                    
                carryBit = tempVal / 10;
                
                index--;
               }
           }
        
        // if rounding has added another digit, resolve that here
        if( carryBit == 1 )
           {
            tempArr = new char[ MAX_DOUBLE_DIGITS ];

            index = 0;
            
            numberLength++;            

            tempArr[ index ] = '1';
            
            index++;
            
            while( index < numberLength )
               {
                tempArr[ index ] = digitStr[ index - 1 ];
                
                index++;
               }
            
            digitStr = tempArr;
           }
        
        // apply negative flag
        if( negativeFlag )
           {
            outStr = "-";
           }
        
        // add front end zero as needed
        if( doubleVal < 1 )
           {
            outStr += "0";
           }

        // put character array data into string
        index = 0;
        
        while( index < numberLength )
           {
            outStr += digitStr[ index ];
            
            index++;
           }

        // return result
        return outStr;
       }
    
    /*
    name: intToChar
    process: converts integer value to character value  (private)
    method input/parameters: value to be converted (int)
    method output/parameters: none
    method output/returned: converted value (char)
    device input/keyboard: none
    device output/monitor: none
    dependencies: none
    */
    private char intToChar( int inInt )
       {
        return (char)( inInt + '0' );
       }

    /*
    name: openOutputFile
    process: opens input file, returns true if successful, false otherwise
    method input/parameters: file name (String)
    method output/parameters: none
    method output/returned: none
    device input/file: file opened
    device output/monitor: none
    dependencies: FileWriter tools, IOException
    */
    public boolean openOutputFile( String fileName )
       {
        try
           {
            outFile = new FileWriter( fileName );
           }
        
        catch( IOException ioe )
           {
            return false;
           }
           
        openFileFlag = true;
        
        return true;
       }
    
    /*
    name: writeChar
    process: writes individual character to file,
             returns true if successful, false otherwise
    method input/parameters: character to output (char)
    method output/parameters: none
    method output/returned: none
    device input/file: none
    device output/file: character written to file as integer
    dependencies: FileWriter tools, IOException
    */
    public boolean writeChar( char outChar )
       {
        if( openFileFlag )
           {
            try
               {
                outFile.write( (int)outChar );
               }
            
            catch( IOException ioe )
               {
                return false;
               }
            
            return true;
           }
        
        return false;
       }
    
    /*
    name: writeChars
    process: writes multiple characters to file,
             returns true if successful, false otherwise
    method input/parameters: number of characters to output (int),
                             character to output (char)
    method output/parameters: none
    method output/returned: none
    device input/file: none
    device output/file: multiple characters written to file
    dependencies: writeChar
    */
    public boolean writeChars( int numChars, char outChar )
       {
        boolean success = false;
        
        while( numChars > 0 )
           {
            success = writeChar( outChar );
            
            numChars--;
           }
        
        return success;
       }
    
    /*
    name: writeDouble
    process: writes individual formatted double value to file,
             returns true if successful, false otherwise
    method input/parameters: double value to output (double),
                             number of digits to right of radix point
                             (precision) (int)
    method output/parameters: none
    method output/returned: none
    device input/file: none
    device output/file: double written to file
    dependencies: FileWriter tools, IOException
    */
    public boolean writeDouble( double outVal, int precision )
       {
        String outString = EMPTY_STRING;
        
        if( openFileFlag )
           {
            outString = formatDouble( outVal, precision );
            
            try
               {
                outFile.write( outString );
               }
            
            catch( IOException ioe )
               {
                return false;
               }
            
            return true;
           }
        
        return false;
       }
    
    /*
    name: writeEndline
    process: writes carriage return ('\r')
             and newline ('\n') to file,
             returns true if successful, false otherwise
    method input/parameters: none
    method output/parameters: none
    method output/returned: none
    device input/file: none
    device output/file: endline pair written to file as String
    dependencies: FileWriter tools, IOException
    */
    public boolean writeEndline()
       {
        String endlineStr = "\r\n";
        
        return writeString( endlineStr );
       }
    
    /*
    name: writeEndlines
    process: writes multiple carriage return ('\r')
             and newline ('\n') pairs to file,
             returns true if successful, false otherwise
    method input/parameters: number of endline pairs to write (int)
    method output/parameters: none
    method output/returned: none
    device input/file: none
    device output/file: multiple endline pairs written to file as Strings
    dependencies: writeString
    */
    public boolean writeEndlines( int numEndlines )
       {
        boolean success = false;
        
        while( numEndlines > 0 )
           {
            success = writeEndline();
            
            numEndlines--;
           }
        
        return success;
       }
    
    /*
    name: writeInt
    process: writes individual integer to file,
             returns true if successful, false otherwise
    method input/parameters: integer to output (int)
    method output/parameters: none
    method output/returned: none
    device input/file: none
    device output/file: integer written to file
    dependencies: FileWriter tools, IOException
    */
    public boolean writeInt( int outVal )
       {
        if( openFileFlag )
           {
            try
               {
                outFile.write( "" + outVal );
               }
            
            catch( IOException ioe )
               {
                return false;
               }
            
            return true;
           }
        
        return false;
       }
    
    /*
    name: writeString
    process: writes String value to file,
             returns true if successful, false otherwise
    method input/parameters: double value to output (double),
                             number of digits to right of radix point
                             (precision) (int)
    method output/parameters: none
    method output/returned: none
    device input/file: none
    device output/file: String written to file
    dependencies: FileWriter tools, IOException
    */
    public boolean writeString( String outString )
       {
        if( openFileFlag )
           {
            try
               {
                outFile.write( outString );
               }
            
            catch( IOException ioe )
               {
                return false;
               }
            
            return true;
           }
        
        return false;
       }
    
   }