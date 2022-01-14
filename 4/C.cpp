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
    freopen("varnim.in", "r", stdin);
    freopen("varnim.out", "w", stdout);
//    cin.tie(nullptr);
//    ios_base::sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
    cout.flush();
    cerr << "\nTime: " << setprecision(2) <<
        int(1000 * (double)clock() / CLOCKS_PER_SEC) << " ms\n";
    return 0;
}


int gr(int sz) {
    if (sz % 4 == 0) return sz - 1;
    if (sz % 4 == 3) return sz + 1;
    return sz;
}

inline void solve() {
    int n; cin >> n;
    vector<int> a(n); cin >> a;
/*
    vector<int> gr(n + 1);
    for (int i = 1; i <= n; i++) {
        vector<int> m;
        for (int j = 0; j < i; j++)
            m.push_back(gr[j]);
        for (int j = 1; j <= i - 1; j++)
            m.push_back(gr[j] ^ gr[i - j]);
        gr[i] = mex(m);
    }
    cerr << gr << "\n";

// 1 2 4 3 5 6 8 7 9 10 12 11 13 14 16 15 17 18 20 19 21 22 24 23 25 26 28 27 29 30 32 31 33 34 36 35 37 38 40 39 
//*/

    int x = 0;
    for (int e : a)
        x ^= gr(e);
    cout << (x != 0 ? "FIRST" : "SECOND") << "\n"; 

}

/*
 * 
*/
