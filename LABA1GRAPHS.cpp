#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <stack>

//BFS
void BFS_comp(std::vector<std::vector<int>>& G, std::vector<int>& Mark, int start)
{
	std::queue<int> q;
	q.push(start);
	Mark[start] = 1;
	int tmp;
	while (q.size() > 0)
	{
		tmp = q.front();
		q.pop();
		for (int i = 0; i < G[tmp].size(); i++)
		{
			if (Mark[G[tmp][i]] == 0)
			{
				Mark[G[tmp][i]] = 1;
				q.push(G[tmp][i]);
			}
		}
	}
}

void BFS_comp_connect()
{
	int n, m;
	std::cout << "n, m: ";
	std::cin >> n >> m;
	std::vector<std::vector<int>> G(n + 1);
	std::vector<int>Mark(n + 1);
	int a, b;
	//граф задается списком ребер 
	for (int i = 0; i < m; i++)
	{
		std::cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	int cnt = 0; //кол-во компонент связности
	for (int i = 1; i <= n; i++)
	{
		if (Mark[i] == 0)
		{
			cnt++;
			BFS_comp(G, Mark, i);
		}
	}
	std::cout << std::endl << cnt << std::endl;
}

void BFS_short()
{
	int start, finish, n, m;
	std::cout << "start, finish: ";
	std::cin >> start >> finish;
	std::cout << std::endl;
	std::cout << "n, m: ";
	std::cin >> n >> m;
	std::queue<int>q;
	q.push(start);
	std::vector<std::vector<int>> G(n + 1);
	std::vector<int>Mark(n + 1);
	Mark[start] = 1;
	std::vector<int> Put(n + 1);
	Put[start] = start;
	std::vector<int>Len(n + 1);
	int a, b;
	//граф задается списком ребер 
	for (int i = 0; i < m; i++)
	{
		std::cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	while (q.size() > 0)
	{
		int tmp = q.front();
		q.pop();
		for (int i = 0; i < G[tmp].size(); i++)
		{
			if (Mark[G[tmp][i]] == 0)
			{
				Mark[G[tmp][i]] = 1;
				Put[G[tmp][i]] = tmp;
				Len[G[tmp][i]] = 1 + Len[tmp];
				q.push(G[tmp][i]);
			}
		}
	}
	if (Mark[finish] == 0)
	{
		std::cout << -1;
	}
	else
	{
		std::cout << Len[finish] << std::endl;
		std::vector<int> path;
		for (int i = finish; i != start; i = Put[i]) {
			path.push_back(i);
		}
		path.push_back(start);
		std::reverse(path.begin(), path.end());
		for (int i = 0; i < path.size(); i++)
		{
			std::cout << path[i] << " ";
		}
	}
}

//DFS
void dfs_1(int x, std::vector<std::vector<int>>& G, std::vector<int>& Mark)
{
	Mark[x] = 1;
	for (int i = 0; i < G[x].size(); i++)
	{
		if (Mark[G[x][i]] == 0)
		{
			dfs_1(G[x][i], G, Mark);
		}
	}
}

void dfs_comp_connect()
{
	int n, m;
	std::cout << "n, m: ";
	std::cin >> n >> m;
	std::vector<std::vector<int>> G(n + 1);
	std::vector <int> Mark(n + 1);
	int a, b;
	int cnt = 0;
	for (int i = 0; i < m; i++)
	{
		std::cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);

	}
	for (int i = 1; i <= n; i++)
	{
		if (Mark[i] == 0)
		{
			cnt++;
			dfs_1(i, G, Mark);
		}
	}
	std::cout << cnt << std::endl;
}

void dfs_2(int x, int y, std::vector<std::vector<int>>& G, std::vector<int> Mark, bool& flag)
{
	//y - предок
	Mark[x] = 1;
	for (int i = 0; i < G[x].size() && flag == false; i++)
	{
		if (Mark[G[x][i]] == 0)
		{
			dfs_2(G[x][i], x, G, Mark, flag);
		}
		else
		{
			if (G[x][i] != y)
			{
				flag = true;
			}
		}
	}
}

void dfs_cycle_exist()
{
	int n, m;
	std::cout << "n, m: ";
	std::cin >> n >> m;
	std::vector<std::vector<int>> G(n + 1);
	std::vector<int>Mark(n + 1);
	int a, b;
	for (int i = 0; i < m; i++)
	{
		std::cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	bool flag = false;
	for (int i = 1; i <= n && flag == false; i++)
	{
		if (Mark[i] == 0)
		{
			dfs_2(i, -1, G, Mark, flag);
		}
	}
	if (flag)
	{
		std::cout << "YES";
	}
	else
	{
		std::cout << "NO";
	}
}

void dfs_3(int x, int y, std::vector<std::vector<int>>& G, std::vector<int> Mark, bool& flag, std::stack<int>& st)
{
	Mark[x] = 1;
	st.push(x);
	for (int i = 0; i < G[x].size() && flag == false; i++)
	{
		if (G[x][i] != y)
		{
			if (Mark[G[x][i]] == 0)
			{
				dfs_3(G[x][i], x, G, Mark, flag, st);
			}
			else
			{
				flag = true;
				st.push(G[x][i]);
			}
		}
	}
	if (flag == false)
	{
		Mark[x] = 0;
		st.pop();
	}
}

void dfs_cycle()
{
	int n, m;
	std::cout << "n, m: ";
	std::cin >> n >> m;
	std::vector<std::vector<int>> G(n + 1);
	std::vector<int>Mark(n + 1);
	int a, b;
	for (int i = 0; i < m; i++)
	{
		std::cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	bool flag = false;
	std::stack<int> st;
	for (int i = 1; i <= n && flag == false; i++)
	{
		if (Mark[i] == 0)
		{
			dfs_3(i, -1, G, Mark, flag, st);
		}
	}
	if (!st.empty())
	{
		int a1 = st.top();
		st.pop();
		std::cout << a1 << " ";
		while (st.top() != a1)
		{
			std::cout << st.top() << " ";
			st.pop();
		}
		std::cout << st.top();
	}
	else std::cout << "ЦИКЛА НЕТ" << std::endl;
}

void Len_1(std::vector<std::vector<std::pair<int, int>>>& G, std::vector<int>& Mark, std::vector<int>& Len_, int start, int finish, int n)
{
	Len_[start] = 0;
	for (int i = 0; i < n; i++)
	{
		int u = -1;
		for (int j = 0; j < n; j++)
		{
			if (Mark[j] == 0 && (u == -1 || Len_[j] < Len_[u]))
			{
				u = j;
			}
		}
		if (Len_[u] == 1e9)
		{
			break;
		}
		Mark[u] = 1;
		for (int j = 0; j < G[u].size(); j++)
		{
			if (Len_[u] + G[u][j].first < Len_[G[u][j].second])
			{
				Len_[G[u][j].second] = Len_[u] + G[u][j].first;
			}
		}
	}
	if (Len_[finish] != 1e9) std::cout << Len_[finish] << std::endl;
	else std::cout << -1 << std::endl;
}

void Dejkstra_school()
{
	int n, m, start, finish;
	std::cout << "n, m: ";
	std::cin >> n >> m;
	std::cout << std::endl << "start, finish: ";
	std::cin >> start >> finish;
	std::vector<std::vector<std::pair<int, int>>> G(n + 1);
	std::vector<int> Mark(n), Len_(n + 1, 1e9);
	for (int i = 0; i < m; i++)
	{
		int a, b, weight;
		std::cin >> a >> b >> weight;
		G[a].emplace_back(weight, b);
		G[b].emplace_back(weight, a);
	}
	Len_1(G, Mark, Len_, start, finish, n);
}

void Len_2(std::vector<std::vector<std::pair<int, int>>>& G, std::vector<int>& Mark, std::vector<int>& Len_, int start, int finish, int n)
{
	std::set<std::pair<int, int>> st;
	std::pair <int, int> tmp1, tmp2;
	tmp1.first = 0;
	tmp1.second = start;
	Mark[start] = 1;
	st.insert(tmp1);
	while (st.size())
	{
		tmp1 = *st.begin();
		st.erase(st.begin());
		if (Len_[tmp1.second] > tmp1.first)
		{
			Len_[tmp1.second] = tmp1.first;
			Mark[tmp1.second] = 1;
			for (int i = 0; i < G[tmp1.second].size(); i++)
			{
				tmp2.second = G[tmp1.second][i].second;
				tmp2.first = tmp1.first + G[tmp1.second][i].first;
				st.insert(tmp2);
			}
		}
	}
	if (Mark[finish] == 1)
	{
		std::cout << Len_[finish];
	}
}

void Dejkstra_stud()
{
	int n, m, start, finish;
	std::cout << "n, m: ";
	std::cin >> n >> m;
	std::cout << std::endl << "start, finish: ";
	std::cin >> start >> finish;
	std::vector<std::vector<std::pair<int, int>>> G(n + 1);
	std::vector<int> Mark(n + 1), Len_(n + 1, 1e9);
	for (int i = 0; i < m; i++)
	{
		int a, b, weight;
		std::cin >> a >> b >> weight;
		G[a].emplace_back(weight, b);
		G[b].emplace_back(weight, a);
	}
	Len_2(G, Mark, Len_, start, finish, n);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	while (true)
	{
		std::cout << "1. BFS" << std::endl;
		std::cout << "2. DFS" << std::endl;
		std::cout << "3. Алгоритм Дейкстры" << std::endl;
		std::cout << std::endl;
		int num;
		std::cout << "Enter: ";
		std::cin >> num;
		if (num == 1)
		{
			std::cout << "1) Нахождение количества компонент связности." << std::endl;
			std::cout << "2) Нахождение длины кратчайшего пути в неориентированном графе и его восстановление." << std::endl;
			int chisl;
			std::cin >> chisl;
			if (chisl == 1)
			{
				BFS_comp_connect();
				std::cout << std::endl;
			}
			if (chisl == 2)
			{
				BFS_short();
				std::cout << std::endl;
			}
		}
		else if (num == 2)
		{
			std::cout << "1) Нахождение количества компонент связности." << std::endl;
			std::cout << "2) Определение существования цикла в графе." << std::endl;
			std::cout << "3) Определение существования цикла в графе и его восстановление." << std::endl;
			int chisl;
			std::cin >> chisl;
			if (chisl == 1)
			{
				dfs_comp_connect();
				std::cout << std::endl;
			}
			if (chisl == 2)
			{
				dfs_cycle_exist();
				std::cout << std::endl;
			}
			if (chisl == 3)
			{
				dfs_cycle();
				std::cout << std::endl;
			}
		}
		else
		{
			std::cout << "1) Школьная версия." << std::endl;
			std::cout << "2) Студенческая версия." << std::endl;
			int chisl;
			std::cin >> chisl;
			if (chisl == 1)
			{
				Dejkstra_school();
				std::cout << std::endl;
			}
			else
			{
				Dejkstra_stud();
				std::cout << std::endl;
			}
		}
	}
}