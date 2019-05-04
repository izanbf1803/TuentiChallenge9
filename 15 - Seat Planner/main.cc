#include <bits/stdc++.h>
using namespace std;
#define D(x) cout << #x << " = " << x << ", "

int n; // number of people
vector<vector<int>> adj;
vector<int> parent;
vector<int> size;
vector<int> unions;
vector<vector<int>> dp;
vector<bool> visited;

int ufind(int u)
{
    if (parent[u] == -1) return u;
    parent[u] = ufind(parent[u]);
    return parent[u];
}

void ujoin(int u, int v)
{
    u = ufind(u);
    v = ufind(v);
    if (u != v) {
        parent[v] = u;
        size[u] += size[v];
    }
}

int unions_subset_with_size(int m, int s)
{
    // m: unions subarray size, s: objective size
    int& ans = dp[m][s];
    if (ans != -1) return ans;
    if (s == 0) {
        ans = 1;
    }
    else if (m == 0) {
        ans = 0;
    }
    else if (size[unions[m-1]] > s) {
        ans = unions_subset_with_size(m-1, s);
    }
    else {
        ans = unions_subset_with_size(m-1, s) | unions_subset_with_size(m-1, s-size[unions[m-1]]);
    }
    return ans;
}

vector<int> reconstruct_subset_with_size(int m, int s)
{
    if (s == 0) {
        return {};
    }
    else if (m == 0) {
        return {-1};
    }
    else if (size[unions[m-1]] > s) {
        return reconstruct_subset_with_size(m-1, s);
    }
    else {
        if (unions_subset_with_size(m-1, s)) {
            return reconstruct_subset_with_size(m-1, s);
        }
        else if (unions_subset_with_size(m-1, s-size[unions[m-1]])) {
            vector<int> sol = reconstruct_subset_with_size(m-1, s-size[unions[m-1]]);
            sol.push_back(unions[m-1]);
            return sol;
        }
        return {-1}; // error
    }
}

int find_dfs_root(int u)
{
    for (int i = 1; i <= n; ++i) {
        if (ufind(i) == u and adj[i].size() == 1) {
            return i;
        }
    }   
    return u; // if not dfs root found
}

void solve_union(vector<int>& v, int i)
{
    visited[i] = true;
    for (int x : adj[i]) {
        if (not visited[x]) solve_union(v, x);
    }
    v.push_back(i);
}

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    if (argc != 2) {
        cout << "ERROR: INVALID INPUT" << endl;
        exit(1);
    }
    istringstream in(argv[1]);
    int S, K;
    in >> S >> K;
    n = 8*S;
    adj.resize(n+1);
    parent.assign(n+1, -1);
    size.assign(n+1, 1);

    for (int i = 0; i < K; ++i) {
        int a, b;
        in >> a >> b;
        if (a > b) swap(a, b);
        adj[a].push_back(b);
        adj[b].push_back(a);
        ujoin(a, b);
    }

    for (int i = 1; i <= n; ++i) {
        if (ufind(i) == i) {
            unions.push_back(i);
        }
    }

    sort(unions.begin(), unions.end(), [](int u, int v){
        return size[u] > size[v];
    });

    vector<vector<int>> tables(8);

    for (int t = 0; t < 8; ++t) {
        dp.assign(unions.size()+1, vector<int>(S+1, -1));
        vector<int> sol = reconstruct_subset_with_size(unions.size(), S);
        for (int u : sol) {
            tables[t].push_back(u);
            unions.erase(find(unions.begin(), unions.end(), u));
        }
    }

    for (int t = 0; t < 8; ++t) {
        vector<int> table;
        for (int u : tables[t]) {
            visited.assign(n+1, false);
            vector<int> sol;
            solve_union(sol, find_dfs_root(u));
            for (int x : sol) {
                table.push_back(x);
            }
        }
        tables[t] = table;
    }

    for (int t = 0; t < 8; ++t) {
        for (int i = 0; i < S; ++i) {
            if (i > 0) cout << ",";
            cout << tables[t][i];
        }
        cout << endl;
    }
}