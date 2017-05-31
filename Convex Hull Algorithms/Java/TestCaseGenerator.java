
/**
 * Generates random test data
 */
import java.io.*;
import java.lang.*;
import java.util.*;
public class TestCaseGenerator
{
    /**
     * Generates n random co-ordinates
     */
    static void generate(int n, PrintWriter out)
    {
        for(int i = 0; i < n; i++)
        {
            double r1 = Math.random();
            double r2 = Math.random();
            double r3 = Math.random();
            double r4 = Math.random();
            int multiplier1 = (r1 > 0.51) ? 1 : ((r1 < 0.49) ? -1 : 0);
            int multiplier2 = (r2 > 0.51) ? 1 : ((r2 < 0.49) ? -1 : 0);
            int x = (int)(multiplier1 * r3 * 1000) + 1;
            int y = (int)(multiplier2 * r4 * 1000) + 1;
            out.println(x + " " + y);
        }
    }
    /**
     * Generates multiple random test cases
     */
    public static void main(String args[])throws FileNotFoundException
    {
        int counter = 1;
        for(int i = 10; i <= 100000; i*=10)
        {
            for(int j = 1; j <= 2; j++)
            {
                PrintWriter out = new PrintWriter(new File("input/in" + counter++));
                generate(i, out);
                out.close();
            }
        }
    }
}
