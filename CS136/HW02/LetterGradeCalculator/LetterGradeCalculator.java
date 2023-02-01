/*
Title:             LetterGradeCalculator
Desc:              Calculates an average and letter grade from 3 inputted grades
Files:             LetterGradeCalculator.java
Semester:          Fall 2019
Author name:          Richard McCormick
Author email:    rlm443@nau.edu
Class section:       01
*/

package lettergradecalculator;

import java.util.Scanner;

public class LetterGradeCalculator {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        Scanner scanner = new Scanner(System.in);
        int[] userGrades = new int[3];
        int averageGrade = 0;
        String letterGrade;
        
        System.out.println("Please enter 3 grades: ");
        
        userGrades[0] = scanner.nextInt();
        userGrades[1] = scanner.nextInt();
        userGrades[2] = scanner.nextInt();
        
        for (int i = 0; i<userGrades.length; i++){

            averageGrade += userGrades[i];
            
        }
        
        averageGrade = averageGrade / userGrades.length;
        System.out.println("Average grade is: " + averageGrade);
        if (averageGrade >= 90)
        {
            letterGrade = "A";
            System.out.println(letterGrade);
        }
        else if (averageGrade >= 80)
        {
            letterGrade = "B";
            System.out.println(letterGrade);
        }
        else if (averageGrade >= 70)
        {
            letterGrade = "C";
            System.out.println(letterGrade);
        }
        else if (averageGrade >= 60)
        {
            letterGrade = "D";
            System.out.println(letterGrade);
        }
        else 
        {
            letterGrade = "F";
            System.out.println(letterGrade);
        }
        
    }
    
}
