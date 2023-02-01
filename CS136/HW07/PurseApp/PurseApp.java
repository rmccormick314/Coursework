/*
Title:             PurseApp.java
Desc:              Creates three purse objects via different constructors
Files:             Purse.java; PurseApp.java
Semester:          Fall 2019
Author name:       Richard McCormick
Author email:      RLM443
Class section:     03
*/


public class PurseApp {

  //Finds the largest purse in an array of purses
  static int findLargest(Purse[] purseArray){
    int largest = -1;
    for (int i = 1; i < purseArray.length; i++){
      if (purseArray[i - 1].get_dollars() > purseArray[i].get_dollars()){
        if (purseArray[i-1].get_dimes() > purseArray[i].get_dimes()){
          largest = i - 1;
        }
      }
    }
    return largest;
  }

  public static void main(String args[]){
    //Creates an array that can hold three purses
    Purse purseArray[] = new Purse[3];

    //Creates a new purse and sets values with setters
    Purse purseOne = new Purse();
    purseOne.set_dollars(4);
    purseOne.set_dimes(5);
    purseOne.set_cents(2);

    //Creates a new purse with an initialized parameter
    Purse purseTwo = new Purse(1, 0, 1, 3, 2);

    //Creates a copy of purse two and adds 1 dollar and 3 quarters
    Purse purseThree = new Purse(purseTwo);
    purseThree.set_dollars(1);
    purseThree.set_quarters(3);

    //Puts the purses in the purse array
    purseArray[0] = purseOne;
    purseArray[1] = purseTwo;
    purseArray[2] = purseThree;

    //Prints the contents of each purse in array
    for (Purse purse : purseArray){
      System.out.println(purse.toString());
    }

    //Prints largest purse index in array
    System.out.println("The index of largest purse is: " + findLargest(purseArray));

  }
}
