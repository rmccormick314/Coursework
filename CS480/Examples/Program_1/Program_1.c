#include <stdio.h>

/*
Function Name:  main
Algorithm:      Accept two integer values, add them to a double sum,
                then display the result.
Precondition:   None
Postcondition:  Return 0 on success.
Exceptions:     None
Notes:          Demonstrate input, output, and simple math.
*/
int main()
   {
   // Initialize function & variables.
   int augend, addend;
   double sum = 0;

   // Display title.
      // Function: printf
      printf( "\nAddition Program\n" );
      printf( "================\n" );  

   // Get input from user.
      // Get augend.
         // Function: printf, scanf
         printf( "\nEnter Augend: " );
         scanf( "%d", &augend );

      // Get addend.
         // Function: printf, scanf
         printf( "\nEnter Addend: " );
         scanf( "%d", &addend );

   // Add values.
   sum = augend + addend;

   // Display result to user.
      // Function: printf
      printf( "\nThe sum of %d and %d is %4.2f\n\n", augend, addend, sum );

   // Shut down.
      // Return Success
      return 0;

   }
