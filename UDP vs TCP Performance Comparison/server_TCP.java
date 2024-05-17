 import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
 import java.util.ArrayList;
 import java.util.Collections;

public class server_TCP {
    // Initialize server socket and client connection
    private Socket clientSocket = null;
    private ServerSocket jokeServer = null;
    private DataInputStream clientInput = null;
    private DataOutputStream clientOutput = null;

    // Constructor with server port
    public server_TCP(int port,long arr[], int count) {
        // Joke files location
        String Joke1Path = "Joke1.txt";
        String Joke2Path = "Joke2.txt";
        String Joke3Path = "Joke3.txt";


        // Start server and wait for a connection
        try {
            jokeServer = new ServerSocket(port);
            System.out.println("JokeServer started");

            System.out.println("Waiting for a client ...");

            clientSocket = jokeServer.accept();



            // Input from client
            clientInput = new DataInputStream(new BufferedInputStream(clientSocket.getInputStream()));
            // Output to client
            clientOutput = new DataOutputStream(clientSocket.getOutputStream());

            System.out.println("Client connected");

            String fileName = "";

            // Process commands from client
            while (true) {
                try {

                    // Handle client requests
                    fileName = clientInput.readUTF();
                    if (fileName.equals("bye")) {
                        break;
                    }

                    //Start Timer
                    long start = System.currentTimeMillis();

                    File file = new File("jokes/" + fileName);
                    clientOutput.writeLong(file.length());

                    //END TIMER
                    long result = System.currentTimeMillis()-start;
                    arr[count] = result;

                    try (FileInputStream fis = new FileInputStream(file)) {
                        byte[] buffer = new byte[4096];
                        int bytesRead;
                        while ((bytesRead = fis.read(buffer)) != -1) {
                            clientOutput.write(buffer, 0, bytesRead);
                        }
                         System.out.println(fileName + " sent --- elapsed time: "+ result + "ms");
                    }

                } catch (IOException e) {
                    System.out.println(e);
                }
            }

            System.out.println("Client Disconnected.");

            // Close resources
            clientSocket.close();
            clientInput.close();
            clientOutput.close();
        } catch (IOException e) {
            System.out.println(e);
        }
    }



    public static void main(String[] args) {
        ArrayStatistics stats = new ArrayStatistics();
        long[] arr = new long[10];

        for(int i = 0; i<10; i++){
            System.out.println("-------------------------------------------------------------------------------\nAttempt: "+(i+1));
            int port = 4010+i;
            new server_TCP(port, arr, i);
            System.out.println(arr[i]);
        }
//        if (args.length != 1) {
//            System.out.println("Please provide valid initilization arguments.");
//        } else {
//            int port = Integer.valueOf(args[0]);
//            new server_TCP(port);
//        }

        long min = stats.findMin(arr);
        long max = stats.findMax(arr);
        double mean = stats.findMean(arr);
        double stddev = stats.findStdDev(arr, mean);

        System.out.println("The stats: ");
        System.out.println("Min: " + min);
        System.out.println("Max: " + max);
        System.out.println("Mean: " + mean);
        System.out.println("StdDev: " + stddev);
    }
}
