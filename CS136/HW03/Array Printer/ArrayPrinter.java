/*
Title:             Array Printer
Desc:              Generates a list of 20 numbers in an array and prints
                    in various forms
Files:             ArrayPrinter.java
Semester:          Fall 2019
Author name:          Richard McCormick
Author email:       rlm443@nau.edu
Class section:       01
*/

import java.util.Random;
import java.util.ArrayList;
public class ArrayPrinter {


    public static void main(String[] args) {
        Random rand = new Random();

        int[] array = new int[20];

        int i = 0;

        while (i < 20){
            array[i] = rand.nextInt(19)+2;
            i += 1;
        }

        int k = 0;
        String theArray = "";
        while (k < 20){
            theArray += array[k] + " ";
            k += 1;
        }

        String evenIndicies = "";
        int j = 0;
        while (j < 20){
            evenIndicies += array[j] + " ";
            j += 2;
        }

        String evenElements = "";
        int g = 0;
        while (g <20){
            if (array[g] % 2 == 0){
                evenElements += array[g] + " ";
            }
            g += 1;
        }

        String reverseList = "";
        int h = 19;
        while (h >= 0){
            reverseList += array[h] + " ";
            h -= 1;
        }

        String lastElement = "";
        lastElement += array[19];

        String firstElement = "";
        firstElement += array[0];


        System.out.println("The whole array is: " + theArray);
        System.out.println("Elements at even indicies: " + evenIndicies);
        System.out.println("Even elements: " + evenElements);
        System.out.println("Array in reverse order: " + reverseList);
        System.out.println("First element in list: " + firstElement);
        System.out.println("Last element in list: " + lastElement);

    }

}
