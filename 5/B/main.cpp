#include <bits/stdc++.h>
using namespace std;
#define len(o) ((int)o.size())
mt19937 rnd(time(nullptr));
inline void solve();
signed main() {
    solve();
    return 0;
}

class Corparation {
    public:
        struct Emp {
            int id = -1;
            int x = 0, y = 0;
            Emp() {}
            Emp(int x, int y) : x(x), y(y) {}
        };

        int ID = 0;
        int TIME = 0;
        int CHARGES = 0;
        int sz = 0, salary = 0, fine = 0;
        vector<Emp> staff;
        int staff_count = 0;
        vector<vector<int>> cityMap;
        map<pair<int, int>, int> distr;

        vector<vector<int>> CloudPrev, CloudCur;
        static void initSqMap(vector<vector<int>> &x, int s) {
            x.resize(s);
            for (auto &row : x) row.resize(s);
        }

        Corparation(int b, int s, int f):
            sz(b), salary(s), fine(f)
        {
            initSqMap(cityMap, sz);
            initSqMap(CloudPrev, sz);
            initSqMap(CloudCur, sz);
        }

        void hire(int x, int y) {
            cout << "H " << x << " " << y << endl;
            staff.push_back(Emp(x, y));
            staff_count++;
            ID++;
            distr[make_pair(x, y)]++;
        }
        
        
        bool ok(int id, char d) {
            switch (d) {
                case 'U': return staff[id].x - 1 >= 0;
                case 'D': return staff[id].x + 1 < sz;
                case 'L': return staff[id].y - 1 >= 0;
                case 'R': return staff[id].y + 1 < sz;
            }
            return true;            
        }
        
        void move(int id, char d) {
            cout << "M " << id << " " << d << endl;
            distr[make_pair(staff[id].x, staff[id].y)]--;
            switch (d) {
                case 'U': staff[id].x--; break;
                case 'D': staff[id].x++; break;
                case 'L': staff[id].y--; break;
                case 'R': staff[id].y++; break;
            }
            distr[make_pair(staff[id].x, staff[id].y)]++;
        }
                
        void update() {
            CHARGES += staff_count * salary;
            for (int x = 0; x < sz; x++)
                for (int y = 0; y < sz; y++)
                    if (cityMap[x][y] == 1) {
                        if (distr[{x, y}] > 0)
                            cityMap[x][y] = 0;
                        else
                            CHARGES += fine;
                    }
        }
        
        void read() {
            int k; cin >> k;
            if (k == 0) return;
            for (int i = 0; i < k; i++) {
                int x, y; cin >> x >> y;
                cityMap[x][y] = 1;
            }
        }
        
        pair<int, int> nearestSnow(int id) {
            int mn = 2 * sz;
            pair<int, int> ans(-1, -1);
            for (int x = 0; x < sz; x++)
                for (int y = 0; y < sz; y++) {
                    if (!cityMap[x][y] || distr[{x, y}] > 0) continue;
                    int d = abs(x - staff[id].x) + abs(y - staff[id].y);
                    if (mn > d && d < sz / 3) {
                        mn = d;
                        ans = {x, y};
                    }
                }
            return ans;
        }
        
        char opt(int id, pair<int, int> c) {
            int x = c.first, y = c.second;
            int mx = staff[id].x, my = staff[id].y;
            if (abs(x - mx) > abs(y - my)) {
                if (mx > x) return 'U';
                else return 'D';
            } else {
                if (my > y) return 'L';
                else return 'R';
            }
        }
        
        vector<pair<int, int>> shouldHire() {
            vector<pair<int, int>> ans;
            if (ID == 100) return ans;
            vector<pair<int, int>> snow;
            for (int x = 0; x < sz; x++)
                for (int y = 0; y < sz; y++) {
                    if (!cityMap[x][y] || distr[{x, y}] > 0) continue;
                    snow.push_back(make_pair(x, y));
                }
            for (auto drift : snow) {
                int minDist = 1000;
                for (auto w : staff)
                    minDist = min(minDist, 
                        abs(w.x - drift.first) + abs(w.y - drift.second)
                    );
                if (minDist > sz / 2) ans.push_back(drift);
            }
                        
            return ans;
        }

        void test() {
            auto recom = shouldHire();
            cout << len(recom) + ID << endl;
//            int count = min(100, sz + 30);
//            cout << (ID < count) + ID << endl;

            vector<char> d({'U', 'D', 'L', 'R'});
            for (int i = 0; i < ID; i++) {
                pair<int, int> near = nearestSnow(i);
                if (near != make_pair(-1, -1)) {
              //      cerr << i << " -> " << near.first << " "<< near.second << "\n";
                    char dir = opt(i, near);
                    move(i, dir);
			    } else {
                    char dir = 0;
                    do {
                        dir = d[rnd() % 4];
                    } while (!ok(i, dir));
                    move(i, dir);
                }
            }

//            if (ID < count) hire(rnd() % sz, rnd() % sz);
            for (auto newWorker : recom) hire(newWorker.first, newWorker.second);
        }
        
        void stonks() {
            while (TIME < 2000) {
                read();
                test();
                update();
                TIME++;
            }
        }
};

/*
 +-----> y
 |
 |
 v x

*/

inline void solve() {
    int b, s, f;
    cin >> b >> s >> f;
    Corparation NorthVenice(b, s, f);
    NorthVenice.stonks();
}
/*

*/
