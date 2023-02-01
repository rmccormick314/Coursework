/*
Title:              Purse.java
Desc:               A purse class that stores an amount of money
Files:              Purse.java; PurseApp.java
Semester:           Fall 2019
Author name:        Richard McCormick
Author email:       RLM443
Class section:      03
*/


public class Purse {
  //Initializes fields
  private int dollars, quarters, dimes, nickels, cents;

    //No-arg constructor that sets all values to zero
    Purse(){
      set_dollars(0);
      set_quarters(0);
      set_dimes(0);
      set_nickles(0);
      set_cents(0);
    }

    //Input constructor that uses setters to initialize to user values
    Purse(int a, int b, int c, int d, int e){
      set_dollars(a);
      set_quarters(b);
      set_dimes(c);
      set_nickles(d);
      set_cents(e);
    }




    //Copy constructor that creates a new purse with same contents
    Purse(Purse x){
      this.dollars = x.dollars;
      this.quarters = x.quarters;
      this.nickels = x.nickels;
      this.dimes = x.dimes;
      this.cents = x.cents;
    }

    //Overrides toString method and returns amount of change
    public String toString(){
      String stringReturn = "";
      stringReturn += "Dollars: " + dollars;
      stringReturn += " Quarters: " + quarters;
      stringReturn += " Dimes: " + dimes;
      stringReturn += " Nickels: " + nickels;
      stringReturn += " Cents: " + cents;

      return stringReturn;
    }

    //Compares the contents of this purse to another using dollars and dimes
    public int compareTo(Purse otherPurse){
      int answer = -2;
      if (get_dollars() > otherPurse.get_dollars()){
        answer = 1;
      }
      else if (get_dollars() == otherPurse.get_dollars()){
        if (get_dimes() > otherPurse.get_dimes()){
          answer = 1;
        }
        else if (get_dimes() == otherPurse.get_dimes()){
          answer = 0;
        }
        else if (get_dimes() < otherPurse.get_dimes()){
          answer = -1;
        }
      }
      else if (get_dollars() < otherPurse.get_dollars()){
        answer = -1;
      }
      return answer;
    }

    //Returns the number of dollars in this purse
    public int get_dollars(){
      return dollars;
    }
    //Adds dollars to the purse
    public void set_dollars(int amount_Dollars){
      dollars += amount_Dollars;
    }

    //Gets the number of quarters in this purse
    public int get_quarters(){
      return quarters;
    }
    //Adds quarters to this purse
    public void set_quarters(int amount_Quarters){
      quarters += amount_Quarters;
    }

    //Returns number of dimes in this purse
    public int get_dimes(){
      return dimes;
    }
    //Adds dimes to this purse
    public void set_dimes(int amount_Dimes){
      dimes += amount_Dimes;
    }

    //Returns the number of nickles in this purse
    public int get_nickles(){
      return nickels;
    }
    //Adds nickles to this purse
    public void set_nickles(int amount_Nickels){
      nickels += amount_Nickels;
    }

    //Returns number of cents in this purse
    public int get_cents(){
      return cents;
    }
    //Adds cents to this purse
    public void set_cents(int amount_Cents){
      cents += amount_Cents;
    }
  }
