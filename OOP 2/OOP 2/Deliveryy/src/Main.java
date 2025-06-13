import java.time.LocalTime;
import java.util.*;

public class Main
{
    public static void main(String[] args)
    {
        Product product1 = new Product("Молоко 3,2%", 1, 66.0);
        Product product2 = new Product("Яйцо С0", 2, 73.0);
        Product product3 = new Product("Багет французский", 3, 108.0);
        Product product4 = new Product("Cheetos сыр", 4, 112.0);

        List<Integer> address1 = List.of(56, 89);
        User user1 = new User("Lisa", "+791111111", address1);
        System.out.println("Пользователь зарегистрирован: " + user1.getUsername());

        List<Integer> address2 = List.of(34, 72);
        User user2 = new User("John", "+792222222", address2);
        System.out.println("Пользователь зарегистрирован: " + user2.getUsername());

        Map<Product, Integer> stock = new HashMap<>();
        stock.put(product1, 5);
        stock.put(product2, 4);
        stock.put(product3, 8);
        stock.put(product4, 2);
        Storehouse storehouse = new Storehouse(stock);

        Map<Product, Integer> supplierInventory = new HashMap<>();
        supplierInventory.put(product1, 10);
        supplierInventory.put(product2, 10);
        supplierInventory.put(product3, 10);
        supplierInventory.put(product4, 10);
        Supplier supplier = new Supplier(supplierInventory);
        storehouse.setSupplier(supplier);

        storehouse.addEmployee(new Storekeeper(
                "Иван",
                LocalTime.of(10, 0),
                LocalTime.of(16, 0)));

        storehouse.addEmployee(new Storekeeper(
                "Мария",
                LocalTime.of(9, 0),
                LocalTime.of(18, 0)));

        storehouse.addEmployee(new Courier(
                "Петр",
                LocalTime.of(10, 0),
                LocalTime.of(18, 0)));

        storehouse.addEmployee(new Courier(
                "Анна",
                LocalTime.of(10, 0),
                LocalTime.of(19, 0)));

        System.out.println("_____ ОБРАБОТКА ЗАКАЗОВ _____");

        Order order1 = user1.createOrder(List.of(1, 1, 2, 3, 4));
        storehouse.processOrder(order1);

        Order order2 = user2.createOrder(List.of(2, 3, 4));
        storehouse.processOrder(order2);
        try
        {
            Thread.sleep(100);
        }
        catch (InterruptedException e)
        {
            Thread.currentThread().interrupt();
        }
    }
}