import java.math.BigInteger;

public class RSATester {

    public static boolean test_2() {
        RSA rsaEncoder = new RSA();
        rsaEncoder.GenerateKeys(265);

        String messageText = "Programming is fun :)"; // Secret message

        byte[] messageByteArray = messageText.getBytes(); // Convert the message to a byte array
        BigInteger messageBI = new BigInteger(messageByteArray); //Convert the byte array to a BigInteger

        BigInteger messageEncrypted = rsaEncoder.Encrypt(messageBI); // Encrypt the BigInteger number
        if (messageEncrypted == null) {
            return false;
        }
        System.out.println("The encrypted text: " + messageEncrypted);

        BigInteger messageDecrypted = rsaEncoder.Decrypt(messageEncrypted); //Decrypt BigInteger number
        if (messageDecrypted == null) {
            return false;
        }

        byte[] decryptedByteArray = messageDecrypted.toByteArray(); //Convert the decrypted number to a byte array

        String decryptedText = new String(decryptedByteArray); //Convert the byte array to a string

        System.out.println("The decrypted text: " + decryptedText);

        if (decryptedText.compareTo(messageText) != 0) {
            return false;
        }

        return true;
    }

    public static boolean test_1() {
        RSA rsaEncoder = new RSA();
        rsaEncoder.GenerateKeys(265);

        BigInteger num = new BigInteger("136"); // Create a number

        BigInteger num_encrypted = rsaEncoder.Encrypt(num); // Encrypt it
        if (num_encrypted == null) {
            return false;
        }
        System.out.println("The encrypted text: " + num_encrypted);

        BigInteger num_decrypted = rsaEncoder.Decrypt(num_encrypted); // Decrypt it
        if (num_decrypted == null) {
            return false;
        }
        System.out.println("The decrypted text: " + num_decrypted);

        if (num.compareTo(num_decrypted) != 0) {
            return false;
        }

        return true;
    }

    public static void main(String[] args) {

        if (!test_1()) {
            System.out.println("Test #1 failed!");
        } else {
            System.out.println("Test #1 passed!");
        }

        System.out.println("");

        if (!test_2()) {
            System.out.println("Test #2 failed!");
        } else {
            System.out.println("Test #2 passed!");
        }
    }

}
