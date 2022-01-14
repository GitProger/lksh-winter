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
    freopen("mpow.in", "r", stdin);
    freopen("mpow.out", "w", stdout);
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


using vec = vector<ll>;
using matrix = vector<vector<ll>>;


ll mul(const vector<ll> &a, const vector<ll> &b, ll p) {
    ll r = 0;
    for (int i = 0; i < len(a); i++) {
        r += a[i] * b[i];
        r %= p;
    }
    return r % p;
}

matrix mul(const matrix &a, const matrix &b, ll p) {
    int n = len(a);
    matrix c(n, vec(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            vec v;
            for (int k = 0; k < n; k++) v.push_back(b[k][j]);
            c[i][j] = mul(a[i], v, p);
        }
    return c;
}


matrix fpow(const matrix &a, ll x, ll p) {
    if (x == 0) {
        matrix ans(len(a), vec(len(a), 0));
        for (int i = 0; i < len(a); i++) ans[i][i] = 1;
        return ans;
    }
    matrix r = fpow(a, x / 2, p);
    if (x % 2 == 0) {
        return mul(r, r, p);
    } else {
        matrix m = mul(r, r, p);
        return mul(m, a, p);
    }
}

inline void solve() {
    ll n, m, p; cin >> n >> m >> p;
    vector<vec> mtx(n, vec(n));
    cin >> mtx;
    auto ans = fpow(mtx, m, p);
    for (auto row : ans) cout << row << "\n";
}

/*
3 5 239
1 0 1
1 2 0
3 2 1
*/
