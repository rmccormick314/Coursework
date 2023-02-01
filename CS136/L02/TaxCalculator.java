import java.util.Scanner;

/*
Title:             TaxCalculator
Desc:              Take a number of seconds and display the total broken down time
Files:             TaxCalculator.java
Semester:          Fall 2019
Author 1:          Richard McCormick
Author 1 Email:    rlm443@nau.edu
Author 2:          Jacob Heslop
Author 2 Email:    jmh727@nau.edu
Lab Section:       3
*/

public class TaxCalculator{

  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    System.out.print("Are you married or single? ");
    String RelationshipStatus = scanner.next();
    System.out.print("What is your income? ");
    int income = scanner.nextInt();
    double tax = 0.00;

    final double TAXABLE_INCOME_OVER = 8000;
    final double TAX_FIRST_PERCENT = .1;
    final double TAX_SECOND_PERCENT = .15;
    final double TAX_THIRD_PERCENT = .25;
    final double SECOND_ADDED = 800;
    final double THIRD_ADDED = 4400;

    if (RelationshipStatus.equalsIgnoreCase("single")){
      if (income <= TAXABLE_INCOME_OVER){
        tax += income * TAX_FIRST_PERCENT;
      }
      else if (income <= (TAXABLE_INCOME_OVER * 4)){
        tax += ((income - TAXABLE_INCOME_OVER) * TAX_SECOND_PERCENT)
        + SECOND_ADDED;
      }
      else{
        tax += THIRD_ADDED + ((income - (TAXABLE_INCOME_OVER * 4))
        * TAX_THIRD_PERCENT);
      }
    }
    else{
      if (income <= (TAXABLE_INCOME_OVER * 2)){
        tax += income * TAX_FIRST_PERCENT;
      }
      else if (income <= (TAXABLE_INCOME_OVER * 8)){
        tax += ((income - (TAXABLE_INCOME_OVER * 2)) * TAX_SECOND_PERCENT + (SECOND_ADDED * 2));
      }
      else{
        tax += (THIRD_ADDED * 2) + ((income - (TAXABLE_INCOME_OVER * 8))
        * TAX_THIRD_PERCENT);
      }
    }

    System.out.println("You owe $" + tax + "0 in tax.");

  }
}
