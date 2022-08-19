package package_7a;


/*
 * This is how this code works:
 * 
 * This program 'guesses' a number that the user chooses,
 * by asking a series of yes or no questions which gradually
 * narrows down the number of possibilities.
 * 
 * The program will increase the range of possible numbers,
 * until the user indicates that the number is smaller than
 * the working range. At this point, the program will slowly
 * narrow down the range until the chosen number is found.
 * 
 * The mid value functions as the working 'guessed value',
 * while the Min and Max values indicate the lowest and
 * highest range the program will attempt to guess within,
 * respectively.
 * 
 * Each loop, the mid value is determined based on an increasing minimum
 * value and a decreasing maximum value. As long as the user indicates 
 * their number is bigger than the current maximum value, the maximum value will
 * continue to increase. However, once the user indicates that
 * their number is BELOW the maximum value, the program will cap the 
 * maximum value wherever it is at, and instead start increasing
 * the MINIMUM value. This process will continue until the min
 * and max values are equal to each other.
 * 
 * Once the maximum and minimum values are the same, the range of
 * the two will be equal to zero, indicating only a single possible
 * answer. Whatever the value of
 * both variables is the user's guessed number.
 */

public class Guess {
   
   //These are private static modifiers: constants
   private static final int  MAX           = 1000;
   private static final int  MIN           = 1;
   
   //These are for reading user interaction
   private static final char QUESTION_MARK = '?';
   private static final char YES_CHAR      = 'y';
   private static final char NO_CHAR       = 'n';
   
   public static void main (String [] args)
   {
      //Initialize working variables
       int    min = MIN, max = MAX, mid;
       
       //Set a default response
       char response = 0;
        Console_IO_Class conIO = new Console_IO_Class();

        //Asks the user for an input
        conIO.printString("Think of a number between ");
        conIO.printInt(MIN);
        conIO.printString(" and ");
        conIO.printInt(MAX);
        conIO.printEndlines(2);
        
       //When min == max, a singular number has been found.
       //This value is the users guess
       while (min != max)
       {
          //Constantly updates midpoint
           mid = (min + max) / 2;
           
           //Updates information based on user response
           conIO.printString("Is your number greater than ");
           conIO.printInt(mid);
           conIO.printChar(QUESTION_MARK);
           conIO.printEndline();
           
           response = conIO.promptForChar("");

           //If selecting yes, number must be bigger than min
           //Thus, min is increased
           if (response == YES_CHAR)
           {
               min = ++mid;
           }
           //If selecting no, we have found that it MUST be smaller
           //Than whatever current working point is. Wherever
           //the program is at is now the new maximum.
           else if (response == NO_CHAR)
           {
               max = mid;
           }
           //If user doesn't enter valid answer, prompt them to
           else
           {
              conIO.printString("Please enter y or n!");
              conIO.printEndline();            
           }
       }
       
       conIO.printString("Your number is: ");
       conIO.printInt(min);
   }
}

