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
    freopen("inverse.in", "r", stdin);
    freopen("inverse.out", "w", stdout);
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

ld EPS = 1e-7;
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

void inv_gauss(matrix &a) {
    int n = len(a);
    int r = 0;

    for (int i = 0; i < n; i++) {
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
            for (int k = i; k < n + n; k++)
                a[j][k] -= a[r][k] * c;
        }
        r++;
        if (r == n) break;
    }
    
    if (r < n) throw 0;
}

inline void solve() {
    int n; cin >> n;
    matrix a(n, vec(n));
    cin >> a;
    
    matrix E(n, vec(n));
    for (int i = 0; i < n; i++) E[i][i] = 1.0;

    for (int i = 0; i < n; i++) 
        for (ld el : E[i]) 
            a[i].push_back(el);

    try {
        inv_gauss(a);
        cout << "YES\n";
        cout.precision(16);
        for (int i = 0; i < n; i++) {
            for (int j = n; j < 2 * n; j++) cout << a[i][j] / a[i][i] << " ";
            cout << "\n";
        }
    } catch (int) {
        cout << "NO\n";
    }
}
/*
         (\___/)
         (='.'=)
         (")_(")
*/
/*

3
0 2 0
0 0 3
1 1 0

-0.5 0 1
0.5 0 0
0 0.33 0
*/
