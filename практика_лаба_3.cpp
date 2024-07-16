#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Hash
{
private:
    string str;
    vector<vector<int>> hashes;
    int bad_count = 12;
    bool flag = false;
    int p = 1;

    int rand_val()
    {
        srand(time(0));
        int p = rand() * rand() % rand();
        return p;
    }

    bool check(vector<vector<int>>& Hash_Table, int bad_count)
    {
        for (int i = 0; i < 9871; i++)
        {
            if (Hash_Table[i].size() > bad_count) return false;
        }
        return true;
    }

    int F(const string& s)
    {

        int hash = 0;
        p = rand_val();
        int m = 9871;
        int p_pow = 1;

        for (char c : s)
        {
            hash = (hash + (c - 'a' + 1) * p_pow) % m;
            p_pow = (p_pow * p) % m;
        }

        return hash;
    }

public:

    Hash(const string& inputStr) : str(inputStr)
    {
        while (!flag)
        {
            hashes.resize(9871, vector<int>(0));
            for (int i = 0; i < str.size(); i++)
            {
                string substr = "";
                for (int j = i; j < str.size(); j++)
                {
                    substr += str[j];
                    hashes[i].push_back(F(substr));
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
    Hash hash("abcdasdfsasd");
    hash.add_Element("abс");
    hash.remove_Element("a");
    cout << hash.find_Substring("ab") << '\n';
    cout << hash.count_Substrings() << '\n';
}
