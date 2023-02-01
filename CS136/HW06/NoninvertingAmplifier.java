/*
Title:             NoninvertingAmplifier
Desc:              Creates a subclass of Amplifier for Noninverting Amp
Files:             Amplifier.java; InvertingAmplifier.java;
                  NonInvertingAmplifier.java; VdivAmplifier.java
Semester:          Fall 2019
Author name:          Richard McCormick
Author email:       rlm443
Class section:       01
*/

public class NoninvertingAmplifier extends Amplifier {
  double r1, r2;

  //Constructor class initializes the resistors
  public NoninvertingAmplifier(double R1, double R2){
    r1 = R1;
    r2 = R2;
  }

  //Calculates gain as a function of resistors
  public double getGain(){
    double gain;
    gain = 1 + (r2/r1);
    return gain;
  }

  //Sets description as Amplifier Type and Resistors
  public String getDescription(){
    String desc = "";
    desc += "Noninverting Amplifier: ";
    desc += "R1 = " + r1 + ", R2 = " + r2;
    return desc;
  }
}
