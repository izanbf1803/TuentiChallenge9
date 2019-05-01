#include <bits/stdc++.h>
using namespace std;

struct Character {
    int name, cost;
    bitset<98> skill; // there are 98 different skills
};

int C, F;
unordered_map<string,int> names_table, skills_table;
vector<Character> characters;
multimap<int,pair<int,int>> fuses;
vector<unordered_map<bitset<98>,Character>> dp;

int id_from_table(unordered_map<string,int>& table, const string& s)
{
    auto it = table.find(s);
    if (it != table.end()) return it->second;
    int id = table.size();
    table[s] = id;
    return id;
}   

void parse_almanac(const string& filename)
{
    string _; // to ignore some strings in input
    ifstream file(filename);
    file >> C >> F;
    characters.resize(C);
    for (int i = 0; i < C; ++i) {
        Character& c = characters[i];
        c.skill.reset();
        string name;
        int n_skills;
        file >> name >> _ >> c.cost >> n_skills;
        c.name = id_from_table(names_table, name);
        for (int j = 0; j < n_skills; ++j) {
            string skill;
            file >> skill;
            int sid = id_from_table(skills_table, skill);
            c.skill.set(sid);
        }
    }
    for (int i = 0; i < F; ++i) {
        string a, b, c;
        file >> a >> b >> c;
        int ida = id_from_table(names_table, a);
        int idb = id_from_table(names_table, b);
        int idc = id_from_table(names_table, c);
        fuses.insert(make_pair( ida, make_pair(idb, idc) ));
    }
    file.close();
}

Character fuse(Character ca, Character& cb, Character& cc)
{
    ca.skill |= cb.skill;
    ca.skill |= cc.skill;
    ca.cost = cb.cost + cc.cost;
    return ca;
}

Character solve(int name, bitset<98> req)
{
    // this method finds the cheapest way to get the character with name <name> with skills that satisfy <req>.

    Character& ch = characters[name];
    
    auto it = dp[name].find(req);
    if (it != dp[name].end()) return it->second;

    Character& sol = dp[name][req];
    sol.cost = INT_MAX;
    req = req & ~(req & ch.skill);
    if (req.count() == 0) {
        sol = ch;
    }
    for (auto it = fuses.equal_range(name).first; it != fuses.equal_range(name).second; ++it) {
        int a = it->second.first;
        int b = it->second.second;
        vector<int> bits;
        for (int i = 0; i < 98; ++i) {
            if (req[i]) bits.push_back(i);
        }
        for (int mask = 0; mask < (1 << bits.size()); ++mask) { // all subsets of bits[]
            bitset<98> req_a;
            for (int j = 0; j < bits.size(); ++j) {
                if (mask & (1 << j)) req_a.set(bits[j]);
            }   
            bitset<98> req_b = req & ~req_a;
            Character ca = solve(a, req_a);
            if (ca.cost == INT_MAX) continue;
            Character cb = solve(b, req_b);
            if (cb.cost == INT_MAX) continue;
            Character f = fuse(ch, ca, cb);
            if (f.cost < sol.cost) {
                sol = f;
            }
        }
    }
    return sol;
}

int main()
{
    parse_almanac("almanac.txt");
    dp.resize(C);

    int tests;
    cin >> tests;
    for (int test = 0; test < tests; ++test) {
        int G, S;
        string str_name;
        bitset<98> skill;
        cin >> G >> str_name >> S;
        int name = id_from_table(names_table, str_name);
        for (int i = 0; i < S; ++i) {
            string str_skill;
            cin >> str_skill;
            int sid = id_from_table(skills_table, str_skill);
            skill.set(sid);
        }
        int cost = solve(name, skill).cost;
        cout << "Case #" << test+1 << ": ";
        if (cost > G) {
            cout << "IMPOSSIBLE" << endl;
        }
        else {
            cout << cost << endl;
        }
    }
}
