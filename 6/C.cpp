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
    freopen("tilings.in", "r", stdin);
    freopen("tilings.out", "w", stdout);
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

string bin(ll x, int ln) {
    string res;
    while (ln--) {
        res += x % 2 == 0 ? '0' : '1';
        x /= 2;
    }
    reverse(all(res));
    return res;
}

int hi(ll m) {
    int r = 0;
    while (m > 0) r++, m /= 2;
    return r;
}

bool bit(ll a, int i) {
    return !!(a & (1 << i));
}

ll rv(ll a) {
    return ((1LL << 60) - 1) ^ a;
}


bool haveSq(ll m1, ll m2, ll ln) {
    for (int i = 1; i < ln; i++) {
        if (!bit(m1, i - 1) && !bit(m1, i) && !bit(m2, i - 1) && !bit(m2, i)) return true;
        if (bit(m1, i - 1) && bit(m1, i) && bit(m2, i - 1) && bit(m2, i)) return true;
    }
    return false;   
}


inline void solve() {
    int n, m; cin >> n >> m;
    if (n > m) swap(n, m);
    ll sz = 1ll << n;
    vector<vec> dp(m, vec(sz));

    vector<vec> ok(sz, vec(sz));
    for (int i = 0; i < sz; i++)
        for (int j = 0; j < sz; j++)
            ok[j][i] = ok[i][j] = !haveSq(i, j, n);

    for (int i = 0; i < sz; i++)
        dp[0][i] = 1;

    for (int i = 1; i < m; i++) {
        for (ll mc = 0; mc < sz; mc++) {
            for (ll mp = 0; mp < sz; mp++) {
                if (ok[mp][mc]) {
                    dp[i][mc] += dp[i - 1][mp];
                }
            }
        }
    }
    
    ll sum = 0;
    for (int i = 0; i < sz; i++)
        sum += dp[m - 1][i];
    cout << sum << "\n";
}

/*

*/
