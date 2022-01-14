#include <bits/stdc++.h>
using namespace std;
typedef __int128 ll;
typedef long double ld;
#define gcd __gcd

mt19937 rnd(1337);
const ll MOD = 1000000007;
inline void solve();
#define EUJUDGE_FILE_IO_DEF
signed main() {
#ifdef EUJUDGE_FILE_IO_DEF
    freopen("pollard.in", "r", stdin);
    freopen("pollard.out", "w", stdout);
#endif
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    int t = 1;
 //   cin >> t;
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
    
    ll a = witness;
    if (a == -1ll)
        a = random(2, p - 1);
    ll g = fpow(a, t, p);
    
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

pair<ll, ll> gcd_extended(ll a, ll b) {
    if (b == 0) return make_pair(1ll, 0ll);
    pair<ll, ll> buf = gcd_extended(b, ((a % b) + b) % b);
    ll x = buf.first, y = buf.second;
    return make_pair(y, x - (a / b) * y);
}

ll rev(ll a, ll m) {
    if (gcd(a, m) != 1) return -1;
    ll x = gcd_extended(a, m).first;
    return (x % m + m) % m;
}

ll abs128(ll x) {
    if (x < 0) return -x;
    return x;
}

vector<ll> stupid_primes = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 
    73, 79, 83, 89, 97
};

ll trivial(ll n) {
    for (ll d : stupid_primes)
        if (n % d == 0) return d;
    return -1;
}

ll pollard(ll n) {
    if (isprime(n)) return n;
    ll s = trivial(n);
    if (s != -1) return s;
    
    auto f = [=, &n] (ll x) { return mod(x * x + 1, n); };
    ll x = random(1, n - 2), y = 1, i = 0, step = 2;
    while (gcd(n, abs128(x - y)) == 1ll) {
        if (i == step) {
            y = x;
            step *= 2; 
        }
        x = f(x);
        i++;
    }
    return gcd(n, abs128(x - y));
}

ostream &operator << (ostream &out, __int128 x) {
    out << (long long)x;
    return out;
}

pair<ll, ll> power(ll x) {
    if (x < 2) return make_pair(1, x);
    ld EPS = 1e-7;
    ll ans = 1, b = 0;
    for (int p = 1; p < 63; p++) {
        ld base = pow((ld)x, (ld)1.0 / (ld)p);
        if (base < 2.0) break;
        ll v = (ll)round(base);
        if (abs(base - (ld)v) < EPS) {
            ans = p;
            b = v;
        }
    }
    return make_pair(ans, b);
}



inline void solve() {
    long long x; cin >> x;    
    ll n = (ll)x;
    vector<ll> dels;
    while (n > 1) {
        ll cur = pollard(n);
        if (cur == 1) continue;
        auto pw = power(cur);
        if (pw.first > 1) cur = pw.second;

        while (n % cur == 0) {
            
            n /= cur;
            dels.push_back(cur);
        }
    }

    sort(dels.begin(), dels.end());
    for (ll e : dels) cout << (long long)e << ' ';
    cout << '\n';
}

/*
1690607689
*/
