#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int main()
{
	ofstream out("input.txt");
	int n, q;
	n = rand() % 100000;
	q = rand() % 100000;
	out << n << '\n';
	vector<long long> a(n);
	vector<long long> b(q);
	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % 10000000;
		out << a[i] << '\n';
	}
	out << q << '\n';
	for (int i = 0; i < q; i++)
	{
		b[i] = rand() % 10000000;
		out << b[i] << '\n';
	}
}