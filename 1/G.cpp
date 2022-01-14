#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

mt19937 rnd(1337);
const ll MOD = 1000000007;
inline void solve();
signed main() {
    freopen("rsa.in", "r", stdin);
    freopen("rsa.out", "w", stdout);
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int t = 1;
  //  cin >> t;
    while (t--) solve();
    cout.flush();
    cerr << "\nTime: " << setprecision(2) <<
        int(1000 * (double)clock() / CLOCKS_PER_SEC) << " ms\n";
    return 0;
}
#define gcd __gcd

pair<ll, ll> gcd_extended(ll a, ll b) {
    if (b == 0) return make_pair(1ll, 0ll);
    pair<ll, ll> buf = gcd_extended(b, ((a % b) + b) % b);
    ll x = buf.first, y = buf.second;
    return make_pair(y, x - (a / b) * y);
}

ll rev(ll a, ll m) {
    ll x = gcd_extended(a, m).first;
    return (x % m + m) % m;
}

ll mod(ll a, ll b) {
    return (a % b + b) % b;
}

ll random(ll l, ll r) {
    return l + rnd() % (r - l + 1);
}

ll fpow(ll a, ll x, ll p) {
    if (x == 0) return 1ll;
    ll r = fpow(a, x / 2, p) % p;
    if (x % 2 == 0) {
        return (r * r) % p;
    } else {
        return (((r * r) % p) * a) % p;
    }
}

bool eq(ll a, ll b, ll p) {
    return mod(a, p) == mod(b, p);
}

vector<ll> factor(ll n) {
    vector<ll> res;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            res.push_back(i);
            res.push_back(n / i);
            break;
        }
    }
    return res;
}


inline void solve() {
    ll n, e, C;
    cin >> n >> e >> C;
    vector<ll> f = factor(n);
    ll p = f[0], q = f[1];
    ll d = rev(e, (p - 1) * (q - 1));
    cout << fpow(C, d, n) << '\n';
}

/*
*/

