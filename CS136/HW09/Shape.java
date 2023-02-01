/*
Title:             Shape.java
Desc:              A shape class with 2 abstract methods
Files:             Line.java; Shape.java; Triangle.java; TriApp.java
Semester:          Fall 2019
Author name:       Richard McCormick
Author email:      RLM443
Class section:     03
*/

public abstract class Shape {

    private String name;

    public Shape(String aName) {
        name = aName;
    }

    public String getName() {
        return name;
    }

    public void setName(String aName) {
        name = aName;
    }

    public abstract double getArea();

    public abstract double getPerimeter();

    public double getSemiPerimeter() {
        return getPerimeter() / 2;
    }
}
