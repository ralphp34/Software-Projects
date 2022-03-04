import java.util.*;
import java.net.*;
import java.io.*;

public class GWackChannel
{
    //TODO
    
    public static class ClientThread extends Thread
    {
        Socket sock;
        public ClientThread(Socket s)
        {
            super();
            sock = s;
        }

        public void run()
        {
            PrintWriter sock_out;
            BufferedReader sock_in;
            BufferedReader user_in;

            try
            {
                sock_out = new PrintWriter(sock.getOutputStream());
                sock_in = new BufferedReader(new InputStreamReader(sock.getInputStream()));
                user_in = new BufferedReader(new InputStreamReader(System.in));
                while(sock.isConnected())
                {
                    String response = sock_in.readLine();
                    if (response.equals("SECRET"))
                    {
                        response = sock_in.readLine();
                    }

                    if (response.equals("n3c3c4ac618656ae32b7f3431e75f7b26b1a14a87"))
                    {
                        response = sock_in.readLine();
                    }
                    
                    if (response.equals("NAME"))
                    {
                        response = sock_in.readLine();
                        sock_out.println("START_CLIENT_LIST\n" + response + "END_CLIENT_LIST\n");
                        sock_out.flush();

                    }
                    
                    System.out.println("Client: " + response);
                    sock_out.flush();
                    String input = user_in.readLine();
                    System.out.println("Server: " + input);
                    sock_out.println(input);
                    sock_out.flush();      
                }
                //sock.close();
            }
            catch(Exception ex)
            {
                System.out.println("Connection lost: "+sock.getRemoteSocketAddress());
            }
        } 
    }   
    public static void main(String args[])
    {
        ServerSocket server = null;
        try
        {
            server = new ServerSocket(2021);
            //server.serve();
        }
        catch (Exception ex)
        {
            System.err.println("Cannot open server socket");
            System.exit(1);
        }
        while(true)
        {
            Socket s;
            try
            {
                s = server.accept();
            }
            catch(Exception e)
            {
                e.printStackTrace();
                break;
            }
            
            System.out.println("Connection from: " + s.getRemoteSocketAddress());

            ClientThread ct = new ClientThread(s);
            ct.start();
        }
    }

}
