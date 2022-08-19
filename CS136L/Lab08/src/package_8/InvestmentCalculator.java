package package_8;



/**
 * A class that provides an interface to work with objects of the other two classes
 * The main method provides two modes of operation:
 *  - Loading, i.e. allowing the user to input any number of investment data records,
 *    creating an InvestmentRecordList object and have the object write all records into a file
 *  - Retrieving, i.e. reading all investment data records from a file
 *    and putting the records into an InvestmentRecordList object
 *  
 *  In both modes of operation, all the records are also printed out on the standard output in table format
 * 
 * @author Dr.-Ing. Wolf-Dieter Otte
 */
public class InvestmentCalculator
{
   // Constant that has the char to construct "thick" lines 
   public static final char THICK_LINE = '=';
   
   // io object to be used in main()
   public static Console_IO_Class conIO = new Console_IO_Class();
   
   // File name to contain investment data
   public static String FILE_NAME = "InvestmentData.txt";
      
   /**
    * Get things started ...
     *
    * @param args Command line arguments, not used
    */
   public static void main(String args[]) 
   {
      // finance variables
      double principle;
      double rate;
      int years;
      
      // headline output
      String heading = "INVESTMENT CALCULATOR:";;
      
      // investment records object
      InvestmentRecordList investmentRecordList = new InvestmentRecordList();
      
      // temporary investment record
      InvestmentRecord tmpInvestmentRecord;
      
      // control character to capture user control input
      char controlChar;
      
        // show title and thick line
        // method: printString, printEndline, printChars
        conIO.printString(heading);
        conIO.printEndline();
        conIO.printChars(heading.length(), THICK_LINE);
        conIO.printEndline();
        conIO.printEndline();

        // determine whether we will be loading data into a file or retrieving data from a file
        controlChar = conIO.promptForChar("Enter 'l' for loading data or 'r' for retrieving data: ");
        
        // load operation, we will be loading data into a file
        if(controlChar == 'l' || controlChar == 'L')
        {
         //keep looping as long as the user enters 'y' at the last prompt
            do
            {
               // get the three pieces of data, i.e. principle, rate and years from the user
                principle = conIO.promptForDouble("Enter the original investment: ");
                rate = conIO.promptForDouble("Enter the rate of return in %: ") / 100;
                years = conIO.promptForInt("Enter the number of years: ");
                
                // create a new investment record object, using the InvestmentRecord initialization constructor
                tmpInvestmentRecord = new InvestmentRecord(principle, rate, years);

                // add the investment data record to the InvestmentRecordList object using its addInvestmentRecord() method
                investmentRecordList.addInvestmentRecord(tmpInvestmentRecord);

                // prompt user to determine whether to continue loading data or to finish
                conIO.printEndline();
                controlChar = conIO.promptForChar("Enter another record? y/n: ");
            }
            while (controlChar == 'y'); // as long as user enters 'y' char
             
            // output investment data records into a file
            investmentRecordList.loadInvestmentRecords(FILE_NAME);

            // print all investment data records
            investmentRecordList.displayResults();

            // print out message indicating that we are done
            System.out.println("Done writing data into file");
        }
        // retrieve operation, we will be retrieving data from a file and display it
        else if(controlChar == 'r' || controlChar == 'R')
        {
         // have the InvestmentRecordList object retrieve all records from the file
            investmentRecordList.retrieveInvestmentRecords(FILE_NAME);

            // print all investment data records
            investmentRecordList.displayResults();

            // indicate that we are done with reading data from file
         System.out.println("Read all data from file");         
        }
        // user entered an invalid character
        else
        {
         // indicate user entered invalid character and the system will exit
         System.out.println("Invalid input, exiting");
         
         // exit program flow
         System.exit(1);
        }
   }
}