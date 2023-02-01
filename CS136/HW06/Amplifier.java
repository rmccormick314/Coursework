/*
Title:             Amplifier
Desc:              Creates a superclass called Amp with empty variables
Files:             Amplifier.java; InvertingAmplifier.java;
                  NonInvertingAmplifier.java; VdivAmplifier.java
Semester:          Fall 2019
Author name:          Richard McCormick
Author email:       rlm443
Class section:       01
*/

public class Amplifier {
  //An empty constructor method
  public Amplifier(){};

  //Sets the gain as -1 (default)
  public double getGain(){
    double gain = -1;

    return gain;
  }

  //Sets default disc
  public String getDescription(){
    String description = "An empty amplifier class.";

    return description;
  }
}
