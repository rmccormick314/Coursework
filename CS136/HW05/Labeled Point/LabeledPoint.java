/*
Title:            LabeledPoint
Desc:              Creates a better subclass of the default java Point Class
Files:             LabeledPoint.java
                    LabeledPointTester.java
Semester:          Fall 2019
Author name:         Richard McCormick
Author email:       rlm443@nau.edu
Class section:       01
*/

import java.awt.Point;

public class LabeledPoint extends Point{
  final String name;
  LabeledPoint(int x, int y, String label){
    super(x,y);
    name = label;
  }

  public String toString(){
    String theThing = "";
    theThing += "LabeledPoint [";
    theThing += "X=" + super.getX() + ",";
    theThing += "Y=" + super.getY() + ",";
    theThing += "Label=" + name + "]";

    return theThing;

  }
}
