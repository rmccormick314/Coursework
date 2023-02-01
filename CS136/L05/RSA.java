/*
Title:             RSA
Desc:              This program does RSA encryption and decryption.
Files:             RSA.java, RSATester.java
Semester:          Fall 2019
Author 1:          Lucina de la Rosa
Author 1 Email:    dld297@nau.edu
Author 2:          Richard McCormick
Author 2 Email:    rlm443@nau.edu
Lab Section:       3
*/

/**
*This is an RSA encryption class.
*@author Lucina de la Rosa and Richard McCormick
*@version 1.0
*@since 2019/10/18
*/

import java.math.BigInteger;
import java.util.Random;

public class RSA {

    Random rand = new Random();

    /**
    *The value of d, which is used to decrypt files
    */
    BigInteger d;

    /**
    *The value of e, which is used to encrypt files.
    */
    BigInteger e;

    /**
    *The value of n, which is used as the modulus and has the same length as the key length.
    */
    BigInteger n;

    /**
    *Generates the d, e, and n values for encryption and decryption.
    *@param length The desired bitlength of the q and p files.
    */
    public void GenerateKeys(int length){
       //make p and q so we can make the rest of the variables
       BigInteger q = new BigInteger(length, 100, rand);
       BigInteger p = new BigInteger(length, 100, rand);
       n = new BigInteger((q.multiply(p)).toString());
       //set up one and zero
       BigInteger one = new BigInteger("1");
       BigInteger zero = new BigInteger("0");

       //get the totient, (p-1)(q-1)/(GCD of p-1 and q-1)
       BigInteger tot = new BigInteger(((p.subtract(one)).multiply(q.subtract(one)).divide(((p.subtract(one))).gcd(q.subtract(one)))).toString());

       e = new BigInteger(tot.bitLength(), 100, rand);
       //makes sure e < tot, e > 1, and the GCD of e and d is 1,then generates new prime
       while(e.compareTo(tot) == -1 && e.compareTo(one) == 1 && (tot.gcd(e).compareTo(one) == 0)){
           e = BigInteger.probablePrime(tot.bitLength(), rand);
       }

       d = new BigInteger(e.modInverse(tot).toString());
    }

    /**
    * Encrypts a message using the e and n files.
    *@param message The message to be encrypted.
    *@return The encrypted message.
    */
    public BigInteger Encrypt(BigInteger message){
      if (n == null || e == null){
        return null;
      }
      return message.modPow(e, n);
    }

    /**
    * Decrypts a message using the d and n files.
    *@param message The message to be decrypted.
    *@return The decrypted message.
    */
    public BigInteger Decrypt(BigInteger message){
      if (n == null || d == null){
        return null;
      }
      return message.modPow(d, n);
    }

}
