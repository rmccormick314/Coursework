package package_3;

import java.io.IOException;

/**
 Formatted Command-Line I/O header file.

 Copyright (c) 2008 - 2020 by Michael E. Leverington

 Code is free for use in whole or in part and may be modified for other
 non-commercial use as long as the above copyright statement is included.
 *
 * @author Michael
 *
 */
/*
CLASS USAGE INSTRUCTIONS:

1) This class contains methods that may be used for input and
   output of assignments when formatted command-line I/O is needed. 
   The class must be placed under the same package as the class in which
   it will be used. As long as no changes are made to this class, it can
   continue to be used.
       
2) For any of the "promptFor..." methods, just place some prompting
   text into the method and call it. The user will be prompted for
   the appropriate value, and the user's response will be assigned
   to the variable you use.

   Example:        userAge = promptForInt( "Enter your age: " );
   Result Displayed:       Enter your age: {user answers here}

3) For any of the formatted print methods, the following must be provided:
   - value to be output
   - the text block size required
   - the justification
   - in the case of floating point values, the precision

   Example 1:    printString( "This is a string", 20, "CENTER" );
   Result Displayed:          |  This is a string  |
   Explanation: "This is a string" is displayed centered in a block
                that is 20 characters wide

   Example 2:   printDouble( 25.45678, 2, 10, "RIGHT" );
   Result Displayed:         |     25.46|
   Explanation: The value 25.45678 is displayed right justified within
                a block of 10 characters, and with 2 digits to the right
                of the decimal point (called precision for purposes of
                this method)

4) For any non-formated print methods, only the data to be output
   needs to be placed in the parameter
   
   Example 1:    printString( "This is a string" );
   Result Displayed: |This is a string
   Explanation: "This is a string" is displayed on the command line
                where the cursor last resided
   
   Example 2:   printDouble( 25.45678, 2 );
   Result Displayed: |25.46
   Explanation: The value 25.45678 is displayed on the command line
                where the cursor last resided with a precision of 2
                (i.e., two digits after the decimal point

    4) You are provided simple information for all of the methods in a
       standardized format.

    END OF INSTRUCTIONS
 */
public class Console_IO_Class
   {
    /**
     * maximum entry characters accepted for any input operation
     */
    private final int MAX_ENTRY_CHARACTERS = 128;

    /**
     * encoding value used to encode and decode data returned
     * from the getInputString method
     */
    private final int ENCODE_VAL = 1000;
    
    /**
     * Constant character value for space
     */
    private final char SPACE = ' ';

    /**
     * Constant character value for exclamation mark
     * which is the first printable letter
     */
    private final char EXCLAMATION_MARK = '!';

    /**
     * Constant character value for tilde
     * which is the last printable letter
     */
    private final char TILDE = '~';
    
    /**
     * Constant character value for minus sign used 
     * in numerical processing methods
     */    
    private final char MINUS_CHAR = '-';

    /**
     * Constant character value for plus sign used 
     * in numerical processing methods
     */    
    private final char PLUS_CHAR = '+';

    /**
     * Constant character value for radix (decimal) point used 
     * in numerical processing methods
     */    
    private final char RADIX_POINT = '.';
    
    
    /*
    name: Default constructor
    process: prepares object for use; however, this class is a utility class
             so no data is managed and no action is necessary              
    method input/parameters: none
    method output/parameters: none
    method output/returned: none
    device input: none
    device output/monitor: none
    dependencies: none
    */
    /**
     * Default Constructor
     */
    public Console_IO_Class()
       {
        // No action here
       }
    
    /*
    name: getCharCount
    process: decodes result from getInputString to get the character count
             that specifies the length of the captured string              
    method input/parameters: none
    method output/parameters: none
    method output/returned: current length of string
    device input: none
    device output/monitor: none
    dependencies: none
    */
   /**
    * Decodes character count from getInputString method
    * 
    * @param combinedVal integer value returned from getInputString method
    * 
    * @return integer decoded character count
    */
   private int getCharCount( int combinedVal )
      {
       return combinedVal / ENCODE_VAL;
      }
   
   /*
   name: getIndex
   process: decodes result from getInputString to get the index from which
            to start using the string              
   method input/parameters: none
   method output/parameters: none
   method output/returned: current index of string as specified
   device input: none
   device output/monitor: none
   dependencies: none
   */
   /**
    * Decodes index from getInputString method
    * 
    * @param combinedVal integer value returned from getInputString method
    * 
    * @return integer decoded index where input array should be started
    * by input operation
    */
   private int getIndex( int combinedVal )
      {
       return combinedVal % ENCODE_VAL;
      }
   
   /*
   name: getInputString
   process: acquires input string from keyboard
   method input/parameters: none
   method output/parameters: byte array
   method output/returned: index of first printable byte
   device input/keyboard: user entry of a character stream
   device output/monitor: keyboard input characters
   dependencies: IOException, System.in.read
   */
   /**
    * Method captures an input character array up to the point of pressing ENTER,
    * then removes any leading white space from the array
    * 
    * @param inputArr byte array returned via parameter
    * 
    * @param clearWhiteSpace boolean control code used to inform the method
    * to clear leading white space (true) or not (false)
    *  
    * @return integer combined (encoded) number of entry characters,
    * and index from the point after any leading white space
    */
   private int getInputString( byte[] inputArr, boolean clearWhiteSpace )
      {
       int charCount = 0, index = 0;
       
       try {
            // get input string
             charCount = System.in.read( inputArr );

             // clear leading white space
             while( clearWhiteSpace 
                            && index < charCount && inputArr[ index ] <= SPACE )
                {
                 index++;
                }                         
           }
       
       catch (IOException ioe)
          {
           System.out.println("Error reading from user");
          }
       
       // Encode the character count and the strting index
       return charCount * ENCODE_VAL + index;
      }
   
   /*
   name: printCharacter (overloaded)
   process: the character value is printed at the current location
            using the overloaded printCharacter method
   method input/parameters: outChar - the character value to be output
   method output/parameters: none
   method output/returned: none
   device input: none
   device output/monitor: character is displayed as specified
   dependencies: overloaded printCharacter method
   */
   /**
    * prints character at current location
    * <p>
    * Note: uses overloaded formatting method
    * 
    * @param outChar character value to be output
    */
   public void printChar( char outChar )
      {
       printChar( outChar, 0, "LEFT" );
      }

   /*
   name: printCharacter (overloaded)
   process: the character is printed with the specified justification
            within the specified blockSize using printString
   method input/parameters: outChar - the character value to be output
                              blockSize - the width of the block within 
                                          which to print the integer value
                              justify - either "LEFT", "RIGHT", or "CENTER" 
                                        to inform method 
                                        of the correct justification
   method output/parameters: none
   method output/returned: none
   device input: none
   device output/monitor: character is displayed as specified
   dependencies: printString
   */
   /**
    * prints character justified left, center, or right within 
    * a given block size
    * 
    * @param outChar character value to be output
    * 
    * @param blockSize integer value specifying number of characters in a block
    * within which the character will be placed
    * 
    * @param justify String parameter indicating justification as specified
    */
   public void printChar( char outChar, int blockSize, String justify )
      {
       String outStr = "" + outChar;
       
       printString( outStr, blockSize, justify );  
      }
   
   /*
   name: printDouble (overloaded)
   process: prints double value with specified precision is printed
            at the current location using the overloaded printDouble method
   method input/parameters: outVal - the integer value to be output
                              precision - number of digits to the right
                                          of the radix point
   method output/parameters: none
   method output/returned: none
   device input: none
   device output/monitor: double value is displayed as specified
   dependencies: overloaded printDouble
   */
   /**
    * prints double at current location
    * <p>
    * Note: uses overloaded formatting method
    * 
    * @param outVal double value to be output
    * 
    * @param precision integer value indicating how many digits are printed
    * to the right of the radix (decimal) point
    */
   public void printDouble( double outVal, int precision )
      {
       printDouble( outVal, precision, 0, "LEFT" );  
      }
   
   /*
   name: printDouble (overloaded)
   process: the double value is printed with the specified justification
            within the specified blockSize using formatDouble and printString
   method input/parameters: outVal - the integer value to be output
                              precision - number of digits to the right
                                          of the radix point
                              blockSize - the width of the block within 
                                          which to print the integer value
                              justify - either "LEFT", "RIGHT", or "CENTER" 
                                        to inform method 
                                        of the correct justification
   method output/parameters: none
   method output/returned: none
   device input: none
   device output/monitor: double value is displayed as specified
   dependencies: formatDouble, printString
   */
   /**
    * prints double value justified left, center, or right within 
    * a given block size; precision is specified to indicate how many digits
    * are printed to the right of the radix (decimal) point
    * 
    * @param outVal double value to be output
    * 
    * @param precision integer value specifying number of digits to be displayed
    * to the right of the radix (decimal) point
    * 
    * @param blockSize integer value specifying number of characters in a block
    * within which the double value will be placed
    * 
    * @param justify String parameter indicating justification as specified
    */
   public void printDouble( double outVal, int precision, 
                                                 int blockSize, String justify )
      {
       String outStr = formatDouble( outVal, precision );
       
       printString( outStr, blockSize, justify );  
      }
   
   /*
   name: printEndline
   process: prints one endline to end a line or create one vertical space
   method input/parameters: none
   method output/parameters: none
   method output/returned: none
   device input: none
   device output/monitor: line is ended and/or vertical space is created
   dependencies: printEndlines
   */
   /**
    * prints a specified number of endline characters, ending
    * and/or adding vertical space to an output operation
    * 
    */
   public void printEndline()
      {
       printEndlines( 1 );
      }
   
   /*
   name: printEndlines
   process: prints a specified number of endline characters, ending
            and/or adding vertical space to an output operation
   method input/parameters: numEndlines - integer number of endlines
                            to be printed
   method output/parameters: none
   method output/returned: none
   device input: none
   device output/monitor: line is ended and/or vertical space is created
   dependencies: System.out.print
   */
   /**
    * prints a specified number of endline characters, ending
    * and/or adding vertical space to an output operation
    * 
    * @param numEndlines - number of endlines to be output
    * 
    */
   public void printEndlines( int numEndlines )
      {
       if( numEndlines > 0 )
          {
           System.out.print( "\n" );
           
           printEndlines( numEndlines - 1 );
          }
      }
   
   /*
   name: printInteger (overloaded)
   process: an integer value is printed at the current location
            using the overloaded printInteger method
   method input/parameters: outVal - the integer value to be output
   method output/parameters: none
   method output/returned: none
   device input: none
   device output/monitor: integer is displayed as specified
   dependencies: overloaded printInteger
   */
   /**
    * prints integer at current location
    * <p>
    * Note: uses overloaded formatting method
    * 
    * @param outVal integer value to be output
    * 
    */
   public void printInt( int outVal )
      {
       printInt( outVal, 0, "LEFT" );  
      }
   
   /*
   name: printInteger (overloaded)
   process: the integer value is printed with the specified justification
            within the specified blockSize using printString
   method input/parameters: outVal - the integer value to be output
                              blockSize - the width of the block within 
                                          which to print the integer value
                              justify - either "LEFT", "RIGHT", or "CENTER" 
                                        to inform method 
                                        of the correct justification
   method output/parameters: none
   method output/returned: none
   device input: none
   device output/monitor: integer is displayed as specified
   dependencies: printString
   */
   /**
    * prints integer value justified left, center, or right within 
    * a given block size
    * 
    * @param outVal integer value to be output
    * 
    * @param blockSize integer value specifying number of characters in a block
    * within which the character will be placed
    * 
    * @param justify String parameter indicating justification as specified
    */
   public void printInt( int outVal, int blockSize, String justify )
      {
       String outStr = "" + outVal;
       
       printString( outStr, blockSize, justify );  
      }
   
   /*
   name: printString (overloaded)
   process: prints string at current location
   method input/parameters: stringVal - the text (String) value to be output
   method output/parameters: none
   method output/returned: none
   device input: none
   device output/monitor: string is displayed as specified
   dependencies: overloaded printString method
   */
   /**
    * prints string at current location
    * <p>
    * Note: uses overloaded formatting method
    * 
    * @param outStr String value to be output
    * 
    */
   public void printString( String outStr )
      {
       printString( outStr, 0, "LEFT" );      
      }
   
   /*
   name: printString (overloaded)
   process: the pre-spaces and post-spaces are calculated for the requested
            justification, then the pre-spaces are printed, the string value
            is printed, and then the post-spaces are printed
   method input/parameters: stringVal - the text (string) value to be output
                              blockSize - the width of the block within 
                                          which to print the integer value
                              justify - either "LEFT", "RIGHT", or "CENTER" 
                                        to inform method 
                                        of the correct justification
   method output/parameters: none
   method output/returned: none
   device input: none
   device output/monitor: string is displayed justified within the given block
   dependencies: printChars, System.out.print
   */
   /**
    * prints string value justified left, center, or right within 
    * a given block size
    * 
    * @param outStr integer value to be output
    * 
    * @param blockSize integer value specifying number of characters in a block
    * within which the character will be placed
    * 
    * @param justify String parameter indicating justification as specified
    */
   public void printString( String outStr, int blockSize, String justify )
      {
       int preSpace = 0, postSpace = 0;
       int strLen = outStr.length();
       
       // check for right justification
       if( justify == "RIGHT" )
          {
           // add front-end spaces
           preSpace = blockSize - strLen;
          }

       // check for center justification
       else if( justify == "CENTER" )
          {
           // add spaces on both ends
           preSpace = ( blockSize / 2 ) - ( strLen / 2 );
           postSpace = blockSize - preSpace - strLen;
          }

       // otherwise, assume left justification
       // default if not "RIGHT" or "CENTER"
       else 
          {
           // add back-end spaces
           postSpace = blockSize - strLen;
          }

       // print front-end spaces, if any
          // method: printChars
       printChars( preSpace, SPACE );

       System.out.print( outStr );
       
       // print back-end spaces, if any
       // method: printChars
       printChars( postSpace, SPACE );              
      }
   
   /*
   name: printChars
   process: prints given number of given charactrer
   method input/parameters: int number of characters, 
                              char character to be printed
   method output/parameters: none
   method output/returned: none
   device input/keyboard: none
   device output/monitor: number of specified characters printed
   dependencies: System.out.print
   */
   /**
    * Prints specified character a specified number of times
    * 
    * @param numChars integer number of characters to printed
    * 
    * @param outputChar character value to be printed
    */
   public void printChars( int numChars, char outputChar )
      {
       if( numChars > 0 )
          {
           System.out.print( "" + outputChar );
           
           printChars( numChars - 1, outputChar );
          }
      }
   
   /*
   name: promptForChar
   process: prompts user for character, then returns it
   method input/parameters: text to prompt user (string)
   method output/parameters: none
   method output/returned: one character (char) is returned to calling method
   device input/keyboard: user entry of a character
   device output/monitor: prompt string displayed
   dependencies: getInputString, getCharCount, getIndex
   */
    /**
     * Prompts for character on command line
     * 
     * @param promptString String parameter for prompt presented to user
     * 
     * @return character value captured from keyboard input
     */
    public char promptForChar( String promptString )
       {
          int countIndex, charCount, index = 0;
          char outChar = '0';
          byte[] inputArr = new byte[ MAX_ENTRY_CHARACTERS ];
          boolean clearLeadingWhiteSpace = true;
          
          System.out.print( promptString );

          countIndex = getInputString( inputArr, clearLeadingWhiteSpace );
          
          charCount = getCharCount( countIndex );
          index = getIndex( countIndex );

          if( index < charCount 
                       && inputArr[ index ] >= EXCLAMATION_MARK 
                                                 && inputArr[ index ] <= TILDE )
             {
              outChar = (char)inputArr[ index ];
             }             

        return outChar;                 
       }

    /*
    name: promptForDouble
    process: prompts user for double, then returns it
    method input/parameters: text to prompt user (string)
    method output/parameters: none
    method output/returned: one double value is returned to calling method
    device input/keyboard: user entry of an integer value
    device output/monitor: prompt string displayed
    exception: if input longer than MAX_ENTRY_CHARACTERS, 
               array out of bounds exception
    dependencies: getInputString, getCharCount, getIndex
    */
    /**
     * Prompts for double value on command line
     * 
     * @param promptString String parameter for prompt presented to user
     * 
     * @return double value captured from keyboard input
     */
    public double promptForDouble( String promptString )
       {
          int countIndex, charCount, index = 0;
          double outDouble = 0.0;
          boolean negativeFlag = false;
          boolean clearLeadingWhiteSpace = true;
          boolean foundDigits = false;
          String numberStr = "";
          byte[] inputArr = new byte[ MAX_ENTRY_CHARACTERS ];
          
          System.out.print( promptString );

          countIndex = getInputString( inputArr, clearLeadingWhiteSpace );
          
          charCount = getCharCount( countIndex );
          index = getIndex( countIndex );
          
          if( inputArr[ index ] == MINUS_CHAR )
             {
              negativeFlag = true;
                   
              index++;
             }
               
          else if( inputArr[ index ] == PLUS_CHAR )
             {
              index++;                  
             }
               
          while( index < charCount 
                        && inputArr[ index ] >= '0' && inputArr[ index ] <= '9'
                                           || inputArr[ index ] == RADIX_POINT )
             {
              numberStr += (char)inputArr[ index ];
                   
              index++;
              
              if( index > 1 )
                 {
                  foundDigits = true;
                 }
             }             
               
          if( foundDigits )
             {
              outDouble = Double.parseDouble( numberStr );
                   
              if( negativeFlag )
                 {
                  outDouble *= -1;
                 }
             }
          
        return outDouble;                 
       }
        
    /*
    name: promptForInt
    process: prompts user for integer, then returns it
    method input/parameters: text to prompt user (string)
    method output/parameters: none
    method output/returned: one integer (int) value 
                              is returned to calling method
    device input/keyboard: user entry of a double value
    device output/monitor: prompt string displayed
    exception: if input longer than MAX_ENTRY_CHARACTERS, 
               array out of bounds exception
    dependencies: getInputString, getCharCount, getIndex
    */
    /**
     * Prompts for integer value on command line
     * 
     * @param promptString String parameter for prompt presented to user
     * 
     * @return integer value captured from keyboard input
     */
    public int promptForInt( String promptString )
       {
          int countIndex, charCount, outInt = 0, index = 0;
          boolean negativeFlag = false;
          boolean clearLeadingWhiteSpace = true;
          boolean foundDigits = false;
          String numberStr = "";
          byte[] inputArr = new byte[ MAX_ENTRY_CHARACTERS ];
          
          System.out.print( promptString );

          countIndex = getInputString( inputArr, clearLeadingWhiteSpace );
          
          charCount = getCharCount( countIndex );
          index = getIndex( countIndex );
          
          if( inputArr[ index ] == MINUS_CHAR )
             {
              negativeFlag = true;
                   
              index++;
             }
               
          else if( inputArr[ index ] == PLUS_CHAR )
             {
              index++;                  
             }
               
          while( index < charCount 
                        && inputArr[ index ] >= '0' && inputArr[ index ] <= '9' )
             {
              numberStr += (char)inputArr[ index ];
                   
              index++;
              
              foundDigits = true;
             }             
               
          if( foundDigits )
             {
              outInt = Integer.parseInt( numberStr );
                   
              if( negativeFlag )
                 {
                  outInt *= -1;
                 }
             }
          
        return outInt;                 
       }
        
    /*
    name: promptForString
    process: prompts user for string, then returns it
    method input/parameters: text to prompt user (string)
    method output/parameters: none
    method output/returned: a string is returned to calling method
    device input/keyboard: user entry of an string value
    device output/monitor: prompt string displayed
    exception: if input longer than MAX_ENTRY_CHARACTERS, 
               array out of bounds exception
    dependencies: getInputString, getCharCount, getIndex
    */
    /**
     * Prompts for string on command line
     * 
     * @param promptString String parameter for prompt presented to user
     * 
     * @return string captured from keyboard input
     */

    public String promptForString( String promptString )
       {
          int countIndex, charCount, index = 0;
          boolean clearLeadingWhiteSpace = true;
          String stringStr = "";
          byte[] inputArr = new byte[ MAX_ENTRY_CHARACTERS ];
          
          System.out.print( promptString );

          countIndex = getInputString( inputArr, clearLeadingWhiteSpace );
          
          charCount = getCharCount( countIndex );
          index = getIndex( countIndex );
          
          while( index < charCount 
                        && inputArr[ index ] >= SPACE 
                                                 && inputArr[ index ] <= TILDE )
             {
              stringStr += (char)inputArr[ index ];
                   
              index++;
             }             
                         
        return stringStr;                 
       }
        
    /*
    name: formatDouble
    process: formats double value with specified precision, converts to string
    method input/parameters: double doubleVal
                               integer precision
    method output/parameters: none
    method output/returned: the value with the correct precision as a String
    device input/keyboard: none
    device output/monitor: none
    dependencies: none
    */
    /**
     * formats double value rounded to a specified number of digits
     * to the right of the radix (decimal) point
     * 
     * @param doubleVal double value to be processed
     * 
     * @param precision integer number of digits to be presented
     * to the right of the radix (decimal) point
     * 
     * @return String value with formatted double value
     */
    public String formatDouble( double doubleVal, int precision )
       {
        final double ROUND_REFERENCE = 0.45;
        double fractionPart, roundingPart;
        int nonFractionPart, precisionCount = precision;
        long intFractionPart;
        boolean negativeFlag = false;
        String outStr = "";
        
        if( doubleVal < 0 )
           {
            doubleVal *= -1;
            
            negativeFlag = true;
           }
        
        nonFractionPart = (int)doubleVal;
        
        fractionPart = doubleVal - nonFractionPart;
        
        while( precisionCount > 0)
           {
            fractionPart *= 10;
            
            precisionCount--;
           }
        
        roundingPart = fractionPart - (long)fractionPart;
        
        intFractionPart = (long)( fractionPart - roundingPart );

        if( roundingPart > ROUND_REFERENCE )
           {
            if( precision > 0 )
               {
                intFractionPart++;
               }
            
            else
               {
                nonFractionPart++;
               }
           }
        
        if( negativeFlag )
           {
            outStr = "-";
           }
        
        if( precision > 0 )
           {
            outStr += "" + nonFractionPart + RADIX_POINT + intFractionPart;
           }
        
        else
           {
            outStr += "" + nonFractionPart;
           }
        
        return outStr;
       }
    
   }
