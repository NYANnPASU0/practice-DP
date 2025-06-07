import java.util.*;

public class Storehouse
{
    private Map<Product, Integer> stock;
    private Supplier supplier;
    private final List<Storekeeper> storekeepers = new ArrayList<>();
    private final List<Courier> couriers = new ArrayList<>();
    private final List<Order> pendingOrders = new ArrayList<>();
    private final List<Integer> location = Arrays.asList(50, 50);

    public Storehouse(Map<Product, Integer> stock)
    {
        this.stock = stock;
        System.out.println("Склад работает.");
    }

    public void setSupplier(Supplier supplier)
    {
        this.supplier = supplier;
        System.out.println("Поставщик назначен для склада.");
    }

    public void addEmployee(Employee employee)
    {
        if (employee instanceof Storekeeper)
        {
            storekeepers.add((Storekeeper) employee);
            System.out.println("Добавлен сборщик: " + employee.getName());
        }
        else if (employee instanceof Courier)
        {
            couriers.add((Courier) employee);
            System.out.println("Добавлен курьер: " + employee.getName());
        }
    }

    public void processOrder(Order order)
    {
        System.out.printf("Получен заказ #%d\n", order.getId());
        pendingOrders.add(order);
        processPendingOrders();
    }

    private void processPendingOrders()
    {
        for (Order order : new ArrayList<>(pendingOrders))
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
                    System.out.printf("  Товар с ID=%d не найден в каталоге\n", productId);
                }
            }

            int addedItems = 0;
            for (int i : actualItems.values())
            {
                addedItems += i;
            }

            int missingItemsCount = 0;
            for (int i : missingItems.values())
            {
                missingItemsCount += i;
            }

            System.out.printf("  В заказ #%d добавлено %d товаров\n", order.getId(), addedItems);
            if (missingItemsCount > 0)
            {
                System.out.printf("  Для заказа #%d не хватило %d товаров\n", order.getId(), missingItemsCount);
            }

            order.setActualItems(actualItems);
            order.setStatus(Order.Status.ASSEMBLING);

            if (!missingItems.isEmpty())
            {
                System.out.printf("Заказ недостающих товаров для заказа #%d: %s\n",
                        order.getId(), formatProductMap(missingItems));
                supplier.deliver(missingItems);
            }

            assignToStorekeeper(order);
            pendingOrders.remove(order);
        }
    }

    private void assignToStorekeeper(Order order)
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
        System.out.println("Нет доступных сборщиков для заказа #" + order.getId());
    }

    public void assignToCourier(Order order)
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
        System.out.println("Нет доступных курьеров для заказа #" + order.getId());
    }

    public void restock(Map<Product, Integer> items)
    {
        System.out.println("Пополнение запасов склада");
        for (Map.Entry<Product, Integer> entry : items.entrySet())
        {
            stock.put(entry.getKey(), stock.getOrDefault(entry.getKey(), 0) + entry.getValue());
        }
    }

    public Map<Product, Integer> getStock() {
        return stock;
    }

    private String formatProductMap(Map<Product, Integer> map) {
        StringBuilder sb = new StringBuilder("{");
        for (Map.Entry<Product, Integer> entry : map.entrySet()) {
            sb.append("ID=").append(entry.getKey().getID())
                    .append(": ").append(entry.getValue()).append(", ");
        }
        if (!map.isEmpty()) {
            sb.setLength(sb.length() - 2);
        }
        sb.append("}");
        return sb.toString();
    }
}