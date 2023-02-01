/*
Title:             NumericQuestion
Desc:              Child class of Question class, to handle numerical questions
                   as opposed to string-based questions.
Files:             NumericQuestion.java
Semester:          Fall 2019
Author 1:          Taylor Yee
Author 1 Email:    tey24@nau.edu
Author 2:          Richard McCormick
Author 2 Email:    rlm443@nau.edu
Lab Section:       3
*/

/**
 * NumericQuestion class whose parent is the Question class.
 */
public class NumericQuestion extends Question{
    /**
     * Variable to hold answer to be set. Needs to be declared here since
     * variables in parent class are private and no getter methods are given.
     */
    private double answer;

    /**
     * Constructor to initialize answer to zero. Could also be done in
     * declaration of the variable.
     */
    public NumericQuestion(){
        answer = 0;
    }

    /**
     * Sets answer to the correct response given as a double.
     * @param correctResponse The correct answer provided.
     */
    public void setAnswer(double correctResponse){
        answer = correctResponse;
    }

    /**
     * Checks to see whether the given response is within |0.01| of the correct
     * answer that was provided to the setAnswer method.
     * @param  response The user's answer.
     * @return          Whether the answer is within the given range of
     *                  acceptable values.
     */
    public boolean checkAnswer(String response){
        /**
         * parseDouble method to cast the response String to type double.
         * Math.abs to take the absolute value. Checks for answer in range.
         * Returns true if within range, false otherwise.
         */
        if (Math.abs(Double.parseDouble(response) - answer) <= 0.01){
            return true;
        }
        return false;
    }
}
