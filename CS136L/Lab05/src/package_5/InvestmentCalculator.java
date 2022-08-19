package package_5;

/**Investment Calculator Class
 * Lab 05 - CS136
 * 
 * @author Richard McCormick (RLM443)
 *
 */
public class InvestmentCalculator
   {      
      /**Character constants for printing
       * 
       */
      private static final char PIPE = '|';
      private static final String PIPE_SPACE = "| ";
      private static final String SPACE_PIPE = " |";
      private static final char THICK_LINE = '=';
      private static final char THIN_LINE = '-';
         
      /**Table size constants for printing
       * 
       */
      private static final int TABLE_WIDTH = 60;
      private static final int LEFT_COLUMN_WIDTH = 40;
      private static final int RIGHT_COLUMN_WIDTH = 17;
      
      private static final int PRECISION = 3;
      
      /**Main method (driver)
       * 
       * @param args
       */
      public static void main (String[] args)
      {
         Console_IO_Class console = new Console_IO_Class();
         double investment = -1;
         double returnRate = -1;
         int numYears = -1;
         double total = -1;
         double compoundedPerYear = -1;
         
         int thenumberone = 1;
         
         console.printString("INVESTMENT CALCULATOR:");
         console.printEndline();
         console.printString("======================");
         console.printEndlines(2);
         
         investment = console.
               promptForDouble("Enter the original investment: ");
         returnRate = console.
               promptForDouble("Enter the rate of return in %: ");
         numYears = console.
               promptForInt("Enter the number of years: ");
         console.printEndlines(2);
         
         compoundedPerYear = computeDoublingPeriod(returnRate);
         total = computeTotal(investment, returnRate, numYears, thenumberone);
         
         displayResult(investment, total, compoundedPerYear);
      }
      
      /**Computes the total amount of money in an account
       * 
       * @param principle                 - Initial investment
       * @param rate                      - Speed at which interest accumulates
       * @param years                     - Time to be held
       * @param numberCompoundsPerYear    - Times interest is compounded per year
       * 
       * @return total                    - Total value of account
       */
      public static double computeTotal(double principle,
                                        double rate,
                                        int years,
                                        int numberCompoundsPerYear)
      {
         double amountTotal = -1;
         
         amountTotal = Math.pow(1+((rate/100)/numberCompoundsPerYear), 
                                years*numberCompoundsPerYear) * principle;
         
         return amountTotal;
      }
      
      /**Computes how long it takes for an investment to double @ given rate
       * 
       * @param rate    - Given rate in percent
       * 
       * @return period - Time to double principle
       */
      public static double computeDoublingPeriod(double rate)
      {
         double doublingPeriod = 72/rate;
                  
         return doublingPeriod;
      }
      
      /**Displays result of math operations in a table
       * 
       * @param principle        - Amount originally invested
       * @param total            - Total amount after time
       * @param doublingPeriod   - Time to double account value
       */
      public static void displayResult(double principle,
                                       double total,
                                       double doublingPeriod)
      {
         Console_IO_Class displayConsole = new Console_IO_Class();
         
         //First line of table
         displayConsole.printChar(PIPE);
         displayConsole.printChars(TABLE_WIDTH, THICK_LINE);
         displayConsole.printChar(PIPE);
         displayConsole.printEndline();
         
         //First entry in table (principle)
         displayConsole.printString(PIPE_SPACE);
         displayConsole.printString("Principle", LEFT_COLUMN_WIDTH, "LEFT");
         displayConsole.printChar(PIPE);
         displayConsole.printDouble(principle, PRECISION, RIGHT_COLUMN_WIDTH, "RIGHT");
         displayConsole.printString(SPACE_PIPE);
         displayConsole.printEndline();
         
         //Seperating line
         displayConsole.printChar(PIPE);
         displayConsole.printChars(TABLE_WIDTH, THICK_LINE);
         displayConsole.printChar(PIPE);
         displayConsole.printEndline();
         
         //Next entry in table (principle + interest)
         displayConsole.printString(PIPE_SPACE);
         displayConsole.printString("Principle + Compounding Interest", 
                                    LEFT_COLUMN_WIDTH, "LEFT");
         displayConsole.printChar(PIPE);
         displayConsole.printDouble(total, PRECISION, RIGHT_COLUMN_WIDTH, "RIGHT");
         displayConsole.printString(SPACE_PIPE);
         displayConsole.printEndline();
         
         //Seperating line
         displayConsole.printChar(PIPE);
         displayConsole.printChars(LEFT_COLUMN_WIDTH+1, THIN_LINE);
         displayConsole.printChar(PIPE);
         displayConsole.printChars(RIGHT_COLUMN_WIDTH+1, THIN_LINE);
         displayConsole.printChar(PIPE);
         displayConsole.printEndline();
         
         //Next entry in table (doubling period)
         displayConsole.printString(PIPE_SPACE);
         displayConsole.printString("Approximate Doubling period", 
                                    LEFT_COLUMN_WIDTH, "LEFT");
         displayConsole.printChar(PIPE);
         displayConsole.printDouble(doublingPeriod, PRECISION, 
                                    RIGHT_COLUMN_WIDTH, "RIGHT");
         displayConsole.printString(SPACE_PIPE);
         displayConsole.printEndline();
         
         //Final line of table
         displayConsole.printChar(PIPE);
         displayConsole.printChars(TABLE_WIDTH, THICK_LINE);
         displayConsole.printChar(PIPE);
         
      }
   }
