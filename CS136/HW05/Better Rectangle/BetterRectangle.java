/*
Title:            BetterRectangle
Desc:              Creates a better subclass of the default java Rectangle Class
Files:             BetterRectangle.java
                    BetterRectangleTester.java
Semester:          Fall 2019
Author name:         Richard McCormick
Author email:       rlm443@nau.edu
Class section:       01
*/

import java.awt.Rectangle;

public class BetterRectangle extends Rectangle{
  //3 constructor classes to allow for different inputs
  public BetterRectangle(){
    super();
  }

  public BetterRectangle(int x, int y){
    super();
    super.setLocation(x, y);
  }

  public BetterRectangle(int x, int y, int w, int h){
    //This is the most used in the testing class
    super();
    super.setLocation(x, y);
    super.setSize(w, h);
  }

  //Calculates the perimeter as a function of 2X + 2Y
  public int getPerimeter(){
    int perimeter;
    int width  = super.width;
    int height = super.height;

    perimeter = (width*2) + (height*2);
    return perimeter;
  }

  //Calculates area as X * Y
  public int getArea(){
    int area;
    int width = super.width;
    int height = super.height;

    area = (width * height);
    return area;
  }
}
