/*
Title:             CompareTimes.java
Desc:              Compares the time is takes to make a list, linked list,
                   and array list of one million items.
Files:             CompareTimes.java
Semester:          Fall 2019
Author name:       Richard McCormick
Author email:      RLM443@nau.edu
Class section:     03
*/

//Imports arrayList and linkedList
import java.util.ArrayList;
import java.util.LinkedList;

//Declares class
class CompareTimes {
  //Finds the time it takes to populate an array
  public static long find_array(){
    Integer[] thing = new Integer[1000000];
    long start_time = System.nanoTime();
    //Populating
    for (int i = 0; i < 1000000; i++){
      thing[i] = i;
    }
    long end_time = System.nanoTime();
    long time_total = end_time - start_time;
    return time_total;
  }

  //Finds the time it takes to populate an arrayList
  public static long find_arraylist(){
    ArrayList<Integer> memes = new ArrayList<Integer>();
    long start_time = System.nanoTime();
    //Populating
    for (int i =0; i < 1000000; i ++){
      memes.add(i);
    }
    long end_time = System.nanoTime();
    long final_time = end_time - start_time;
    return final_time;
  }

  //Finds the time it takes to populate a linked list
  public static long find_linkedlist(){
    LinkedList<Integer> memes = new LinkedList<Integer>();
    long start_time = System.nanoTime();
    //Populating
    for (int i = 0; i < 1000000; i++){
      memes.add(i);
    }
    long end_time = System.nanoTime();
    long final_time = end_time - start_time;
    return final_time;
  }

  //Tests the 3 main methods by using the test variable 'test'
  public static void main(String args[]){
    long test = 0;
    //Find and print time for an array of size 1,000,000
    test = find_array();
    System.out.println("Array: " + test + " nanoseconds.");

    //Find and print time for an arrayList of size 1,000,000
    test = find_arraylist();
    System.out.println("ArrayList: " + test + " nanoseconds.");

    //Find and print time for a linkedList of size 1,000,000
    test = find_linkedlist();
    System.out.println("LinkedList: " + test + " nanoseconds.");
  }
}
