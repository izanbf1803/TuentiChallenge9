#include <bits/stdc++.h>
using namespace std;
#define D(x) cerr << #x << " = " << (x) << ", "

int main()
{
    int tests;
    cin >> tests;
    for (int test = 0; test < tests; ++test) {
        long long w, h, f, p;
        cin >> w >> h >> f >> p;
        vector<char> fold(f);
        vector<pair<long long,long long>> punch(p); // vector of pairs (x,y)
        for (int i = 0; i < f; ++i) {
            cin >> fold[i];
        }
        for (int i = 0; i < p; ++i) {
            cin >> punch[i].first >> punch[i].second;
        }
        for (int i = 0; i < f; ++i) {
            p = punch.size(); // update current size
            switch (fold[i]) { // use symmetries to solve next state based on last state:
                case 'L':
                    for (int i = 0; i < p; ++i) { 
                        punch[i].first += w; // move to the right
                    }
                    w *= 2;
                    for (int i = 0; i < p; ++i) {
                        punch.push_back(make_pair(w-1-punch[i].first, punch[i].second));
                    }
                    break;
                case 'R':
                    w *= 2;
                    for (int i = 0; i < p; ++i) {
                        punch.push_back(make_pair(w-1-punch[i].first, punch[i].second));
                    }
                    break;
                case 'T':
                    for (int i = 0; i < p; ++i) {
                        punch[i].second += h; // move below
                    }
                    h *= 2;
                    for (int i = 0; i < p; ++i) {
                        punch.push_back(make_pair(punch[i].first, h-1-punch[i].second));
                    }
                    break;
                case 'B':
                    h *= 2;
                    for (int i = 0; i < p; ++i) {
                        punch.push_back(make_pair(punch[i].first, h-1-punch[i].second));
                    }
                    break;
            }
        }
        sort(punch.begin(), punch.end());
        cout << "Case #" << test+1 << ":" << endl;
        for (int i = 0; i < punch.size(); ++i) {
            cout << punch[i].first << " " << punch[i].second << endl;
        }
    }
}
