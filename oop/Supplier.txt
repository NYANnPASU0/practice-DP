import java.util.*;

public class Supplier
{
    private final Map<Product, Integer> inventory;

    public Supplier(Map<Product, Integer> inventory)
    {
        this.inventory = inventory;
        System.out.println("Поставщик создан.");
    }

    public void deliver(Map<Product, Integer> requestedItems)
    {
        System.out.println("Поставщик получил запрос: " + formatProductMap(requestedItems));
        Map<Product, Integer> delivered = new HashMap<>();

        for (Map.Entry<Product, Integer> entry : requestedItems.entrySet())
        {
            Product product = entry.getKey();
            int available = inventory.getOrDefault(product, 0);
            int toDeliver = Math.min(available, entry.getValue());

            if (toDeliver > 0)
            {
                delivered.put(product, toDeliver);
                inventory.put(product, available - toDeliver);
            }
        }
        System.out.println("Поставщик доставил на склад: " + formatProductMap(delivered));
    }

    private String formatProductMap(Map<Product, Integer> map)
    {
        StringBuilder sb = new StringBuilder("{");
        for (Map.Entry<Product, Integer> entry : map.entrySet())
        {
            sb.append("ID=")
            .append(entry.getKey().getID())
            .append(": ")
            .append(entry.getValue())
            .append(", ");
        }
        if (!map.isEmpty())
        {
            sb.setLength(sb.length() - 2);
        }
        sb.append("}");
        return sb.toString();
    }
}