/*
Title:             Triangle.java
Desc:              A triangle containing 3 lines
Files:             Line.java; Shape.java; Triangle.java; TriApp.java
Semester:          Fall 2019
Author name:       Richard McCormick
Author email:      RLM443
Class section:     03
*/

public class Triangle extends Shape {
  public Line lineOne, lineTwo, lineThree;
  //Regular constructor; takes in 3 line objects
  public Triangle(Line lineOne, Line lineTwo, Line lineThree){
    super("Triangle");
    this.lineOne = lineOne;
    this.lineTwo = lineTwo;
    this.lineThree = lineThree;
  }

  //No-arg Constructor
  public Triangle(){
    super("Triangle");
  }

  //Copy Constructor
  public Triangle (Triangle triangle){
    super("Triangle");
  }

  //Abstract implementation from class Shape
  public double getArea(){
    double area = 0;

    double distanceOne = lineOne.get_length();
    double distanceTwo = lineTwo.get_length();
    double distanceThree = lineThree.get_length();

    area = (distanceOne + distanceTwo + distanceThree)/2;



    return area;
  }

  //Abstract implementation from class Shape
  public double getPerimeter(){
    double perimeter = 0;

    double distanceOne = lineOne.get_length();
    double distanceTwo = lineTwo.get_length();
    double distanceThree = lineThree.get_length();

    perimeter = distanceOne + distanceTwo + distanceThree;

    return perimeter;
  }
}
