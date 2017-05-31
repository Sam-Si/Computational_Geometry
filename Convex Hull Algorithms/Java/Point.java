/**
 * Has all the functionalities of a point in a 2D plane
 */
import java.lang.*;
import java.util.*;

public class Point 
{
    double x;
    double y;
    int id;
    /**
     * Default Constructor
     */
    public Point()
    {
        x = 0;
        y = 0;
        id = 0;
    }
    /**
     * Basic Constructor
     */
    public Point(double _x, double _y, int _id)
    {
        x = _x;
        y = _y;
        id = _id;
    }
    /**
     * Copy Constructor
     */
    public Point(int _x, int _y, int _id)
    {
        x = (double) _x;
        y = (double) _y;
        id = _id;
    }
    /**
     * Returns the distance between two points
     */
    public double distanceFrom(Point that)
    {
        return Math.sqrt( (this.x - that.x)*(this.x - that.x) + (this.y - that.y)*(this.y - that.y) ); 
    }
    /**
     * Returns the vector area formed by the triangle using three points as vertices
     */
    public static double vectorArea(Point p, Point q, Point r)
    {
        return (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    }
    /**
     * Returns true if three points are colinear and false otherwise
     */
    public static boolean areCollinear(Point p, Point q, Point r)
    {
       double area = Point.vectorArea(p, q, r);
       
       if(area == 0) return true;
       return false;
    }
    /**
     * Returns true if three points take a left turn and false otherwise
     */
    public static boolean turnsLeft(Point p, Point q, Point r)
    {
        double area = Point.vectorArea(p, q, r);
        if(area < 0) return true;
        return false;
    }
    /**
     * Returns true if three points take a right turn and false otherwise
     */
    public static boolean turnsRight(Point p, Point q, Point r)
    {
        double area = Point.vectorArea(p, q, r);
        if(area > 0) return true;
        return false;
    }
    /**
     * Converts the point into printable string
     */
    public String toString()
    {
        return "(" + x + "," + y + ")";
    }
    /**
     * Sorts by x co-ordinate breaking ties by y co-ordinate
     */
    public static Comparator<Point> byX()
    {
        return new Comparator<Point>()
        {
            public int compare(Point a, Point b)
            {
                if(a.x > b.x) return 1;
                else if(a.x < b.x) return -1;
                else return (int)(a.y - b.y);
            }
        };
    }
    /**
     * Sorts by y co-ordinate breaking ties by x co-ordinate
     */
    public static Comparator<Point> byY()
    {
        return new Comparator<Point>()
        {
            public int compare(Point a, Point b)
            {
                if(a.y > b.y) return 1;
                else if(a.y < b.y) return -1;
                else return (int)(a.x - b.x);
            }
        };
    }
    /**
     * sorts anticlockwise around a given pivot
     */
    public static Comparator<Point> antiClockWise(Point pivot)
    {
        return new Comparator<Point>()
        {
            public int compare(Point a, Point b)
            {
                double area = vectorArea(pivot, a, b);
                
                if(area == 0){
                    if(pivot.distanceFrom(a) > pivot.distanceFrom(b)) return 1;
                    else return -1;
                }
                else if(area > 0) return 1;
                else return -1;
            }
        };
    }
    /**
     * sorts clockwise around a given pivot
     */
    public static Comparator<Point> clockWise(Point pivot)//Sorts clockwise around a given pivot
    {
        return new Comparator<Point>()
        {
            public int compare(Point a, Point b)
            {
                double area = vectorArea(pivot, a, b);
                
                if(area == 0){
                    if(pivot.distanceFrom(a) > pivot.distanceFrom(b)) return 1;
                    else return -1;
                }
                else if(area > 0) return -1;
                else return 1;
            }
        };
    }
}