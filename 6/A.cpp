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
    freopen("mmul.in", "r", stdin);
    freopen("mmul.out", "w", stdout);
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

ll mul(const vector<ll> &a, const vector<ll> &b) {
    ll r = 0;
    for (int i = 0; i < len(a); i++)
        r += a[i] * b[i];
    return r;
}

using vec = vector<ll>;

inline void solve() {
    int p, q, r; cin >> p >> q >> r;
    vector<vec> m1(p, vec(q));
    vector<vec> m2(q, vec(r));
    cin >> m1 >> m2;
    vector<vec> m(p, vec(r));
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++) {
            vec c;
            for (int k = 0; k < q; k++) c.push_back(m2[k][j]);
            m[i][j] = mul(m1[i], c);
        }

    for (auto e : m) cout << e << "\n";
}

/*

*/
