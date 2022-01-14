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

int n, m;
vector<vector<int>> g;
vector<int> used, lose, win, deg, degwin, noose;

void dfs(int v, int p=-1) {
    used[v] = 1;

    if (noose[v]) {
        win[v] = lose[v] = 0;
        return;
    }
 
    if (p != -1 && win[p]) degwin[v]++;
    if (deg[v] == degwin[v]) lose[v] = 1;

    for (int u : g[v]) {
        if (lose[v]) win[u] = 1;
        if (!used[u]) dfs(u, v);
    }

    if (deg[v] <= degwin[v]) lose[v] = 1;    
    
}


inline void solve() {
    while (cin >> n >> m) {
        g = decltype(g)(n);
        noose = degwin = deg = used = lose = win = vector<int>(n);
        
        for (int i = 0; i < m; i++) {
            int v, u; cin >> v >> u; --v; --u;
            if (v == u) noose[v] = 1;
            g[u].push_back(v);
            deg[v]++;
        }
        
        vector<int> leafs;
        for (int i = 0; i < n; i++)
            if (deg[i] == 0) {
                leafs.push_back(i);
                lose[i] = 1;
            }

        for (int v : leafs)
            if (!used[v]) 
                dfs(v);
        
        //*
        cerr << "W: " <<  win << "\n";
        cerr << "L: " <<  lose << "\n";
        cerr << "DG: " <<  deg << "\n";
        cerr << "DW: " <<  degwin << "\n";
        //*/

        for (int i = 0; i < n; i++) {
            if (win[i]) cout << "FIRST\n";
            else if (lose[i]) cout << "SECOND\n";
            else cout << "DRAW\n";
        }
    }
}

/*
10 11
1 2
2 3
3 4
4 5
5 6
6 7
7 1
2 8
8 9
9 1
5 10
DRAW
DRAW
FIRST
SECOND
FIRST
DRAW
DRAW
DRAW
DRAW
SECOND


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

           1
           ^
           |
 2--->3<---4--->5
 ^    |    ^    |
 |    v    |    v
 6--->7--->8<---9
      v
      10
      v
      11


SECOND
FIRST
SECOND
FIRST
SECOND
DRAW
FIRST
SECOND
FIRST
FIRST
SECOND

 *    11

*/
