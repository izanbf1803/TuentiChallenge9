#include <bits/stdc++.h>
using namespace std;

typedef unsigned char byte;
typedef array<byte,16> Hash;

Hash notSoComplexHash(const string& text, int offset = 0) 
{
    Hash hash;
    fill(hash.begin(), hash.end(), 0);
    for (int i = 0; i < text.size(); ++i) {
        hash[(i+offset)%16] += text[i];
    }
    return hash;
}

Hash operator-(Hash a, Hash b)
{
    Hash ans;
    for (int i = 0; i < 16; ++i) {
        ans[i] = a[i] - b[i];
    }
    return ans;
}

vector<byte> k_sum(int k, byte v)
{
    /*
    generate vector of size k with sum equal to v mod 256 where
    all values lie in range [48, 122].
    */
    if (k == 1) { // base case
        if (v >= 48 and v <= 122) return {v};
    }
    else {
        for (byte x = 48; x <= 122; ++x) { // lexicographically smallest solution
            vector<byte> sol = k_sum(k-1, v-x);
            if (not sol.empty()) {
                sol.push_back(x);
                return sol;
            }
        }
    }
    return vector<byte>(); // unable to solve
}

int main()
{
    vector<byte> minv(256); // modular inverse table
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            if (i*j%256 == 1) {
                minv[i] = j;
                break;
            }
        }
    }
    int tests;
    cin >> tests;
    for (int test = 0; test < tests; ++test) {
        int m, l;

        cin >> m;
        cin.ignore();
        string otext; // original text
        for (int i = 0; i < m; ++i) {
            string line;
            getline(cin, line);
            otext += line;
        }

        cin >> l;
        cin.ignore();
        string text1;
        string text2;
        int idx = -1;
        bool half = true;
        for (int i = 0; i < l; ++i) {
            string line;
            getline(cin, line);
            if (line == "------") {
                text1 += "---";
                text2 += "---";
                half = false;
            }
            else {
                if (half) {
                    text1 += line;
                }
                else {
                    text2 += line;
                }   
            }
        }

        string payload = "";
        for (int len = 16; len <= 80; ++len) {
            Hash h1 = notSoComplexHash(text1);
            Hash h2 = notSoComplexHash(text2, text1.size()+len);
            Hash h3 = notSoComplexHash(otext);
            Hash h4 =  (h3 - h1 - h2); // expected hash value for payload (with shfit offset)
            string s = string(len, '*');
            bool solved = true;
            for (int i = 0; i < 16; ++i) { // solve all indices 16k+i independently
                int j = (text1.size()+i)%16;
                int k = (len-1-i)/16+1;
                vector<byte> sol = k_sum(k, h4[j]);
                if (sol.empty()) {
                    solved = false;
                    break;
                }
                sort(sol.begin(), sol.end()); // lexicographically smallest solution
                for (int j = 0; j < k; ++j) { // merge solutions
                    s[i+16*j] = sol[j];
                }
            }
            if (solved) {
                payload = s;
                break;
            }
        }

        if (notSoComplexHash(otext) != notSoComplexHash(text1+payload+text2)) {
            cout << "ERROR ON TESTCASE #" << test+1 << endl << endl;
            exit(1);
        }
        cout << "Case #" << test+1 << ": " << payload << endl;
    }
}
