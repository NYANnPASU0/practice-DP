import java.time.LocalTime;
import java.util.List;

public class Courier extends Employee
{
    public Courier(String name, LocalTime shiftStart, LocalTime shiftEnd)
    {
        super(name, shiftStart, shiftEnd);
    }

    public void work(Order order, Storehouse storehouse)
    {
        startWork(order);
        List<Integer> storehouseAddress = List.of(50, 50);
        List<Integer> userAddress = order.getUserAddress();

        double distance = Math.sqrt(
                Math.pow(userAddress.get(0) - storehouseAddress.get(0), 2) +
                        Math.pow(userAddress.get(1) - storehouseAddress.get(1), 2));

        int deliveryTime = 60 + (int)(distance * 30) + 60;
        int returnTime = (int)(distance * 30);

        System.out.printf("Курьер %s начал доставку заказа #%d\n", getName(), order.getId());
        System.out.printf("Расстояние до клиента: %.2f у.е., ( %d сек)\n ", distance, deliveryTime);

        try
        {
            System.out.printf("Курьер %s готовится к выходу (заказ #%d)...\n",
                    getName(), order.getId());
            Thread.sleep(500);

            System.out.printf("Курьер %s в пути (%d сек)...\n",
                    getName(), (int)(distance * 30));
            Thread.sleep((long)(distance * 250));

            System.out.printf("Курьер %s доставляет товар клиенту (заказ #%d)...\n",
                    getName(), order.getId());
            Thread.sleep(500);

            order.setStatus(Order.Status.DELIVERED);
            System.out.printf("Заказ #%d доставлен\n", order.getId());

            System.out.printf("Курьер %s возвращается на склад после доставки заказа #%d (%d сек)...\n",
                    getName(), order.getId(), returnTime);
            Thread.sleep((long)(distance * 250));

            System.out.printf("Курьер %s вернулся на склад\n", getName());
        }
        catch (InterruptedException e)
        {
            Thread.currentThread().interrupt();
        }

        finishWork();
        salary();
    }
}