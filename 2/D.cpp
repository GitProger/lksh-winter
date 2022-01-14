#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef string str;
#define all(lalala) lalala.begin(),lalala.end()
#define len(_obj) ((int)_obj.size())
#define $ '\n'
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

vector<int> used;
bool cycle(TAB &g, int v) {
    used[v] = 1;
    bool has = false;
    for (int u : g[v]) {
        if (used[u] == 1) {
            return true;
        }
        if (used[u] == 0) has |= cycle(g, u);
    }
    used[v] = 2;
    return has;
}

void go() {
    int s = 1;
    queue<int> q; q.push(s);
    vector<int> used(n + 1);
    used[s] = 1;
    vars[s] = 1;
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int u : table[v]) {
            vars[u] = (vars[u] + vars[v]) % MOD;
            if (!used[u]) {
                used[u] = 1;
                q.push(u);
            }
        }
    }
}

inline void solve() {
    cin >> n >> m >> k;
    term = vector<int>(k);
    vars = vector<ll>(n + 1);
    for (int &e : term) { 
        cin >> e;
    }
    table = TAB(n + 1);
    used = vector<int>(n + 2);
    rtable = TAB(n + 1);
    
    for (int i = 0; i < m; i++) {
        int a, b; char c;
        cin >> a >> b >> c;
        table[a].push_back(b);
        rtable[b].push_back(a);
    }
    
    rtable.push_back(term); // new vertex n+1 -> term_i
    bool has = cycle(rtable, n + 1);
    used.assign(n + 2, 0);
    has &= cycle(table, 1);
    if (has) {
        cout << -1 << $;
        return;
    }
    
    
    
    ll sum = 0;
    go();
    for (int v : term)
        sum = (sum + vars[v]) % MOD;
    cout << sum << $;
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

*/


