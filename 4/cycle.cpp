#include <bits/stdc++.h>
using namespace std;
typedef __int128 lll;
typedef long long ll;
typedef string str;
#define all(obj) obj.begin(),obj.end()
#define rall(obj) obj.rbegin(),robj.end()
#define len(obj) ((int)obj.size())

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
    freopen("retro.in", "r", stdin);
    freopen("retro.out", "w", stdout);
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

int n, m;
vector<vector<int>> g;
vector<int> used;
vector<int> lose, win;

void cyclef(vector<vector<int>> &g, vector<int> &used, int v, vector<int> &p, vector<pair<int, int>> &c) {
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

void cycle_forward(
        vector<vector<int>> &g, 
        vector<vector<int>> &cycles_ans, 
        vector<int> &incycle, 
        vector<int> &used, 
        int v) 
{
    vector<int> p(n, -1);
    vector<pair<int, int>> cycles;
    cyclef(g, used, v, p, cycles);

    for (auto c : cycles) {
        vector<int> cur_cycle;
        int beg = c.first, cur = c.second;
        while (cur != -1 && cur != p[beg]) {
            cur_cycle.push_back(cur);
            incycle[cur] = 1;
            cur = p[cur];
        }
        cycles_ans.push_back(cur_cycle);
    }
}

vector<vector<int>> get_cycles(vector<vector<int>> &g, vector<int> &incycle) {
    int n = len(g);
    vector<int> used(n);
    vector<vector<int>> cycles(n);
    for (int v = 0; v < n; v++) {
        if (!used[v])
            cycle_forward(g, cycles, incycle, used, v);
    }
    return cycles;
}

void dfs(int v) {
    used[v] = 1;
    for (int u : g[v]) {
        if (win[v]) lose[u] = 1;
        if (lose[v]) win[u] = 1;
    }
    for (int u : g[v]) {
        if (!used[u]) dfs(u);
    }
}


inline void solve() {
    while (cin >> n >> m) {
        g = decltype(g)(n);
        decltype(g) orig(n);
        used = lose = win = vector<int>(n + 1);
        
        vector<int> deg(n);
        for (int i = 0; i < m; i++) {
            int v, u; cin >> v >> u; --v; --u;
            g[u].push_back(v);
            orig[v].push_back(u);
            deg[v]++;
        }
        
        vector<int> leafs;
        for (int i = 0; i < n; i++)
            if (deg[i] == 0) {
                leafs.push_back(i);
                lose[i] = 1;
            }
        g.push_back(leafs);
        dfs(n);

        vector<int> incycle(n);
        auto cycles = get_cycles(orig, incycle);

        vector<int> draw(n);
        for (auto cycle : cycles) {
    //        cerr << cycle << " !!!\n";
            for (int v : cycle) draw[v] = 1;
            bool can_escape = false;
            
            for (int v : cycle) {
                if (can_escape) break;
                for (int u : orig[v]) {
                    if (!incycle[u] && lose[u]) {
                        can_escape = true;
          //              cerr << "from " << v << " run to " << u << "\n";
                        break;
                    }
                }
            }
     //       cerr << "escape: " << can_escape << "\n";
            if (can_escape)
                for (int v : cycle) draw[v] = 0;
        }
    //    cerr << incycle << "\n";
    //    cerr << draw << "\n";
    //    cerr << win << "\n" << lose << "\n--------\n";
        
        for (int i = 0; i < n; i++) {
            if (draw[i]) cout << "DRAW\n";
            else if (win[i]) cout << "FIRST\n";
            else if (lose[i]) cout << "SECOND\n";
            else cout << "DRAW\n";
        }
    }
}

/*
5 5
1 2
2 3
3 1
1 4
4 5
DRAW
DRAW
DRAW
FIRST
SECOND

2 1
1 2
FIRST
SECOND

4 4
1 2
2 3
3 1
1 4
FIRST
FIRST
SECOND
SECOND

*/
