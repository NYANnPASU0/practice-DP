template <int N>

class Finite
{
    int value;

public:

    Finite(int value_)
    {
        value = value_ % N;
    }

    Finite operator+(const Finite& other) const
    {
        return Finite(value + other.value);
    }

    Finite operator-(const Finite& other) const
    {
        return Finite(value - other.value);
    }

    Finite operator*(const Finite& other) const
    {
        return Finite(value * other.value);
    }


    Finite operator/(const Finite& other) const
    {
        return Finite(value / other.value);
    }


    bool operator==(const Finite& other) const
    {
        return value == other.value;
    }

    bool operator!=(const Finite& other) const
    {
        return value != other.value;
    }

    bool operator >(const Finite& other) const
    {
        return value > other.value;
    }

    bool operator <(const Finite& other) const
    {
        return value <  other.value;
    }


    int get() const
    {
        return value;
    }

    void print() const { std::cout << value << std::endl; }
};

#pragma once
