public class Product
{
    private String name;
    private int ID;
    private double price;

    public Product(String name, int ID, double price)
    {
        this.name = name;
        this.ID = ID;
        this.price = price;
    }

    public double getPrice()
    {
        return price;
    }

    public int getID()
    {
        return ID;
    }

    public String getName()
    {
        return name;
    }
}