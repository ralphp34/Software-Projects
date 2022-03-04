import java.util.Scanner;

public class Prob2{

    public static void main(String args[]){

        Scanner sc = new Scanner(System.in);

	    
        System.out.println("Enter a number:");
        int a = sc.nextInt();
        System.out.println();


        if(a <= 0){
            //note printing to stderr!
            System.err.println("Houston, we have a problem");
            System.exit(1); //exit with e
        }
        
        System.out.println("Lift off in ...");
        for(int i=0;i<a;i++){
            System.out.println(a-i);
        }

        System.out.println();
        System.out.println("        | ");
        System.out.println("       / \\ ");
        System.out.println("      / _ \\ ");
        System.out.println("     |.o '.| ");
        System.out.println("     |'._.'| ");
        System.out.println("     |     | ");
        System.out.println("   ,'|  |  |`. ");
        System.out.println("  /  |  |  |  \\ ");
        System.out.println("  |,-'--|--'-.| ");
        
    }
}
