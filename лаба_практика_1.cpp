#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

void BFS_comp(vector<vector<int>>& G, vector<int>& Mark, int start)
{
	queue<int> q;
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
	cin >> n >> m;
	vector<vector<int>> G(n + 1);
	vector<int>Mark(n + 1);
	int a, b;
	int cnt = 0;
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	for (int i = 1; i <= n; i++)
	{
		if (Mark[i] == 0)
		{
			cnt++;
			BFS_comp(G, Mark, i);
		}
	}
	cout << '\n' << cnt << '\n';
}

void BFS_short()
{
	int start, finish, n, m;
	cin >> start >> finish;
	cin >> n >> m;
	queue<int>q;
	q.push(start);
	vector<vector<int>> G(n + 1);
	vector<int>Mark(n + 1);
	Mark[start] = 1;
	vector<int> Put(n + 1);
	Put[start] = start;
	vector<int>Len(n + 1);
	int a, b;
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b;
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
		cout << -1;
	}
	else
	{
		cout << Len[finish] << endl;
		vector<int> path;
		for (int i = finish; i != start; i = Put[i]) {
			path.push_back(i);
		}
		path.push_back(start);
		reverse(path.begin(), path.end());
		for (int i = 0; i < path.size(); i++)
		{
			cout << path[i] << " ";
		}
	}
}

void dfs(int x, vector<vector<int>>& G, vector<int>& Mark)
{
	Mark[x] = 1;
	for (int i = 0; i < G[x].size(); i++)
	{
		if (Mark[G[x][i]] == 0)
		{
			dfs(G[x][i], G, Mark);
		}
	}
}

void dfs_comp_connect()
{
	int n, m;
	cin >> n >> m;
	vector<vector<int>> G(n + 1);
	vector <int> Mark(n + 1);
	int a, b;
	int res = 0;
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);

	}
	for (int i = 1; i <= n; i++)
	{
		if (Mark[i] == 0)
		{
			res++;
			dfs(i, G, Mark);
		}
	}
	cout << res << '\n';
}

void dfs_cycle(int x, int y, vector<vector<int>>& G, vector<int>& Mark, bool& flag)
{
	//y - предок
	Mark[x] = 1;
	for (int i = 0; i < G[x].size() && flag == false; i++)
	{
		if (Mark[G[x][i]] == 0)
		{
			dfs_cycle(G[x][i], x, G, Mark, flag);
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
	cin >> n >> m;
	vector<vector<int>> G(n + 1);
	vector<int>Mark(n + 1);
	int a, b;
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	bool flag = false;
	for (int i = 1; i <= n && flag == false; i++)
	{
		if (Mark[i] == 0)
		{
			dfs_cycle(i, -1, G, Mark, flag);
		}
	}
	if (flag)
	{
		cout << "YES\n";
	}
	else
	{
		cout << "NO\n";
	}
}

void dfs_cycle_recov(int x, int y, vector<vector<int>>& G, vector<int> Mark, bool& flag, stack<int>& st)
{
	Mark[x] = 1;
	st.push(x);
	for (int i = 0; i < G[x].size() && flag == false; i++)
	{
		if (G[x][i] != y)
		{
			if (Mark[G[x][i]] == 0)
			{
				dfs_cycle_recov(G[x][i], x, G, Mark, flag, st);
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

void dfs_cycle_recovery()
{
	int n, m;
	cin >> n >> m;
	vector<vector<int>> G(n + 1);
	vector<int>Mark(n + 1);
	int a, b;
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);
	}
	bool flag = false;
	stack<int> st;
	for (int i = 1; i <= n && flag == false; i++)
	{
		if (Mark[i] == 0)
		{
			dfs_cycle_recov(i, -1, G, Mark, flag, st);
		}
	}
	if (flag == true)
	{
		int tmp = st.top();
		cout << st.top();
		st.pop();
		while (st.top() != tmp)
		{
			cout << st.top() << ' ';
			st.pop();
		}
		cout << tmp << '\n';
	}
	else
	{
		cout << "NO CYCLE" << '\n';
	}
}

void len_1(vector<vector<pair<int, int>>>& G, vector<int>& used, vector<int>& Len, int start, int finish, int n)
{
	Len[start] = 0;
	int tmp;
	for (int i = 0; i < n; i++) // цикл кол-во релакс
	{
		tmp = -1;
		int length = 1e9;
		for (int j = 1; j <= n; j++)
		{
			if (used[j] == 0)
			{
				if (length > Len[j])
				{
					length = Len[j];
					tmp = j;
				}
			}
		}
		if (tmp != -1)
		{
			used[tmp] = 1;
			for (int j = 0; j < G[tmp].size(); j++)
			{
				Len[G[tmp][j].second] = min(Len[G[tmp][j].second], Len[tmp] + G[tmp][j].first);
			}
		}
	}
	if (Len[finish] != 1e9)
	{
		cout << Len[finish] << '\n';
	}
	else
	{
		cout << -1 << '\n';
	}
}

void deykstra_school()
{
	int n, m, start, finish;
	cin >> n >> m;
	cin >> start >> finish;
	vector<vector<pair<int, int>>> G(n + 1);
	vector<int> used(n + 1), Len(n + 1, 1e9);
	for (int i = 0; i < m; i++)
	{
		int a, b, weight;
		cin >> a >> b >> weight;
		G[a].emplace_back(weight, b);
		G[b].emplace_back(weight, a);
	}
	len_1(G, used, Len, start, finish, n);
}

void Len_2(vector<vector<pair<int, int>>>& G, vector<int>& Mark, vector<int>& Len, int start, int finish, int n)
{
	set<pair<int, int>> st;
	pair <int, int> tmp1, tmp2;
	tmp1.first = 0;
	tmp1.second = start;
	Mark[start] = 1;
	st.insert(tmp1);
	while (st.size())
	{
		tmp1 = *st.begin();
		st.erase(st.begin());
		if (Len[tmp1.second] > tmp1.first)
		{
			Len[tmp1.second] = tmp1.first;
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
		cout << Len[finish];
	}
}

void deykstra_stud()
{
	int n, m, start, finish;
	cout << "n, m: ";
	cin >> n >> m;
	cout << endl << "start, finish: ";
	cin >> start >> finish;
	vector<vector<pair<int, int>>> G(n + 1);
	vector<int> Mark(n + 1), Len(n + 1, 1e9);
	for (int i = 0; i < m; i++)
	{
		int a, b, weight;
		cin >> a >> b >> weight;
		G[a].emplace_back(weight, b);
		G[b].emplace_back(weight, a);
	}
	Len_2(G, Mark, Len, start, finish, n);
}

int main()
{
	//BFS_comp_connect();
	//BFS_short();
	//dfs_comp_connect();
	//dfs_cycle_exist();
	//dfs_cycle_recovery();
	//deykstra_school();
	//deykstra_stud();
}