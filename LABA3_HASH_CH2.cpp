#include <iostream>
#include <vector>
#include <string>
#include <ctime>

class Hash_Table
{
private:
    int p = 26;
    std::vector<std::vector<std::string>> hash;
    std::string str;
    bool flag = false;

    int rand_q()
    {
        srand(time(0));
        int q = rand() % 100000 + 1;
        return q;
    }

    bool check_repetition(std::vector<std::vector<std::string>>& hash, std::string stroka)
    {
        for (int i = 0; i < hash.size(); i++)
        {
            for (int j = 0; j < hash[i].size(); j++)
            {
                if (hash[i][j] == stroka) return false;
            }
        }
        return true;
    }

    bool check_collision(std::vector<std::vector<std::string>>& hash, int q)
    {
        for (int i = 0; i < q; i++)
        {
            int count = 0;
            for (int j = 0; j < hash[i].size(); j++)
            {
                if (!hash[i][j].empty()) count++;
                if (count > 6) return false;
            }
        }
        return true;
    }

public:
    Hash_Table(const std::string& inp)
    {
        str = inp;
        while (!flag)
        {
            int q = rand_q();
            hash.resize(q, std::vector<std::string>(0));
            for (int i = 0; i < str.size(); i++)
            {
                std::string tmp = "";
                long long last = 0;
                for (int j = i; j < str.size(); j++)
                {
                    tmp += str[j];
                    long long key = (last * p + str[j]) % q;
                    if (check_repetition(hash, tmp))
                    {
                        hash[key].push_back(tmp);
                    }
                    last = key;
                }
            }
            flag = check_collision(hash, q);
            if (!flag)
            {
                hash.clear();
            }
        }
    }



    void add_str(const std::string& substr)
    {
        long long last = 0;
        long long key = 0;
        for (int i = 0; i < substr.size(); i++)
        {
            key = (last * p + substr[i]) % hash.size();
            last = key;
        }
        if (check_repetition(hash, substr))
        {
            hash[key].push_back(substr);
        }
        else return;
    }



    void remove_str(const std::string& substr)
    {
        long long last = 0;
        long long key = 0;
        for (int i = 0; i < substr.size(); i++)
        {
            key = (last * p + substr[i]) % hash.size();
            last = key;
        }
        for (auto i = hash[key].begin(); i != hash[key].end(); i++)
        {
            if (*i == substr)
            {
                hash[key].erase(i);
                break;
            }
        }
    }



    ~Hash_Table()
    {
        hash.clear();
    }


    int count_substr()
    {
        int count = 0;
        for (int i = 0; i < hash.size(); i++)
        {
            for (int j = 0; j < hash[i].size(); j++)
            {
                if (!hash[i][j].empty()) count++;
            }
        }
        return count;
    }



    bool find_substr(const std::string& substr)
    {
        for (int i = 0; i < hash.size(); i++)
        {
            for (int j = 0; j < hash[i].size(); j++)
            {
                if (hash[i][j] == substr) return true;
            }
        }
        return false;
    }



    /*void print_hash_table()
    {
        for (int i = 0; i < hash.size(); i++)
        {
            for (int j = 0; j < hash[i].size(); j++)
            {
                std::cout << hash[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    */

};
int main()
{
    Hash_Table a("abacaba");
    //a.print_hash_table();
    int cnt = a.count_substr();
    std::cout << std::endl << cnt << std::endl;
    if (a.find_substr("a"))
    {
        std::cout << "YES" << std::endl;
    }
    else std::cout << "NO" << std::endl;
}
