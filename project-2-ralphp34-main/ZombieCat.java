import java.util.Random;
import java.util.HashSet;
import java.util.LinkedList;

public class ZombieCat extends Cat
{
    private int stepCounter;
    private int lastTimeEatenMouse;
    private int lastTimeEatenCat;
    protected boolean chasing;

    public ZombieCat(int r, int c, City cty, Random rnd) 
    {
        super(r, c, cty, rnd);
        lab = LAB_RED;
        this.stepCounter = 0;
        this.lastTimeEatenCat = 0;
        this.lastTimeEatenMouse = 0;

    }
    
    public void takeAction()
    {
        for(Creature c : city.getCreatures())
        {
            if (this.getGridPoint() == c.getGridPoint() && c instanceof Mice)
            {
                lastTimeEatenMouse = stepCounter;
                city.queueRmCreature(c);
                //city.getCreatureGrid().get(c.getGridPoint()).remove(c);

            }

            if (this.getGridPoint() == c.getGridPoint() && c instanceof Cat)
            {
                lastTimeEatenCat = stepCounter;
                c = new ZombieCat(this.getRow(), this.getCol(), city, rand);
                city.queueAddCreature(c);
            }
        }
    }

    public boolean die() 
    {
        if ((stepCounter - lastTimeEatenMouse >=  100) && (stepCounter - lastTimeEatenCat >= 100))
        {
            return true;
        }
        return false;
    }

    public char getLab()
    {
        return this.lab;
    }

    public int stepCounter()
    {
       return this.stepCounter;
    }

    public int lastTimeEatenCat()
    {
        return this.lastTimeEatenMouse;
    }

    public void step() 
    {
        chasing = foundCreature();
        if(!chasing) 
        {
            maybeTurn();
        }
        
        int row = (getGridPoint().row + dirRow[this.getDir()] * 3 + City.MAX_ROW) % City.MAX_ROW;
        int col = (getGridPoint().col + dirCol[this.getDir()] * 3 + City.MAX_COL) % City.MAX_COL;

        GridPoint updatedPoint = new GridPoint(row, col);
        setPoint(updatedPoint);
        stepCounter++;
    }

    public boolean foundCreature()
    {
       
        //GridPoint mPoint = new GridPoint(0, 0);

        //Doing the searching from both sides

        // LinkedList<Creature> found = new LinkedList<Creature>();

        // searching(this.getGridPoint(), 0, new HashSet<GridPoint>(), found);

        Creature closest = null;
        for (Creature c : city.getCreatures())  
        {
            if(c.dist(this) > 40 ) continue;
            if(c instanceof ZombieCat || c instanceof CheeseCreature) continue;

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
            lab = LAB_RED;
            return false;
        }
        
            //determine the direction to chase
            // GridPoint me = this.getGridPoint();
            // GridPoint them = closest.getGridPoint();
            if(Math.max(this.getCol(),closest.getCol()) - Math.min(this.getCol(),closest.getCol()) >
            Math.max(this.getRow(),closest.getRow()) - Math.min(this.getRow(),closest.getRow()))
            //if( Math.abs(me.col - them.col) < Math.abs(me.row - them.row))
            {
                //I'm going to either turn EAST or WEST
                if (this.getCol() > closest.getCol())
                {
                    this.setDir(Creature.WEST);
                }
                else 
                {
                    this.setDir(Creature.EAST);
                }
            }

            else
            {
                if (this.getRow() > closest.getRow())
                {
                    //NORTH
                    this.setDir(Creature.NORTH);
                   

                }
                else
                {
                    //SOUTH
                    this.setDir(Creature.SOUTH);
                    //this.setDir(Creature.EAST);
                }
            }
            System.err.println("ZCat "+this.getGridPoint() + " chasing Mouse " + closest.getGridPoint() + " in direction" + this.getDir());
            lab = LAB_BLACK;
            return true;
        
    }


    public void searching(GridPoint point, int steps, HashSet<GridPoint> h, LinkedList<Creature> found)
    {
        if(steps > 40)
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
            if(c instanceof Mice || c instanceof Cat)
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
