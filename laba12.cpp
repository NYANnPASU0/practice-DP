#include <iostream>
#include "deque.h"

int main()
{
    setlocale(LC_ALL, "ru");

    Deque<int> deque;
    deque.push_back(1);
    deque.push_back(2);
    deque.push_back(3);
    deque.push_back(4);
    deque.push_back(5);

    std::cout << "Добавили все элементы в конец: " << std::endl;
    for (Deque<int>::Iterator it = deque.begin(); it != deque.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;;

    std::cout << "Текущий размер: ";
    std::cout << deque.get_size();
    std::cout << std::endl << std::endl;

    std::cout << "Добавили 0 в начало: ";
    std::cout << std::endl;
    deque.push_front(0);

    for (auto it = deque.begin(); it != deque.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Текущий размер: ";
    std::cout << deque.get_size();
    std::cout << std::endl << std::endl;

    std::cout << "Удалим 3 элементa начиня с конца: " << std::endl;
    deque.pop_back();
    deque.pop_back();
    deque.pop_back();

    for (auto it = deque.begin(); it != deque.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Текущий размер: ";
    std::cout << deque.get_size();
    std::cout << std::endl << std::endl;
    return 0;
}