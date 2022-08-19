package package_9;

public class TimesTable {

   // contains the dimensions of the times table
   private int rows = 0;
   private int cols = 0;
   
   // helper variables to be able to traverse through the array elements
   private int index_rows, index_cols;
   
   // this variable holds the 2-dim array data
   int [][] timesTableData = null;
   
   /**
    * Initialization constructor
    * @param rows
    * @param cols
    */
   public TimesTable(int rows, int cols)
   {
      // set the dimensions
      this.rows = rows;
      this.cols = cols;
      
      // create new 2-dim integer object
      timesTableData = new int[rows][cols];
      
      // fill times table with data
      fillTimesTable();
   }
   
   /**
    * Default constructor - creates a times table object of 10x10
    */
   public TimesTable()
   {
      
      //Constructs array to default 10x10, populates
      rows = 10;
      cols = 10;
      
      timesTableData = new int[rows][cols];
      fillTimesTable();
   }
   
   
   /**
    * Fills a times table with multiplication data
    */
   private void fillTimesTable()
   {
      for (index_cols = 1; index_cols <= cols; index_cols++)
         {
            for(index_rows = 1; index_rows <= rows; index_rows++)
               {
                  //Populates table within bounds (zero inclusive)
                  //Offset by 1 to remove zero col/row
                  timesTableData[index_cols-1][index_rows-1] = index_cols * index_rows;
               }
         }
   }
   
   
   /**
    * Print out times table
    */
   void printTimesTable()
   {
      Console_IO_Class printer = new Console_IO_Class();
      
      for (index_cols = 0; index_cols < cols; index_cols++)
         {
            for (index_rows = 0; index_rows < rows; index_rows++)
               {
                  //Prints table as would normally be recognized
                  printer.printInt(timesTableData[index_cols][index_rows], 3, "LEFT");
                  printer.printChar(' ');
               }
            //Hop down to next row in table
            printer.printEndline();
         }
      printer.printEndline();
   }
   
   
   /**
    * Look up a specific result from the times table and return it
    * 
    * @param a - First integer to be multiplied
    * @param b - Second integer to be multiplied
    * 
    * @return  - Result of operation (int value)
    */
   int getResult(int a, int b)
   {
      //Returns result of specific operation (a times b)
      //Offset by one for aesthetics (ignoring blank row/col)
      return (timesTableData[a-1][b-1]);
   }
   
   
   /**
    * Driver
    * 
    * @param args
    */
   public static void main(String [] args)
   {
      // create times table
      TimesTable tt = new TimesTable();
      
      // create variables for two factors
      int a = 5, b = 7;
      
      // create the IO object
      Console_IO_Class conIO = new Console_IO_Class(); 
      
      // print out whole table
      tt.printTimesTable();
      
      // print out a specific result
      conIO.printString("Result is: " + tt.getResult(a, b));
      conIO.printEndline();
      
      conIO.printString("Searching 9 times 7: " +tt.getResult(9, 7));
      conIO.printEndline();
      
      conIO.printString("Searching 4 times 5: " +tt.getResult(4, 5));
   }
}