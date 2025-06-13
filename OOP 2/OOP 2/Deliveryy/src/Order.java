import java.util.*;

public class Order
{
    public enum Status { PENDING, ASSEMBLING, DELIVERING, DELIVERED }

    private static int orderId = 1;
    private final int id;
    private final List<Integer> orderCart;
    private Status status;
    private final List<Integer> userAddress;
    private Map<Product, Integer> actualItems = new HashMap<>();

    public Order(List<Integer> orderCart, List<Integer> userAddress)
    {
        this.id = orderId++;
        this.orderCart = orderCart;
        this.status = Status.PENDING;
        this.userAddress = userAddress;
        System.out.printf("Создан заказ #%d: %s\n", id, orderCart);
    }

    public void setActualItems(Map<Product, Integer> items)
    {
        this.actualItems = items;
    }

    public Map<Product, Integer> getActualItems()
    {
        return actualItems;
    }

    public void setStatus(Status status)
    {
        this.status = status;
    }

    public Status getStatus()
    {
        return status;
    }

    public List<Integer> getOrderCart()
    {
        return orderCart;
    }

    public List<Integer> getUserAddress()
    {
        return userAddress;
    }

    public int getId()
    {
        return id;
    }

}