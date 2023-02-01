/*
Title:             AnyCorrectChoiceQuestion
Desc:              Child class of ChoiceQuestion class, which is a child class
                   of the Question class. Handles multiple choice questions
                   where there may be multiple correct responses.
Files:             AnyCorrectChoiceQuestion.java
Semester:          Fall 2019
Author 1:          Taylor Yee
Author 1 Email:    tey24@nau.edu
Author 2:          Richard McCormick
Author 2 Email:    rlm443@nau.edu
Lab Section:       3
*/

/*
 * Allows multiple correct questions. Respondent should provide any one of the
 * correct choices. Answer string should contain all correct choices, separated
 * by spaces. Provide instructions to the question text.
 */
public class AnyCorrectChoiceQuestion extends ChoiceQuestion{
    String correctAnswers;
    int choiceSize;

    AnyCorrectChoiceQuestion(){
        correctAnswers = "";
        choiceSize = 0;
    }

    /**
     * Should add index of correct answers to the correctAnswers string,
     * which is separated from the next string by a space. This overrides
     * the parent addChoice method by allowing multiple correct answers.
     * @param choice  The choice to be checked for correctness.
     * @param correct The conditional (true or false) of whether this is a
     *                valid answer or not.
     */
    public void addChoice(String choice, boolean correct){
        /**
         * Invokes the addChoice method from the ChoiceQuestion class.
         * choiceSize variable is made to index so that we can keep track
         * of what number choice is being passed in.
         */
        super.addChoice(choice, correct);
        choiceSize += 1;
        /**
         * If it's a corret answer, concatenate (add) it to the string of
         * correct answers.
         */
        if (correct){
            String number = Integer.toString(choiceSize);
            correctAnswers += number + " ";
        }
    }

    /**
     * Checks to see whether the given response (a numerical choice) is in the
     * string of correct answers. that was given values in the addChoice method.
     * Should override the checkAnswer method that is inherited
     * from the Question class.
     * @param  response The user's answer to be checked for correctness.
     * @return Whether the response is correct or not.
     */
    public boolean checkAnswer(String response){
        if (correctAnswers.contains(response)){
            return true;
        }
        return false;
    }

    /**
     * Calls the display method from the choiceQuestion class, then prints
     * an extra line of instructions for the user so that they know that there
     * may be multiple correct answers.
     */
    public void display(){
        super.display();
        System.out.println("Note, there may be several correct answers.");
    }
}
