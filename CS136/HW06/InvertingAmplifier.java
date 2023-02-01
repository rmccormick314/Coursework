/*
Title:             InvertingAmplifier
Desc:              Creates a subclass of Amplifier for Inverting Amp
Files:             Amplifier.java; InvertingAmplifier.java;
                  NonInvertingAmplifier.java; VdivAmplifier.java
Semester:          Fall 2019
Author name:          Richard McCormick
Author email:       rlm443
Class section:       01
*/

public class InvertingAmplifier extends Amplifier{
  //initializes two resistors and the gain
  double r1;
  double r2;
  double gain;

  //constructs the amplifier and sets resistor values
  public InvertingAmplifier(double R1, double R2){
    r1 = R1;
    r2 = R2;
  }

  //Calculates gain as a function of r1 and r2
  public double getGain(){
    double gain = (-1)*(r2/r1);
    return gain;
  }

  //Sets the description: Amplifier Type and Resistors
  public String getDescription(){
    String desc = "";
    desc += "Inverting Amplifier: ";
    desc += "R1 = " + r1 + " R2 = " + r2;
    return desc;
  }
}
