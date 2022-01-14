#include <bits/stdc++.h>
using namespace std;
typedef __int128 lll;
typedef long long ll;
typedef long double ld;
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
//    freopen("inverse.in", "r", stdin);
  //  freopen("inverse.out", "w", stdout);
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

ld EPS = 1e-8;
using vec = vector<ld>;
using matrix = vector<vector<ld>>;

template <class T> vector<T> operator + (const vector<T> &a, const vector<T> &b) {
    vector<T> c(len(a));
    for (int i = 0; i < len(a); i++) c[i] = a[i] + b[i];
    return c;
}
template <class T> vector<T> operator - (const vector<T> &a, const vector<T> &b) {
    vector<T> c(len(a));
    for (int i = 0; i < len(a); i++) c[i] = a[i] - b[i];
    return c;
}
template <class T> vector<T> operator * (const vector<T> &a, T m) {
    vector<T> c(len(a));
    for (int i = 0; i < len(a); i++) c[i] = a[i] * m;
    return c;
}

bool zero(ld x) {
    return abs(x) < EPS;
}

vec gauss(matrix &a) {
    int n = len(a), m = len(a[0]) - 1;
    vec x(m);
    int r = 0;

    for (int i = 0; i < m; i++) {
        int found = -1;
        for (int j = r; j < n; j++) {
            if (!zero(a[j][i])) {
                found = j;
                break;
            }
        }
        if (found == -1) continue;
        if (zero(a[found][i])) continue;
        a[found].swap(a[r]);

        for (int j = 0; j < n; j++) {
            if (j == r) continue;
            ld c = a[j][i] / a[r][i];
            for (int k = i; k <= m; k++)
                a[j][k] -= a[r][k] * c;
        }
        r++;
        if (r == n) break;
    }
    
    if (r < m) {
        for (int i = 0; i < n; i++) {
            bool all_zero = true;
            for (int j = 0; j < m; j++)
                if (!zero(a[i][j])) all_zero = false;
            if (all_zero && !zero(a[i][m])) throw -1;
        }
        throw 0;
    }
    
    for (int i = m - 1; i >= 0; i--) {
        x[i] = a[i][m] / a[i][i];
        for (int c = m - 1; c > i; c--) {
            x[i] -= a[i][c] * x[c] / a[i][i];
        }
    }
            
    return x;
}

ld sum(int n, int k) {
    ld s = 0.0;
    for (int i = 1; i <= n; i++) 
        s += pow((ld)i, k);
    return s;
}

inline void solve() {
    int k; cin >> k;
    // a_k n^(k+1) | a_k-1 n^k | ... | a0 n = s(n, k)

    matrix a;
    for (int n = 1; n <= k + 1; n++) {
        vec cur(k + 1);
        for (int i = k; i >= 0; i--) cur[i] = pow((ld)n, i + 1);
        
        cur.push_back(sum(n, k));
        a.push_back(cur);
    }

    try {
        vector<ld> ans = gauss(a);
        reverse(all(ans));
        cout.precision(16);
        cout << ans << "\n";
    } catch (int err) {
        if (err == 0) {
            cerr << "inf\n";
        } else if (err == -1) {
            cerr << "emp\n";
        }
    }
}

/*

2
1 2 1
2 1 0
-0.333 0.666

2
1 1 1
2 2 2
infinity

2
1 2 0
1 2 1
impossible

*/
