import java.time.LocalTime;

public abstract class Employee
{
    private final LocalTime Start;
    private final LocalTime End;
    private boolean occupation;
    private Order currOrder;
    private final String name;

    public Employee(String name, LocalTime Start, LocalTime End)
    {
        this.name = name;
        this.occupation = false;
        this.Start = Start;
        this.End = End;
    }

    public abstract void work(Order order, Storehouse storehouse);

    public String getRoleName()
    {
        if (this instanceof Courier)
        {
            return "Курьер";
        }
        if (this instanceof Storekeeper)
        {
            return "Сборщик";
        }
        return getClass().getSimpleName();
    }

    public double salary()
    {
        long secondsWorked = java.time.Duration.between(Start, End).getSeconds();
        double salary = (secondsWorked / 3600.0) * 300;
        System.out.printf("%s %s получил зарплату %.2f руб. за смену %s - %s\n",
                getRoleName(), name, salary, Start, End);
        return salary;
    }

    public boolean isAvailable()
    {
        return !occupation;
    }

    public void startWork(Order order)
    {
        this.occupation = true;
        this.currOrder = order;
    }

    public void finishWork()
    {
        this.occupation = false;
        this.currOrder = null;
    }

    public LocalTime getStart()
    {
        return Start;
    }

    public LocalTime getEnd()
    {
        return End;
    }

    public Order getCurrentOrder()
    {
        return currOrder;
    }

    public String getName()
    {
        return name;
    }
}