#include <iostream>
#include <set>
#include <vector>

void prefix_function(int n)//ОДНОМЕРНАЯ ДИНАМИКА, ПРЕФИКС ФУНКЦИИ
{
	std::vector<int> A(n + 1);
	std::vector<int> B(n + 1);
	for (int i = 1; i <= n; i++)
	{
		std::cin >> A[i];
	}
	B[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		B[i] = B[i - 1] + A[i];
	}
	for (int i = 0; i < B.size(); i++)
	{
		std::cout << B[i] << " ";
	}
	std::cout << std::endl;
}

void matrix_traversal(int n, int m)//ДВУМЕРНАЯ ДИНАМИКА, ОБХОД МАТРИЦЫ
{
	std::vector<std::vector<int>>Dp(n, std::vector<int>(m));
	std::vector<std::vector<int>>A(n, std::vector<int>(m));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			std::cin >> Dp[i][j];
		}
	}
	A[0][0] = Dp[0][0];
	for (int i = 1; i < n; i++)
	{
		A[i][0] = A[i - 1][0] + Dp[i][0];
	}
	for (int j = 1; j < m; j++)
	{
		A[0][j] = A[0][j - 1] + Dp[0][j];
	}
	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j < m; j++)
		{
			A[i][j] = std::max(A[i - 1][j], A[i][j - 1]) + Dp[i][j];
		}
	}
	std::cout << std::endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			std::cout << A[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << A[n - 1][m - 1];
	std::cout << std::endl;
}

void NVP_school(int n)
{
	std::vector<int> A(n);
	std::vector<int>Dp_len(n, 1);
	for (int i = 0; i < n; i++)
	{
		std::cin >> A[i];
	}
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (A[j] < A[i])
			{
				Dp_len[i] = std::max(Dp_len[i], Dp_len[j] + 1);
			}
		}
	}
	int max_len = 0;
	for (int i = 0; i < n; i++)
	{
		max_len = std::max(max_len, Dp_len[i]);
	}
	std::cout << max_len;
	std::cout << std::endl;
}

int ind(std::vector<int>& Dp_len, int find_el)
{
	int l = 0;
	int r = Dp_len.size();
	while (l < r)
	{
		int mid = l + (r - l) / 2;
		if (Dp_len[mid] < find_el) l = mid + 1;
		else r = mid;
	}
	return l;
}

void NVP_stud(int n)
{
	std::vector<int> A(n + 1);
	std::vector<int>Dp_len(n + 1, 1e9);
	Dp_len[0] = 0;
	for (int i = 0; i < n; i++)
	{
		std::cin >> A[i];
	}
	for (int i = 1; i < n; i++)
	{
		int j = ind(Dp_len, A[i]);
		if (Dp_len[j - 1] < A[i] && A[i] <= Dp_len[j])
		{
			Dp_len[j] = A[i];
		}
	}
	int i = 0;
	while (Dp_len[i] != 1e9)
	{
		i++;
	}
	std::cout << i;
	std::cout << std::endl;
}

void backpack()
{
	int s, n;
	//s - вместимость
	std::cout << "s, n: ";
	std::cin >> s >> n;
	std::vector<std::vector<int>> pack(n + 1, std::vector<int>(s + 1));
	std::vector<int> w(n);
	std::vector<int> c(n);
	for (int i = 0; i < n; i++)
	{
		std::cout << i + 1 << "    ";
		std::cin >> w[i] >> c[i];
	}
	for (int i = 0; i <= s; i++)
	{
		pack[0][i] = -1;
	}
	pack[0][0] = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j <= s; j++)
		{
			pack[i][j] = pack[i - 1][j];
		}
		for (int j = 0; j <= s; j++)
		{
			if (j - w[i] >= 0)
			{
				if (pack[i - 1][j - w[i]] != -1)
				{
					pack[i][j] = std::max(pack[i][j], pack[i - 1][j - w[i]] + c[i]);
				}
			}
		}
	}
	int curr = pack[n][0];
	for (int j = 0; j <= s; j++)
	{
		if (pack[n][j] <= curr)
		{
			curr = pack[n][j];
		}
	}
	std::cout << curr << std::endl;
	std::cout << std::endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	while (true)
	{
		std::cout << "1. Одномерная динамика, префикс функции." << std::endl;
		std::cout << "2. Двумерная динамика, обход матрицы." << std::endl;
		std::cout << "3. НВП, школьный вариант." << std::endl;
		std::cout << "4. НВП, студенческий вариант." << std::endl;
		std::cout << "5. Классическая задача о рюкзаке." << std::endl;
		std::cout << std::endl;
		int num;
		std::cout << "Enter: ";
		std::cin >> num;
		switch (num)
		{
		case 1:
			int n;
			std::cout << "n: ";
			std::cin >> n;
			prefix_function(n);
			std::cout << std::endl;
			break;
		case 2:
			int n1, m;
			std::cout << "n, m: ";
			std::cin >> n1 >> m;
			matrix_traversal(n1, m);
			std::cout << std::endl;
			break;

		case 3:
			int n2;
			std::cout << "n: ";
			std::cin >> n2;
			NVP_school(n2);
			std::cout << std::endl;
			break;
		case 4:
			int n3;
			std::cout << "n: ";
			std::cin >> n3;
			NVP_stud(n3);
			std::cout << std::endl;
			break;
		case 5:
			int n4;
			std::cout << "n: ";
			std::cin >> n4;
			NVP_stud(n3);
			std::cout << std::endl;
			break;
		}

	}

}