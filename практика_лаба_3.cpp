#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <ctime>
#include <Windows.h>
#include <fstream>
#include <cmath>

using namespace std;

double count_lin = 0;
double count_bin = 0;
double count_set = 0;
double count_freq_dict = 0;
double count_hash = 0;

void Lin()
{

	// инициализация и чтение данных

	ifstream in_lin("input.txt");
	ofstream out_lin("output_lin.txt");
	int n, q;
	in_lin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
	{
		in_lin >> a[i];
	}
	in_lin >> q;
	vector<int> b(q);
	for (int i = 0; i < q; i++)
	{
		in_lin >> b[i];
	}

	// решение 


	clock_t start = clock();
	for (int i = 0; i < q; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (b[i] == a[j])
			{
				out_lin << "YES\n";
			}
			else
			{
				out_lin << "NO\n";
			}
		}
	}
	count_lin = (clock() - start) / (CLOCKS_PER_SEC * 1.0);
	in_lin.close();
	out_lin.close();
}

void Bin()
{

	// инициализация и чтение данных

	ifstream in_bin("input.txt");
	ofstream out_bin("output_bin.txt");
	int n, q;
	in_bin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
	{
		in_bin >> a[i];
	}
	in_bin >> q;
	vector<int> b(q);
	for (int i = 0; i < q; i++)
	{
		in_bin >> b[i];
	}

	// решение 

	double start = clock();
	sort(a.begin(), a.end());
	for (int i = 0; i < q; i++)
	{
		if (binary_search(a.begin(), a.end(), b[i]))
		{
			out_bin << "YES\n";
		}
		else
		{
			out_bin << "NO\n";
		}
	}
	count_bin = (clock() - start) / (CLOCKS_PER_SEC * 1.0);
	in_bin.close();
	out_bin.close();
}

void Set()
{

	// инициализация и чтение данных 

	ifstream in_set("input.txt");
	ofstream out_set("output_set.txt");
	int n, q;
	in_set >> n;
	vector<int> a(n);
	set <int> st;
	for (int i = 0; i < n; i++)
	{
		in_set >> a[i];
		st.insert(a[i]);
	}
	in_set >> q;
	vector<int> b(q);
	for (int i = 0; i < q; i++)
	{
		in_set >> b[i];
	}
	
	// решение 

	double start_set = clock();
	for (int i = 0; i < q; i++)
	{
		if (st.find(b[i]) != st.end())
		{
			out_set << "YES\n";
		}
		else
		{
			out_set << "NO\n";
		}
	}
	count_set = (clock() - start_set) / (CLOCKS_PER_SEC * 1.0);
	in_set.close();
	out_set.close();
}

void Freq_Dict()
{
	
	//инициализация и чтение данных 

	ifstream in_freq("input.txt");
	ofstream out_freq("output_freq.txt");
	int n, q;
	in_freq >> n;
	vector<int> a(n);
	vector<int> freq_dict(1e7, 0);
	for (int i = 0; i < n; i++)
	{
		in_freq >> a[i];
		freq_dict[a[i]] = 1;
	}
	in_freq >> q;
	vector<int> b(q);
	for (int i = 0; i < q; i++)
	{
		in_freq >> b[i];
	}

	//решение
	
	double start_freq = clock();
	for (int i = 0; i < q; i++)
	{

		if (freq_dict[b[i]])
		{
			out_freq << "YES\n";
		}
		else
		{
			out_freq << "NO\n";
		}
	}
	count_freq_dict = (clock() - start_freq) / (CLOCKS_PER_SEC * 1.0);
	in_freq.close();
	out_freq.close();
}

int rand_F_val()
{
	srand(time(0));
	int p = (rand() * rand()) % 1000;
	return p;
}

int F(int val, int p)
{
	int key = (val * p) % 625000;
	return key;
}

void Hash()
{

	// инициализация и чтение данных

	ifstream in_hash("input.txt");
	ofstream out_hash("output_hash.txt");
	int n, q;
	in_hash >> n;
	vector<int> a(n);
	for (int i = 0; i < n; i++)
	{
		in_hash >> a[i];
	}
	in_hash >> q;
	vector<int> b(q);
	for (int i = 0; i < q; i++)
	{
		in_hash >> b[i];
	}

	// сборка Хэш-Таблицы

	double start_hash = clock();
	vector<set<int>> Hash_Table(6250, set<int>());
	int p = rand_F_val();
	for (int i = 0; i < n; i++)
	{
		int hash_value = F(a[i], p);
		if (hash_value >= 0 && hash_value < Hash_Table.size()) 
		{
			Hash_Table[hash_value].insert(a[i]);
		}
	}

	for (int i = 0; i < q; i++)
	{
		bool flag = false;
		int key = F(b[i], p);
		if (key >= 0 && key < Hash_Table.size()) 
		{
			for (int j = 0; j < Hash_Table[key].size(); j++)
			{
				if (Hash_Table[key].find(b[i]) != Hash_Table[key].end())
				{
					flag = true;
					break; 
				}
			}
		}
		if (flag)
		{
			out_hash << "YES\n";
		}
		else
		{
			out_hash << "NO\n";
		}
	}
	count_hash = (clock() - start_hash) / (CLOCKS_PER_SEC * 1.0);
}

int main()
{
	setlocale(LC_ALL, "ru");
	//Lin();
	cout << "Время работы Лин поиска: " << fixed << count_lin << '\n';
	Bin();
	cout << "Время работы Бин поиска: " << fixed << count_bin << '\n';
	Set();
	cout << "Время работы поиска через set: " << fixed << count_set << '\n';
	Freq_Dict();
	cout << "Время работы поиска через частотный словарь: " << fixed << count_freq_dict << '\n';
	Hash();
	cout << "Время работы поиска через Хеш-таблицу: " << fixed << count_freq_dict << '\n';
}
