#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

int main()
{
    srand(time(0));
    std::ofstream out("input.txt");
    int n, q;
    n = rand() * rand() % 100000;
    q = rand() * rand() % 100000;
    out << n << std::endl;
    std::vector<int> a(n);
    std::vector<int> b(q);
    for (int i = 0; i < n; i++)
    {
        a[i] = rand() * rand() % 10000000;
        out << a[i] << std::endl;
    }
    out << q << std::endl;
    for (int i = 0; i < q; i++)
    {
        b[i] = rand() * rand() % 10000000;
        out << b[i] << std::endl;
    }
}