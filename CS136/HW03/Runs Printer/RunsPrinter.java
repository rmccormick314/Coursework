/*
Title:             RunsPrinter
Desc:              Generates a list of 20 dice and groups similar values
Files:             RunsPrinter.java
Semester:          Fall 2019
Author name:          Richard McCormick
Author email:       rlm443@nau.edu
Class section:       01
*/

import java.util.Random;
import java.util.ArrayList;

public class RunsPrinter {

    public static void main(String[] args) {
        //Some variables
        Random rand = new Random();
        int[] diceArray = new int[20];
        boolean inRun = false;

        //Variable initialization
        String dice = "";
        int current = -1;
        int last = -1;
        int next = -1;

        //This loop generates the array of dice values
        for (int i = 0; i < 20; i++){
          //For each array slot, generate a number between 1 and 6 (inclusive)
          diceArray[i] += (rand.nextInt(6)+1);
        }

        //This loop is where the work is done
        for (int i = 0; i < 20; i++){
          //Set previous and next dice numbers
          current = diceArray[i];
          if (i != 0){
            last = diceArray[i-1];
          }
          if (i != 19){
            next = diceArray[i+1];
          }
          //This one is a check for the final value in sequence
          if (i == 19){
            next = -1;
          }


          //Main code chunk, checks current value against previous and
          //next values to determine if they are the same
          if (inRun){
            if (current != last){
              dice += ")";
              inRun = false;
            }
          }

          if (inRun == false){
            if (current == next){
              dice += "(";
              inRun = true;
            }
          }

          //Adds current value to the dice string
          dice += diceArray[i];

          //Check for the final value; fixes final index error
          if(next == (-1) && current == last){
            dice += ")";
          }

        }

        //Prints completed run
        System.out.println(dice);
    }
}
