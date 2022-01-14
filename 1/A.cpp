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

inline void solve() {
    ll n = (ll)1e8;
    ll l, r; cin >> l >> r;
    vector<ll> primes;
    vector<ll> d(n + 1ll, -1ll);
    ll s = 0ll;
    for (ll i = 2; i <= n; i++) {
        if (d[i] == -1ll) {
            d[i] = int(primes.size());
            primes.push_back(i);
        }
        for (ll j = 0; j <= d[i] && i * primes[j] <= n; j++) {
            ll k = i * primes[j];
            if (d[k] == -1) d[k] = j;
        }
    }

    cout << '\n';
    for (ll i = l; i <= r; i++)
        s += primes[d[i]];
    
    cout << s << '\n';
}
/*

*/

