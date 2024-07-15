#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <set>
#include <fstream>
#include <ctime>
//#include <Windows.h>
void lin_search()
{
	std::ifstream in("input.txt");
	std::ofstream out("output_lin.txt");
	double timer_lin = 0;
	int n, q;
	in >> n;
	std::vector<int> A(n);
	for (int i = 0; i < n; i++)
	{
		in >> A[i];
	}
	in >> q;
	std::vector<int>B(q);
	for (int i = 0; i < q; i++)
	{
		in >> B[i];
	}
	double count = clock();
	for (int i = 0; i < q; i++)
	{
		bool flag = false;
		for (int j = 0; j < n && !flag; j++)
		{
			if (B[i] == A[j])
			{
				out << "YES" << std::endl;
				flag = true;
				break;
			}
		}
		if (!flag) out << "NO" << std::endl;
	}
	timer_lin = (clock() - count) / (CLOCKS_PER_SEC * 1.0);
	std::cout << "Линейный поиск: " << std::fixed << std::setprecision(8) << timer_lin << std::endl;
	in.close();
	out.close();
}

void bin_search()
{
	std::ifstream in("input.txt");
	std::ofstream out("output_bin.txt");
	double timer_bin = 0;
	int n, q;
	in >> n;
	std::vector<int> A(n);
	for (int i = 0; i < n; i++)
	{
		in >> A[i];
	}
	in >> q;
	std::vector<int> B(q);
	for (int i = 0; i < q; i++)
	{
		in >> B[i];
	}
	double count = clock();
	std::sort(A.begin(), A.end());
	for (int i = 0; i < q; i++)
	{
		int l = 0;
		int r = n - 1;
		int mid;
		while (r - l > 1)
		{
			mid = (l + r) / 2;
			if (A[mid] > B[i])
			{
				r = mid;
			}
			else l = mid;
		}
		if (A[l] == B[i] || A[r] == B[i]) out << "YES" << std::endl;
		else out << "NO" << std::endl;
	}
	timer_bin = (clock() - count) / (CLOCKS_PER_SEC * 1.0);
	std::cout << "Бинарный поиск: " << std::fixed << std::setprecision(8) << timer_bin << std::endl;
	in.close();
	out.close();
}

void search_set()
{
	std::ifstream in("input.txt");
	std::ofstream out("output_set.txt");
	double timer_set = 0;
	int n, q;
	in >> n;
	std::vector<int>A(n);
	std::set<int>st;
	for (int i = 0; i < n; i++)
	{
		in >> A[i];
		st.insert(A[i]);
	}
	in >> q;
	std::vector<int>B(q);
	for (int i = 0; i < q; i++)
	{
		in >> B[i];
	}
	double count = clock();
	for (int i = 0; i < q; i++)
	{
		if (st.find(B[i]) != st.end())
		{
			out << "YES" << std::endl;
		}
		else out << "NO" << std::endl;
	}
	timer_set = (clock() - count) / (CLOCKS_PER_SEC * 1.0);
	std::cout << "Поиск через сет: " << std::fixed << std::setprecision(8) << timer_set << std::endl;
	in.close();
	out.close();
}

void dictionary()
{
	std::ifstream in("input.txt");
	std::ofstream out("output_dict.txt");
	double timer_dictionary = 0;
	int n, q;
	in >> n;
	std::vector<int>A(n);
	std::vector<int>C(1e7, 0);
	for (int i = 0; i < n; i++)
	{
		in >> A[i];
		C[A[i]] = 1;
	}
	in >> q;
	std::vector<int>B(q);
	for (int i = 0; i < q; i++)
	{
		in >> B[i];
	}
	double count = clock();
	for (int i = 0; i < q; i++)
	{
		if (C[B[i]] == 1) out << "YES" << std::endl;
		else out << "NO" << std::endl;
	}
	timer_dictionary = (clock() - count) / (CLOCKS_PER_SEC * 1.0);
	std::cout << "Частотный словарь: " << std::fixed << std::setprecision(8) << timer_dictionary << std::endl;
	in.close();
	out.close();
}

int rand_p()
{
	srand(time(0));
	int p = (rand() * rand()) % 100000;
	return p;
}

int F(int val, int p)
{
	int key = (val * p) % 625007;
	return key;
}

bool check_collision(std::vector<std::vector<int>>& hash_table, int q)
{
	for (int i = 0; i < q; i++)
	{
		int count = 0;
		for (int j = 0; j < hash_table[i].size(); j++)
		{
			if (hash_table[i][j]) count++;
			if (count > 6) return false;
		}
	}
	return true;
}

void hash_table()
{
	std::ifstream in("input.txt");
	std::ofstream out("output_hash.txt");
	double timer_hash = 0;
	int n, q;
	in >> n;
	std::vector<int>A(n);
	for (int i = 0; i < n; i++)
	{
		in >> A[i];
	}
	in >> q;
	std::vector<int>B(q);
	for (int i = 0; i < q; i++)
	{
		in >> B[i];
	}
	double count = clock();
	bool flag = false;
	int p = 0;
	std::vector<std::vector<int>>hash_table(0, std::vector<int>(0));
	while (!flag)
	{
		p = rand_p();
		hash_table.resize(625007, std::vector<int>(0));
		for (int i = 0; i < n; i++)
		{
			int key = F(A[i], p);
			if (key >= 0 && key < hash_table.size())
			{
				hash_table[key].push_back(A[i]);
			}
		}
		flag = check_collision(hash_table, 625007);
		if (!flag)
		{
			hash_table.clear();
		}
	}
	for (int i = 0; i < q; i++)
	{
		bool find = false;
		int key_ = F(B[i], p);
		if (key_ >= 0 && key_ < hash_table.size())
		{
			for (int j = 0; j < hash_table[key_].size(); j++)
			{
				if (hash_table[key_][j] == B[i])
				{
					find = true;
				}
			}
		}
		if (find) out << "YES" << std::endl;
		else out << "NO" << std::endl;
	}
	timer_hash = (clock() - count) / (CLOCKS_PER_SEC * 1.0);
	std::cout << "Хэш-таблица: " << std::fixed << std::setprecision(8) << timer_hash << std::endl;
	in.close();
	out.close();
}

int main()
{
	setlocale(LC_ALL, "ru");
	lin_search();
	bin_search();
	search_set();
	dictionary();
	hash_table();
}