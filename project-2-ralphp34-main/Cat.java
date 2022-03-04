import java.util.HashSet;
import java.util.LinkedList;
import java.util.Random;


public class Cat extends Creature
{

    private int stepCounter;
    private int lastTimeEatenMouse;
    protected boolean chasing;

    public Cat(int r, int c, City cty, Random rnd) {
        super(r, c, cty, rnd);
        lab = LAB_YELLOW;
        stepCounter = 0;
        lastTimeEatenMouse = 0;
        chasing = false;
    }

    @Override
    public void maybeTurn() {
        int chance = rand.nextInt(100);
        int newDir = rand.nextInt(NUM_DIRS);

        if(chance < 5)
        {
            setDir(newDir);
        }
    }

    @Override
    public void takeAction() 
    {
        for(Creature c : city.getCreatures())
        {
            if ((this.getGridPoint() == c.getGridPoint()) && c instanceof Mice)
            {
                lastTimeEatenMouse = stepCounter;
                city.queueRmCreature(c);
            }
        }

    }

    @Override
    public boolean die() {
        if (stepCounter - lastTimeEatenMouse >=  50)
        {
            city.queueAddCreature(new ZombieCat(this.getRow(), this.getCol(), city, rand));
            return true;
        }
        return false;
    }

    @Override
    public void step() {
        // TODO Auto-generated method stub
        chasing = foundMouse();
        if(!chasing) 
        {
            maybeTurn();
        }
        int row = (getGridPoint().row + dirRow[this.getDir()] * 2 + City.MAX_ROW) % City.MAX_ROW;
        int col = (getGridPoint().col + dirCol[this.getDir()] * 2 + City.MAX_COL) % City.MAX_COL;
       

        GridPoint updatedPoint = new GridPoint(row, col);
        setPoint(updatedPoint);
        stepCounter++;
    }

    public char getLab()
    {
        return lab;
    }

    public int stepCounter()
    {
       return this.stepCounter;
    }

    public int lastTimeEatenCat()
    {
        return this.lastTimeEatenMouse;
    }

    public boolean foundMouse()
    {
       
        //GridPoint mPoint = new GridPoint(0, 0);

        //Doing the searching from both sides

       // LinkedList<Creature> found = new LinkedList<Creature>();

        //searching(this.getGridPoint(), 0, new HashSet<GridPoint>(), found);

        Creature closest = null;
        for (Creature c : city.getCreatures())  
        {
            if(!(c instanceof Mice)) continue;
            if(c.dist(this) > 20 ) continue;

            if (closest == null)
            {
                closest = c;
            }
            else if(this.dist(c) < this.dist(closest))
            {
                closest = c;  
            }
        }
        
        if(closest == null)
        {
            lab = LAB_YELLOW;
            return false;
        }
        
            //determine the direction to chase
            // GridPoint me = this.getGridPoint();
            // GridPoint them = closest.getGridPoint();

            if(Math.max(this.getCol(),closest.getCol()) - Math.min(this.getCol(),closest.getCol()) >
               Math.max(this.getRow(),closest.getRow()) - Math.min(this.getRow(),closest.getRow()))
            //if( Math.abs(this.getCol() - closest.getCol()) < Math.abs(this.getRow() - closest.getRow()))
            {
                //I'm going to either turn EAST or WEST
                //çSystem.out.println(me);
                if (this.getCol() > closest.getCol())
                {
                    //EAST
                    this.setDir(Creature.WEST);
                    //this.setDir(Creature.SOUTH);
                }
                else 
                {
                    //WEST
                    this.setDir(Creature.EAST);
                    //this.setDir(Creature.NORTH);
                }
            }

            else
            {
                if (this.getRow() > closest.getRow())
                {
                    //NORTH
                    this.setDir(Creature.NORTH);
                    //this.setDir(Creature.WEST);
                   

                }
                else
                {
                    //SOUTH
                    this.setDir(Creature.SOUTH);
                    //this.setDir(Creature.EAST);
                }
            }

            //System.err.println("Cat "+this.getGridPoint() + " chasing Mouse " + closest.getGridPoint() + " in direction" + this.getDir());
            lab = LAB_CYAN;
            return true;
    }


    public void searching(GridPoint point, int steps, HashSet<GridPoint> h, LinkedList<Creature> found)
    {
        if(steps > 20)
        {
            return;
        }
        if(h.contains(point))
        {
            return;
        }

        h.add(point);
        if (city.getCreaturesAtLoc(point) == null)
        {
            return;
        }
        for (Creature c : city.getCreaturesAtLoc(point))
        {
            if(c instanceof Mice)
            {
                found.add(c);
            }
        }

        searching(new GridPoint(point.row+1, point.col), steps+1, h, found);
        searching(new GridPoint(point.row-1, point.col), steps+1, h, found);
        searching(new GridPoint(point.row, point.col+1), steps+1, h, found);
        searching(new GridPoint(point.row, point.col-1), steps+1, h, found);

    }
    
}
