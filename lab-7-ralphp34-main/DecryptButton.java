import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class DecryptButton implements ActionListener
{
    public Rotor [] rotors;
    public String[] possibleRotor = {"#GNUAHOVBIPWCJQXDKRYELSZFMT", 
    "#EJOTYCHMRWAFKPUZDINSXBGLQV", 
     "#BDFHJLNPRTVXZACEGIKMOQSUWY", 
     "#NWDKHGXZVRIFJBLMAOPSCYUTQE", 
    "#TGOWHLIFMCSZYRVXQABUPEJKND"};
    
    JComboBox<Integer> in;
    JComboBox<Integer> mid;
    JComboBox<Integer> out;
    JTextField pos;
    JTextArea input;
    JTextArea output;
    public DecryptButton(JComboBox<Integer> in, JComboBox<Integer> mid, JComboBox<Integer> out, JTextField pos, JTextArea input, JTextArea output)
    {
        this.in = in;
        this.mid = mid;
        this.out = out;
        this.pos = pos;
        this.input = input;
        this.output = output;
        
        String chars = pos.getText();
    
        Integer id1 = (Integer) in.getSelectedItem();
        Integer id2 = (Integer) mid.getSelectedItem();
        Integer id3 = (Integer) out.getSelectedItem();
    

        rotors = new Rotor[3];
        rotors[0] = new Rotor (chars.charAt(0), possibleRotor[id1 - 1]);
        rotors[1] = new Rotor (chars.charAt(1), possibleRotor[id2 - 1]);
        rotors[2] = new Rotor (chars.charAt(2), possibleRotor[id3 - 1]);

    }

    public void actionPerformed(ActionEvent e) 
    {
        String message = input.getText();
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
        output.setText(decryptedStr);
    }

}
