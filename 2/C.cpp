#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
using namespace std;
typedef long long ll;
typedef string str;
#define all(lalala) lalala.begin(),lalala.end()


mt19937 rnd(1337);
const ll MOD = 1000000007;
inline void solve();
signed main() {
    freopen("hawfinch.in", "r", stdin);
    freopen("hawfinch.out", "w", stdout);
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
#define gcd __gcd

str s;
int n, m, k;
vector<int> term;
using TAB = vector<
        map<char, 
            vector<int>
        >
    >;
TAB table;

bool go(int q, int index) {
    if (q == 0) return false;
    if (index == (int)s.length()) return term[q];
    vector<int> used(n + 1);
    for (int next : table[q][s[index]]) {
        if (!used[next] && go(next, index + 1))
            return true;
        used[next] = 1;
    }
    return false;
}

inline void solve() {
    cin >> s;
//s=str(10000, 'a');
    cin >> n >> m >> k;

//n=100;m=1000;k=0;
    term = vector<int>(n + 1);
    table = TAB(n + 1);

    for (int i = 0; i < k; i++) { 
        int a; cin >> a;
        term[a] = 1;
    }
    
    for (int i = 0; i < m; i++) {
        int a, b; char c;
        cin >> a >> b >> c;
//a=b=1;c='a';
        table[a][c].push_back(b);
    }

    bool res = go(1, 0);
    
    cout << (
        res ? "Accepts" : "Rejects"
    ) << '\n';
}
/*

*/
