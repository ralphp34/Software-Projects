import java.util.Random;

public class CheeseCreature extends Creature
{
    int stepCounter;

    public CheeseCreature(int r, int c, City cty, Random rnd) {
        super(r, c, cty, rnd);
        lab = LAB_ORANGE;
        stepCounter = 0;
    }

    @Override
    public void maybeTurn() 
    {
        int chance = rand.nextInt(50);
        int newDir = rand.nextInt(NUM_DIRS);

        if(chance == 1)
        {
            setDir(newDir);
        }
    }

    @Override
    public void takeAction() 
    {
        
    }

    @Override
    public boolean die() 
    {   
        if (stepCounter == 15)
        {
            return true;
        }
        return false;
    }

    @Override
    public void step() 
    {
        maybeTurn();
        int chance = rand.nextInt(20);

        if (chance == 1)
        {
            int row = (getGridPoint().row + dirRow[this.getDir()] + City.MAX_ROW) % City.MAX_ROW;
            int col = (getGridPoint().col + dirCol[this.getDir()] + City.MAX_COL) % City.MAX_COL;

            GridPoint updatedPoint = new GridPoint(row, col);
            setPoint(updatedPoint);
            stepCounter++;
        }
    }
    
}
