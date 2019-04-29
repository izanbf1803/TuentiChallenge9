#include <bits/stdc++.h>
using namespace std;

int main()
{
    int c;
    cin >> c;
    for (int t = 0; t < c; ++t) {
        int n, m;
        cin >> n >> m;
        /*
            Every two persons in N or M we need 1 tortilla, but if number is even we need N/2+1 or M/2+1.
            ceil(N/2) + ceil(M/2) will give correct answer in both cases for N and M.
        */
        cout << "Case #" << t+1 << ": " << (n+1)/2 + (m+1)/2 << endl;
    }
}
