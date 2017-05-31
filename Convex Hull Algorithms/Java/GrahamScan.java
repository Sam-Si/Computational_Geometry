/**
 * Finds and returns the convex hull using Graham Scan Algorithm
 */
import java.lang.*;
import java.util.*;

public class GrahamScan
{
    /**
     * Returns the bottom-most and then the left-most point as the pivot
     */
    static int getPivotIndex(ArrayList<Point> points)
    {
        int res=0;
        for(int i = 1; i < points.size(); i++)
        {
            if(points.get(i).y < points.get(res).y) 
            {
                res = i;
            }
            else if(points.get(i).y == points.get(res).y && points.get(i).x < points.get(res).x)
            {
                res = i;
            }
        }
        return res;
    }
    /**
     *Utility function to get the element below the top in the stack
     */
    static Point nextToTop(Stack<Point> stack) 
    {
        Point p = stack.pop();
        Point q = stack.peek();
        stack.push(p);
        return q;
    }
    /**
     * Returns the convex hull given an arraylist of points
     */
    public static ArrayList<Point> run(ArrayList<Point> points) throws notPossible
    {
        ArrayList<Point> result = new ArrayList<Point>();     // Initialisation 
        ArrayList<Point> buffer = new ArrayList<Point>();
        Stack<Point> stack = new Stack<Point>();           
        
        int n = 1;

        int pivotIndex = getPivotIndex(points);               //Getting the pivot point
        Point pivot = points.get(pivotIndex);
        
        points.set(pivotIndex, points.get(0));
        points.set(0, pivot);                                //swapping elements points[0] and points[pivot]
        
        Collections.sort(points.subList(1,points.size()), Point.antiClockWise(pivot)); //Sorts the points in anti-clockwise order
        
        buffer.add(points.get(0));
        for(int i = 1; i < points.size(); i++) //Removing all co-linear points between two most-distant co-linear points
        {
            while(i < points.size() - 1 && Point.areCollinear(pivot, points.get(i), points.get(i+1)))
            {
                i++;
            }
            buffer.add(points.get(i));
            n++;
        }
        
        if(n < 3) throw new notPossible("No possible Convex Hull"); // If hull not possible
        
        stack.push(buffer.get(0));
        stack.push(buffer.get(1));
        stack.push(buffer.get(2));
        
        for(int i = 3; i < n; i++)
        {
            while(!Point.turnsLeft(nextToTop(stack), stack.peek(), buffer.get(i))) //Pop untill points take a left turn
            {
                stack.pop();
            }
            stack.push(buffer.get(i)); //adding points[i] to the answer
        }
        
        while(!stack.empty()) //storing the elements of the stack in a random-access arraylist
        {
            result.add(stack.pop());
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
