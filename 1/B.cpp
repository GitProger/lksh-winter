#include <bits/stdc++.h>
using namespace std;
#define $ '\n'
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define len(o) ((int)o.size())
typedef long long ll;
typedef vector<ll> veci;
typedef pair<ll, ll> prll;

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

prll gcd_extended(ll a, ll b) {
    if (b == 0) return make_pair(1ll, 0ll);
    prll buf = gcd_extended(b, ((a % b) + b) % b);
    ll x = buf.first, y = buf.second;
    return make_pair(y, x - (a / b) * y);
}

#define gcd __gcd
inline void solve() {
    ll a, b, c;
    cin >> a >> b >> c;
    prll r = gcd_extended(a, b);
    ll g = gcd(a, b);
    if (c % g != 0ll) {
        cout << "Impossible\n";
        return;
    }
    ll x = r.first, y = r.second;
    x *= c / g;
    y *= c / g;

    if (x > 0) {
        ll n = x / (b / g);
        x -= n * b / g;
        y += n * a / g;
    } else if (x < 0) {
        ll n = -x / (b / g);
        x += n * b / g;
        y -= n * a / g;
        if (x < 0) {
            x += b / g;
            y -= a / g;
        }
    }
    
    cout << x << " " << y << $;
}
/*
*/


