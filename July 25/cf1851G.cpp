/*
  Num of Submissions: 1
  Analysis: hi - hj + hj - hk = hi - hk. After that it's just implementation
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("avx2")

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
typedef pair <ll, ll> pll;
typedef pair <int, int> pii;
typedef tuple <int, int, int> tui;

template <typename T>
using prq = priority_queue <T>;

template <typename T>
using pgq = priority_queue <T, vec <T>, greater <T>>;

template <typename T> bool umin(T &a, T b) { return a > b ? a = b, 1 : 0; }
template <typename T> bool umax(T &a, T b) { return a < b ? a = b, 1 : 0; }

inline int solve(){
      int n, m;
      cin >> n >> m;
      vec <int> h(n);
      for (auto &i: h) cin >> i;
      vec <vec <int>> g(n);
      for (int i = 0; i < m; ++i){
            int u, v;
            cin >> u >> v, --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
      }
      int q; cin >> q;
      vec <array <int, 4>> sc;
      for (int i = 0; i < q; ++i){
            int u, v, w;
            cin >> u >> v >> w, --u, --v;
            sc.push_back({h[u] + w, u, v, i});
      }
      for (int i = 0; i < n; ++i){
            sc.push_back({h[i], ~i, -1, -1});
      }
      vec <int> dsu(n, -1);
      auto get = [&](int u){
            while(dsu[u] >= 0) u = dsu[u];
            return u;
      };
      auto unite = [&](int u, int v){
            u = get(u), v = get(v);
            if (u == v) return;
            if (dsu[u] > dsu[v]) swap(u, v);
            dsu[u] += dsu[v], dsu[v] = u;
      };
      sort(all(sc));
      vec <bool> ans(q);
      for (auto [_, x, y, z]: sc){
            if (x < 0){
                  int u = ~x;
                  for (auto &v: g[u]){
                        if (h[v] <= h[u]) unite(u, v);
                  }
            }
            else{
                  int u = x, v = y, i = z;
                  ans[i] = get(u) == get(v);
            }
      }
      for (int i = 0; i < q; ++i){
            cout << (ans[i] ? "YES\n" : "NO\n");
      }
      return 0;
}

inline void precalc(){}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; cin >> tst;
      precalc();
      while(tst--) solve();
      return 0;
}
