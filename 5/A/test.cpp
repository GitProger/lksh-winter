#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef string str;
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define len(o) ((int)o.size())
template<class T>istream&operator>>(istream&in,vector<T>&v){for(T&t:v)in>>t;return in;}
template<class T>ostream&operator<<(ostream&out,const vector<T>&v){for(const T&t:v)out<<t<<' ';return out;}
mt19937 rnd(time(nullptr));
inline void solve();
signed main() {
    solve();
    return 0;
}

vector<vector<str>> table;
int h, w, c;
int mx = 0;

bool ok(int x, int y) { return 0 <= x && x < h && 0 <= y && y < w; }
vector<pair<int, int>> steps = {
    {0, -1}, {0, 1}, {-1, 0}, {1, 0}
};


vector<vector<int>> used;

bool can(const str &a, const str &b, int dx, int dy) {
    char t1 = a[0], t2 = b[0];
    if (a[1] == b[1]) return false;
    switch (t1) {
        case '0': return (dy ==  1 && (t2 == '1' || t2 == '2' || t2 == '4'))
                      || (dx ==  1 && (t2 == '2' || t2 == '3' || t2 == '5'));
        case '1': return (dy == -1 && (t2 == '0' || t2 == '3' || t2 == '4'))
                      || (dx ==  1 && (t2 == '2' || t2 == '3' || t2 == '5'));
        case '2': return (dy == -1 && (t2 == '0' || t2 == '3' || t2 == '4'))
                      || (dx == -1 && (t2 == '0' || t2 == '1' || t2 == '5'));
        case '3': return (dy ==  1 && (t2 == '1' || t2 == '2' || t2 == '4'))
                      || (dx == -1 && (t2 == '0' || t2 == '1' || t2 == '5'));
        case '4': return (dy == -1 && (t2 == '0' || t2 == '3'))
                      || (dy ==  1 && (t2 == '1' || t2 == '2'));
        case '5': return (dx == -1 && (t2 == '0' || t2 == '1'))
                      || (dx ==  1 && (t2 == '2' || t2 == '3'));
    }
    return false;
}

int cnt = 1;
int dfs(int x, int y, int depth, int px, int py) {
    used[x][y] = cnt;
    for (auto d : steps) {
        int dx = d.first, dy = d.second;
        int nx = x + dx, ny = y + dy;
        if (nx == px && ny == py) continue;
        if (!ok(nx, ny)) continue;
        if (!can(table[x][y], table[nx][ny], dx, dy)) continue;
        if (!used[nx][ny]) 
            return dfs(nx, ny, depth + 1, x, y);
        else if (used[nx][ny] == cnt) {
			cout << x+1 << " " << y+1 << " -> " << nx+1 << " " << ny+1 << "\n";
            return depth + 1;
		}
    }
    return 0;
}

int getcycles() {
    used = vector<vector<int>>(h, vector<int>(w));
    int ans = 0;
    for (int x = 0; x < h; x++)
        for (int y = 0; y < w; y++)
            if (!used[x][y]) {
                ans = max(ans, dfs(x, y, 0, -1, -1));
                cnt++;
            }
    return ans;
}

inline void solve() {
 //   cin >> h >> w >> c;
    h = w = c = 5;
    table = vector<vector<str>>(h, vector<str>(w));
    cin >> table;
    cout << "C: " << getcycles() << "\n";
}
/*

*/

