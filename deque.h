#pragma once
#include <iterator> 
#include <iostream>

template <typename T>
class Deque
{
private:
    T* deque;
    int capacity; //макс количество элементов в массиве
    int front_ind;
    int back_ind;
    int size;

    void resize() //изменение размера
    {
        int new_capacity = capacity * 2;
        T* new_deque = new T[new_capacity];
        for (int i = 0; i < size; i++)
        {
            new_deque[i] = deque[(front_ind + i) % capacity];
        }
        delete[] deque;
        deque = new_deque;
        front_ind = 0;
        back_ind = size;
        capacity = new_capacity;
    }

public:

    Deque()
    {
        capacity = 10;
        size = 0;
        front_ind = 0;
        back_ind = 0;
        deque = new T[capacity];
    }

    Deque(const Deque& other)
    {
        capacity = other.capacity;
        size = other.size;
        front_ind = other.front_ind;
        back_ind = other.back_ind;
        deque = new T[capacity];
        for (int i = 0; i < size; i++)
        {
            deque[i] = other.deque[i];
        }
    }


    ~Deque()
    {
        delete[] deque;
    }



    //методы
    void push_back(const T& val)
    {
        if (size == capacity)
        {
            resize();
        }
        deque[back_ind] = val;
        back_ind = (back_ind + 1) % capacity;
        size++;
    }

    void pop_back()
    {
        if (size > 0)
        {
            back_ind = (back_ind - 1 + capacity) % capacity;
            size--;
        }
    }

    void push_front(const T& val)
    {
        if (size == capacity)
        {
            resize();
        }
        front_ind = (front_ind - 1 + capacity) % capacity;
        deque[front_ind] = val;
        size++;
    }


    //доступ к i-му элементу в массиве
    T& operator[](int index)
    {
        return deque[(front_ind + index) % capacity];
    }

    const T& operator[](int index) const
    {
        return deque[(front_ind + index) % capacity];
    }



    // ¬озвращает ссылку на первый элемент в deque.
    T& front()
    {
        return deque[front_ind];
    }
    const T& front() const
    {
        return deque[front_ind];
    }


    // ¬озвращает ссылку на последний элемент в deque.
    T& back()
    {
        return deque[(back_ind - 1 + capacity) % capacity];
    }
    const T& back() const
    {
        return deque[(back_ind - 1 + capacity) % capacity];
    }


    // ¬озвращает true, если deque не содержит элементов, и false, если он содержит один или несколько элементов.
    bool empty() const
    {
        return (size == 0);
    }

    // ¬озвращает количество эдементов в deque.
    int get_size() const
    {
        return size;
    }




    //неконстантный итератор
    class Iterator : public std::iterator<std::random_access_iterator_tag, const T>
    {
    private:
        Deque* data;
        int index;

    public:
        Iterator(Deque* deque, int ind)
        {
            data = deque;
            index = ind;
        }


        T& operator*() //оператор разыменовани€(получить элемент по индексу)
        { 
            return (*data)[index];
        }


        // +
        Iterator& operator++()
        {
            index++;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        Iterator& operator+=(int n)
        {
            index += n;
            return *this;
        }

        Iterator operator+(int n)
        {
            Iterator tmp = *this;
            tmp += n;
            return tmp;
        }


        // -
        Iterator& operator--()
        {
            index--;
            return *this;
        }

        Iterator operator--(int)
        {
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        Iterator& operator-=(int n)
        {
            index -= n;
            return *this;
        }

        Iterator operator-(int n)
        {
            Iterator tmp = *this;
            tmp -= n;
            return tmp;
        }



        bool operator==(const Iterator& other) const
        {
            return index == other.index;
        }
        bool operator!=(const Iterator& other) const
        {
            return !(*this == other);
        }
        bool operator<(const Iterator& other)
        {
            return index < other.index;
        }
        bool operator>(const Iterator& other)
        {
            return index > other.index;
        }
        bool operator<=(const Iterator& other)
        {
            return index <= other.index;
        }
        bool operator>=(const Iterator& other)
        {
            return index >= other.index;
        }
    };



    //константный итератор
    class CONST_Iterator : public std::iterator<std::random_access_iterator_tag, const T>
    {
    private:
        const Deque* data;
        int index;

    public:
        CONST_Iterator(const Deque* deque, int ind)
        {
            data = deque;
            index = ind;
        }

        const T& operator*() const
        {
            return (*data)[index];
        }


        CONST_Iterator& operator++()
        {
            index++;
            return *this;
        }



        // +
        Iterator& operator++()
        {
            index++;
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator tmp = *this;
            (*this)++;
            return tmp;
        }
        Iterator& operator+=(int n)
        {
            index += n;
            return *this;
        }
        Iterator operator+(int n)
        {
            Iterator tmp = *this;
            tmp += n;
            return tmp;
        }



        //-
        Iterator& operator--()
        {
            index--;
            return *this;
        }
        Iterator operator--(int)
        {
            Iterator temp = *this;
            (*this)--;
            return temp;
        }
        Iterator& operator-=(int n)
        {
            index -= n;
            return *this;
        }
        Iterator operator-(int n)
        {
            Iterator tmp = *this;
            tmp -= n;
            return tmp;
        }


        
        bool operator==(const CONST_Iterator& other)
        {
            return index == other.index;
        }
        bool operator!=(const CONST_Iterator& other)
        {
            return !(*this == other);
        }
        bool operator<(const CONST_Iterator& other)
        {
            return index < other.index;
        }
        bool operator>(const CONST_Iterator& other)
        {
            return index > other.index;
        }
        bool operator<=(const CONST_Iterator& other)
        {
            return index <= other.index;
        }
        bool operator>=(const CONST_Iterator& other)
        {
            return index >= other.index;
        }
    };

    Iterator begin()
    {
        return Iterator(this, 0);
    }
    Iterator end()
    {
        return Iterator(this, size);
    }



    CONST_Iterator begin() const
    {
        return CONST_Iterator(this, 0);
    }
    CONST_Iterator cbegin() const
    {
        return CONST_Iterator(this, 0);
    }
    CONST_Iterator end() const
    {
        return CONST_Iterator(this, size);
    }
    CONST_Iterator cend() const
    {
        return CONST_Iterator(this, size);
    }

    //указывает на первый элемент в обратном deque.
    Iterator rbegin()
    {
        return Iterator(this, size - 1);
    }
    CONST_Iterator rbegin() const
    {
        return CONST_Iterator(this, size - 1);
    }
    CONST_Iterator crbegin() const
    {
        return CONST_Iterator(this, size - 1);
    }


    // указывает на расположение после последнего элемента в обратном deque.
    Iterator rend()
    {
        return Iterator(this, -1);
    }
    CONST_Iterator rend() const
    {
        return CONST_Iterator(this, -1);
    }
    CONST_Iterator crend() const
    {
        return CONST_Iterator(this, -1);
    }


};





