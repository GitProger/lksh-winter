#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

mt19937 rnd(1337);
const ll MOD = 1000000007;
inline void solve();
signed main() {
 //   freopen("again.in", "r", stdin);
 //   freopen("again.out", "w", stdout);
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int t = 1;
    cin >> t;
    while (t--) solve();
    cout.flush();
    cerr << "\nTime: " << setprecision(2) <<
        int(1000 * (double)clock() / CLOCKS_PER_SEC) << " ms\n";
    return 0;
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

inline bool test(ll p, ll witness = -1) {
    if (p < 2) return 0;
    if (p <= 3) return 1;
    if (p % 2 == 0) return 0;
        
    ll t = p - 1, s = 0;
    while (t % 2 == 0) {
        t /= 2;
        s++;
    }
    
//    cerr << p << " = 2 ^ " << s << " * " << t << '\n';
    ll a = witness;
    if (a == -1ll)
        a = random(2, p - 1);
    ll g = fpow(a, t, p);
    
//    cerr << a << " ^ " << t << " = " << g << '\n';
    
    if (eq(g, 1, p) || eq(g, -1, p)) return 1;
    for (ll i = 0; i < s - 1; i++) {
        g = (g * g) % p;
        if (eq(g, 1, p)) return 0;
        if (eq(g, -1, p)) return 1;
    }
    //cerr << "! " << g << " -> " << a << " ^ " << t << " % " << p << endl;
    return eq(g, 1, p);
}

bool isprime(ll x) {
    for (int good : {2, 3, 5, 7, 13, 17, 23, 561}) {
        if (good < x && !test(x, good)) return false;
    }
    for (int q = 0; q < 20; q++) {
        if (!test(x)) return false;
    }
    return true;
}

inline void solve() {
    ll x; cin >> x;
    cout << (isprime(x) ? "YES" : "NO") << '\n';
}

/*
*/

