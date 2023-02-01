/*
Title:            BetterRectangleTester
Desc:              Tests the betterRectangle class
Files:             BetterRectangle.java
                    BetterRectangleTester.java
Semester:          Fall 2019
Author name:         Richard McCormick
Author email:       rlm443@nau.edu
Class section:       01
*/

import java.awt.Rectangle;
import java.awt.Point;
import java.util.Random;

public class BetterRectangleTester{
  public static void main(String[]args){
    BetterRectangle testingObjectOne = new BetterRectangle(1, 1, 5, 5);
    BetterRectangle testingObjectTwo = new BetterRectangle(12, 15, 220, 230);
    BetterRectangle testingObjectThree = new BetterRectangle(0, 0, 80, 10);

    //A randomized rectangle to ensure tests are valid
    Random r = new Random();
    int xtest = r.nextInt(100);
    int ytest = r.nextInt(100);
    int cordxtest = r.nextInt(100);
    int cordytest = r.nextInt(100);
    BetterRectangle testingObjectFour = new BetterRectangle(xtest, ytest,
    cordxtest, cordytest);

    //Rectangle One test, using provided starting cords and dimensions
    System.out.println("");
    System.out.println("Rectangle #1:");
    System.out.println("  Upper Left-Hand Cordinates: (" +
    testingObjectOne.getLocation().getX() + ", " +
    testingObjectOne.getLocation().getY() + ")");
    System.out.println("  Width: " + testingObjectOne.width);
    System.out.println("  Height: " + testingObjectOne.height);
    System.out.println("  Area: " + testingObjectOne.getArea());
    System.out.println("  Perimeter: " + testingObjectOne.getPerimeter());

    //Testing Rectangle #2
    System.out.println("");
    System.out.println("Rectangle #2:");
    System.out.println("  Upper Left-Hand Cordinates: (" +
    testingObjectTwo.getLocation().getX() + ", " +
    testingObjectTwo.getLocation().getY() + ")");
    System.out.println("  Width: " + testingObjectTwo.width);
    System.out.println("  Height: " + testingObjectTwo.height);
    System.out.println("  Area: " + testingObjectTwo.getArea());
    System.out.println("  Perimeter: " + testingObjectTwo.getPerimeter());

    //Testing Rectangle #3
    System.out.println("");
    System.out.println("Rectangle #3:");
    System.out.println("  Upper Left-Hand Cordinates: (" +
    testingObjectThree.getLocation().getX() + ", " +
    testingObjectThree.getLocation().getY() + ")");
    System.out.println("  Width: " + testingObjectThree.width);
    System.out.println("  Height: " + testingObjectThree.height);
    System.out.println("  Area: " + testingObjectThree.getArea());
    System.out.println("  Perimeter: " + testingObjectThree.getPerimeter());

    //Testing Rectangle #4. All inputs randomized
    System.out.println("");
    System.out.println("Rectangle #4 (Randomized):");
    System.out.println("  Upper Left-Hand Cordinates: (" +
    testingObjectFour.getLocation().getX() + ", " +
    testingObjectFour.getLocation().getY() + ")");
    System.out.println("  Width: " + testingObjectFour.width);
    System.out.println("  Height: " + testingObjectFour.height);
    System.out.println("  Area: " + testingObjectFour.getArea());
    System.out.println("  Perimeter: " + testingObjectFour.getPerimeter());

  }
}
