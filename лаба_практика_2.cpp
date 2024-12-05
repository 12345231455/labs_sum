#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

void Pref_1d()
{
        // инициализация

        int n;
        cin >> n;
        vector<int> a(n + 1);
        vector<long long> Pr(n + 1);

        // база

        Pr[0] = 0;

        // счет

        for (int i = 1; i <= n; i++)
        {
                cin >> a[i];
                Pr[i] = Pr[i - 1] + a[i];
        }

        // ответ

        for (int i = 0; i <= n; i++)
        {
                cout << Pr[i] << ' ';
        }
}

void Pref_2d()
{

        // инициализация

        int n, m;
        cin >> n >> m;
        vector<vector<int>> a(n, vector<int> (m));
        vector<vector<int>> Pr(n, vector<int>(m));
        for (int i = 0; i < n; i++)
        {
                for (int j = 0; j < m; j++)
                {
                        cin >> a[i][j];
                }
        }

        // база

        Pr[0][0] = a[0][0];

        for (int i = 1; i < n; i++)
        {
                Pr[i][0] = Pr[i - 1][0] + a[i][0];
        }
        for (int i = 1; i < m; i++)
        {
                Pr[0][i] = Pr[0][i - 1] + a[0][i];
        }

        // счет

        for (int i = 1; i < n; i++)
        {
                for (int j = 1; j < m; j++)
                {
                        Pr[i][j] = max(Pr[i - 1][j], Pr[i][j - 1]) + a[i][j];
                }
        }

        // ответ

        cout << Pr[n - 1][m - 1];
}

void NVP_school()
{

        // инициализация

        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++)
        {
                cin >> a[i];
        }
        vector<int> Dp_len(n + 1, 1);

        // счет

        for (int i = 1; i < n; i++)
        {
                for (int j = 0; j < i; j++)
                {
                        if (a[j] < a[i])
                        {
                                Dp_len[i] = max(Dp_len[i], Dp_len[j] + 1);
                        }
                }
        }
        int mx = 0;
        for (int i = 0; i <= n; i++)
        {
                if (Dp_len[i] > mx)
                {
                        mx = Dp_len[i];
                }
        }
        cout << mx;
}

int Bin_search(vector<int>& best, int x)
{
        int l = 0;
        int r = best.size();
        while (l < r)
        {
                int mid = l + (r - l) / 2;
                if (best[mid] <= x)
                {
                        l = mid + 1;
                }
                else
                {
                        r = mid;
                }
        }
        return l;
}

void NVP_stud()
{

        // инициализация

        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++)
        {
                cin >> a[i];
        }
        vector<int> Dp_len(n + 2, 1e9);

        // база

        Dp_len[0] = 0;

        // счет

        for (int i = 0; i < n; i++)
        {
                int j = Bin_search(Dp_len, a[i]);
                if (Dp_len[j - 1] < a[i] && a[i] < Dp_len[j])
                {
                        Dp_len[j] = a[i];
                }
        }

        // ответ

        int mx = 0;
        int ind = 0;
        for (int i = 0; i <= n; i++)
        {
                if (Dp_len[i] >= mx && Dp_len[i] != 1e9)
                {
                        mx = Dp_len[i];
                        ind = i;
                }
        }
        cout << ind;
}

void backpack()
{

        // инициализация

        int n;
        cin >> n;
        vector<int> weight(n + 1);
        vector<int> cost(n + 1);
        for (int i = 1; i <= n; i++)
        {
                cin >> weight[i];
                cin >> cost[i];
        }
        int s;
        cin >> s;
        vector<vector<int>> Dp_backpack(n + 1, vector<int>(s + 1));

        // база

        Dp_backpack[0][0] = 0;
        for (int i = 1; i <= s; i++)
        {
                Dp_backpack[0][i] = -1;
        }

        // счет

        for (int i = 1; i <= n; i++)
        {
                for (int j = 0; j <= s; j++)
                {
                        Dp_backpack[i][j] = Dp_backpack[i - 1][j];
                }
                for (int j = 0; j <= s; j++)
                {
                        if (j - weight[i] >= 0)
                        {
                                if (Dp_backpack[i - 1][j - weight[i]] != -1)
                                {
                                        Dp_backpack[i][j] = max(Dp_backpack[i][j], Dp_backpack[i - 1][j - weight[i]] + cost[i]);
                                }
                        }
                }
        }

        // ответ

        int mx = 0;
        for (int i = 0; i <= s; i++)
        {
                if (mx < Dp_backpack[n][i])
                {
                        mx = Dp_backpack[n][i];
                }
        }
        cout << mx;
}

int main()
{
        //Pref_1d();
        //Pref_2d();
        //NVP_school();
        //NVP_stud();
        //backpack();
}