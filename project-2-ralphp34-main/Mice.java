import java.util.Random;

public class Mice extends Creature
{

    int stepCounter;
    
    public Mice(int r, int c, City cty, Random rnd) 
    {
        super(r, c, cty, rnd);
        lab = LAB_BLUE;
        this.stepCounter = 0;
    }

    @Override
    public void maybeTurn() 
    {
        int chance = rand.nextInt(5);
        int newDir = rand.nextInt(NUM_DIRS);

        if(chance == 1)
        {
            setDir(newDir);
        }
    }

    @Override
    public void takeAction() 
    {

        for(Creature c : city.getCreatures())
        {
            if (this.getGridPoint() == c.getGridPoint() && c instanceof CheeseCreature)
            {
                city.queueRmCreature(c);
            }
        }

        if(stepCounter == 20)
        {
            Mice newMice = new Mice(this.getRow(), this.getCol(), this.city, this.rand);
            city.queueAddCreature(newMice);
        } 
    }

    public boolean die() 
    {
        if (stepCounter == 30)
        {
            return true;
        }

        return false;
    }

    @Override
    public void step() 
    {
        maybeTurn();
        int row = (getGridPoint().row + dirRow[this.getDir()] + City.MAX_ROW) % City.MAX_ROW;
        int col = (getGridPoint().col + dirCol[this.getDir()] + City.MAX_COL) % City.MAX_COL;

        GridPoint updatedPoint = new GridPoint(row, col);
        setPoint(updatedPoint);
        stepCounter++;
    }

    public String toString() 
    {
        //output in col,row format or (x,y) format
        return ""+this.getGridPoint().col+" "+this.getGridPoint().row+" "+lab;
    }

}