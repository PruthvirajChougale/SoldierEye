#include <iostream>
#include<string>
#include<map>
#include<vector>
#include <algorithm>

using namespace std;

class Sentinel{
protected:
    int id;
    string name;
    string rank;

public:
    virtual int countHigherRanked(map<string, int> freq) const { return 0; }
    virtual string get_rank() const { return ""; }
    virtual int get_id() const { return 0; }
};

class comp{
public:
    bool operator()(Sentinel *A, Sentinel *B){
        map<string, int> rank_map = {
            {"CAPTAIN", 3},
            {"MAJOR", 2},
            {"SEPOY", 1},
        };

        if (A->get_rank() == B->get_rank())
        {
            return (A->get_id() < B->get_id());
        }
        else
        {
            return (rank_map[A->get_rank()] > rank_map[B->get_rank()]);
        }
    }
};

class CAPTAIN : public Sentinel
{
public:
    CAPTAIN(int id, string name, string rank) : Sentinel()
    {
        this->id = id;
        this->name = name;
        this->rank = rank;
    }
    int get_id() const override
    {
        return id;
    }
    string get_rank() const override
    {
        return rank;
    }
    int countHigherRanked(map<string, int> freq) const override
    {
        return 0;
    }
};

class MAJOR : public Sentinel
{
public:
    MAJOR(int id, string name, string rank) : Sentinel()
    {
        this->id = id;
        this->name = name;
        this->rank = rank;
    }
    int get_id() const override
    {
        return id;
    }
    string get_rank() const override
    {
        return rank;
    }
    int countHigherRanked(map<string, int> freq) const override
    {
        return freq["CAPTAIN"];
    }
};

class SEPOY : public Sentinel
{
public:
    SEPOY(int id, string name, string rank) : Sentinel()
    {
        this->id = id;
        this->name = name;
        this->rank = rank;
    }
    int get_id() const override
    {
        return id;
    }
    string get_rank() const override
    {
        return rank;
    }
    int countHigherRanked(map<string, int> freq) const override
    {
        return freq["CAPTAIN"] + freq["MAJOR"];
    }
};

template <typename T>
class Kingdom
{
private:
    map<int, vector<int>> adj_list;
    map<string, int> freq;
    vector<T> sentinels;

public:
    Kingdom(int n)
    {
        for (int i = 0; i < n; i++)
        {
            adj_list[i] = {};
        }
    }
    void addEdges(int A, int B)
    {
        adj_list[A].push_back(B);
        return;
    }
    void addSentinel(T n)
    {
        sentinels.push_back(n);
        freq[n->get_rank()]++;
        return;
    }
    void dfs(int n, int parent, vector<vector<int>> &dp)
    {
        dp[n][0] = 0;
        dp[n][1] = 1;
        for (auto i : adj_list[n])
        {
            if (i == parent)
                continue;
            dfs(i, n, dp);
            dp[n][0] += dp[i][1];
            dp[n][1] += min(dp[i][0], dp[i][1]);
        }
        return;
    }
    int qType1()
    {
        vector<vector<int>> dp(sentinels.size(), vector<int>(2));
        dfs(0, -1, dp);
        return min(dp[0][0], dp[0][1]);
    }
    void qType2()
    {
        vector<T> sen_copy(sentinels.begin(), sentinels.end());
        comp C;
        sort(sen_copy.begin(), sen_copy.end(), C);
        for (auto i : sen_copy)
        {
            cout<<i->get_id()<<" ";
        }
        cout << '\n';
    }
    void qType3(int id)
    {
        cout<<sentinels[id]->countHigherRanked(freq)<<'\n';
    }
};

int main()
{
    int n;
    cin >> n;
    Kingdom<Sentinel *> K(n);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        K.addEdges(u, v);
    }
    for (int i = 0; i < n; i++)
    {
        string name, rank;
        cin >> name >> rank;
        Sentinel *S;
        if (rank == "CAPTAIN")
        {
            S = new CAPTAIN(i, name, rank);
        }
        else if (rank == "MAJOR")
        {
            S = new MAJOR(i, name, rank);
        }
        else
        {
            S = new SEPOY(i, name, rank);
        }
        K.addSentinel(S);
    }
    int q;
    cin>>q;
    for (int i = 0; i < q; i++)
    {
        int t;
        cin>>t;
        if (t == 1)
        {
            cout<<K.qType1()<<'\n';
        }
        else if (t == 2)
        {
            K.qType2();
        }
        else
        {
            int id;
            cin>>id;
            K.qType3(id);
        }
    }
}