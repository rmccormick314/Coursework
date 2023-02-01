import java.util.Scanner;
import java.util.ArrayList;

public class QuestionsApp {

    public static void main(String[] args) {
        ArrayList<Question> Questions = new ArrayList<Question>();
        int totalScore = 0;

        NumericQuestion n1 = new NumericQuestion();
        n1.setText("What is the value of PI to the nearest thousandth?");
        n1.setAnswer(3.141);
        Questions.add(n1);

        NumericQuestion n2 = new NumericQuestion();
        n2.setText("What is the value of the Euler's number to the nearest thousandth?");
        n2.setAnswer(2.718);
        Questions.add(n2);

        FillInQuestion f1 = new FillInQuestion();
        f1.setText("The inventor of Java was _James Gosling_");
        Questions.add(f1);

        FillInQuestion f2 = new FillInQuestion();
        f2.setText("The inventor of Pascal was _Niklaus Wirth_");
        Questions.add(f2);

        AnyCorrectChoiceQuestion a1 = new AnyCorrectChoiceQuestion();
        a1.setText("The inventor of Java lived in ___.");
        a1.addChoice("Australia", false); //wrong answer
        a1.addChoice("Canada", true); //correct answer
        a1.addChoice("Denmark", false); //wrong answer
        a1.addChoice("United States", true); //correct answer
        Questions.add(a1);

        AnyCorrectChoiceQuestion a2 = new AnyCorrectChoiceQuestion();
        a2.setText("The inventor of Pascal lived in ___.");
        a2.addChoice("Australia", false); //wrong answer
        a2.addChoice("Canada", true); //correct answer
        a2.addChoice("Denmark", false); //wrong answer
        a2.addChoice("United States", true); //correct answer
        a2.addChoice("Switzerland", true); //correct answer
        Questions.add(a2);

        for (Question q : Questions) {
            boolean isCorrect = presentQuestion(q);

            if (isCorrect) {
                System.out.println("Correct answer :)\n");
                if (q instanceof NumericQuestion) {
                    totalScore += 1;
                }
                if (q instanceof FillInQuestion) {
                    totalScore += 2;
                }
                if (q instanceof AnyCorrectChoiceQuestion) {
                    totalScore += 3;
                }
            } else {
                System.out.println("Wrong answer :(\n");
            }

        }

        System.out.printf("Total score is %d out of %d\nThank You!", totalScore, 12);
    }

    /**
     * Presents a question to the user and checks the response.
     *
     * @param q the question
     */
    public static boolean presentQuestion(Question q) {
        q.display();
        System.out.print("Your answer: ");
        Scanner in = new Scanner(System.in);
        String response = in.nextLine();
        return q.checkAnswer(response);
    }
}
