/*
Title:            VdivAmplifier
Desc:              Creates a subclass of Amplifier for Voltage Divider
Files:             Amplifier.java; InvertingAmplifier.java;
                  NonInvertingAmplifier.java; VdivAmplifier.java
Semester:          Fall 2019
Author name:          Richard McCormick
Author email:       rlm443
Class section:       01
*/

public class VdivAmplifier extends Amplifier{
  //Initializes variables
  double r1, r2;

  //Constructor that sets instance variables
  public VdivAmplifier(double R1, double R2){
    r1 = R1;
    r2 = R2;
  }

  //Calculates gain as a function of R1 and R2
  public double getGain(){
    double gain;
    gain = r2 / (r2 + r1);
    return gain;
  }

  //Sets description: Amplifier Type and Resistor values
  public String getDescription(){
    String desc = "";
    desc += "Voltage Divider and Voltage Follower: ";
    desc += "R1 = " + r1 + ", R2 = " + r2;
    return desc;
  }

}
