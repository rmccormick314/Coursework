import java.util.Scanner;

/*
Title:             TimeCalculator
Desc:              Take a number of seconds and display the total broken down time
Files:             TimeCalculator.java
Semester:          Fall 2019
Author 1:          Richard McCormick
Author 1 Email:    rlm443@nau.edu
Author 2:          Jacob Heslop
Author 2 Email:    jmh727@nau.edu
Lab Section:       3
*/

public class TimeCalculator{

  public static void main(String[] args) {
    final int MINUTES = 60;
    final int HOURS = 3600;
    final int DAYS = 86400;
    Scanner scanner = new Scanner(System.in);
    System.out.print("Enter a number of seconds: ");
    int startingSeconds = scanner.nextInt();
    int seconds = startingSeconds;
    int day, hour, minutes, second;

    if (seconds >= DAYS){
      day = seconds / DAYS;
      hour = (seconds - (day * DAYS)) / HOURS;
      minutes = (seconds - (day * DAYS) - (hour * HOURS)) / MINUTES;
      second = (seconds - (day * DAYS) - (hour * HOURS) - (minutes * MINUTES));
      System.out.print(startingSeconds + " seconds  is equal to " + day +
      " day(s), " + hour + " hour(s), " + minutes + " minute(s), " + second
      + " second(s).");}

    else if (seconds > HOURS){
      hour = seconds / HOURS;
      minutes = (seconds - (hour * HOURS)) / MINUTES;
      second = (seconds - (hour * HOURS) - (minutes * MINUTES));
      System.out.print(startingSeconds + " seconds  is equal to " + hour +
      " hour(s), " + minutes + " minute(s), " + second + " second(s).");}

    else if (seconds > MINUTES){
      minutes = seconds / MINUTES;
      second = (seconds - (minutes * MINUTES));
      System.out.print(startingSeconds + " seconds  is equal to " + minutes
      + " minute(s), " + second + " second(s).");}

    else{
      System.out.print(startingSeconds + " seconds is equal to "
      + startingSeconds + " second(s).");}
  }
}
