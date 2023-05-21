// https://codeforces.com/gym/104345/problem/B
// I though about sqrt for some time (though i shouldn't have because constraints are clearly trying to cut off sqrt)
// It turns out it can be solved easier, if you will only check edges of vertex u that are connected to its parent

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

template <typename T> bool umin(T &a, T b) { return a > b ? a = b, 1 : 0; }
template <typename T> bool umax(T &a, T b) { return a < b ? a = b, 1 : 0; }

inline int solve(){
      int n; cin >> n;
      vec <vec <int>> g(n);
      for (int i = 0; i < n - 1; ++i){
            int u, v;
            cin >> u >> v, --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
      }
      vec <int> par(n);
      auto dfs = [&](auto &&dfs, int u, int p) -> void {
            par[u] = p;
            for (auto &v: g[u]) if (v != p){
                  dfs(dfs, v, u);
            }
      }; dfs(dfs, 0, 0);

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

      int q; cin >> q;
      vec <int> mrk(n);
      while(q--){
            int k; cin >> k;
            vec <int> x(k);
            for (int &i: x){
                  cin >> i, --i, mrk[i] = 1;
            }
            for (int i: x){
                  if (mrk[par[i]]){
                        unite(i, par[i]);
                  }
            }
            ll ans = 0;
            for (int i: x){
                  i = get(i);
                  if (mrk[i] != 2){
                        mrk[i] = 2;
                        ans += -dsu[i] * ll(-dsu[i] - 1) / 2;
                  }
            }
            cout << ans << "\n";
            for (int i: x){
                  dsu[i] = -1, mrk[i] = 0;
            }
      }
      return 0;
}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; //cin >> tst;
      while(tst--) solve();
      return 0;
}
