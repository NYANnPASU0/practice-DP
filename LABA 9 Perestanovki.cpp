#include <iostream>
#include <algorithm>

class Permutation
{
private:
    unsigned int* perm;
    unsigned int size;

public:
    Permutation(const unsigned int& n)
    {
        size = n;
        perm = new unsigned int[size];
        for (int i = 0; i < size; i++)
        {
            perm[i] = i + 1;
        }
    }

    Permutation(unsigned int n, unsigned int* A)
    {
        size = n;
        perm = new unsigned int[size];
        for (int i = 0; i < size; i++)
        {
            perm[i] = A[i];
        }
    }

    Permutation operator * (const Permutation& other) const
    {
        unsigned int* result_perm = new unsigned int[size];
        if (size == other.size)
        {
            for (int i = 0; i < size; i++)
            {
                result_perm[i] = perm[other.perm[i] - 1];
            }
        }
        else
        {
            std::cout << "Different sizes of permutations A and B" << std::endl;
            exit(1);
        }
        Permutation result(size, result_perm);
        return result;
    }

    ~Permutation()
    {
        delete[] perm;
    }

    Permutation& operator++()
    {
        for (int i = 0; i < size; i++)
        {
            ++perm[i];
        }
        return *this;
    }

    Permutation operator++(int)
    {
        Permutation temp(*this);
        ++(*this);
        return temp;
    }


    Permutation& operator--()
    {
        for (int i = 0; i < size; i++)
        {
            --perm[i];
        }
        return *this;
    }


    Permutation operator--(int)
    {
        Permutation temp(*this);
        --(*this);
        return temp;
    }

    friend bool operator==(const Permutation& first, const Permutation& second)
    {
        if (first.size == second.size)
        {
            for (int i = 0; i < first.size; i++)
            {
                if (first.perm[i] != second.perm[i])
                {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    friend bool operator!=(const Permutation& first, const Permutation& second)
    {
        return !(first == second);
    }

    friend bool operator>(const Permutation& first, const Permutation& second)
    {
        if(first.size == second.size)
        {
            for (int i = 0; i < first.size; i++)
            {
                if (first.perm[i] < second.perm[i])
                {
                    return false;
                }
                else if (first.perm[i] > second.perm[i])
                {
                    return true;
                }
            } 
            return false;
        }
        return false;
    }

    friend bool operator<(const Permutation& first, const Permutation& second)
    {
        return (first != second) && !(first > second);
    }

    friend bool operator<=(const Permutation& first, const Permutation& second)
    {
        return (first < second) || (first == second);
    }

    friend bool operator>=(const Permutation& first, const Permutation& second)
    {
        return (first > second) || (first == second);

    }

    void next()
    {
        int max_i = -1;
        for (int i = size - 2; i >= 0; i--)
        {
            if (perm[i] < perm[i + 1])
            {
                max_i = i;
                break;
            }
        }
        if (max_i == -1)
        {
            std::reverse(perm, perm + size);
        }
        else
        {
            int max_j = -1;//указывает на самый правый элемент, значение которого больше значения элемента с индексом max_i
            for (int i = size - 1; i > max_i; i--)
            {
                if (perm[i] > perm[max_i])
                {
                    max_j = i;
                    break;
                }
            }
            std::swap(perm[max_i], perm[max_j]);
            std::reverse(perm + max_i + 1, perm + size);
        }
    }


    void previous()
    {
        int max_i = -1;
        for (int i = size - 2; i >= 0; i--)
        {
            if (perm[i] > perm[i + 1])
            {
                max_i = i;
                break;
            }
        }
        if (max_i == -1)
        {
            std::reverse(perm, perm + size);
        }
        else
        {
            int max_j = -1;//указывает на самый правый элемент, значение которого меньше значения элемента с индексом max_i
            for (int i = size - 1; i > max_i; i--)
            {
                if (perm[i] < perm[max_i])
                {
                    max_j = i;
                    break;
                }
            }
            std::swap(perm[max_i], perm[max_j]);
            std::reverse(perm + max_i + 1, perm + size);
        }
    }


   void print()
   {
       for (int i = 1; i <= size; i++)
       {
           std::cout << i << ' ';
       }
       std::cout << std::endl;
       for (int i = 0; i < size; i++)
       {
           std::cout << perm[i] << ' ';
       }
   }

};

int main()
{
    setlocale(LC_ALL, "Russian");

    unsigned int n_a, n_b, ai, bi;

    //________________________________________________________________
    std::cout << "Введите количество элементов в перестановке A: ";
    std::cin >> n_a;
    std::cout << std::endl;

    unsigned int* A = new unsigned int[n_a];

    std::cout << "Введите элементы перестановки A: " << std::endl;
    for (int i = 0; i < n_a; i++)
    {
        std::cin >> ai;
        A[i] = ai;
    }
    std::cout << std::endl;
    

    //_______________________________________________________________
    std::cout << "Введите количество элементов в перестановке B: ";
    std::cin >> n_b;
    std::cout << std::endl;

    unsigned int* B = new unsigned int[n_b];
    std::cout << "Введите элементы перестановки B : " << std::endl;
    for (int i = 0; i < n_b; i++)
    {
        std::cin >> bi;
        B[i] = bi;
    }
    std::cout << std::endl;


    //________________________________________________________________
    std::cout << std::endl << "Перестановка A: " << std::endl;
    Permutation permA(n_a, A);
    permA.print();
    std::cout << std::endl;

    std::cout << std::endl << "Перестановка B: " << std::endl;
    Permutation permB(n_b, B);
    permB.print();
    std::cout << std::endl;


    //----------------------------------------------------------------
    if (permA == permB) std::cout << std::endl << "A = B" << std::endl;
    if (permA > permB) std::cout << std::endl << "A > B" << std::endl;
    if (permA < permB) std::cout << std::endl << "A < B" << std::endl;


    //________________________________________________________________
    std::cout << std::endl << "A * B: " << std::endl;
    Permutation C = permA * permB;
    C.print();
    std::cout << std::endl;


    //________________________________________________________________
    std::cout << std::endl << "Cледующая перестановка A: " << std::endl;
    permA.next();
    permA.print();
    std::cout << std::endl;


    //________________________________________________________________
    std::cout << std::endl << "Предыдущая перестановка B: " << std::endl;
    permB.previous();
    permB.print();
    std::cout << std::endl;


    //----------------------------------------------------------------
    std::cout << std::endl << "++A: " << std::endl;
    ++permA;
    permA.print();
    std::cout << std::endl;


    //----------------------------------------------------------------
    std::cout << std::endl << "--B: " << std::endl;
    --permB;
    permB.print();
    std::cout << std::endl;

    delete[] A;
    delete[] B;
}
