/*
Title:             Common Array Algorithms
Desc:              Implements 7 different array methods
Files:             commonarrayalgorithmsapp package
Semester:          Fall 2019
Author name:         Richard McCormick
Author email:       RLM443@nau.edu
Class section:       01
*/

package commonarrayalgorithmsapp;
import java.util.Arrays;

//This class tests the implementation of 7 common array algorithms
public class CommonArrayAlgorithmsTester {

    public static void main(String[] args) {

        int[] testArray1 = {90, 0, -12, 25, 10412, 445, -32, 1};
        int[] testArray2 = {12};

        CommonArrayAlgorithms testingObject = new CommonArrayAlgorithms();

        //Testing arrayToString
        System.out.println("Testing arrayToString");
        String arrayString;
        arrayString = testingObject.arrayToString(testArray1);
        System.out.println(" arrayToString returned: " + arrayString); //Should display 90|0|-12|25|10412|445|-32|1

        arrayString = testingObject.arrayToString(testArray2);
        System.out.println(" arrayToString returned: " + arrayString); //Should display 12
        System.out.println("");

        //Testing arraySum
        System.out.println("Testing arraySum");
        int arraySumValue;
        arraySumValue = testingObject.arraySum(testArray1);
        System.out.println(" arraySum returned: " + arraySumValue); //Should display 10929

        arraySumValue = testingObject.arraySum(testArray2);
        System.out.println(" arraySum returned: " + arraySumValue); //Should display 12
        System.out.println("");

        //Testing arrayAvg
        System.out.println("Testing arrayAvg");
        double arrayAvgValue;
        arrayAvgValue = testingObject.arrayAvg(testArray1);
        System.out.println(" arrayAvg returned: " + arrayAvgValue); //Should display 1366.125

        arrayAvgValue = testingObject.arrayAvg(testArray2);
        System.out.println(" arrayAvg returned: " + arrayAvgValue); //Should display 12.0
        System.out.println("");

        //Testing arrayMax
        System.out.println("Testing arrayMax");
        int arrayMaxValue;
        arrayMaxValue = testingObject.arrayMax(testArray1);
        System.out.println(" arrayMax returned: " + arrayMaxValue); //Should display 10412

        arrayMaxValue = testingObject.arrayMax(testArray2);
        System.out.println(" arrayMax returned: " + arrayMaxValue); //Should display 12
        System.out.println("");

        //Testing arraySearch
        System.out.println("Testing arraySearch");
        int arraySearchValue;
        arraySearchValue = testingObject.arraySearch(testArray1, 445);
        System.out.println(" arraySearch returned: " + arraySearchValue); //Should display 5

        arraySearchValue = testingObject.arraySearch(testArray2, 445);
        System.out.println(" arraySearch returned: " + arraySearchValue); //Should display -1
        System.out.println("");

        //Testing arraySwap
        System.out.println("Testing arraySwap");
        boolean isSuccess;

        System.out.println(" testArray1 before the first swap: " + testingObject.arrayToString(testArray1)); //Should display 90|0|-12|25|10412|445|-32|1
        isSuccess = testingObject.arraySwap(testArray1, 2, 3);
        System.out.println(" arraySwap returned:" + isSuccess); //Should display true
        System.out.println(" testArray1 after the first swap: " + testingObject.arrayToString(testArray1)); //Should display 90|0|25|-12|10412|445|-32|1

        //In this test, the swap methods will return false (and the array will not be changed) since the value of the first index is larger than the array size
        isSuccess = testingObject.arraySwap(testArray1, 15, 3);
        System.out.println(" arraySwap returned:" + isSuccess); //Should display false
        System.out.println(" testArray1 after the swap: " + testingObject.arrayToString(testArray1)); //Should display 90|0|25|-12|10412|445|-32|1

        isSuccess = testingObject.arraySwap(testArray1, 5, 1);
        System.out.println(" arraySwap returned:" + isSuccess); //Should display true
        System.out.println(" testArray1 after the swap: " + testingObject.arrayToString(testArray1)); //Should display 90|445|25|-12|10412|0|-32|1
        System.out.println("");

        //Testing arrayGrowDouble
        System.out.println("Testing arrayGrowDouble");
        int[] largerArray;
        System.out.println(" testArray1 size: " + testArray1.length); //Should display 8
        System.out.println(" testArray1 contents: " + testingObject.arrayToString(testArray1)); //Should display 90|445|25|-12|10412|0|-32|1

        largerArray = testingObject.arrayGrowDouble(testArray1);
        System.out.println(" largerArray size: " + largerArray.length); //Should display 16
        System.out.println(" largerArray contents: " + testingObject.arrayToString(largerArray)); //Should display 90|445|25|-12|10412|0|-32|1|0|0|0|0|0|0|0|0

        int[] evenLargerArray;
        evenLargerArray = testingObject.arrayGrowDouble(largerArray);
        System.out.println(" evenLargerArray size: " + evenLargerArray.length); //Should display 32
        System.out.println(" evenLargerArray contents: " + testingObject.arrayToString(evenLargerArray)); //Should display 90|445|25|-12|10412|0|-32|1|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0|0
    }

    public static class CommonArrayAlgorithms {
      //Array to String
      String arrayToString(int[] inputArray){
        String returnString = "";
        for (int input : inputArray){
          if (inputArray.length == 1){
            returnString += input;
          }
          else {
            returnString += input + "|";
          }
        }
        return returnString;
      }

      //Array Sumation
      int arraySum(int[] inputArray){
        int returnSum = 0;
        for (int i = 0; i < inputArray.length; i++){
          returnSum += inputArray[i];
        }
        return returnSum;
      }

      //Array Average
      double arrayAvg(int[] inputArray){
        double returnSum = 0;
        int counter = 0;
        for (int i = 0; i < inputArray.length; i++){
          returnSum += inputArray[i];
          counter += 1;
        }
        returnSum = returnSum/counter;
        return returnSum;
      }

      //Array Max
      int arrayMax(int[] inputArray){
        int returnMax = 0;
        for (int i = 0; i < inputArray.length; i++){
          if (inputArray[i] > returnMax){
            returnMax = inputArray[i];
          }
        }
        return returnMax;
      }

      //Array Search
      int arraySearch(int[] inputArray, int term){
        int result = (-1);
        for (int i = 0; i < inputArray.length; i++){
          if (inputArray[i] == term){
            result = i;
          }
        }
        return result;
      }

      //Array swap
      boolean arraySwap(int[] inputArray, int first, int second){
        boolean status = false;
        int firstPoint = -1;
        int secondPoint = -1;
        for (int i = 0; i < inputArray.length; i++){
          if (first < inputArray.length && second < inputArray.length){
            if (first != 0 && second != 0){
              status = true;
            }
          }
        }
        for (int i = 0; i < inputArray.length; i++){
          if (inputArray[i] == first){
            inputArray[i] = second;
          }
          else if (inputArray[i] == second){
            inputArray[i] = first;
          }
        }
        return status;
      }

      //Grow double the array
      int[] arrayGrowDouble(int[] inputArray){
        int[] outputArray = Arrays.copyOf(inputArray, inputArray.length*2);
        return outputArray;
      }

    }


}
