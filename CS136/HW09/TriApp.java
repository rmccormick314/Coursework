/*
Title:             TriApp.java
Desc:              Main for testing Triangle class
Files:             Line.java; Shape.java; Triangle.java; TriApp.java
Semester:          Fall 2019
Author name:       Richard McCormick
Author email:      RLM443
Class section:     03
*/

import java.awt.Point;

public class TriApp {
  public static void main(String args[]){
    //Points for triangle one
    Point pointOne = new Point(-7, 5);
    Point pointTwo = new Point(-4, 4);
    Point pointThree = new Point(-7, 0);

    //Lines for triangle one
    Line lineOne = new Line(pointOne, pointTwo);
    Line lineTwo = new Line(pointTwo, pointThree);
    Line lineThree = new Line(pointThree, pointOne);

    //(-7, 5), (-4, 4), (-7, 0)
    //Builds triangle one and prints area
    Triangle triangleOne = new Triangle(lineOne, lineTwo, lineThree);
    System.out.println("Triangle one size: " + triangleOne.getArea());

    //(0, 3), (6, -3), (-2, -5)
    //Points for triangle two
    Point pointFour = new Point(0, 3);
    Point pointFive = new Point(-4, 4);
    Point pointSix = new Point(-2, -5);

    //Lines for triangle two
    Line lineFour = new Line(pointFour, pointFive);
    Line lineFive = new Line(pointFive, pointSix);
    Line lineSix = new Line(pointSix, pointOne);

    //Constructs triangle two and prints area
    Triangle triangleTwo = new Triangle(lineFour, lineFive, lineSix);
    System.out.println("Triangle two size: " + triangleTwo.getArea());

    //Compares two triangles and returns the larger.
    if (triangleTwo.getArea() > triangleOne.getArea()){
      System.out.println("Triange two is bigger.");
    }

    if (triangleOne.getArea() > triangleTwo.getArea()){
      System.out.println("Triangle one is bigger.");
    }

    if (triangleOne.getArea() == triangleTwo.getArea()){
      System.out.println("The two triangles are equal.");
    }
  }
}
