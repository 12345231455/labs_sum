﻿#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Hash
{
private:
    string str;
    vector<vector<int>> hashes;

    int F(const string& s)
    {
        int hash = 0;
        int p = 457;
        int m = 7237;
        int p_pow = 1;

        for (char c : s)
        {
            hash = ((c - 'a' + 1) * p) % m;
        }

        return hash;
    }

public:

    Hash(const string& inputStr) : str(inputStr)
    {
        hashes.resize(str.size());
        for (int i = 0; i < str.size(); i++)
        {
            string substr = "";
            for (int j = i; j < str.size(); j++)
            {
                substr += str[j];
                hashes[i].push_back(F(substr));
            }
        }
    }

    ~Hash()
    {
        hashes.clear();
    }

    void add_Element(const string& new_Elem)
    {
        string substr = "";
        for (int i = 0; i < new_Elem.size(); i++)
        {
            substr += new_Elem[i];
            hashes[new_Elem.size() - 1].push_back(F(substr));
        }
    }

    void remove_Element(const string& elem_Remove)
    {
        string substr = "";
        for (int i = 0; i < elem_Remove.size(); i++)
        {
            substr += elem_Remove[i];
            int hash = F(substr);
            auto& vec = hashes[elem_Remove.size() - 1];
            for (int k = 0; k < vec.size();)
            {
                if (vec[k] == hash)
                {
                    vec.erase(vec.begin() + k);
                }
                else
                {
                    k++;
                }
            }
        }
    }

    bool find_Substring(const string& substring)
    {
        int hash = F(substring);
        for (size_t i = 0; i < hashes.size(); i++)
        {
            for (size_t j = 0; j < hashes[i].size(); j++)
            {
                if (hashes[i][j] == hash)
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
    Hash hash("abcd");
    hash.add_Element("abс");
    hash.remove_Element("a");
    cout << hash.find_Substring("ab") << '\n';
    cout << hash.count_Substrings() << '\n';
}
