package package_8;

/**
 * A class to create objects that represent a list of investment data records.
 * 
 * InvestmentRecordList objects keep an array of investment data records
 * as the internal data structure, thus implementing a HAS-A relationship.

 * InvestmentRecordList objects have the following capabilities:
 *  - Investment data records can be added to the object's internal array, one at a time
 *  - All investment data records contained in an object's internal array can be (up-)loaded into a file
 *  - All investment data records contained in a given file can be retrieved and loaded into the object's internal array
 *  - All investment data records contained in an object's internal array can be displayed in table format.
 * 
 * @author Dr.-Ing. Wolf-Dieter Otte
 */
public class InvestmentRecordList 
{
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
   
   // defaults
   private static final int MAX_NUMBER_RECORDS = 32;

   // important - the internal array that contains all InvestmentRecord objects
   // note that the variable needs to be initialized (to a certain capacity) in a constructor
   private InvestmentRecord [] investmentRecordList; 

   // capacity of above array
   private int arrayCapacity = 0;
   
   // number of filled slots in the array
   private int numberRecords = 0; 
   
   // convenience object to do console IO
   private Console_IO_Class conIO = new Console_IO_Class();

   
   /**
    * Default constructor
    * 
    * Initializes the internal array of InvestmentRecords to provide
    * MAX_NUMBER_RECORDS of slots in that array
    */
   public InvestmentRecordList()
   {
      this.arrayCapacity        = MAX_NUMBER_RECORDS;
      this.numberRecords        = 0;;
      this.investmentRecordList = new InvestmentRecord [arrayCapacity];
   }
   
   
   /**
    * Initialization Constructor
    * 
    * Initializes the internal array of InvestmentRecords to provide
    * a number of slots in that array that is passed in as a parameter
    * 
    * @param principle Initial investment
    * @param rate Rate of return
    * @param years Number of years compounded
    */
   public InvestmentRecordList(int arrayCapacity)
   {
      this.arrayCapacity        = arrayCapacity;
      this.numberRecords        = 0;;
      this.investmentRecordList = new InvestmentRecord [arrayCapacity];
   }

   
   /**
    * Copy constructor
    * 
    * This constructor creates an InvestmentRecordList object that has an internal array
    * of InvestmentRecords, that has the SAME array capacity as the copied object,
    * with exact COPIES of EACH of the array elements of the copied object.
    * 
    * @param copied Object to copy from
    */
   public InvestmentRecordList(InvestmentRecordList copied)
   {
      int index;
      
      this.arrayCapacity = copied.arrayCapacity;
      this.numberRecords = copied.numberRecords;
        this.investmentRecordList = new InvestmentRecord [arrayCapacity];

        // run through the internal array of the 'copied' object,
        // create exact copies of each of the objects contained in that array and
        // put them into the internal array of this object.
      for (index = 0; index < numberRecords; index++)
      {
            this.investmentRecordList[index] = 
                  new InvestmentRecord(copied.investmentRecordList[index]);
      }
   }

   
   /**
    * Adds an investment record to list
    * 
    * @param investmentRecord
    * @return true on success, false otherwise
    */
   public boolean addInvestmentRecord(InvestmentRecord investmentRecord)
   {
        // check if the number of records is less than the array capacity
        // if so, the record will be added and true returned, otherwise return false
        // note that a copy of the InvestmentRecord object passed in as a parameter needs to be added!
      if(numberRecords < arrayCapacity)
      {
         investmentRecordList[numberRecords] = investmentRecord;
         numberRecords++;
         return true;
      }
      
      return false;
   }
   
   
   /**
    * Displays all investment data records contained in this object's internal array 
    */
   public void displayResults()
   {
      int index;
      
      for (index = 0; index < numberRecords; index++) {
         displayResult(investmentRecordList[index]);
         conIO.printEndline();
      }
   }
   
   
   /**
    * Displays one record of investment data in table format
    * 
    * @param investmentRecord to be displayed
    */
   public void displayResult(InvestmentRecord investmentRecord) 
   {     
      double total, doublingPeriod;
      
      total = investmentRecord.computeTotal();
      doublingPeriod = investmentRecord.computeDoublingPeriod();

      // display result
      
        // show top thick line
        conIO.printEndline();
        displayThickLine(conIO, TABLE_WIDTH - 2);

        // show principle
        displayDoubleLine(conIO, "Principle", investmentRecord.getPrinciple());
        
        // show divider thin line
        displayThinLine(conIO, LEFT_COLUMN_WIDTH, RIGHT_COLUMN_WIDTH);

        // show rate in %, so multiply by 100
        displayDoubleLine(conIO, "Rate of Return", investmentRecord.getRate()*100);

        // show divider thin line
        displayThinLine(conIO, LEFT_COLUMN_WIDTH, RIGHT_COLUMN_WIDTH);

        // show number of years
        displayIntLine(conIO, "Number of years", investmentRecord.getYears());
        
        // show middle thick line
        displayThickLine(conIO, TABLE_WIDTH - 2);

        // show total compounded investment
        displayDoubleLine(conIO, "Principle + Compounded Interest", total);

        // show divider thin line
        displayThinLine(conIO, LEFT_COLUMN_WIDTH, RIGHT_COLUMN_WIDTH);

        // show doubling period
        displayDoubleLine(conIO, "Approximate Doubling Period", doublingPeriod);

        // show bottom thick line of table
        displayThickLine(conIO, TABLE_WIDTH - 2);

        conIO.printEndline();
   }

   
   /**
    * Helper method, displays a line in the output table that has a double value.
    * 
    * @param conIO Object doing the I/O
    * @param itemDescription Item description
    * @param value Value of item
    */
   private void displayDoubleLine(Console_IO_Class conIO, String itemDescription, Double value)
   {
        // method: printString, printChar, printDouble, printEndline
      conIO.printString(PIPE_SPACE);
        conIO.printString(itemDescription, LEFT_COLUMN_WIDTH - 1, "LEFT");
        conIO.printChar(PIPE);
        conIO.printDouble(value, PRECISION, RIGHT_COLUMN_WIDTH - 1, "RIGHT");
        conIO.printString(SPACE_PIPE);
        conIO.printEndline();
   }

   /**
    * Helper method, displays a line in the output table that has an int value.
    * 
    * @param conIO Object doing the I/O
    * @param itemDescription Item description
    * @param value Value of item
    */
   private void displayIntLine(Console_IO_Class conIO, String itemDescription, int value)
   {
        // method: printString, printChar, printInt, printEndline
      conIO.printString(PIPE_SPACE);
        conIO.printString(itemDescription, LEFT_COLUMN_WIDTH - 1, "LEFT");
        conIO.printChar(PIPE);
        conIO.printInt(value, RIGHT_COLUMN_WIDTH - 1, "RIGHT");
        conIO.printString(SPACE_PIPE);
        conIO.printEndline();
   }
   
   
   /**
    * Helper method displaying a thick line in the output table.
    * 
    * @param conIO Object doing the I/O
    * @param width Width of the line
    */
   private void displayThickLine(Console_IO_Class conIO, int width)
   {
        // method: printChar, printChars, printEndline
        conIO.printChar(PIPE);
        conIO.printChars(width, THICK_LINE);
        conIO.printChar(PIPE);
        conIO.printEndline();
   }
   
   
   /**
    * Helper method displaying a thick thin in the output table.
    * 
    * @param conIO Object doing the I/O
    * @param widthLeft Width of the line to the left of middle pipe symbol
    * @param widthRight Width of the line to the right of middle pipe symbol
    */
   private void displayThinLine(Console_IO_Class conIO, int widthLeft, int widthRight)
   {
        // method: printChar, printChars, printEndline
        conIO.printChar(PIPE);
        conIO.printChars(widthLeft, THIN_LINE);
        conIO.printChar(PIPE);
        conIO.printChars(widthRight, THIN_LINE);
        conIO.printChar(PIPE);
        conIO.printEndline();
   }


   /**
    * Writes all investment data records to a file.
     * Before any record is written, the number of records is put into the file first

     * @param fileName The name of the file the data is being written to.
     * @return boolean true if the file could be opened, false otherwise.
    */
   public boolean loadInvestmentRecords(String fileName)
   {
      // create file output object
        File_Output_Class outputFile = new File_Output_Class();
        
        // helper index for looping
      int index;
      
        // if the output file can be opened, write the number of records and then all records into the file and return true,
        // return false otherwise
      if( outputFile.openOutputFile(fileName) )
      {
         // write the number of records and a new line
            outputFile.writeInt(this.numberRecords);
         outputFile.writeEndline();
         
            // run through all records and write each record with a space in between values and a new line at the end of each record
         for( index = 0; index < numberRecords; index++ )
         {  
            outputFile.writeDouble(investmentRecordList[index].getPrinciple(),
                                   PRECISION);
            
            outputFile.writeChar(' ');
            
            outputFile.writeDouble(investmentRecordList[index].getRate(),
                                   PRECISION);
            outputFile.writeChar(' ');
            
            outputFile.writeInt(investmentRecordList[index].getYears());
            outputFile.writeEndline();
         }
         
            // close output file
         outputFile.closeOutputFile();
         
         return true;
      }
      
      return false;  
   }

   
   /**
    * Reads all investment data records from the file whose name is passed in as a parameter
    * 
    * @param fileName the name of the file that investment data records are being read from.
    * @return boolean true if the file could be opened, false otherwise.
    */
   public boolean retrieveInvestmentRecords(String fileName)
   {
        // creat input file object
      File_Input_Class inputFile = new File_Input_Class();

      
      double tmpPrinciple;
      double tmpRate;
      int    tmpYears;
      
      InvestmentRecord tempRecord;
      
        // if the input file can be opened, read the number of records and then all of the records,
        // load into this object's internal array and return true,
        // return false otherwise
      if( inputFile.openInputFile(fileName) )
      {
         
            // read number of records
            numberRecords = inputFile.getInt();
         
            // run through all record of the file and load each record's pieces into tmp variables
            // create an InvestmewntRecord object and put it into the correct slot of this object's internal array
         for( int counter = 0; counter < numberRecords; counter++ )
         {     
             tmpPrinciple = inputFile.getDouble();
             tmpRate = inputFile.getDouble();
             tmpYears = inputFile.getInt();
             
             tempRecord = new InvestmentRecord(tmpPrinciple, tmpRate, tmpYears);
             
             investmentRecordList[counter] = tempRecord;
         }
         
            // close input file
         inputFile.closeInputFile()
;        
         return true;
      }
      
      return false;     
   }
}