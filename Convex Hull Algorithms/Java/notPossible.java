/**
 * Exception Class to handle cases where no convex hull possible
 */
class notPossible extends Exception
{
    /**
     * Default Constructor
     */
    public notPossible(){}
    /**
     * Custom Message Constructor
     */
    public notPossible(String message)
    {
        super(message);
    }
}