#include <bits/stdc++.h>
using namespace std;
typedef __int128 int128;

mt19937 rnd(time(nullptr));
const long long MOD = 1000000007;
inline void solve();
signed main() {
    freopen("pollard.in", "r", stdin);
    freopen("pollard.out", "w", stdout);
   // cin.tie(nullptr);
    //ios_base::sync_with_stdio(false);
    int t = 1;
 //   cin >> t;
    while (t--) solve();
    cout.flush();
    cerr << "\nTime: " << setprecision(2) <<
        int(1000 * (double)clock() / CLOCKS_PER_SEC) << " ms\n";
    return 0;
}

int128 mod(int128 a, int128 b) {
    return (a % b + b) % b;
}

int128 random(int128 l, int128 r) {
    return l + rnd() % (r - l + 1);
}

int128 fpow(int128 a, int128 x, int128 p) {
    if (x == 0) return 1ll;
    int128 r = fpow(a, x / 2, p) % p;
    if (x % 2 == 0) {
        return (r * r) % p;
    } else {
        return (((r * r) % p) * a) % p;
    }
}

bool eq(int128 a, int128 b, int128 p) {
    return mod(a, p) == mod(b, p);
}

inline bool test(int128 p, int128 witness = -1) {
    if (p < 2) return 0;
    if (p <= 3) return 1;
    if (p % 2 == 0) return 0;
        
    int128 t = p - 1, s = 0;
    while (t % 2 == 0) {
        t /= 2;
        s++;
    }
    
    int128 a = witness;
    if (a == -1ll)
        a = random(2, p - 1);
    int128 g = fpow(a, t, p);
    
    if (eq(g, 1, p) || eq(g, -1, p)) return 1;
    for (int128 i = 0; i < s - 1; i++) {
        g = (g * g) % p;
        if (eq(g, 1, p)) return 0;
        if (eq(g, -1, p)) return 1;
    }
    //cerr << "! " << g << " -> " << a << " ^ " << t << " % " << p << endl;
    return eq(g, 1, p);
}

bool isprime(int128 x) {
    for (int good : {2, 3, 5, 7, 13, 17, 23, 561}) {
        if (good < x && !test(x, good)) return false;
    }
    for (int q = 0; q < 10; q++) {
        if (!test(x)) return false;
    }
    return true;
}

pair<int128, int128> gcd_extended(int128 a, int128 b) {
    if (b == 0) return make_pair(1ll, 0ll);
    pair<int128, int128> buf = gcd_extended(b, ((a % b) + b) % b);
    int128 x = buf.first, y = buf.second;
    return make_pair(y, x - (a / b) * y);
}

int128 rev(int128 a, int128 m) {
    if (__gcd(a, m) != 1) return -1;
    int128 x = gcd_extended(a, m).first;
    return (x % m + m) % m;
}

int128 abs128(int128 x) {
    if (x < 0) return -x;
    return x;
}

vector<int128> stupid_primes = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 
    73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 
    157, 163, 167, 173, 179, 181, 191, 193, 197, 199
};

int128 trivial(int128 n) {
    for (int128 d : stupid_primes)
        if (n % d == 0) return d;
    return -1;
}

int128 point128ard(int128 n) {
    if (isprime(n)) return n;
    int128 s = trivial(n);
    if (s != -1) return s;    
    auto f = [=, &n] (int128 x) { return (x * x + 1) % n; };

    int128 x = random(2, n - 1);
    int128 k = ceil(pow(n, 0.25));
    for (int128 i = 0; i <= k; i++) x = f(x);
    int128 y = f(x);
    
    for (int128 i = 0; i <= k - 1; i++) {
        int128 g = __gcd(abs128(x - y), n);
        if (g != 1ll && g != n)
            return g;
        y = f(y);
    }
    return 1;
}


inline void solve() {
    long long x; cin >> x;
    
    int128 n = (int128)x;
    vector<int128> multipliers;
    while (n > 1) {
        int128 cur = point128ard(n);
        if (cur == 1ll) continue;
        while (n % cur == 0) {
            n /= cur;
            multipliers.push_back(cur);
        }
    }

    sort(multipliers.begin(), multipliers.end());
    for (int128 e : multipliers) cout << (long long)e << ' ';
    cout << '\n';
}

/*
1690607689
*/
