import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

public class Prob3{

    public static void main(String args[]){
        File inputFile = new File("input.txt");
        Scanner sc = null;
        try{
            sc = new Scanner(inputFile);
        }catch(Exception e){
            System.out.println("ERROR: cannot open file");
            System.exit(1);
        }

        while(true){

            int i;
            float f;
            
            if(sc.hasNextInt())
                i = sc.nextInt();
            else
                break;
            
            if(sc.hasNextFloat())
                f = sc.nextFloat();
            else
                break;

            if(i >= 3 && f < 3){ 
                System.out.println("i:"+i+" f:"+f+" i*f:"+((float) i * f));
            }else{
                System.out.println("i:"+i+" f:"+(int) f+" i*f:"+ (int)(i * f));
            }
            
        }

    }

}
