/*
Title:             FillInQuestion
Desc:              Child class of Question class, to handle "fill in the blank"
                   types of quiz questions.
Files:             FillInQuestion.java
Semester:          Fall 2019
Author 1:          Taylor Yee
Author 1 Email:    tey24@nau.edu
Author 2:          Richard McCormick
Author 2 Email:    rlm443@nau.edu
Lab Section:       3
*/

/**
 * FillInQuestion class whose parent is the Question class.
 */
public class FillInQuestion extends Question{
    /**
     * Private variables that will be needed later.
     */
    private String text;
    private String answer;
    private String[] textAndAnswer;

    /**
     * Constructor method to initialize empty strings.
     */
    public FillInQuestion(){
        text = "";
        answer = "";
    }

    /**
     * Sets the question and answer texts accordingly.
     * @param questionText The full question and answer text provided.
     */
    public void setText(String questionText){
        /**
         * Splits the text into question and answer by using the '_' delimiter
         * provided in the problem statement. Stored in an array, with question
         * text first, then answer.
         */
        textAndAnswer = questionText.split("_");
        text = textAndAnswer[0] + "___";
        answer = textAndAnswer[1];
    }

    /**
     * Method that overrides the one found in teh Question class, to check
     * the user's response for correctness. Identical in code, but slightly
     * different in inner workings due to the need to split text into question
     * and answer.
     * @param  response The user's answer.
     * @return          Whether the user's answer is identical to the
     *                  correct answer.
     */
    public boolean checkAnswer(String response){
        return response.equals(answer);
    }

    /**
     * Method that overrides the one found in the Question class, to display
     * the question text separate from the answer.
     */
    public void display(){
        System.out.println(text);
    }
}
