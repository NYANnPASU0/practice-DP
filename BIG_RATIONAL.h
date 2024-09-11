#pragma once
#include "BIG_INTEGER.h"
#include <fstream>
#include <iostream>
#include <string>

class BigRational
{
private:

	BigInteger A = 0;
	BigInteger B = 1;

public:
	BigRational() = default;

	BigRational(BigInteger num)
	{
		this->A = num;
		this->B = 1;
	}

	BigRational(BigInteger num, BigInteger denom)
	{
		this->A = num;
		this->B = denom;
	}


	BigRational(const double a)
	{
		std::string s = std::to_string(a);
		BigRational br = s;
		*this = br;
	}

	BigRational(const int a)
	{
		std::string s = std::to_string(a);
		BigRational br = s;
		*this = br;
	}

	BigRational(std::string a)
	{
		int it = 0;
		for (int i = 0; i < a.size(); i++)
		{
			if (a[i] == '.' || a[i] == ',')
			{
				for (int j = 0; j < a.size() - 1 - i; j++)
				{
					B *= 10;
				}
				a.erase(i, 1);
				break;
			}
		}
		A = a;
	}

	~BigRational() = default;



	std::string toString() const
	{
		std::string str = A.toString();
		if (B != 1)
		{
			str += '/' + B.toString();
		}
		return str;
	}


	std::string asDecimal(size_t precision = 0)
	{
		for (int i = 0; i < precision; i++)
		{
			A *= 10;
		}
		std::string str = (A / B).toString();
		std::string str2;
		int it = 0;
		if (str.size() <= precision)
		{
			str2 += '0';
		}
		else
		{
			for (int i = 0; i < str.size() - precision; i++)
			{
				str2 += str[i];
			}
			it = str.size() - precision;
		}
		if (precision != 0)
		{
			str2 += '.';
		}
		if (str.size() < precision)
		{
			for (int i = 0; i < precision - str.size(); i++)
			{
				str2 += '0';
			}
		}
		for (int i = it; i < str.size(); i++)
			str2 += str[i];

		return str2;
	}


	// јрифметическ операции 
	// = 
	BigRational& operator=(const BigRational& other)
	{
		A = other.A;
		B = other.B;
		return *this;
	}

	BigRational& operator=(const int& other)
	{
		BigRational с = other;
		*this = с;
		return *this;
	}

	BigRational& operator=(const double& other)
	{
		BigRational с = other;
		*this = с;
		return *this;
	}


	// += 
	BigRational operator+=(BigRational& other)
	{
		this->A = this->A * other.B + B * other.A;
		this->B = this->B * other.B;

		return *this;
	}
	BigRational operator+=(const int& other)
	{
		BigRational tmp(other);
		this->A = this->A * tmp.B + B * tmp.A;
		this->B = this->B * tmp.B;

		return *this;
	}



	// +
	BigRational operator+(const BigRational& other) const
	{
		BigRational result;
		result.A = (A * other.B) + (other.A * B);
		result.B = other.B * B;

		return result;
	}
	BigRational operator+(const int& a)
	{
		BigRational one(a);
		return *this + one;
	}



	// -=
	BigRational operator-=(BigRational& other)
	{
		A = (A * other.B) - (other.A * B);
		B = other.B * B;

		return *this;
	}
	BigRational& operator-=(const int& other)
	{
		BigRational tmp(other);
		A = (A * tmp.B) - (tmp.A * B);
		B = tmp.B * B;
		return *this;
	}





	// -
	BigRational operator-(const BigRational& other) const
	{
		BigRational result;
		result.A = (A * other.B) - (other.A * B);
		result.B = other.B * B;

		return result;
	}
	BigRational operator-(const int& a)
	{
		BigRational one(a);
		return *this - one;
	}





	//унарный минус
	BigRational operator-() const
	{
		BigRational result = *this;
		return BigRational(-result.A, result.B);
	}


	//// ++
	BigRational& operator++()
	{
		BigRational one(1);
		*this += one;
		return *this;
	}

	BigRational operator++(int)
	{
		BigRational cop = *this;
		++*this;
		return cop;
	}



	// --
	BigRational& operator--()
	{
		*this -= 1;
		return *this;
	}

	BigRational operator--(int)
	{
		BigRational cop = *this;
		--*this;
		return cop;
	}



	// *= 
	BigRational operator*=(BigRational& other)
	{
		A = A * other.A;
		B = other.B * B;
		return *this;
	}
	BigRational operator*=(const int& other)
	{
		BigRational tmp(other);
		A = A * tmp.A;
		B = tmp.B * B;
		return *this;
	}




	// *
	BigRational operator*(const BigRational& other) const
	{
		BigRational result;
		result.A = A * other.A;
		result.B = other.B * B;
		return result;
	}
	BigRational operator*(const int& a) const
	{
		BigRational one(a);
		return *this * one;
	}


	// /=
	BigRational operator/=(BigRational& other)
	{
		A = (A * other.B);
		B = other.A * B;
		return *this;
	}
	BigRational operator/=(const int& other)
	{
		BigRational tmp(other);
		A = (A * tmp.B);
		B = tmp.A * B;
		return *this;
	}



	// /
	BigRational operator/(const BigRational& other) const
	{
		BigRational result;
		result.A = (A * other.B);
		result.B = other.A * B;

		return result;
	}
	BigRational operator/(const int& a)
	{
		BigRational one(a);
		return *this / one;
	}



	BigInteger NOK(BigInteger& a, BigInteger& b) const
	{
		BigInteger maximum;
		if (a >= b)
		{
			maximum = a;
		}
		else
		{
			maximum = b;
		}
		BigInteger null(0);
		BigInteger maxx(101);
		for (BigInteger i = maximum; i < maxx; i++)
		{
			if (i % a == null && i % b == null)
			{
				return i;
				break;
			}
		}
	}



	//cравнение
	// <
	bool operator<(const BigRational& a)const
	{
		BigInteger null(0);
		BigInteger A_(A);
		BigInteger a_A(a.A);
		BigInteger B_(B);
		BigInteger a_B(a.B);
		if (B == null || a.B == 0)
		{
			throw std::invalid_argument("Denominator cannot be zero.");
		}
		if (A_ < null && a_A > null)
		{
			return true;
		}
		if (A_ > null && a_A < null)
		{
			return false;
		}
		BigInteger our_denominator(NOK(B_, a_B));
		BigInteger left = A * (our_denominator / B);
		BigInteger right = a.A * (our_denominator / a.B);

		return left < right;
	}



	//// >
	bool operator>(const BigRational& a) const
	{
		return a < *this;
	}
	bool operator>(const int& a) const
	{
		BigRational bi = a;
		return *this > bi;
	}
	bool operator>(const double& a) const
	{
		BigRational bi = a;
		return *this > bi;
	}



	// <=
	bool operator<=(const BigRational& a) const
	{
		return !(*this > a);
	}
	bool operator<=(const int& a) const
	{
		return !(*this > a);
	}
	bool operator<=(const double& a) const
	{
		return !(*this > a);
	}




	// >=
	bool operator>=(const BigRational& a) const
	{
		return !(*this < a);
	}
	bool operator>=(const int& a) const
	{
		return !(*this < a);
	}
	bool operator>=(const double& a) const
	{
		return !(*this < a);
	}




	// !=
	bool operator!=(const BigRational& a) const
	{
		return (*this > a) || (*this < a);
	}
	bool operator!=(const int& a) const
	{
		return (*this > a) || (*this < a);
	}
	bool operator!=(const double& a) const
	{
		return (*this > a) || (*this < a);
	}




	// ==
	bool operator==(const BigRational& a) const
	{
		return !(*this != a);
	}
	bool operator==(const int& a) const
	{
		return !(*this != a);
	}
	bool operator==(const double& a) const
	{
		return !(*this != a);
	}

	///////////// ¬вод и вывод
	friend std::istream& operator>>(std::istream& is, BigRational& s) {
		std::string str;
		is >> str;
		return is;
	}

	friend std::ostream& operator<<(std::ostream& out, BigRational& b_int) {
		std::string num = b_int.toString();
		out << num;
		return out;
	}

};