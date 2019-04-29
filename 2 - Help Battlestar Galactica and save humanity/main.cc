#include <bits/stdc++.h>
using namespace std;

vector<string> str_split(const string& str, char sep)
{
    vector<string> ans;
    string curr = "";
    for (char c : str) {
        if (c == sep) {
            ans.push_back(curr);
            curr = "";
        }
        else {
            curr += c;
        }
    }
    if (not curr.empty()) {
        ans.push_back(curr);
    }
    return ans;
}

int str_id(unordered_map<string,int>& table, const string& str)
{
    if (table.count(str)) {
        return table[str];
    }
    int id = table.size();
    table[str] = id;
    return id;
}

long long dfs(vector<long long>& cache, vector<vector<int>>& adj, int u)
{
    long long& ans = cache[u];
    if (ans != -1) {
        return ans; // already computed
    }
    ans = 0;
    for (int v : adj[u]) {
        ans += dfs(cache, adj, v);
    }
    return ans;
}

int main()
{
    int tests;
    cin >> tests; 
    cin.ignore();
    for (int test = 0; test < tests; ++test) {
        int p;
        cin >> p; 
        cin.ignore();
        unordered_map<string,int> table;
        vector<vector<int>> adj(p+1); // adjacency list
        vector<long long> cache(p+1, -1); // cache for dfs computations
        for (int i = 0; i < p; ++i) {
            string line;
            getline(cin, line);
            vector<string> v = str_split(line, ':');
            int l = str_id(table, v[0]);
            v = str_split(v[1], ',');
            for (const string& planet : v) {
                int r = str_id(table, planet);
                adj[l].push_back(r);
            }
        }
        const string start = "Galactica";
        const string end = "New Earth";
        cache[str_id(table, end)] = 1; // base case
        cout << "Case #" << test+1 << ": " << dfs(cache, adj, str_id(table, start)) << endl;
    }
}
