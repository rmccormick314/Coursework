/*
Title:            LabeledPointTester
Desc:              Tests the labeledpoint class
Files:             LabeledPoint.java
                    LabeledPointTester.java
Semester:          Fall 2019
Author name:         Richard McCormick
Author email:       rlm443@nau.edu
Class section:       01
*/

import java.awt.Point;

public class LabeledPointTester{
  public static void main(String[] args){
    LabeledPoint testingObjectOne = new LabeledPoint(0, 0, "Origin");
    LabeledPoint testingObjectTwo = new LabeledPoint(10, 15, "Point 1");
    LabeledPoint testingObjectThree = new LabeledPoint(12, 22, "Point 2");

    System.out.println(testingObjectOne.toString());
    System.out.println(testingObjectTwo.toString());
    System.out.println(testingObjectThree.toString());
  }
}
