#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Hash
{
private:
    string str;
    vector<vector<string>> hashes;
    int bad_count = 7;
    bool flag = false;
    int p = 26;
    int q = 1;

    int rand_val()
    {
        srand(time(0));
        int p = rand() * rand() % 100000;
        return p;
    }

    bool check(vector<vector<string>>& Hash_Table, int bad_count)
    {
        for (int i = 0; i < q; i++)
        {
            if (Hash_Table[i].size() > bad_count) return false;
        }
        return true;
    }

    long long F(const string& s)
    {

        long long hash = 0;

        for (char c : s)
        {
            hash = (hash * p + (c - 'a' + 1)) % q;
        }

        return hash;
    }

    bool check_(vector<vector<string>>& hashes, string s)
    {
        for (int i = 0; i < hashes.size(); i++)
        {
            for (int j = 0; j < hashes[i].size(); j++)
            {
                if (hashes[i][j] == s) return false;
            }
        }
        return true;
    }

public:

    Hash(const string& inputStr) : str(inputStr)
    {
        str = inputStr;
        while (!flag)
        {
            q = rand_val();
            hashes.resize(q, vector<string>(0));
            for (int i = 0; i < str.size(); i++)
            {
                string substr = "";
                for (int j = i; j < str.size(); j++)
                {
                    substr += str[j];
                    if(check_(hashes, substr)) hashes[F(substr)].push_back(substr);
                }
            }
            flag = check(hashes, bad_count);
            if (!flag)
            {
                hashes.clear();
            }
        }
    }

    ~Hash()
    {
        hashes.clear();
    }

    void add_Element(const string& new_Elem)
    {
        if (check_(hashes, new_Elem)) hashes[F(new_Elem)].push_back(new_Elem);
        else return;
    }

    void remove_Element(const string& elem_Remove)
    {
        for (int i = 0; i < hashes[F(elem_Remove)].size(); i++)
        {
            if (hashes[F(elem_Remove)][i] == elem_Remove)
            {
                hashes[F(elem_Remove)].erase(hashes[F(elem_Remove)].begin() + i);
            }
        }
    }

    bool find_Substring(const string& substring)
    {
        for (size_t i = 0; i < hashes.size(); i++)
        {
            for (size_t j = 0; j < hashes[i].size(); j++)
            {
                if (hashes[i][j] == substring)
                {
                    return true;
                }
            }
        }
        return false;
    }

    int count_Substrings()
    {
        int count = 0;
        for (size_t i = 0; i < hashes.size(); i++)
        {
            count += hashes[i].size();
        }
        return count;
    }
};

int main()
{
    Hash hash("abcsavjfurthrgthbfghyjjhkljt");
    //hash.add_Element("abc");
    //hash.remove_Element("a");
    if (hash.find_Substring("a")) cout << "YES" << '\n';
    else cout << "NO\n";
    cout << hash.count_Substrings() << '\n';
}
