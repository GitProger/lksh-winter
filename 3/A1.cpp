#include <bits/stdc++.h>
using namespace std;
typedef __int128 lll;
typedef long long ll;
typedef string str;
#define all(obj) obj.begin(),obj.leaf()
#define rall(obj) obj.rbegin(),robj.leaf()
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
   // freopen("karlsson.in", "r", stdin);
   // freopen("karlsson.out", "w", stdout);
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


struct Node {
    map<char, Node *> next;
    Node *cur; 
    Node *leaf = nullptr;
    int str_id = -1;
    Node(Node *cur = nullptr) : cur(cur), leaf(NULL), str_id(-1) {}
    bool isleaf() { return str_id >= 0; }
};

Node root;
vector<string> dict;
unordered_map<string, int> ans;
Node* current;

void addString(const string &x)  {
    Node *cur = &root;
    for(const char c : x) {
        Node *nxt = cur->next[c];
        if (!nxt) {
            nxt = new Node(&root);
            cur->next[c] = nxt;
        }
        cur = nxt;
    }
    cur->str_id = len(dict);
    dict.push_back(x);
}

void bfs() {
    queue<Node*> q;
    q.push(&root);
    while (!q.empty()) {
        Node *v = q.front(); q.pop();
        for (auto p : v->next) {
            char key = p.first;
            Node *u = p.second;
            Node *temp = v->cur;
            while (temp != nullptr) {
                Node *cur_c = temp->next[key];
                if (cur_c) {
                    u->cur = cur_c;
                    break;
                }
                temp = temp->cur;
            }
            if (u->cur->isleaf())
                u->leaf = u->cur;
            else
                u->leaf = u->cur->leaf;
            q.push(u);
        }
    }
}

void go(const char c)  {
    while (current) {
        Node *x = current->next[c];
        if (x != nullptr) {
            current = x;
            return;
        }
        current = current->cur;
    }
    current = &root;
}

void update() {
    if (current->isleaf()) ans[dict[current->str_id]]++;
    Node *temp = current->leaf;
    while (temp) {
        ans[dict[temp->str_id]]++; 
        temp = temp->leaf;
    }
}


inline void solve() {
    int n; cin >> n;
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
        addString(s[i]);
    }
    bfs();
    string t; cin >> t;
    current = &root;
    for (char c : t) {
        go(c);
        update();
    }
    for (string e : s) cout << ans[e] << "\n";
}
/*
3
abc
abcdr
abcde
xabcdef


6
aabb
ababb
abbab
baba
bb
bbbaa


*/
