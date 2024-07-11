#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <stack>

using namespace std;

void BFS_comp (vector<vector<int>>& G, vector<int>& Mark, int st)
{
    queue<int> que;
    que.push(st);
    Mark[st] = 1;
    int tmp;
    while (que.size() > 0)
    {
        tmp = que.front();
        que.pop();
        for (int i = 0; i < G[tmp].size(); i++)
        {
            if (Mark[G[tmp][i]] == 0)
            {
                Mark[G[tmp][i]] = 1;
                que.push(G[tmp][i]);
            }
        }
    }
}

void BFS_comp_con()
{

    // инициализация и считывание данных

    int n, m;
    cout << "n, m: ";
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
    int count = 0; 

    // решение

    for (int i = 1; i <= n; i++)
    {
        if (Mark[i] == 0)
        {
            count++;
            BFS_comp(G, Mark, i);
        }
    }
    cout << count << '\n';
}

void BFS_short_path()
{

    // инициализация и считывание данных

    int n, m;
    cin >> n >> m;
    vector<vector<int>> G(n + 1);
    vector<int>Len(n + 1);
    int a, b;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    int st, fin;
    cin >> st >> fin;
    queue<int> que;
    que.push(st);
    vector<int>Mark(n + 1);
    Mark[st] = 1;
    vector<int> Path(n + 1);
    Path[st] = st;

    // решение

    while (que.size() > 0)
    {
        int tmp = que.front();
        que.pop();
        for (int i = 0; i < G[tmp].size(); i++)
        {
            if (Mark[G[tmp][i]] == 0)
            {
                Mark[G[tmp][i]] = 1;
                Path[G[tmp][i]] = tmp;
                Len[G[tmp][i]] = 1 + Len[tmp];
                que.push(G[tmp][i]);
            }
        }
    }
    if (Mark[fin] == 0)
    {
        cout << -1;
    }
    else
    {
        cout << Len[fin] << '\n';
        vector<int> path;
        for (int i = fin; i != st; i = Path[i]) 
        {
            path.push_back(i);
        }
        path.push_back(st);
        reverse(path.begin(), path.end());
        for (int i = 0; i < path.size(); i++)
        {
            cout << path[i] << ' ';
        }
    }
}

void DFS_comp_ (int x, vector<vector<int>>& G, vector<int>& Mark)
{
	Mark[x] = 1;
	for (int i = 0; i < G[x].size(); i++)
	{
		if (Mark[G[x][i]] == 0)
		{
			DFS_comp_(G[x][i], G, Mark);
		}
	}
}

void DFS_comp_con()
{

	// инициализация и чтение данных

	int n, m;
	cin >> n >> m;
	vector<vector<int>> G(n + 1);
	vector <int> Mark(n + 1);
	int a, b;
	int count = 0;
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b;
		G[a].push_back(b);
		G[b].push_back(a);

	}

	// решение

	for (int i = 1; i <= n; i++)
	{
		if (Mark[i] == 0)
		{
			count++;
			DFS_comp_(i, G, Mark);
		}
	}
	cout << count << '\n';
}

void DFS_cycle_exist_ (int x, int y, vector<vector<int>>& G, vector<int> Mark, bool& flag)
{
	//y - предок
	Mark[x] = 1;
	for (int i = 0; i < G[x].size() && flag == false; i++)
	{
		if (Mark[G[x][i]] == 0)
		{
			DFS_cycle_exist_(G[x][i], x, G, Mark, flag);
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

void DFS_cycle_exist()
{

	// инициализация и чтение данных

	int n, m;
	cout << "n, m: ";
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

	// решение

	for (int i = 1; i <= n && flag == false; i++)
	{
		if (Mark[i] == 0)
		{
			DFS_cycle_exist_(i, -1, G, Mark, flag);
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

void DFS_cycle_ (int x, int y, vector<vector<int>>& G, vector<int> Mark, bool& flag, stack<int>& st)
{
	Mark[x] = 1;
	st.push(x);
	for (int i = 0; i < G[x].size() && flag == false; i++)
	{
		if (G[x][i] != y)
		{
			if (Mark[G[x][i]] == 0)
			{
				DFS_cycle_(G[x][i], x, G, Mark, flag, st);
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

void DFS_cycle()
{
	int n, m;
	cout << "n, m: ";
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
			DFS_cycle_(i, -1, G, Mark, flag, st);
		}
	}
	if (!st.empty())
	{
		int a1 = st.top();
		st.pop();
		cout << a1 << " ";
		while (st.top() != a1)
		{
			cout << st.top() << " ";
			st.pop();
		}
		cout << st.top();
	}
	else
	{
		cout << "no cycle" << '\n';
	}
}

int main()
{
    //BFS_short_path();
	//BFS_comp_con();
	//DFS_comp_con();
	//DFS_cycle_exist();
	//DFS_cycle();
}