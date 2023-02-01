/*
Title:             Nim
Desc:              Plays Nim
Files:             Nim.java
Semester:          Fall 2019
Author 1:          Amy Stamile
Author 1 Email:    ak2224@nau.edu
Author 2:          Richard McCormick
Author 2 Email:    rlm443@nau.edu
Lab Section:       03
*/
import java.util.Scanner;
import java.util.Random;

public class Nim {

    public static void main(String[] args) {
        Random random = new Random();
        Scanner scan = new Scanner(System.in);
        int intelligence = random.nextInt(1);
        int starter = random.nextInt(1);
        int pile = random.nextInt(100 - 10 + 1) + 10;
        int compChoice = -1;
        //Human starts
        if (starter == 0){
            while(pile > 0){
                System.out.println("Current number of marbles in pile: " + pile);
                System.out.print("How many marbles do you want to remove?: ");
                int userInput = scan.nextInt();
                //Checks user input to make sure it is valid.
                while (userInput > (pile/2) || userInput <= 0){
                  System.out.print("Please enter a valid number: ");
                  userInput = scan.nextInt();
                }
                pile = pile - userInput;
                //Dumb mode
                if (intelligence == 0){
                    if (pile > 1){
                        compChoice = random.nextInt(pile/2) + 1;
                        System.out.println("Computer removes " + compChoice + " marble(s)");
                        pile -= compChoice;
                        if (pile == 1){
                          System.out.print("The user took the last marble. Computer Wins!");
                          pile = 0;
                        }
                    }
                    else{
                        compChoice = 1;
                        System.out.print("The computer took the last one. You win!");
                        pile = 0;
                    }
                }
                //Smart Mode
               else if (intelligence == 1){
                if (pile > 1){
                  if (pile > 64){
                    compChoice = pile - 63;
                  }
                  else if (pile > 32){
                    compChoice = pile - 31;
                  }
                  else if (pile > 16){
                    compChoice = pile - 15;
                  }
                  else if (pile > 8){
                    compChoice = pile - 7;
                  }
                  else if (pile > 4){
                    compChoice = pile - 3;
                  }
                  else if (pile == 2){
                    compChoice = 1;
                  }
                  else if (pile == 3) {
                    compChoice = 2;
                  }
                  System.out.println("Computer removes " + compChoice + " marbles(s)");
                  pile -= compChoice;
                  if (pile == 1){
                    System.out.print("The user took the last marble. Computer Wins!");
                    pile = 0;
                  }
                }
                else{
                  compChoice = 1;
                  System.out.print("The computer took the last one. You win!");
                  pile = 0;
                }
              }
             }
           }
        //Computer starts
        if (starter == 1){
          while(pile > 0){
            System.out.println("Current number of marbles in pile: " + pile);
            //Dumb mode
            if (intelligence == 0){
              if (pile > 1){
                  compChoice = random.nextInt(pile/2) + 1;
                  System.out.println("Computer removes " + compChoice + " marble(s)");
                  pile -= compChoice;
                  if (pile == 1){
                    System.out.print("There is one marble left. You lose!");
                    pile = 0;
                  }
              }
              else if (pile == 1){
                  compChoice = 1;
                  System.out.print("The computer took the last one. You win!");
                  pile = 0;
              }
              if (pile > 1){
                System.out.print("How many marbles do you want to remove?: ");
                int userInput = scan.nextInt();
                while (userInput > (pile/2) || userInput <= 0){
                  System.out.print("Please enter a valid number: ");
                  userInput = scan.nextInt();
                }
                pile = pile - userInput;
              }
            }
            //Smart Mode
            else if (intelligence == 1){
              if (pile > 1){
                if (pile > 64){
                  compChoice = pile - 63;
                }
                else if (pile > 32){
                  compChoice = pile - 31;
                }
                else if (pile > 16){
                  compChoice = pile - 15;
                }
                else if (pile > 8){
                  compChoice = pile - 7;
                }
                else if (pile > 4){
                  compChoice = pile - 3;
                }
                else if (pile == 2){
                  compChoice = 1;
                }
                else if (pile == 3){
                  compChoice = 2;
                }
                System.out.println("Computer removes " + compChoice + " marbles(s)");
                pile -= compChoice;
                if (pile == 1){
                  System.out.print("The user took the last marble. Computer Wins!");
                  pile = 0;
                }
              }
               else{
                 compChoice = 1;
                 System.out.print("The computer took the last one. You win!");
                 pile = 0;
               }
              }
          }
      }
  }
}
