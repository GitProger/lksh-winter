#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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
inline void solve() {
    ll a, m;
    cin >> a >> m;
    if (gcd(a, m) != 1) {
        cout << -1 << '\n';
        return;
    }
    
    pair<ll, ll> r = gcd_extended(a, m);
    ll x = r.first;
    x = (x % m + m) % m;

    cout << x << '\n';
}
/*
*/


