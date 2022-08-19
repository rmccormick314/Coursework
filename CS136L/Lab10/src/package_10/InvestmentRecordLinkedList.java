package package_10;



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
public class InvestmentRecordLinkedList 
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
   
   // The reference into the linked list, i.e. its first element
   private InvestmentRecord headRecord = null;

   // convenience object to do console IO
   private Console_IO_Class conIO = new Console_IO_Class();

   
   /**
    * Default constructor
    * 
    * Initializes the internal array of InvestmentRecords to provide
    * MAX_NUMBER_RECORDS of slots in that array
    */
   public InvestmentRecordLinkedList()
   {
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
    public InvestmentRecordLinkedList(InvestmentRecordLinkedList copied)
    {
      InvestmentRecord currentCopiedRecord = copied.headRecord;
      InvestmentRecord currentRecord = null; // work reference
      
      // check if there is any record in copied, if not, we can bail out
      if ( currentCopiedRecord != null)
      {
         // copy over the head record
           this.headRecord = new InvestmentRecord(currentCopiedRecord);
         
         // set the work reference to the newly created head record
           currentRecord = this.headRecord;
           
           // as long as there are more records in copied ...
         while (currentCopiedRecord.nextRecord != null)
         {
            // COPY over record
            currentRecord.nextRecord = 
                  new InvestmentRecord(currentCopiedRecord.nextRecord);
            
            // update references for both linked lists
            currentRecord = currentRecord.nextRecord;
            currentCopiedRecord = currentCopiedRecord.nextRecord;
         }  
      }
    }
    
    
   /**
    * Adds an investment record to list
    * 
    * @param investmentRecord
    * @return true on success, false otherwise
    */
   public void addInvestmentRecord(InvestmentRecord investmentRecord)
   {
      InvestmentRecord currentRecord = null; // work reference
      
      // is there a head record?
      if (headRecord != null)
      {
         // load work reference with head record
         currentRecord = headRecord;
         
         // as long as there are records ... traverse list until you reached end
         while (currentRecord.nextRecord != null)
         {
            // update reference
            currentRecord = currentRecord.nextRecord;
         }
         
         // arrived at the end, store record
         currentRecord.nextRecord = new InvestmentRecord(investmentRecord);
      } 
      else
      {
         // save the record directly into the head record
         headRecord = new InvestmentRecord(investmentRecord);
      }
      
   }
   
   
   /**
    * Displays all investment data records contained in this object's internal array 
    */
   public void displayResults()
   {
      InvestmentRecord currentRecord = headRecord;
      
      while(currentRecord != null)
      {
         displayResult(currentRecord);
         conIO.printEndline();
         
         currentRecord = currentRecord.nextRecord;
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
      File_Output_Class outputFile = new File_Output_Class();
      InvestmentRecord currentRecord = null; // work reference
      
      // open file and check return flag
      if( outputFile.openOutputFile(fileName) )
      {     
         // check if there is a head record
         if ( headRecord != null )
         {
            // set the work reference
            currentRecord = headRecord;
            
            //This section adds the number of records to the file
            //as the first line, however, does not appear to be supported
            
            //int numberOfRecords = 1;
            //InvestmentRecord tempRef = headRecord;
            
            //while (tempRef.nextRecord != null)
               {
                  //numberOfRecords++;
                  //tempRef = tempRef.nextRecord;
               }

            //outputFile.writeInt(numberOfRecords);
            //outputFile.writeEndline();
            
            // as long as work reference has a record ...
            while( currentRecord != null )
            {
               // write the full line of data, i.e. the three pieces of the record, separated by spaces, then terminated with newline
               outputFile.writeDouble(currentRecord.getPrinciple(), PRECISION);
               outputFile.writeChar(' ');
               
               outputFile.writeDouble(currentRecord.getRate(), PRECISION);
               outputFile.writeChar(' ');
               
               outputFile.writeInt(currentRecord.getYears());
               outputFile.writeEndline();
               
               // update work reference
               currentRecord = currentRecord.nextRecord;
            }

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
    * @param fileName the name of the file that investment data records are being read from
    * @return boolean true if the file could be opened, false otherwise
    */
   public boolean retrieveInvestmentRecords(String fileName)
   {
      File_Input_Class inputFile = new File_Input_Class();
      InvestmentRecord currentRecord = null;
      boolean stop = false;
      
      double tmpPrinciple;
      double tmpRate;
      int    tmpYears;
      
      if ( inputFile.openInputFile(fileName ))
      {

         // read first record for the headRecord
         tmpPrinciple = inputFile.getDouble();     
         tmpRate      = inputFile.getDouble();
         tmpYears     = inputFile.getInt();

         // check if there was data at all ...
         if ( !inputFile.checkForEndOfFile() )
         {
            // load the headRecord with the data read
            headRecord    = new InvestmentRecord(tmpPrinciple, tmpRate, tmpYears);
            currentRecord = headRecord;
            
            // read all remaining records
            do
            {
               tmpPrinciple = inputFile.getDouble();
               tmpRate      = inputFile.getDouble();
               tmpYears     = inputFile.getInt();
               
               // we only detect if we have reached the end of file after we tried to read data
               // so check whether last read attempt didn't retrieve data
               if( !inputFile.checkForEndOfFile() )
               {
                  // there was data, so save another record
                  currentRecord.nextRecord = new InvestmentRecord(tmpPrinciple, tmpRate, tmpYears);
                  currentRecord = currentRecord.nextRecord;
               }
               else
               {
                  // there was no data, break out of the loop
                  stop = true;
               }
            }
            while(!stop);
         }
            
         // close file
         inputFile.closeInputFile();
         
         // we successfully accessed the file and read data (if there was any)
         return true;
      }
      
      // there was a problem opening the file
      return false;     
   }
}