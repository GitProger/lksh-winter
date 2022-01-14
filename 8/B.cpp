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
   // freopen("flow.in", "r", stdin); 
  //  freopen("flow.out", "w", stdout);
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

struct Edge {
    int a = -1, b = -1;
    int f = -1, c = -1;
    Edge(int a, int b, int f, int c) :
        a(a), b(b), f(f), c(c) 
    {}
    Edge() {}
};
int n, m, s, t;
vector<Edge> edges;
vector<vector<int>> g;
vector<int> used;

int dfs(int v, int current_flow) {
    if (v == t) return current_flow;
    if (current_flow == 0) return 0;
    used[v] = 1;
    for (int id : g[v]) {
        Edge e = edges[id];
        int able = dfs(e.b, min(current_flow, e.c - e.f));
        if (e.f < e.c && !used[e.b] && able > 0) {
            edges[id].f += able;
            edges[id ^ 1].f -= able;
            return able;
        }
    }
    return 0;
}


bool bfs() {
    queue<int> q; q.push(s);
    cerr << "A\n";
    cerr << n << " " << s << "\n";
    vector<int> used(n); //used[s] = 1;
    cerr << "B\n";
    vector<int> d(n, n); d[s] = 0;
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int id : g[v]) {
            auto e = edges[id];
            int u = e.b;
            if (!used[u] && e.f < e.c) {
                used[u] = 1;
                q.push(u);
                d[u] = d[v] + 1;
            }
        }
    }
    return used[t];
}


inline void solve() {
    cin >> n >> m;
    g.resize(n);
    used.resize(2 * m + 10);
    s = 0; t = n - 1;
    
    for (int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c; --a; --b;
        g[a].push_back(2 * i);
        edges.push_back(Edge(a, b, 0, c));
        g[b].push_back(2 * i + 1);
        edges.push_back(Edge(b, a, 0, c));
    }

    int ans = 0;
    while (bfs()) {
        used.assign(n, 0);
        int add = dfs(s, MOD);
        while (add) {
            ans += add;
            add = dfs(s, MOD);
        }
    }
    
    cout << ans << "\n";
    for (int id = 0; id < len(edges); id += 2) 
        cout << edges[id].f << "\n";

}

/*


*/
