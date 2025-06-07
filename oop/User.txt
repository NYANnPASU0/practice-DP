import java.util.List;

public class User
{
    private String username;
    private String phone;
    private List<Integer> address;

    public User(String username, String phone, List<Integer> address)
    {
        this.username = username;
        this.phone = phone;
        this.address = address;
    }

    public List<Integer> getAddress()
    {
        return address;
    }

    public String getPhone()
    {
        return phone;
    }

    public String getUsername()
    {
        return username;
    }

    public Order createOrder(List<Integer> productIDs)
    {
        System.out.printf("Пользователь %s создает заказ: %s\n", username, productIDs);
        return new Order(productIDs, address);
    }
}