package package_4;

/**Lab 04
 * 9/11/20
 * 
 * @author richard mccormick
 *         rlm443@nau.edu
 *
 */
public class Greatest
   {
      private static final char PIPE = '|';
      private static final String PIPE_SPACE = "| ";
      private static final String SPACE_PIPE = " |";
      private static final char THICK_LINE = '=';
      private static final char THIN_LINE = '-';
      
      private static final int TABLE_WIDTH = 60;
      private static final int LEFT_COLUMN_WIDTH = 40;
      private static final int RIGHT_COLUMN_WIDTH = 17;
      
      private static final int PRECISION = 3;
      
      private static Console_IO_Class conIO = new Console_IO_Class();
      
      
      public static void main(String[] args)
      {         
         double numOne = 0;
         double numTwo = 0;
         double numThree = 0;
         double greatest = 0;
         
         conIO.printString("FIND THE GREATEST OF THREE NUMBERS:");
         conIO.printEndline();
         conIO.printChars(25, THICK_LINE);
         conIO.printEndline();
         
         numOne = conIO.promptForDouble("Enter first number: ");
         numTwo = conIO.promptForDouble("Enter second number: ");
         numThree = conIO.promptForDouble("Enter third number: ");
         conIO.printEndline();
                  
         greatest = getGreatest(numOne, numTwo, numThree);
         
         displayResult(numOne, numTwo, numThree, greatest);
      }
      
      public static double getGreatest(double first,
                                       double second,
                                       double third)
      {
         double greatest = third;
         
         if (first > second && first > third)
            {
               greatest = first;
            }
         else if (second > first && second > third)
            {
               greatest = second;
            }

         return greatest;
      }
      
      public static void displayResult(double first,
                                       double second,
                                       double third,
                                       double result)
      {
         conIO.printChar(PIPE);
         conIO.printChars(TABLE_WIDTH, THICK_LINE);
         conIO.printChar(PIPE);
         conIO.printEndline();
         
         conIO.printString(PIPE_SPACE);
         conIO.printString("First Number", LEFT_COLUMN_WIDTH, "LEFT");
         conIO.printChar(PIPE);
         conIO.printDouble(first, PRECISION, RIGHT_COLUMN_WIDTH, "RIGHT");
         conIO.printString(SPACE_PIPE);
         conIO.printEndline();
         conIO.printChar(PIPE);
         conIO.printChars(LEFT_COLUMN_WIDTH+1, THIN_LINE);
         conIO.printChar(PIPE);
         conIO.printChars(RIGHT_COLUMN_WIDTH+1, THIN_LINE);
         conIO.printChar(PIPE);
         conIO.printEndline();
         
         conIO.printString(PIPE_SPACE);
         conIO.printString("Second Number", LEFT_COLUMN_WIDTH, "LEFT");
         conIO.printChar(PIPE);
         conIO.printDouble(second, PRECISION, RIGHT_COLUMN_WIDTH, "RIGHT");
         conIO.printString(SPACE_PIPE);
         conIO.printEndline();
         conIO.printChar(PIPE);
         conIO.printChars(LEFT_COLUMN_WIDTH+1, THIN_LINE);
         conIO.printChar(PIPE);
         conIO.printChars(RIGHT_COLUMN_WIDTH+1, THIN_LINE);
         conIO.printChar(PIPE);
         conIO.printEndline();
         
         conIO.printString(PIPE_SPACE);
         conIO.printString("Third Number", LEFT_COLUMN_WIDTH, "LEFT");
         conIO.printChar(PIPE);
         conIO.printDouble(third, PRECISION, RIGHT_COLUMN_WIDTH, "RIGHT");
         conIO.printString(SPACE_PIPE);
         conIO.printEndline();
         conIO.printChar(PIPE);
         conIO.printChars(TABLE_WIDTH, THICK_LINE);
         conIO.printChar(PIPE);
         conIO.printEndline();
         
         conIO.printString(PIPE_SPACE);
         conIO.printString("Result", LEFT_COLUMN_WIDTH, "LEFT");
         conIO.printChar(PIPE);
         conIO.printDouble(result, PRECISION, RIGHT_COLUMN_WIDTH, "RIGHT");
         conIO.printString(SPACE_PIPE);
         conIO.printEndline();
         conIO.printChar(PIPE);
         conIO.printChars(TABLE_WIDTH, THICK_LINE);
         conIO.printChar(PIPE);
      }
   }
