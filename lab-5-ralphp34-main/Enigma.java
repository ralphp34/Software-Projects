//TODO
import java.util.*;
import java.io.*;
public class Enigma
{
    String[] possibleRotor = {"#GNUAHOVBIPWCJQXDKRYELSZFMT", 
                            "#EJOTYCHMRWAFKPUZDINSXBGLQV", 
                             "#BDFHJLNPRTVXZACEGIKMOQSUWY", 
                             "#NWDKHGXZVRIFJBLMAOPSCYUTQE", 
                            "#TGOWHLIFMCSZYRVXQABUPEJKND"};

    public Rotor [] rotors;
    public int size = 27;
    public Enigma(int id1, int id2, int id3, String chars)
    {
        rotors = new Rotor[3];
        rotors[0] = new Rotor (chars.charAt(0), possibleRotor[id1 - 1]);
        rotors[1] = new Rotor (chars.charAt(1), possibleRotor[id2 - 1]);
        rotors[2] = new Rotor (chars.charAt(2), possibleRotor[id3 - 1]);
    }

    public String encrypt (String message)
    {
        String encryptedStr = "";
        for (int i = 0; i < message.length(); i++)
        {
            char cur = message.charAt(i);
            int innerInd = rotors[0].getIndexOfChar(cur);
            char outterChar = rotors[2].getCharacterAtIndex(innerInd);
            int middleInd = rotors[1].getIndexOfChar(outterChar);
            char encryptChar = rotors[2].getCharacterAtIndex(middleInd);
            encryptedStr = encryptedStr + encryptChar;

            if (rotors[0].rotate())
            {
                if (rotors[1].rotate())
                {
                    rotors[2].rotate();
                }
            }


        }


        return encryptedStr;
    }

    public String decrypt (String message)
    {
        String decryptedStr = "";
        for (int i = 0; i < message.length(); i++)
        {
            char cur = message.charAt(i);
            int outterInd = rotors[2].getIndexOfChar(cur);
            char middleChar = rotors[1].getCharacterAtIndex(outterInd);
            int innerInd = rotors[2].getIndexOfChar(middleChar);
            char decryptChar = rotors[0].getCharacterAtIndex(innerInd);
            decryptedStr = decryptedStr + decryptChar;

            if (rotors[0].rotate())
            {
                if (rotors[1].rotate())
                {
                    rotors[2].rotate();
                }
            }

        }

        return decryptedStr;

    }
}