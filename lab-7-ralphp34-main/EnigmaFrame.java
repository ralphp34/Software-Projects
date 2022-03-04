import javax.swing.*;
import java.awt.*;
import java.awt.event.*;


public class EnigmaFrame extends JFrame {

    public Integer[] rotorNums = {1,2,3,4,5};


    public EnigmaFrame()
    {
        super();
        this.setTitle("Enigma GUI");
        this.setSize(800,500);
        this.setLocation(600, 600);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        JComboBox<Integer> in = new JComboBox<Integer>(rotorNums);
        JComboBox<Integer> mid = new JComboBox<Integer>(rotorNums);
        JComboBox<Integer> out = new JComboBox<Integer>(rotorNums);

        JTextField pos = new JTextField("###");

        JTextArea input = new JTextArea(2,35);
        JTextArea output = new JTextArea(2,35);


        JButton eButton = new JButton("encrypt");
        JButton dButton = new JButton("decrypt");


        eButton.addActionListener(new EncryptButton(in,mid,out,pos,input,output));

        dButton.addActionListener(new DecryptButton(in,mid,out,pos,input,output));

        JPanel nPanel = new JPanel();
        nPanel.setLayout(new FlowLayout());

        nPanel.add(new JLabel("Inner"));
        nPanel.add(in);
        nPanel.add(new JLabel("Middle"));
        nPanel.add(mid);
        nPanel.add(new JLabel("Outter"));
        nPanel.add(out);
        nPanel.add(new JLabel("Initial Position"));
        nPanel.add(pos);
        nPanel.add(eButton);
        nPanel.add(dButton);
        
        this.add(nPanel);

        JPanel cPanel = new JPanel();
        cPanel.setLayout(new FlowLayout());
        cPanel.add(new JLabel("Input"));
        cPanel.add(input, BorderLayout.NORTH);
    
        cPanel.add(new JLabel("Output"));
        cPanel.add(output, BorderLayout.SOUTH);

        this.add(cPanel, BorderLayout.SOUTH);

        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.pack();
    }


}
