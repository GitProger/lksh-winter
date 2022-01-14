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
    freopen("karlsson.in", "r", stdin);
    freopen("karlsson.out", "w", stdout);
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
    int a, b, c; cin >> a >> b >> c;
    int n = max({a, b, c});
    vector<int> gr(n + 1);
    for (int i = 1; i <= n; i++) {
        vector<int> m;
        for (int j = (i + 1) / 2; j < i; j++)
            m.push_back(gr[j]);
        gr[i] = mex(m);
        
    }

//    for (int i = 1; i <= n; i++) cerr << gr[i] << " "; cerr << "\n";
    
    for (int i = a - 1; i >= (a + 1) / 2; i--)
        if ((gr[i] ^ gr[b] ^ gr[c]) == 0) {
            a = i;
            goto ans;
        }
    for (int i = b - 1; i >= (b + 1) / 2; i--)
        if ((gr[a] ^ gr[i] ^ gr[c]) == 0) {
            b = i;
            goto ans;
        }
    for (int i = c - 1; i >= (c + 1) / 2; i--)
        if ((gr[a] ^ gr[b] ^ gr[i]) == 0) {
            c = i;
            goto ans;    
        }
    cout << "NO\n";
    return;
ans:;
    cout << "YES\n";
    cout << a << " " << b << " " << c << "\n";
}

/*
 * 
*/
