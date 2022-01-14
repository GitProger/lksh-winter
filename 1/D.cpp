#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template <class T> istream &operator >> (istream &in, vector<T> &v) {
    for (T &t : v) in >> t;
    return in;
}



mt19937 rnd(1337);
const ll MOD = 1000000007;
inline void solve();
signed main() {
//    freopen(".in", "r", stdin);
//    freopen(".out", "w", stdout);
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int t = 1;
   // cin >> t;
    while (t--) solve();
    cout.flush();
    cerr << "\nTime: " << setprecision(2) <<
        int(1000 * (double)clock() / CLOCKS_PER_SEC) << " ms\n";
    return 0;
}

pair<ll, ll> gcd_extended(ll a, ll b) {
    if (b == 0) return make_pair(1ll, 0ll);
    pair<ll, ll> buf = gcd_extended(b, ((a % b) + b) % b);
    ll x = buf.first, y = buf.second;
    return make_pair(y, x - (a / b) * y);
}

#define gcd __gcd

ll rev(ll a, ll m) {
    ll x = gcd_extended(a, m).first;
    return (x % m + m) % m;
}


ll solve(const vector<ll> &r, const vector<ll> &a) {
    int n = (int)r.size();
    ll M = 1;
    for (ll e : a) M *= e;
    vector<ll> Ms(n);
    for (int i = 0; i < n; i++) {
        Ms[i] = M / a[i];
    }

    ll x = 0;
    for (int i = 0; i < n; i++) {
        x += r[i] * Ms[i] * rev(Ms[i], a[i]);
    }
    return (x + M) % M;
}

inline void solve() {
    vector<ll> r(2), a(2);
    cin >> r >> a;
    cout << solve(r, a) << '\n';
}
/*
*/
