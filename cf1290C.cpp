/*
  Time: 1:12:46 (duh)
  Num Submissions: 2
  Learnt: How to keep two different bipartite colorings in one dsu
  Analysis: Do not spend time on debugging beatiful but broken code
  Rating: 2500
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define fi first
#define se second
#define all(m) (m).begin(), (m).end()
#define rall(m) (m).rbegin(), (m).rend()
#define vec vector
#define sz(a) (int) (a).size()
#define mpp make_pair
#define mtt make_tuple

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef tuple <int, int, int> tui;

template <typename T>
using prq = priority_queue <T>;

template <typename T>
using pgq = priority_queue <T, vec <T>, greater <T>>;

template <typename T> bool umin(T &a, T b) { return a > b ? a = b, 1 : 0; }
template <typename T> bool umax(T &a, T b) { return a < b ? a = b, 1 : 0; }

const int N = 3e5 + 42, inf = 1e9 + 42;

// 2i -> not taken
// 2i + 1 -> taken

int p[2 * N];
ll res[2 * N], ans = 0;

int get(int u){
      if (p[u] < 0) return u;
      return p[u] = get(p[u]);
}

ll f(int u){
      return res[get(u)];
}

void change(int u, ll val){
      ans -= min(f(u), f(u ^ 1));
      res[get(u)] = val;
      ans += min(f(u), f(u ^ 1));
}

bool _unite(int u, int v){
      u = get(u), v = get(v);
      if (u == v) return 0;
      if (p[u] > p[v]) swap(u, v);
      p[u] += p[v], p[v] = u;
      res[u] += res[v];
      return 1;
}

void unite(int u, int v){
      ll rem = min(f(u), f(u ^ 1)) + min(f(v), f(v ^ 1));
      bool ch = 0;
      ch |= _unite(u, v);
      ch |= _unite(u ^ 1, v ^ 1);
      if (ch){
            ans += min(f(u), f(u ^ 1)) - rem;
      }
}

inline int solve(){
      int n, k;
      cin >> n >> k;
      string s; cin >> s;
      vec <vec <int>> id(n);
      for (int i = 0; i < k; ++i){
            int z; cin >> z;
            while(z--){
                  int x; cin >> x, --x;
                  id[x].push_back(i);
            }
            p[2 * i] = p[2 * i + 1] = -1;
            res[2 * i] = 0;
            res[2 * i + 1] = 1;
      }
      for (int i = 0; i < n; ++i){
            if (sz(id[i]) == 2){
                  int u = id[i][0], v = id[i][1];
                  if (s[i] == '0'){
                        unite(2 * u, 2 * v + 1);
                  }
                  else{
                        unite(2 * u, 2 * v);
                  }
            }
            else if (sz(id[i]) == 1){
                  int u = id[i][0];
                  change(2 * u + (s[i] == '1'), inf);
            }
            cout << ans << "\n";
      }
      return 0;
}

inline void precalc(){}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; //cin >> tst;
      precalc();
      while(tst--) solve();
      return 0;
}
