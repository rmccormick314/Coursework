package package_8;


/**
 * A class to create objects that represent records of investment data.
 * Each record contains a principle, a rate and a number of years.
 * Getter and setter methods are provided to access the pieces of data,
 *    to enforce data encapsulation (or information hiding)
 * Objects are also able to compute the principle + compounded interest as well as the investment's doubling period
 * 
 * @author Dr.-Ing. Wolf-Dieter Otte
 */
public class InvestmentRecord 
{
   // finance constants
   private static final int NUM_COMPOUNDS_PER_YEAR = 1;
   private static final int RULE_OF_72_FACTOR = 72;
   
   // default constructor default values
   private static final double DEFAULT_RATE = 0.0;
   private static final double DEFAULT_PRINCIPLE = 0.0;
   private static final int    DEFAULT_YEARS = 0;
   
   // member variables
   private double principle;
   private double rate;
   private int    years;

   
   /**
    * Default constructor
    */
   public InvestmentRecord()
   {
      this.principle = DEFAULT_PRINCIPLE;
      this.rate      = DEFAULT_RATE;
      this.years     = DEFAULT_YEARS;
   }
   
   
   /**
    * Initialization Constructor
    * 
    * @param principle Initial investment
    * @param rate Rate of return
    * @param years Number of years compounded
    */
   public InvestmentRecord(double principle, double rate, int years)
   {
      this.principle = principle;
      this.rate      = rate;
      this.years     = years;
   }

   
   /**
    * Copy constructor
    * 
    * @param copied Object to copy from
    */
   public InvestmentRecord(InvestmentRecord copied)
   {
      this.principle = copied.principle;
      this.rate      = copied.rate;
      this.years     = copied.years;
   }

   
   /**
    * Computes number of years in which the principle doubles by compounding interest
    * 
    * @return Returns number of years
    */
   public double computeDoublingPeriod()
   {
      return RULE_OF_72_FACTOR / rate / 100.0;
   }

   
   /**
    * Computes the overall total, after the principle has compounded for the given number of years at the given rate of return
    * 
    * @return Returns the overall total
    */
   public double computeTotal() 
   {
      double rateUnit = rate / NUM_COMPOUNDS_PER_YEAR;
      double parenthesized = 1 + rateUnit;
      double totalInterest = Math.pow(parenthesized, years * NUM_COMPOUNDS_PER_YEAR);

      return principle * totalInterest;
   }


   /**
    * Returns the principle of this record
    * 
    * @return principle
    */
   public double getPrinciple() {
      return principle;
   }


   /**
    * Returns the interest rate of this record
    * 
    * @return rate
    */
   public double getRate() {
      return rate;
   }


   /**
    * Returns the number of compounding years of this record
    * 
    * @return years
    */
   public int getYears() {
      return years;
   }


   /**
    * Sets the principle of this record
    * 
    * @param principle
    */
   public void setPrinciple(double principle) {
      this.principle = principle;
   }


   /**
    * Sets the interest rate of this record
    * 
    * @param rate
    */
   public void setRate(double rate) {
      this.rate = rate;
   }


   /**
    * Sets the number of compounding years of this record
    * 
    * @param years
    */
   public void setYears(int years) {
      this.years = years;
   }

   
   
   
   
} 