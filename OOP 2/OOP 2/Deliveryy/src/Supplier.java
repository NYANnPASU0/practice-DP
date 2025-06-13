import java.util.*;

public class Supplier
{
    private final Map<Product, Integer> inventory;

    public Supplier(Map<Product, Integer> inventory)
    {
        this.inventory = inventory;
    }

    public void deliver(Map<Product, Integer> requestItems)
    {
        System.out.println("Поставщик получил запрос за пополнение склада ");
        Map<Product, Integer> delivered = new HashMap<>();

        Map.Entry<Product, Integer>[] entries = requestItems.entrySet().toArray(new Map.Entry[0]);
        for (int i = 0; i < entries.length; i++)
        {
            Map.Entry<Product, Integer> entry = entries[i];
            Product product = entry.getKey();
            int available = inventory.getOrDefault(product, 0);
            int deliver = Math.min(available, entry.getValue());

            if (deliver > 0)
            {
                delivered.put(product, deliver);
                inventory.put(product, available - deliver);
            }
        }
        System.out.println("Поставщик доставил на склад: " + output(delivered));
    }

    private String output(Map<Product, Integer> map)
    {
        StringJoiner sj = new StringJoiner(", ", "{", "}");
        map.forEach((product, quantity) ->
                sj.add("ID=" + product.getID() + ": " + quantity));
        return sj.toString();
    }
}