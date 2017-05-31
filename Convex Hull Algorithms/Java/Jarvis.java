/**
 * Finds and returns the convex hull using Jarvis Algorithm
 */
import java.util.*;
import java.lang.*;

public class Jarvis
{
    /**
     * Returns the left-most and then the bottom-most point as the pivot
     */
   public static int getPivot(ArrayList<Point> points)
   {
       int pivot = 0;
       for(int i = 1; i < points.size(); i++)
       {
           if(points.get(i).x < points.get(pivot).x)
           {
               pivot = i;
           }
           else if(points.get(i).x == points.get(pivot).x && points.get(i).y < points.get(pivot).y)
           {
               pivot = i;
           }
       }
       return pivot;
   }
   /**
     * Returns the convex hull given an arraylist of points
     */
   public static ArrayList<Point> run(ArrayList<Point> points)throws notPossible //main process
   {
       if(points.size() < 3) throw new notPossible("No Possible Convex Hull");
       boolean allColinear = true;
       for(int i = 2; i < points.size(); i++)
       {
           if(!Point.areCollinear(points.get(0), points.get(1), points.get(2))) allColinear = false;
       }
       if(allColinear) throw new notPossible("Degeneracy Detected");
       ArrayList<Point> result = new ArrayList<Point>();
       
       int pivot = getPivot(points), next, n = points.size(); //initialisation, getting the pivot element
       
       int start = pivot;
       do
       {
           result.add(points.get(pivot));
           
           next = (pivot+1)%n;
           
           for(int i = 0; i < n; i++)//find the point most counter-clockwise to pivot
           {
               if(Point.turnsLeft(points.get(pivot), points.get(i), points.get(next)))
               {
                   next = i;
               }
           }
           
           pivot = next;
       }while(pivot != start); //run untill we are back to the starting point
       
       return result;
   }    
   /**
     * Main function for testing purposes.
     */
   public static void main(String args[])
   {
       Scanner sc = new Scanner(System.in);
        
       int n = sc.nextInt(); //input number of elements from the user
        
       ArrayList<Point> points = new ArrayList<Point>();
       
       for(int i = 0; i < n; i++) //input the points
       {
           double x = sc.nextDouble();
           double y = sc.nextDouble();
           points.add(new Point(x, y, i));
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
