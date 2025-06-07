import java.time.LocalTime;

public abstract class Employee
{
    private final LocalTime Start;
    private final LocalTime End;
    private boolean isWorking;
    private Order currentOrder;
    private final String name;

    public Employee(String name, LocalTime Start, LocalTime End)
    {
        this.name = name;
        this.Start = Start;
        this.End = End;
        this.isWorking = false;
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
        return !isWorking;
    }

    public void startWork(Order order)
    {
        this.isWorking = true;
        this.currentOrder = order;
    }

    public void finishWork()
    {
        this.isWorking = false;
        this.currentOrder = null;
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
        return currentOrder;
    }

    public String getName()
    {
        return name;
    }
}