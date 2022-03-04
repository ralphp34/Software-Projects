import java.util.Random;
import java.util.Scanner;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Simulator {
	
    public static void main(String[] args) {

        //This is the arguments for running your program so you can test with different settings
        final String USAGE = "java Simulator numMice numCats numZombieCats rounds [randSeed] [--DEBUG]";
        //note that [ ] is to indicate an optional argument. You do not include [ ] when using this argument.
        //When using the --DEBUG flag, you must set a random seed.
        
        boolean DEBUG = false;
        
        //parse arguments
        if(args.length < 4){
            System.out.println("ERROR: missing arguments");
            System.out.println(USAGE);
            System.exit(1);
        }
        int numMice = Integer.parseInt(args[0]);
        int numCats = Integer.parseInt(args[1]);
        int numZombieCats = Integer.parseInt(args[2]);
        int numCheeseCreatures = Integer.parseInt(args[3]);
        int rounds = Integer.parseInt(args[4]);

        Random rand;
        if(args.length > 4)
            rand = new Random(Integer.parseInt(args[4]));
        else
            rand = new Random(100);

        if(args.length > 5 && args[5].equals("--DEBUG")){
            DEBUG=true;
        }

        //Initialize a city with mice, cats, and zombie cats
        City city= new City(rand,numMice,numCats,numZombieCats,numCheeseCreatures);
        //Note for Level 4 you may need to change your constructors arguments.
        
        int count = 0;


        while (count < rounds) {
            count++;

            //TODO: You'll eventually need to complete functionality
            //for adding mice and cats per round, but start small and
            //build up.

            if (count % 25 == 0)
            {
                city.addCats();
            }           
            
            if (count % 75 == 0)
            {
                city.addCheeseCreature();
            }
            if (count % 100 == 0)
            {
                city.addMice();
            }
            city.simulate();
            System.out.println("done "+count);
            System.out.flush();

            if(DEBUG){
                System.err.print("Enter anything to continue: ");
                try{
                    (new BufferedReader(new InputStreamReader(System.in))).readLine();
                }catch(Exception e){
                    System.exit(1);
                }
            }
            
        }
    }
}
