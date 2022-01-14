#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef string str;
#define all(lalala) lalala.begin(),lalala.end()
#define len(_obj) ((int)_obj.size())
template <class T> istream &operator >> (istream &in, vector<T> &v) { 
    for (T &t : v) in >> t;
    return in;
}
template <class T> ostream &operator << (ostream &out, const vector<T> &v) {
    for (const T &t : v) out << t << ' ';
    return out;
}

mt19937 rnd(1337);
const ll MOD = 1000000007;
inline void solve();
signed main() {
    freopen("pratincole.in", "r", stdin);
    freopen("pratincole.out", "w", stdout);
//    cin.tie(nullptr);
//    ios_base::sync_with_stdio(false);
    int t = 1;
  //  cin >> t;
    while (t--) solve();
    cout.flush();
    cerr << "\nTime: " << setprecision(2) <<
        int(1000 * (double)clock() / CLOCKS_PER_SEC) << " ms\n";
    return 0;
}

int n, m, k;
vector<int> term;
using TAB = vector<vector<int>>;
TAB table, rtable;
vector<ll> vars;

void cyclef(TAB &g, vector<int> &used, int v, vector<int> &p, vector<pair<int, int>> &c) {
    used[v] = 1;
    for (int u : g[v]) {
        if (used[u] == 1) {
            c.emplace_back(u, v);
            return;
        } else if (used[u] == 0) {
            p[u] = v;
            cyclef(g, used, u, p, c);
        }
    }
    used[v] = 2;
}

void cycle_forward(TAB &g, vector<int> &incycle, int v) {
    vector<int> used(n + 2);
    vector<int> p(n + 2, -1);
    vector<pair<int, int>> cycles;
    cyclef(g, used, v, p, cycles);

//    cerr << "p: ";
//    for (int i = 1; i <= n; i++) cerr << p[i] << ' '; cerr << '\n';

    for (auto c : cycles) {
        int beg = c.first, cur = c.second;
//        cerr << beg << " " << cur << " ... ";
        while (cur != -1 && cur != p[beg]) {
            incycle[cur] = 1;
            cur = p[cur];
        }
//         cerr << "processed\n";
    }

//    cerr << "in: ";
//    for (int i = 1; i <= n; i++) cerr << incycle[i] << ' '; cerr << '\n';
//    cerr << "----------------\n";
}

ll go(vector<vector<int>> &g, vector<int> &used, int v) {
    if (used[v]) return vars[v];
    used[v] = 1;
    if (v == 1) return vars[v] = 1;
    ll s = 0;
    for (int u : g[v]) {
        if (used[u]) {
            s += vars[u];
            continue;
        }
        vars[u] = go(g, used, u) % MOD;
        s = (s + vars[u]) % MOD;
    }
    return s;
}

inline void solve() {
    cin >> n >> m >> k;
    term = vector<int>(k);
    vars = vector<ll>(n + 1);
    for (int &e : term) {
        cin >> e;
    }
    table = TAB(n + 1);
    rtable = TAB(n + 1);
    
    for (int i = 0; i < m; i++) {
        int a, b; char c;
        cin >> a >> b >> c;
        table[a].push_back(b);
        rtable[b].push_back(a);
    }
    
    vector<int> in_cycle(n + 2, 0);
    vector<int> rin_cycle(n + 2, 0);
    cycle_forward(table, in_cycle, 1);
    rtable.push_back(term); // new vertex n+1 -> term_i
    cycle_forward(rtable, rin_cycle, n + 1);
    
    for (int i = 1; i <= n; i++)
        if (in_cycle[i] && rin_cycle[i]) {
            cout << -1 << '\n';
            return;
        }
    
    vector<int> used(n + 2);
    ll sum = go(rtable, used, n + 1);
    cout << sum << '\n';
}
/*
6 8 1
4
1 2 x
1 6 y
2 3 c
6 5 b
3 4 a
5 4 a
2 3 d
2 4 f

!!!==============
6 7 1
4
1 2 q
2 3 q
3 2 q
1 4 q
5 4 q
5 6 q
6 5 q
!!!==============
8 9 1
2
1 2 a
2 3 b
3 4 c
4 5 d
5 6 e
6 1 f
1 8 g
8 7 h
7 6 i


*/


