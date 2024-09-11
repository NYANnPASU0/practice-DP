#include <iostream>
#include <vector>
#include <string>
#include <fstream>


class BigInteger
{
private:
	std::vector<int> numbers;

public:

	int sgn = 1;

	std::vector<int> getNumbers() { return numbers; }
	int getNumbersSize() { return numbers.size(); }
	int getNumberByIndex(int n) { return numbers[n]; }
	int getSgn() { return sgn; }
	void setSgn(int n) { sgn = n; }
	void setNumbersSize(int n) { numbers.resize(n); }

	BigInteger() { numbers = { 0 }; sgn = 1; }


	BigInteger(const std::string& str)
	{
		if (str[0] == '-')
		{
			sgn = -1;
		}
		else
		{
			sgn = 1;
		}
		numbers.clear();
		for (int i = str.size() - 1; i >= 0; i--)
		{
			if ('0' <= str[i] && str[i] <= '9')
			{
				numbers.push_back(str[i] - '0');
			}
		}
	}


	BigInteger(const BigInteger& number) 
	{
		sgn = number.sgn;
		numbers.resize(number.numbers.size());
		for (int i = 0; i < number.numbers.size(); i++)
			numbers[i] = number.numbers[i];
	}

	BigInteger(const int& num)
	{
		if (num < 0)
		{
			sgn = -1;
		}
		else
		{
			sgn = 1;
		}
		int copy = num;
		while (copy)
		{
			numbers.push_back(std::abs(copy) % 10);
			copy /= 10;
		}
	}

	BigInteger NOD( BigInteger& b) const {
		BigInteger a = *this;
		BigInteger null(0);
		if (a < null) a = -a;
		if (b < null) b = -b;

		while (a != null && b != null) {
			if (a < b)
				b = b % a; // Убедитесь, что оператор % работает
			else
				a = a % b;
		}
		return (a != null) ? a : b;
	}

	~BigInteger()
	{
		numbers.clear();
	}

	// Удаляем незначащие нули и восстанавливаем знак, если число 0.
	void del_0()
	{
		while (numbers[numbers.size() - 1] == 0 && numbers.size() > 1)
			numbers.resize(numbers.size() - 1);
		if (numbers.size() == 1 && numbers[0] == 0)
			sgn = 1;
		return;
	}


	operator bool()
	{
		if (numbers.size() == 1 && numbers[0] == 0)
		{
			return false;
		}
		else return true;
	}

	bool operator> (const BigInteger& other)
	{
		if (sgn * other.sgn == -1)
		{
			if (sgn == 1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (sgn * other.sgn == 1)
		{
			if (sgn == 1)
			{
				if (numbers.size() > other.numbers.size())
				{
					return true;
				}
				else if (numbers.size() < other.numbers.size())
				{
					return false;
				}
				else if (numbers.size() == other.numbers.size())
				{
					for (int i = numbers.size() - 1; i >= 0; i--)
					{
						if (numbers[i] > other.numbers[i])
						{
							return true;
						}
						else if (numbers[i] < other.numbers[i])
						{
							return false;
						}
					}
				}
			}
			if (sgn == -1)
			{
				if (numbers.size() < other.numbers.size())
				{
					return true;
				}
				else if (numbers.size() > other.numbers.size())
				{
					return false;
				}
				else if (numbers.size() == other.numbers.size())
				{
					for (int i = numbers.size() - 1; i >= 0; i--)
					{
						if (numbers[i] < other.numbers[i])
						{
							return true;
						}
						else if (numbers[i] > other.numbers[i])
						{
							return false;
						}
					}
				}
			}
		}
	}

	bool operator < (const BigInteger& other)
	{
		return !(*this > other || *this == other);
	}

	bool operator==(const BigInteger& other) const
	{
		if (numbers == other.numbers && sgn == other.sgn)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator<=(const BigInteger& number)
	{
		return (*this < number || *this == number);
	}

	bool operator>=(const BigInteger& number)
	{
		return (*this > number || *this == number);
	}

	bool operator!=(const BigInteger& number)
	{
		if (numbers != number.numbers || sgn != number.sgn)
		{
			return true;
		}
		else return false;
	}


	bool operator!=(const int& a) const
	{
		return !(*this == a);
	}

	BigInteger Min(const BigInteger& second)
	{
		BigInteger res(*this);
		int first_size = numbers.size();
		int sec_size = second.numbers.size();
		for (int i = 0; i < sec_size; i++)
		{
			if (res.numbers[i] < second.numbers[i])
			{
				res.numbers[i] = res.numbers[i] + 10 - second.numbers[i];
				int j = i + 1;
				while (res.numbers[j] == 0)
				{
					res.numbers[j] = 9;
					j++;
				}
				res.numbers[j]--;
			}
			else
			{
				res.numbers[i] -= second.numbers[i];
			}
		}
		return res;
	}

	BigInteger Sum(const BigInteger& second)
	{
		BigInteger res(*this);
		int first_size = numbers.size();
		int sec_size = second.numbers.size();
		for (int i = 0; i < sec_size; i++)
		{
			if (i < first_size)
			{
				res.numbers[i] += second.numbers[i];
			}
			else
			{
				res.numbers.push_back(second.numbers[i]);
			}
			if (res.numbers[i] >= 10)
			{
				res.numbers[i] -= 10;
				if (i + 1 < res.numbers.size())
				{
					res.numbers[i + 1]++;
				}
				else
				{
					res.numbers.push_back(1);
				}
			}
		}
		return res;
	}

	BigInteger abs() const
	{
		BigInteger res = *this;
		res.sgn = 1;
		return res;
	}


	// Стандартные операторы.
	BigInteger operator+(const BigInteger& other) const
	{
		BigInteger result, copy_first, copy_sec;
		copy_first = *this;
		copy_first.sgn = 1;
		copy_sec = other;
		copy_sec.sgn = 1;
		result.numbers.resize(std::max(numbers.size(), other.numbers.size()) + 1);
		int first_size = numbers.size();
		int sec_size = other.numbers.size();

		if (sgn == other.sgn)
		{
			for (int i = 0; i < std::min(first_size, sec_size); i++)
			{
				result.numbers[i] += numbers[i] + other.numbers[i];
				result.numbers[i + 1] += result.numbers[i] / 10;
				result.numbers[i] %= 10;
			}
			if (first_size < sec_size)
			{
				for (int i = first_size; i < sec_size; i++)
				{
					result.numbers[i] += other.numbers[i];
					result.numbers[i + 1] += result.numbers[i] / 10;
					result.numbers[i] %= 10;
				}
			}
			else if (first_size > sec_size)
			{
				for (int i = sec_size; i < first_size; i++)
				{
					result.numbers[i] += numbers[i];
					result.numbers[i + 1] += result.numbers[i] / 10;
					result.numbers[i] %= 10;
				}
			}
			result.sgn = sgn;
			result.del_0();
			return result;
		}
		if (sgn != other.sgn)
		{
			if (copy_first > copy_sec)
			{
				for (int i = 0; i < sec_size; i++)
				{
					result.numbers[i] += numbers[i] - other.numbers[i];
					if (result.numbers[i] < 0)
					{
						result.numbers[i + 1]--;
						result.numbers[i] += 10;
					}
				}
				for (int i = sec_size; i < first_size; i++)
				{
					if (result.numbers[i] < 0)
					{
						result.numbers[i + 1]--;
						result.numbers[i] += 10;
					}
					result.numbers[i] += numbers[i];
					result.numbers[i + 1] += result.numbers[i] / 10;
					result.numbers[i] %= 10;
				}
				result.sgn = sgn;
				result.del_0();
				return result;
			}
			if (copy_first < copy_sec)
			{
				for (int i = sec_size; i < first_size; i++)
				{
					result.numbers[i] += -numbers[i] + other.numbers[i];
					if (result.numbers[i] < 0)
					{
						result.numbers[i + 1]--;
						result.numbers[i] += 10;
					}
				}
				for (int i = first_size; i < sec_size; i++)
				{
					result.numbers[i] += other.numbers[i];
					result.numbers[i + 1] += result.numbers[i] / 10;
					result.numbers[i] %= 10;
				}
				result.sgn = sgn;
				result.del_0();
				return result;
			}
			if (copy_first == copy_sec)
			{
				result = BigInteger("0");
				return result;
			}
		}
	}

	BigInteger operator-(const BigInteger& other) const
	{
		BigInteger first_num(*this);
		BigInteger sec_num(other);
		BigInteger result;
		if (sgn == other.sgn)
		{
			if (first_num.abs() >= sec_num.abs())
			{
				result = first_num.Min(sec_num);
				result.sgn = sgn;
				result.del_0();
				return result;
			}
			else
			{
				result = sec_num.Min(first_num);
				result.sgn = -sgn;
				result.del_0();
				return result;
			}
		}
		if (sgn != other.sgn)
		{
			if (first_num.abs() >= sec_num.abs())
			{
				result = sec_num.Sum(first_num);
				result.sgn = sgn;
				result.del_0();
				return result;
			}
			else
			{
				result = first_num.Sum(sec_num);
				result.sgn = -sec_num.sgn;
				result.del_0();
				return result;
			}
		}
	}


	BigInteger operator*(const BigInteger& other) const
	{
		BigInteger res;
		if ((numbers.size() == 1 && numbers[0] == 0) || (other.numbers.size() == 1 && other.numbers[0] == 0))
		{
			return res;
		}
		res.numbers.resize(numbers.size() + other.numbers.size(), 0);
		for (int i = 0; i < numbers.size(); i++)
		{
			int app = 0;
			for (int j = 0; j < other.numbers.size(); j++)
			{
				long long rezult = res.numbers[i + j] + (long long)numbers[i] * other.numbers[j] + app;
				app = rezult / 10;
				res.numbers[i + j] = rezult % 10;
			}
			if (app > 0)
			{
				res.numbers[i + other.numbers.size()] += app;
			}
		}
		res.sgn = sgn * other.sgn;
		res.del_0();
		return res;
	}

	BigInteger operator *= (const BigInteger& other)
	{
		sgn *= other.sgn;
		int one = numbers.size();
		int two = other.numbers.size();
		std::vector <int> result(one + two, 0);
		for (int i = 0; i < one; i++)
		{
			int app = 0;
			for (int j = 0; j < two; j++)
			{
				int temp = numbers[i] * other.numbers[j] + app + result[i + j];
				result[i + j] = temp % 10;
				app = temp / 10;
			}
		}
		int i = result.size() - 1;
		while (result[i] == 0 && i > 0)
		{
			result.pop_back();
			i--;
		}
		numbers = result;
		return *this;
	}

	BigInteger operator-() const
	{
		BigInteger result = *this;
		result.sgn = -result.sgn;
		return result;
	}

	BigInteger operator/(const BigInteger& other) const
	{
		if (other.numbers.size() == 1 && other.numbers[0] == 0)
		{
			return 0;
		}
		BigInteger dividend = this->abs();
		BigInteger del = other.abs();
		BigInteger tmp;
		BigInteger copy_dividend(*this);
		BigInteger copy_del(other);
		tmp.numbers.resize(dividend.numbers.size(), 0);
		if (dividend < del)
		{
			return 0;
		}
		if (dividend == del)
		{
			if (copy_dividend.sgn == copy_del.sgn)
			{
				return BigInteger(1);
			}
			else if (copy_dividend.sgn != copy_del.sgn)
			{
				return BigInteger(-1);
			}
		}
		BigInteger curr;
		for (int i = dividend.numbers.size() - 1; i >= 0; i--)
		{
			curr = curr * BigInteger(10) + BigInteger(dividend.numbers[i]);
			int count = 0;
			while (curr >= del)
			{
				curr = curr - del;
				count++;
			}
			tmp.numbers[i] = count;
		}
		if (this->sgn == other.sgn)
		{
			tmp.sgn = 1;
		}
		else
		{
			tmp.sgn = -1;
		}
		tmp.del_0();
		return tmp;
	}

	BigInteger& operator/=(const BigInteger& number)
	{
		BigInteger curr = *this;
		if (curr.sgn == number.sgn)
		{
			*this = *this / number;
		}
		else
		{
			*this = *this / number;
			*this *= number.sgn;
		}
		return *this;
	}

	BigInteger operator%(const BigInteger& number)
	{
		if (number == BigInteger(0))
		{
			return 0;
		}
		BigInteger dividend = this->abs();
		BigInteger diviser = number.abs();

		BigInteger res = *this / number;
		BigInteger buf = res * number;
		res = *this - buf;
		if (res.sgn == -1)
		{
			res += number;
		}
		return res;
	}

	BigInteger& operator%=(BigInteger& number)
	{
		return *this = *this % number;
	}

	// Вывод числа в консоль.
	void print()
	{
		if (sgn != 1)
			std::cout << '-';
		for (int i = numbers.size() - 1; i >= 0; i--)
			std::cout << numbers[i];
		std::cout << '\n';
	}

	BigInteger& operator ++ ()
	{
		BigInteger one = 1;
		*this = *this + one;
		return *this;
	}

	BigInteger operator ++ (int)
	{
		BigInteger Temp(*this);
		BigInteger one = 1;
		*this = *(this) + one;
		return Temp;
	}

	BigInteger operator += (const BigInteger& other)
	{
		return *this = *this + other;
	}

	BigInteger& operator -- ()
	{
		return *this = *this - BigInteger(1);
	}

	BigInteger operator-- (int)
	{
		BigInteger result = *this;
		*this = *this - BigInteger(1);
		return *this;
	}

	BigInteger operator -=(const BigInteger& other)
	{
		return *this = *this - other;
	}

	std::string toString() const
	{
		std::string rez = "";
		if (numbers.empty())
		{
			return "0";
		}
		if (sgn == -1)
		{
			rez += '-';
		}
		for (int i = numbers.size() - 1; i >= 0; i--)
		{
			rez += std::to_string(numbers[i]);
		}
		return rez;
	}


};


std::ostream& operator<<(std::ostream& out, BigInteger& b_int) {
	std::string num = b_int.toString();
	out << num;
	return out;
}

std::istream& operator>>(std::istream& in, BigInteger& b_int) {
	std::string res;
	in >> res;
	b_int = BigInteger(res);
	return in;
}
