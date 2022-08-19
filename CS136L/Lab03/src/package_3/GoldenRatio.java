package package_3;


public class GoldenRatio
   {
      private static final char     PIPE        = '|';
      private static final String   PIPE_SPACE  = "| ";
      private static final String   SPACE_PIPE  = " |";
      private static final char     THICK_LINE  = '=';
      private static final char     THIN_LINE   = '-';
      
      private static final int TABLE_WIDTH         = 60;
      private static final int LEFT_COLUMN_WIDTH   = 40;
      private static final int RIGHT_COLUMN_WIDTH  = 17;
      
      private static final double GOLDEN_RATIO_INVERSE = (Math.sqrt(5)-1)/2;
      private static final int    PRECISION = 3;
      
      public static void main(String[] args)
      {
         Console_IO_Class console = new Console_IO_Class();
         
         //Header lines
         String lineOne = "COMPUTE GOLDEN RATIO PART OF LINE WITH GIVEN LENGTH:";
         String lineTwo = "====================================================";
         
         //Prints header
         console.printString(lineOne);
         console.printEndline();
         console.printString(lineTwo);
         console.printEndline();
         
         //Asks for user input
         double userInput = console.promptForDouble("Enter length of line: ");
         console.printEndline();
         
         //Obtains answers from user inputs
         double shortAnswer = calcShortPart(userInput);
         double longAnswer = calcLongPart(userInput);
         
         //Prints results in table form to screen
         displayResult(longAnswer, shortAnswer);
      }
      
      //Calculates the long part of the Golden Ratio (length)
      public static double calcLongPart(double length)
      {
         double longPart = length * GOLDEN_RATIO_INVERSE;
         return longPart;
      }
      
      //Calculates the short part of the Golden Ratio (length)
      public static double calcShortPart(double length)
      {
         double shortPart = length - calcLongPart(length);     
         return shortPart;
      }
      
      //Displays a table containing results of operations
      public static void displayResult(double longPart, double shortPart)
      {
         Console_IO_Class console = new Console_IO_Class();
         
         //Top line of table
         console.printChar(PIPE);
         console.printChars(TABLE_WIDTH, THICK_LINE);
         console.printChar(PIPE);
         console.printEndline();
         
         //First entry in table
         console.printString(PIPE_SPACE);
         console.printString("Long Part",
                              LEFT_COLUMN_WIDTH,
                              "LEFT");
         console.printChar(PIPE);
         console.printDouble(longPart,
                             PRECISION,
                             RIGHT_COLUMN_WIDTH,
                             "RIGHT");
         console.printString(SPACE_PIPE);
         console.printEndline();
         
         //Seperating line in table
         console.printChar(PIPE);
         console.printChars(LEFT_COLUMN_WIDTH + 1, THIN_LINE);
         console.printChar(PIPE);
         console.printChars(RIGHT_COLUMN_WIDTH + 1, THIN_LINE);
         console.printChar(PIPE);
         console.printEndline();
         
         //Second entry in table
         console.printString(PIPE_SPACE);
         console.printString("Short Part",
                              LEFT_COLUMN_WIDTH,
                              "LEFT");
         console.printChar(PIPE);
         console.printDouble(shortPart,
                             PRECISION,
                             RIGHT_COLUMN_WIDTH,
                             "RIGHT");
         console.printString(SPACE_PIPE);
         console.printEndline();
         
         //Final line
         console.printChar(PIPE);
         console.printChars(TABLE_WIDTH, THICK_LINE);
         console.printChar(PIPE);
      }
   }
