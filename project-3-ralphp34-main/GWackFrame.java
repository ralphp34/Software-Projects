import javax.lang.model.util.ElementScanner6;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;

public class GWackFrame extends JFrame
{
    JTextField name; 
    JTextField ip;
    JTextField port;
    JButton connectionButton; 
    JButton send;
    JTextArea members;
    JTextArea message;
    JTextArea compose;
    Socket sock;
    PrintWriter write;
    InputStreamReader input;
    private static BufferedReader reader;
    boolean connected;
    String clientList;
    JScrollPane scroll;



    public GWackFrame()
    {
        super();
        this.setTitle("GWack -- GW Slack Simulator");
        this.setBounds(600, 600, 900, 900);
        name = new JTextField(10);
        ip = new JTextField(10);
        port = new JTextField(10);

        connectionButton = new JButton("Connect");
        send = new JButton("Send");
        JPanel nPanel = new JPanel();
        nPanel.setLayout(new FlowLayout());

        connectionButton.addActionListener(new Connection());
        send.addActionListener(new Send());

        nPanel.add(new JLabel("Name"));
        nPanel.add(name);
        nPanel.add(new JLabel("IP Address"));
        nPanel.add(ip);
        nPanel.add(new JLabel("Port"));
        nPanel.add(port);
        nPanel.add(connectionButton);
        this.add(nPanel, BorderLayout.NORTH);

        members = new JTextArea(10,8);
        message = new JTextArea(3,5);
        scroll = new JScrollPane(message);
        scroll.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
        compose = new JTextArea(3,5);

        JPanel cPanel = new JPanel();
        cPanel.setLayout(new BorderLayout());
        cPanel.add(new JLabel("Members Online    "), BorderLayout.NORTH);
        cPanel.add(members, BorderLayout.WEST);
        this.add(cPanel, BorderLayout.WEST);
        
        JPanel gPanel = new JPanel();
        gPanel.setLayout(new BoxLayout(gPanel, BoxLayout.Y_AXIS));
        gPanel.add(new JLabel("Message"));
        gPanel.add(message);
        gPanel.add(new JLabel("Compose"));
        gPanel.add(compose);
        this.add(gPanel, BorderLayout.CENTER);

        JPanel sPanel = new JPanel();
        sPanel.setLayout(new FlowLayout(FlowLayout.RIGHT));
        sPanel.add(send);
        this.add(sPanel, BorderLayout.SOUTH);

        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        this.pack();
    }

    private class Connection implements ActionListener
    {           
        @Override
        public void actionPerformed(ActionEvent e) 
        {
            String input_ip = ip.getText();
            String input_port = port.getText();
            int portNum = Integer.parseInt(input_port);

            if (sock == null)
            {
                try 
                {
                    sock = new Socket(input_ip, portNum);
                    connectionButton.setText("Disconnect");
                    connected = true;
                    write = new PrintWriter(sock.getOutputStream());
                    write.println("SECRET\n3c3c4ac618656ae32b7f3431e75f7b26b1a14a87\nNAME");
                    write.println(name.getText());
                    write.println();
                    //add thread to update members and read list
                    //need method to update list should be in thread
                    reader = new BufferedReader(new InputStreamReader(sock.getInputStream()));
                    System.out.println(sock);
                    //System.out.println("hello");
                } 
                catch (Exception ex) 
                {
                    // TODO Auto-generated catch block
                    System.err.println("Cannot Connect");
                    //System.out.println(ex);
                    JOptionPane.showMessageDialog(new JFrame(), "Cannot Connect", "Connection Error", JOptionPane.WARNING_MESSAGE);

                    System.exit(1);
                }
                ReadThread thread = new ReadThread(sock);
                thread.start();
            }
            else
            {
                try
                {
                    sock.close();
                    sock = null;
                    connectionButton.setText("Connect");
                    members.setText("");
                    message.setText("");
                    connectionButton.removeActionListener(this);
                    connected = false;
                    connectionButton.addActionListener(this);

                }
                catch (IOException ex)
                {
                    System.err.print("IOExceptiom");
                    System.exit(1);
                }
            }
        
        }
    
    }

    private class Send implements ActionListener
    {
        @Override
        public void actionPerformed(ActionEvent e) 
        {
            String msg = compose.getText();
            compose.setText("");
            // create print writer and send to the socket
            // and print from socket
            try
            {
                write.println(msg);
                write.flush();
                //message.append(msg + "\n");
            }
            catch(Exception ex)
            {
                System.exit(1);
            }

        }
        
    } 

    private class ReadThread extends Thread
    {
        //ServerSocket server = null;

        public ReadThread(Socket s)
        {
            sock = s;
        }

        public void run()
        {
            //System.out.println("hi");
            String x;

            try
            {
                //System.out.println("hi");
               // System.out.println(x);
               x = reader.readLine();

                while (sock.isConnected())
                {
                    write.flush();
                    if (x.equals("START_CLIENT_LIST"))
                    {
                        members.setText("");
                        while(!x.equals("END_CLIENT_LIST"))
                        {
                            x = reader.readLine();
                            if (!x.equals("END_CLIENT_LIST"))
                            {
                                clientList = clientList + (x + "\n");
                            }
                        }
                        dispalymembers(clientList);
                    }

                    if (x.equals("END_CLIENT_LIST"))
                    {
                        x = reader.readLine();
                    }
                    // while (x != null)
                    if (!x.equals("START_CLIENT_LIST"))
                    {
                        message.append(x + "\n");
                        x = reader.readLine(); 
                    }
                    
                }
            

            }

            catch(Exception e)
            {
                System.out.println("Connection lost: "+sock.getRemoteSocketAddress());
                JOptionPane.showMessageDialog(new JFrame(), "Server Lost Connection", "Connection Error", JOptionPane.WARNING_MESSAGE);

            }

        }
    }

    private String dispalymembers(String s)
    {
        s = clientList;
        members.setText(s);
        clientList = "";
        return s;
        
    }

    
}
