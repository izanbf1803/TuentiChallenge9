#include <bits/stdc++.h>
using namespace std;
#define D(x) cerr << #x << " = " << (x) << ", "

typedef long double Real;
typedef tuple<int,int,int64_t,int> State;

const Real SCALE = 1e16;
const Real TIME_SCALE = 6;
const int INVALID = -2;

struct Moon {
    Real d_, r_, t_;
    int u_;

    pair<Real,Real> pos(int t) const
    {
        if (t_ == 0) return make_pair(0, 0);
        Real r = r_ + TIME_SCALE * t * 2 * M_PI / t_;
        return make_pair(d_ * cos(r), d_ * sin(r));
    }
};

int64_t dist(const Moon& a, const Moon& b, int t)
{
    pair<Real,Real> pa = a.pos(t);
    pair<Real,Real> pb = b.pos(t);
    Real dx = pa.first - pb.first;
    Real dy = pa.second - pb.second;
    return SCALE*sqrt(dx*dx + dy*dy);
}

int M;
Moon m[17];
map<State,int> dp;
vector<int> path;

int solve(int mask, int i, int64_t R, int C, bool gen_path = false)
{
    // mask encodes explored moons as a bit array.

    int t = __builtin_popcount(mask); // recover time from number of visited moons

    if (m[i].u_ > C or R < 0) {
        return INVALID;
    }

    if (i == M and (mask & (1 << M))) {
        return 0; // back to base planet
    }

    State state = make_tuple(mask, i, R, C);

    auto it = dp.find(state);
    if (it != dp.end() and not gen_path) {
        return it->second; // already computed
    }

    int& ans = dp[state];
    ans = INVALID;

    int next = -1;
    for (int j = 0; j <= M; ++j) {
        if (i == j) continue;
        if (mask & (1<<j)) continue;

        int v = solve(mask|(1<<j), j, R-dist(m[i],m[j],t), C-m[i].u_);

        if (v == INVALID) continue;

        int nans = v + m[i].u_;

        if (nans > ans) {
            ans = nans;
            next = j;
        }
    }

    if (gen_path and (i != M or t == 0)) {
        assert(next != -1);
        path.push_back(m[next].u_);
        solve(mask|(1<<next), next, R-dist(m[i],m[next],t), C-m[i].u_, true);
    }

    return ans;
}

void maximize(int& a, int b)
{
    a = max(a, b);
}

int main()
{
    int tests;
    cin >> tests;
    for (int test = 0; test < tests; ++test) {
        dp.clear();

        int64_t R;
        int C;
        cin >> M;
        for (int i = 0; i < M; ++i)
            cin >> m[i].d_;
        for (int i = 0; i < M; ++i)
            cin >> m[i].r_;
        for (int i = 0; i < M; ++i)
            cin >> m[i].t_;
        for (int i = 0; i < M; ++i)
            cin >> m[i].u_;
        cin >> C;
        Real rR;
        cin >> rR;
        R = SCALE*rR;

        // m[M] represents the base planet
        m[M].d_ = 0;
        m[M].r_ = 0;
        m[M].t_ = 0;
        m[M].u_ = 0;

        int ans = solve(0, M, R, C);
        // D(ans) << endl;

        cout << "Case #" << test+1 << ": ";

        if (ans != INVALID) {
            path.clear();
            solve(0, M, R, C, true);
            path.pop_back();
            sort(path.begin(), path.end());
            for (int i = 0; i < path.size(); ++i) {
                if (i > 0) cout << " ";
                cout << path[i];
            }
        }
        else {
            cout << "None";
        }

        cout << endl;

    }
}
