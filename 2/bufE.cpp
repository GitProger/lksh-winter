//https://neerc.ifmo.ru/wiki/index.php?title=Минимизация_ДКА,_алгоритм_за_O(n%5E2)_с_построением_пар_различимых_состояний
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

str alpha;
int n, k, q0;
vector<int> term;
vector<map<char, int>> table, rtable;

void dfs(vector<map<char, int>> &g, vector<int> used, int v) {
    used[v] = 1;
    for (auto next : g[v]) {
        int u = next.second;
        if (!used[u]) dfs(g, used, u);
    }
}


inline void solve() {
    cin >> alpha;
    cin >> n;
    term.resize(n + 1);
    table.resize(n + 1);
    klass.resize(n + 1);
    cin >> q0 >> k; 
    for (int i = 0; i < k; i++) {
        int e; cin >> e;
        term[e] = 1;
    }
    
    for (int v = 1; v <= n; v++) {
        for (char c : alpha) {
            int u; cin >> u;
            table[v][c] = u;
            rtable[u][c] = v;
        }
    }
    
    vector<int> used(n + 1);
    dfs(table, used, 1);

    vector<vector<int>> diff(n + 1, vector<int>(n + 1));    
    queue<pair<int, int>> pairs;
    for (int p = 1; p <= n; p++)
        for (int q = 1; q <= n; q++)
            if (!diff[p][q] && term[p] != term[q]) {
                diff[p][q] = diff[q][p] = 1;
                pairs.push({p, q});
            }
    
    while (!pairs.empty) {
        auto top = pairs.front(); pairs.pop();
        int u = top.first, v = top.second;
        for (char c : alpha)
            for (int r : rtable[u][c])
                for (int s : rtable[v][c]) {
                    diff[r][s] = diff[s][r] = 1;
                    pairs.push({r, s});
                }
    }
    
    
}
/*


*/


