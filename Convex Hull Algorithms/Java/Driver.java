/**
 * Driver class, runs all the three algorithms on every file in the folder input and generates the output in output folder
 */
import java.io.*;
import java.util.*;
import java.lang.*;
public class Driver
{
    /**
     * Prints the resultant convex hull to a ch file
     */
    public static void printResult(ArrayList<Point> allPoints, ArrayList<Point> hull, PrintWriter out)
    {
        out.println("CH");
        out.println(allPoints.size() + " " + hull.size());
        for(Point p : allPoints)
        {
            out.println(p.x + " " + p.y + " 0");
        }
        for(Point p : hull)
        {
            out.write((int)p.id + " ");
        }
    }
    /**
     * Runs the Jarvis algorithm on given set of points
     */
    public static void runJarvis(ArrayList<Point> points, PrintWriter outCh, PrintWriter outRes)throws notPossible
    {
        ArrayList<Point> buffer = new ArrayList<Point>(points);
        
        long startTime = System.nanoTime();
        ArrayList<Point> hull = Jarvis.run(buffer);
        printResult(points, hull, outCh);
        long timeTaken = System.nanoTime() - startTime;
        
        outRes.println("Jarvis Algorithm");
        outRes.println("Size of the dataset : " + points.size());
        outRes.println("Time Taken : " + timeTaken/1000000.0 + "ms");
        outRes.println("----------------------------");
    }
    /**
     * Runs the Graham Scan algorithm on given set of points
     */
    public static void runGraham(ArrayList<Point> points, PrintWriter outCh, PrintWriter outRes)throws notPossible
    {
        ArrayList<Point> buffer = new ArrayList<Point>(points);
        
        long startTime = System.nanoTime();
        ArrayList<Point> hull = GrahamScan.run(buffer);
        printResult(points, hull, outCh);
        long timeTaken = System.nanoTime() - startTime;
        
        outRes.println("Graham Scan");
        outRes.println("Size ofthe dataset : " + points.size());
        outRes.println("Time Taken : " + timeTaken/1000000.0 + "ms");
        outRes.println("----------------------------");
    }
    /**
     * Runs the Andrews algorithm on given set of points
     */
    public static void runAndrews(ArrayList<Point> points, PrintWriter outCh, PrintWriter outRes)throws notPossible
    {
        ArrayList<Point> buffer = new ArrayList<Point>(points);
        
        long startTime = System.nanoTime();
        ArrayList<Point> hull = Andrews.run(buffer);
        printResult(points, hull, outCh);
        long timeTaken = System.nanoTime() - startTime;
        
        outRes.println("Andrews Algorithm");
        outRes.println("Size of the dataset : " + points.size());
        outRes.println("Time Taken : " + timeTaken/1000000.0 + "ms");
        outRes.println("----------------------------");
    }
    /**
     * Main driver function. Generates the output for all input files present in the input folder.
     */
    public static void main(String args[])throws FileNotFoundException, IOException
    {
        File folder = new File("input");
        File listOfInput[] = folder.listFiles();
        
        for(File file : listOfInput)
        {
            if(file.isFile())
            {
                Scanner sc = new Scanner(file);
                ArrayList<Point> points = new ArrayList<Point>();
                int n = sc.nextInt();
                for(int i = 0; i < n; i++)
                {
                     Double x = sc.nextDouble(), y = sc.nextDouble(), z = sc.nextDouble();
                     x *= 10;
                     y *= 10;
                     points.add(new Point(x, y, i));
                }
                
                PrintWriter outChJ = new PrintWriter(new File("output/" + file.getName() + " jarvis.ch"));
                PrintWriter outChG = new PrintWriter(new File("output/" + file.getName() + " graham.ch"));
                PrintWriter outChA = new PrintWriter(new File("output/" + file.getName() + " andrews.ch"));
                PrintWriter outResult = new PrintWriter(new File("output/" + file.getName() + " analysis.txt"));
                
                try
                {
                    runJarvis(points, outChJ, outResult);
                    runGraham(points, outChG, outResult);
                    runAndrews(points, outChA, outResult);
                }
                catch(notPossible np)
                {
                    System.out.println(np);
                }
                
                outChJ.close();
                outChG.close();
                outChA.close();
                outResult.close();
            }
        }
        
        System.out.print("Process Successful");
    }
}
