/*
Title:             StallsApp
Desc:              Finds the middle unoccupied stall in a bathroom
Files:             StallsApp.java
Semester:          Fall 2019
Author name:       Richard McCormick
Author email:      RLM443@nau.edu
Class section:     03
*/

class StallsApp {
  //Prints the stalls in given array, X is occupied, - is open
  static String print_stalls(boolean[] bathroom){
    String answer = "";
    for (boolean stall : bathroom){
      if (stall == true){
        answer += "X";
      }
      if (stall == false){
        answer += "-";
      }
    }
    return answer;
  }

  //Finds the middle unoccupied stall in array
  static int find_mid(boolean[] bathroom){
    //Fields for finding middle unoccupied stall
    int answer = 0;
    int cMin = 0;
    int cMax = 0;
    int lMin = 0;
    int lMax = 0;
    boolean inRun = false;

    //Checks each stall in bathroom
    for (int i = 0; i < bathroom.length; i++){
      //If stall is open, start counting unoccupied stalls
      if (bathroom[i] == false){
        //If the previous stall was closed, start counting here
        if(inRun == false){
          cMin = i;
        }
        cMax = i;
        inRun = true;
        //If current is bigger than largest, update largest
        if ((lMax - lMin)<=(cMax - cMin)){
          lMax = cMax;
          lMin = cMin;
        }
      }

      //If stall is occupied, update largest unoccupied array
      if (bathroom[i] == true){
        //If current is less than largest, update largest
        if ((lMax - lMin)<=(cMax - cMin)){
          lMax = cMax;
          lMin = cMin;
        }
        //Sets previous stall as closed
        inRun = false;
      }
    }
    //Finds the middle unoccupied stall and returns answer
    answer = Math.round((lMax - lMin)/2) + lMin;
    return answer;
  }

  //Main method
  public static void main(String args[]){
    //Creates an array called bathroom with 10 stalls
    boolean[] bathroom = new boolean[10];
    boolean oneCheck = false;

    //Runs the find_mid and print_stalls for each stall
    for (boolean stall : bathroom){
      int middle = find_mid(bathroom);
      //Simplistic rounding for first stall in array
      if (oneCheck == false){
        middle += 1;
        oneCheck = true;
      }
      bathroom[middle] = true;
      System.out.println(print_stalls(bathroom));

    }
  }
}
