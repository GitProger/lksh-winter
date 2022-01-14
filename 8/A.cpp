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
    //freopen("retro.in", "r", stdin);
  //  freopen("retro.out", "w", stdout);
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
vector<int> used_ed;

int dfs(int v) {
    used[v] = 1;
    for (int id : g[v]) {
        Edge e = edges[id];
        if (e.f < e.c && !used[e.b] && (e.b == t || dfs(e.b))) {
            edges[id].f++;
            edges[id ^ 1].f--;
            return 1;
        }
    }
    return 0;
}

bool bfs(int s, int t) {
    queue<int> q; q.push(s);
    vector<int> used(n); used[s] = 1;
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

vector<int> path;
void dfs_rec(int v) {
    path.push_back(v);
    if (v == t) return;
    for (int id : g[v]) {
        int u = edges[id].b;
        if (!used[id] && edges[id].f == 1) {
            used[id] = 1;
            dfs_rec(u);
            return;
        }
    }
}

void newPath() {
    path.clear();
    dfs_rec(s);
    for (int e : path) cout << e + 1 << " ";
    cout << "\n";
}


inline void solve() {
    cin >> n >> m >> s >> t; --s; --t;
    g.resize(n);
    used.resize(2 * m + 10);
    
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; --a; --b;
        g[a].push_back(2 * i);
        edges.push_back(Edge(a, b, 0, 1));
        g[b].push_back(2 * i + 1);
        edges.push_back(Edge(b, a, 0, 0));
    }

    for (int i = 0; i < 2; i++) {
        used.assign(n, 0);    
        if (!dfs(s)) {
            cout << "NO\n";
            return;
        }
    }
    
    //for (auto e : edges) cout << e.a << " -> " << e.b << "   " << e.f << "/" << e.c << "\n";
    

    cout << "YES\n";
    used.assign(2 * m, 0);
    newPath();
    newPath();
}

/*


*/
