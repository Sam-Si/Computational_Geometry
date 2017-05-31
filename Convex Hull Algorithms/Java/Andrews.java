/**
 * Finds and returns the convex hull using Andrews Algorithm
 */
import java.lang.*;
import java.util.*;

public class Andrews
{
    /**
     *Utility function to get the element below the top in the stack
     */
    static Point nextToTop(Stack<Point> stack) //Utility function to get the second element in the stack
    {
        Point p = stack.pop();
        Point q = stack.peek();
        stack.push(p);
        return q;
    }
    /**
     * Returns the convex hull given an arraylist of points
     */
    public static ArrayList<Point> run(ArrayList<Point> points) throws notPossible //Main process
    {
       Stack<Point> U = new Stack<Point>();     // Initialisation 
       Stack<Point> L = new Stack<Point>();
       ArrayList<Point> result = new ArrayList<Point>();           
       if(points.size() < 3) throw new notPossible("No Possible Convex Hull"); 
       boolean allColinear = true;
       for(int i = 2; i < points.size(); i++)
       {
           if(!Point.areCollinear(points.get(0), points.get(1), points.get(2))) allColinear = false;
       }
       if(allColinear) throw new notPossible("Degeneracy Detected");
       Collections.sort(points, Point.byX()); //Sorts the points according to X co-ordinate
       int n = points.size();
       for(int i = 0; i < n; i++)
       {
           while(L.size() > 1 && !Point.turnsLeft(nextToTop(L), L.peek(), points.get(i)))
           {
               L.pop();
           }
           L.push(points.get(i));
       }
       
       for(int i = n - 1; i >= 0; i--)
       {
           while(U.size() > 1 && !Point.turnsLeft(nextToTop(U), U.peek(), points.get(i)))
           {
               U.pop();
           }
           U.push(points.get(i));
       }
       
       L.pop();
       U.pop();
        
       while(!U.empty())
       {
           result.add(U.pop());
       }
       while(!L.empty())
       {
           result.add(L.pop());
       }
       return result;
    }
    /**
     * Main function for testing purposes.
     */
    public static void main(String args[])
    {
        Scanner sc = new Scanner(System.in);
        
        int n = sc.nextInt(); // number of points
        
        ArrayList<Point> points = new ArrayList<Point>();
        
        for(int i = 0; i < n; i++) //input points
        {
            double x = sc.nextDouble();
            double y = sc.nextDouble();
            points.add(new Point(x,y,i));
        }
        
        try
        {
            ArrayList<Point> convexHull = run(points);
            System.out.println("The points on the convex hull are : ");
            for(int i = 0; i < convexHull.size(); i++)
            {
                System.out.println(convexHull.get(i));
            }
        }catch(notPossible nP)
        {
            System.out.println("No possible Convex Hull");
        }
    }
}
