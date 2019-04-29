#include <bits/stdc++.h>
using namespace std;
#define D(x) cerr << #x << " = " << (x) << ", "

vector<int> color;
vector<set<char>> adj; // adjacency list
bool is_dag;
vector<char> order;

/*
    I create a graph in O(n log n) time using the given words order, then
    i try to sort it topologically, and i check if this order is unique.
    For example, from:
        >> dad
        >> bad
    we deduce b > d and i create an edge b -> d to represent this.
*/

void dfs(int u)
{
    if (color[u] == 2) return;
    if (color[u] == 1) {
        is_dag = false;
        return;
    }
    color[u] = 1;
    for (int v : adj[u]) {
        dfs(v);
    }
    color[u] = 2;
    order.push_back(u); // topological sort
}

int main()
{
    int tests;
    cin >> tests;
    for (int test = 0; test < tests; ++test) {
        int m;
        cin >> m;
        cout << "Case #" << test+1 << ": ";
        vector<string> s(m);
        adj.assign(256, set<char>());
        vector<int> in_degree(256, 0);
        set<char> alphabet;
        for (int i = 0; i < m; ++i) {
            cin >> s[i];
            for (char c : s[i]) {
                alphabet.insert(c);
            }
        }
        for (int i = 1; i < m; ++i) {
            const string& a = s[i-1];
            const string& b = s[i];
            for (int j = 0; j < min(a.size(), b.size()); ++j) {
                if (a[j] != b[j]) {
                    adj[a[j]].insert(b[j]);
                    ++in_degree[b[j]];
                    break;
                }
            }
        }
        bool solved = false;
        int feasible_roots = 0;
        char root = '_';
        for (char l : alphabet) {
            if (in_degree[l] == 0) {
                ++feasible_roots;
                root = l;
            }
        }
        if (feasible_roots == 1 and root != '_') {
            color.assign(256, 0);
            is_dag = true;
            order.clear();
            dfs(root);
            solved = true;
            for (int i = order.size()-1; i >= 1; --i) {
                if (not adj[order[i]].count(order[i-1])) { // check uniqueness
                    solved = false;
                    break;
                }
            }
            if (solved) {
                for (int i = order.size()-1; i >= 0; --i) {
                    cout << order[i];
                    if (i > 0) cout << ' ';
                }
                cout << endl;
            }
        }
        if (not solved) {
            cout << "AMBIGUOUS" << endl;
        }
    }
}
