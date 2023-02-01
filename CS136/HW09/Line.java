/*
Title:             Line.java
Desc:              A line containing two points
Files:             Line.java; Shape.java; Triangle.java; TriApp.java
Semester:          Fall 2019
Author name:       Richard McCormick
Author email:      RLM443
Class section:     03
*/

import java.awt.Point;

public class Line {
  //Initializing class variables
  public Point pointOne, pointTwo;

  //No-arg constructor that initializes to zero
  public Line(){
    pointOne = new Point(0, 0);
    pointTwo = new Point(0, 0);
  }

  //Constructor with two args; one for each point
  public Line(Point point_one, Point point_two){
    pointOne = point_one;
    pointTwo = point_two;
  }

  //Copy constructor
  public Line(Line line){
    pointOne = line.pointOne;
    pointTwo = line.pointTwo;
  }

  //Gets the distance between the two points
  public double get_length(){
    double distance = 0;

    double xOne = pointOne.getX();
    double xTwo = pointTwo.getX();
    double yOne = pointOne.getY();
    double yTwo = pointTwo.getY();

    distance = Math.sqrt(Math.abs((xTwo - xOne) - (yTwo - yOne)));
    return distance;
  }
}
