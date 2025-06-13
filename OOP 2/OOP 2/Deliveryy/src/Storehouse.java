import java.util.*;

public class Storehouse
{
    private Map<Product, Integer> stock;
    private Supplier supplier;
    private final List<Storekeeper> storekeepers = new ArrayList<>();
    private final List<Courier> couriers = new ArrayList<>();
    private final List<Order> acceptingOrders = new ArrayList<>();
    private final List<Integer> location = Arrays.asList(50, 50);

    public Storehouse(Map<Product, Integer> stock)
    {
        this.stock = stock;
    }

    public void setSupplier(Supplier supplier)
    {
        this.supplier = supplier;
        System.out.println("Поставщик назначен.");
    }

    public void addEmployee(Employee employee)
    {
        if (employee instanceof Storekeeper)
        {
            storekeepers.add((Storekeeper) employee);
            System.out.println("Назначен сборщик: " + employee.getName());
        }
        else if (employee instanceof Courier)
        {
            couriers.add((Courier) employee);
            System.out.println("Назначен курьер: " + employee.getName());
        }
    }

    public void processOrder(Order order)
    {
        System.out.printf("Получен заказ #%d\n", order.getId());
        acceptingOrders.add(order);
        processPendingOrders();
    }

    private void processPendingOrders()
    {
        for (Order order : new ArrayList<>(acceptingOrders))
        {
            System.out.printf("Обработка заказа #%d\n", order.getId());

            Map<Product, Integer> actualItems = new HashMap<>();
            Map<Product, Integer> missingItems = new HashMap<>();

            for (int productId : order.getOrderCart())
            {
                boolean found = false;
                for (Product product : stock.keySet())
                {
                    if (product.getID() == productId)
                    {
                        found = true;
                        int available = stock.getOrDefault(product, 0);
                        if (available > 0)
                        {
                            actualItems.put(product, actualItems.getOrDefault(product, 0) + 1);
                            stock.put(product, available - 1);
                        }
                        else
                        {
                            missingItems.put(product, missingItems.getOrDefault(product, 0) + 1);
                        }
                        break;
                    }
                }
                if (!found)
                {
                    System.out.printf("  Товар с ID=%d не найден \n", productId);
                }
            }

            int addedItems = 0;
            Integer[] actual1 = actualItems.values().toArray(new Integer[0]);
            for (int i = 0; i < actual1.length; i++)
            {
                addedItems += actual1[i];
            }

            int missingItemsCount = 0;
            Integer[] actual2 = missingItems.values().toArray(new Integer[0]);
            for (int i = 0; i < actual2.length; i++)
            {
                missingItemsCount += actual2[i];
            }

            if (missingItemsCount > 0)
            {
                System.out.printf("  Для заказа #%d не хватило %d товаров\n", order.getId(), missingItemsCount);
            }

            order.setActualItems(actualItems);
            order.setStatus(Order.Status.ASSEMBLING);

            if (!missingItems.isEmpty())
            {
                System.out.printf("Заказ недостающих товаров для заказа #%d: \n",
                        order.getId());
                supplier.deliver(missingItems);
            }

            freeStorekeepers(order);
            acceptingOrders.remove(order);
        }
    }

    private void freeStorekeepers(Order order)
    {
        for (Storekeeper storekeeper : storekeepers)
        {
            if (storekeeper.isAvailable())
            {
                System.out.printf("Заказ #%d назначен сборщику %s\n",
                        order.getId(), storekeeper.getName());
                new Thread(() -> storekeeper.work(order, this)).start();
                return;
            }
        }
        System.out.println("Нет свободных сборщиков для заказа #" + order.getId());
    }

    public void freeCourier(Order order)
    {
        for (Courier courier : couriers)
        {
            if (courier.isAvailable())
            {
                order.setStatus(Order.Status.DELIVERING);
                System.out.printf("Заказ #%d назначен курьеру %s\n",
                        order.getId(), courier.getName());
                new Thread(() -> courier.work(order, this)).start();
                return;
            }
        }
        System.out.println("Нет свободных курьеров для заказа #" + order.getId());
    }

    public void restock(Map<Product, Integer> items)
    {
        System.out.println("Пополнение запасов склада");
        for (Map.Entry<Product, Integer> entry : items.entrySet())
        {
            stock.put(entry.getKey(), stock.getOrDefault(entry.getKey(), 0) + entry.getValue());
        }
    }

    public Map<Product, Integer> getStock()
    {
        return stock;
    }

}