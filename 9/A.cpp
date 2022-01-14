#include <bits/stdc++.h>
using namespace std;
typedef __int128 lll;
typedef long long ll;
typedef string str;
#define all(obj) obj.begin(),obj.end()
#define rall(obj) obj.rbegin(),obj.rend()
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
  //  freopen("invnim.in", "r", stdin);
  //  freopen("invnim.out", "w", stdout);
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

int mex(vector<int> &m) {
    if (len(m) == 0) return 0;
    int mx = *max_element(all(m));
    vector<int> has(mx + 1);
    for (int e : m) has[e]++;
    for (int i = 0; i <= mx; i++)
        if (!has[i]) return i;
    return mx + 1;
}

inline void solve() {
    int n; cin >> n;
    vector<int> a(n); cin >> a;
    
    vector<int> gr(n);
    for (int i = 0; i < n; i++) gr[i] = a[i];

    int x = 0;
    for (int e : gr) x ^= e;
    
    for (int i = 0; i < n; i++) {
        for (int e = 0; e < gr[i]; e++)
            if ((x ^ gr[i] ^ e) != 0) {
                cout << "FIRST\n";
                return;
            }
    }
    cout << "SECOND\n";
}
/*

*/
