package package_7;


/**
 * Driver to test objects of type InvestmentCalculator
 * 
 * @author Dr.-Ing. Wolf-Dieter Otte
 */
public class InvestmentCalculatorMain
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
        // declare and initialize variables
		
		// finance variables
		double principle = 0.0;
		double rate = 0.0;
		int years = 0;
		
		// headline output
		String heading = "INVESTMENT CALCULATOR:";;
		
		// input and output file objects
		File_Output_Class outputFile = null;
		File_Input_Class inputFile = null;
		
		// investment calculator object
		InvestmentCalculator calculator = new InvestmentCalculator();
		
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
        	// create a file output object
            // ...
            outputFile = new File_Output_Class();
            
            // open up the data file with the given name
        	// ...
            outputFile.openOutputFile(FILE_NAME);
            
        	//keep looping as long as the user enter 'y' at the last prompt
            do
            {
            	// get the three pieces of data, i.e. principle, rate and years
                // ...
                principle = conIO.promptForDouble("Enter the original investment: ");
                rate = conIO.promptForDouble("Enter the rate of return in %: ");
                years = conIO.promptForInt("Enter the number of years: ");
               
                // create a new calculator object, using the initialization constructor
                // ...
                InvestmentCalculator newCalc = new InvestmentCalculator(principle, rate, years);
                
                // load the data into the open file
                // ... call load method on calculator
                newCalc.loadInvestmentRecord(outputFile);
                conIO.printEndline();
                
                // prompt user to determine whether to continue loading data or to finish
                // ...
                controlChar = conIO.promptForChar("Load another record? Y/n: ");
                
                // if the user intends to load another record, we need to print a newline character '\n' into file
                if(controlChar == 'y')
                {
                	outputFile.writeChar('\n');
                }
                
            } while (controlChar == 'y'); // as long as user enters 'y' char
               
            // we are done, close file
            // ...
            outputFile.closeOutputFile();

            // print out message indicating that we are done
            System.out.println("Done writing data into file");
        }
        
        // retrieve operation, we will be retrieving data from a file and display it
        else if(controlChar == 'R' || controlChar == 'r')
        {
        	// create file input object
            // ...
            inputFile = new File_Input_Class();
           
            // open up the data file with the given name
           // ...
            inputFile.openInputFile(FILE_NAME);
            
           // keep retrieving data from the file as long as we have not reached the end of the file
           // for each loop, the calculator object's fields get new principle, rate and years data
            while(calculator.retrieveInvestmentRecord(inputFile))
            {
            	// display the new data record in table format
            	// ...
               calculator.displayResult();
            }
            
            // close the input file
            // ...
            inputFile.closeInputFile();
            
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