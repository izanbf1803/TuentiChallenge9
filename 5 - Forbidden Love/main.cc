#include <bits/stdc++.h>
using namespace std;

int mod(int a, int m)
{
    return (a % m + m) % m;
}

int main()
{
    const int w = 10;
    const int h = 4;
    const vector<string> key = {
        "1234567890",
        "QWERTYUIOP",
        "ASDFGHJKL;",
        "ZXCVBNM,.-",
    };
    unordered_map<char,pair<int,int>> idx;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            idx[key[i][j]] = make_pair(j, i);
        }
    }
    int tests;
    cin >> tests;
    for (int test = 0; test < tests; ++test) {
        char p;
        cin >> p;
        cin.ignore();
        string str;
        getline(cin, str);
        int offsetX = mod(idx[p].first - idx[str.back()].first, w);
        int offsetY = mod(idx[p].second - idx[str.back()].second, h);
        for (char& c : str) {
            if (idx.count(c)) {
                int j = mod(idx[c].first + offsetX, w);
                int i = mod(idx[c].second + offsetY, h);
                c = key[i][j];
            }
        }
        cout << "Case #" << test+1 << ": " << str << endl;
    }
}
