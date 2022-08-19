package package_6;

/**Investment Calculator Class
 * 
 * @author Richard McCormick (RLM443)
 * CS136L-03
 * September 19th, 2020
 *
 * Lab 06
 */
public class InvestmentCalculator 
{
    // finance constants
    private static final int NUM_COMPOUNDS_PER_YEAR = 1;
    private static final int RULE_OF_72_FACTOR = 72;
    
    // default constructor default values
    private static final double DEFAULT_RATE = 0.05;
    private static final double DEFAULT_PRINCIPLE = 100000;
    private static final int    DEFAULT_YEARS = 30;
    
   // set table characters
   private static final char PIPE = '|';
   private static final String PIPE_SPACE = "| ";
   private static final String SPACE_PIPE = " |";
   private static final char THICK_LINE = '=';
   private static final char THIN_LINE = '-';

   // set table widths
   private static final int TABLE_WIDTH = 60;
   private static final int LEFT_COLUMN_WIDTH = 40;
   private static final int RIGHT_COLUMN_WIDTH = 17;

   // precision
   private static final int PRECISION = 3;

   // member variables
   private double principle;
   private double rate;
   private int    years;

   
   /**
    * Default constructor
    */
   public InvestmentCalculator()
   {
        principle = DEFAULT_PRINCIPLE;
        rate = DEFAULT_RATE;
        years = DEFAULT_YEARS;
    }
   
   
   /**
    * Initialization Constructor
    * 
    * @param principle Initial investment
    * @param rate Rate of return
    * @param years Number of years compounded
    */
   public InvestmentCalculator(double principleInvestment,
                               double rateOfReturn,
                               int yearsCompounded)
   {
        principle = principleInvestment;
        rate = rateOfReturn / 100;
        years = yearsCompounded;
    }

   
   /**
    * Copy constructor
    * 
    * @param copied Object to copy from
    */
   public InvestmentCalculator(InvestmentCalculator copied)
   {
        this.principle = copied.principle;
        this.rate = copied.rate;
        this.years = copied.years;
   }

   
   /**
    * Computes number of years in which the principle doubles by compounding interest
    * 
    * @return Returns number of years
    */
   public double computeDoublingPeriod()
   {
        return(RULE_OF_72_FACTOR / rate/100);
    }

   
   /**
    * Computes Computes the overall total, after the principle has compounded for the given number of years at the given rate of return
    * 
    * @return Returns the overall total
    */
   public double computeTotal() 
   {
        return(Math.pow(1+((rate)/NUM_COMPOUNDS_PER_YEAR), 
              years*NUM_COMPOUNDS_PER_YEAR) * principle);
    }

   /**
    * Displays the results in table format
    * 
    * @param total Total yielded after the principle compounded over a  number of years at an interest rate of return 
    * @param doublingPeriod
    */
   public void displayResult() 
   {
      Console_IO_Class conIO = new Console_IO_Class();
            
      //First line of table
      conIO.printChar(PIPE);
      conIO.printChars(TABLE_WIDTH, THICK_LINE);
      conIO.printChar(PIPE);
      conIO.printEndline();
      
      //First entry in table (principle)
      conIO.printString(PIPE_SPACE);
      conIO.printString("Principle", LEFT_COLUMN_WIDTH, "LEFT");
      conIO.printChar(PIPE);
      conIO.printDouble(principle, PRECISION, RIGHT_COLUMN_WIDTH, "RIGHT");
      conIO.printString(SPACE_PIPE);
      conIO.printEndline();
      
      //Seperating line
      conIO.printChar(PIPE);
      conIO.printChars(TABLE_WIDTH, THICK_LINE);
      conIO.printChar(PIPE);
      conIO.printEndline();
      
      //Next entry in table (principle + interest)
      conIO.printString(PIPE_SPACE);
      conIO.printString("Principle + Compounding Interest", 
                                 LEFT_COLUMN_WIDTH, "LEFT");
      conIO.printChar(PIPE);
      double total = computeTotal();
      conIO.printDouble(total, PRECISION, RIGHT_COLUMN_WIDTH, "RIGHT");
      conIO.printString(SPACE_PIPE);
      conIO.printEndline();
      
      //Seperating line
      conIO.printChar(PIPE);
      conIO.printChars(LEFT_COLUMN_WIDTH+1, THIN_LINE);
      conIO.printChar(PIPE);
      conIO.printChars(RIGHT_COLUMN_WIDTH+1, THIN_LINE);
      conIO.printChar(PIPE);
      conIO.printEndline();
      
      //Next entry in table (doubling period)
      conIO.printString(PIPE_SPACE);
      conIO.printString("Approximate Doubling period", 
                                 LEFT_COLUMN_WIDTH, "LEFT");
      conIO.printChar(PIPE);
      double doublingPeriod = computeDoublingPeriod();
      conIO.printDouble(doublingPeriod, PRECISION, 
                                 RIGHT_COLUMN_WIDTH, "RIGHT");
      conIO.printString(SPACE_PIPE);
      conIO.printEndline();
      
      //Final line of table
      conIO.printChar(PIPE);
      conIO.printChars(TABLE_WIDTH, THICK_LINE);
      conIO.printChar(PIPE);
      conIO.printEndline();
    }

}
