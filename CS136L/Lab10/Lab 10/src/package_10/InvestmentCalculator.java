package package_10;


/**
 * A class that provides an interface to work with objects of the other two classes
 * The main method provides two modes of operation:
 *  - Loading, i.e. allowing the user to input any number of investment data records,
 *    creating an InvestmentRecordList object and have the object write all records into a file
 *  - Retrieving, i.e. reading all investment data records from a file
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
    * @param args Command line arguments, not used
    */
   public static void main(String args[]) 
   {
      // finance variables
      double principle = 0.0;
      double rate = 0.0;
      int years = 0;
      
      // headline output
      String heading = "INVESTMENT CALCULATOR:";;
      
      // investment records object
      InvestmentRecordLinkedList investmentRecordList = new InvestmentRecordLinkedList();
      
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
               // get the three pieces of data, i.e. principle, rate and years
                principle = conIO.promptForDouble("Enter the original investment: ");
                rate      = conIO.promptForDouble("Enter the rate of return in %: ") / 100.0;
                years     = conIO.promptForInt("Enter the number of years: ");
                conIO.printEndline();
                
                // create a new calculator object, using the initialization constructor
                tmpInvestmentRecord = new InvestmentRecord(principle, rate, years);
                
                // add the investment record to the list
                investmentRecordList.addInvestmentRecord(tmpInvestmentRecord);
                
                // prompt user to determine whether to continue loading data or to finish
                controlChar = conIO.promptForChar("Enter another record? y/n: ");                
            }
            while (controlChar == 'y'); // as long as user enters 'y' char
             
            // output data into a file
            investmentRecordList.loadInvestmentRecords(FILE_NAME);
            
            // print all data
            investmentRecordList.displayResults();
            
            // print out message indicating that we are done
            System.out.println("Done writing data into file");
        }
        // retrieve operation, we will be retrieving data from a file and display it
        else if(controlChar == 'r' || controlChar == 'R')
        {
         investmentRecordList.retrieveInvestmentRecords(FILE_NAME);

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