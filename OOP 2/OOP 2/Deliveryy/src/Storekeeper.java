import java.time.LocalTime;
import java.util.Map;

public class Storekeeper extends Employee
{
    public Storekeeper(String name, LocalTime Start, LocalTime End)
    {
        super(name, Start, End);
    }

    public void work(Order order, Storehouse storehouse)
    {
        startWork(order);
        int itemsCount = 0;
        for (int quantity : order.getActualItems().values())
        {
            itemsCount += quantity;
        }

        int allTime = itemsCount * 45;

        System.out.printf("Заказ #%d, время сборки: %d сек\n", order.getId(), allTime);

        try
        {
            for (int i = 0; i < allTime; i += 5)
            {
                Thread.sleep(45);
                if (i % 45 == 0 && i > 0)
                {
                    System.out.printf("Сборщик %s собирает заказ #%d... (%d из %d сек)\n",
                            getName(), order.getId(), i, allTime);
                }
            }
            System.out.printf("Сборщик %s закончил сборку заказа #%d\n", getName(), order.getId());
        }
        catch (InterruptedException e)
        {
            Thread.currentThread().interrupt();
        }

        finishWork();
        storehouse.freeCourier(order);
    }
}