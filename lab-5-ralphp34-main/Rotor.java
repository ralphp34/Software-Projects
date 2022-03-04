//TODO
public class Rotor
{
    public char startChar;
    public String rotorString;
    public int rotorNum;

    public Rotor (char start, String str)
    {
        startChar = start;
        rotorString = str;
        while (rotorString.charAt(0) != startChar)
        {
            rotate();
        }
    }

    public boolean rotate ()
    {
        this.rotorString = rotorString.charAt(rotorString.length() - 1) + rotorString.substring(0, rotorString.length() -1);
        
        if (rotorString.charAt(0) == startChar)
        {
            return true;
        }
        else
        {
            return false;
        }
    }


    public int getIndexOfChar (char character)
    {
        return rotorString.indexOf(character);
    }

    public char getCharacterAtIndex (int index)
    {
        return rotorString.charAt(index);
    }
}