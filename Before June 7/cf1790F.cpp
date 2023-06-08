// I think there is a smart sqrt solution, but I just did cd

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

inline int solve(){
      int n, c0;
      cin >> n >> c0, --c0;
      vec <int> c(n);
      c[0] = c0;
      for (int i = 1; i < n; ++i){
            cin >> c[i], --c[i];
      }
      vec <vec <int>> g(n);
      for (int i = 0; i < n - 1; ++i){
            int u, v;
            cin >> u >> v, --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
      }
      vec <bool> us(n);
      vec <int> ss(n);
      auto siz = [&](auto &&siz, int u, int p) -> void{
            ss[u] = 1;
            for (auto &v: g[u]) if (v != p && !us[v]){
                  siz(siz, v, u), ss[u] += ss[v];
            }
      };
      auto _cen = [&](auto &&_cen, int u, int p, int s) -> int{
            for (auto &v: g[u]) if (v != p && !us[v]){
                  if (ss[v] > s / 2){
                        return _cen(_cen, v, u, s);
                  }
            }
            return u;
      };
      auto cen = [&](int u){
            siz(siz, u, u);
            return _cen(_cen, u, u, ss[u]);
      };

      vec <vec <int>> cs(n), ds(n);
      auto dfs = [&](auto &&dfs, int u, int p, int c, int d) -> void{
            cs[u].push_back(c);
            ds[u].push_back(d);
            for (auto &v: g[u]) if (v != p && !us[v]){
                  dfs(dfs, v, u, c, d + 1);
            }
      };
      auto bld = [&](auto &&bld, int u) -> void{
            us[u] = 1;
            cs[u].push_back(u);
            ds[u].push_back(0);
            for (auto &v: g[u]) if (!us[v]){
                  dfs(dfs, v, u, u, 1);
            }
            for (auto &v: g[u]) if (!us[v]){
                  bld(bld, cen(v));
            }
      };
      bld(bld, cen(0));

      vec <int> mn(n, 1e9);
      auto upd = [&](int u){
            for (int i = 0; i < sz(cs[u]); ++i){
                  umin(mn[cs[u][i]], ds[u][i]);
            }
      };
      auto get = [&](int u){
            int res = 1e9;
            for (int i = 0; i < sz(cs[u]); ++i){
                  umin(res, ds[u][i] + mn[cs[u][i]]);
            }
            return res;
      };
      int ans = 1e9;
      for (int i = 0; i < n; ++i){
            if (i != 0){
                  umin(ans, get(c[i]));
                  cout << ans << " ";
            }
            upd(c[i]);
      }
      cout << "\n";
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
