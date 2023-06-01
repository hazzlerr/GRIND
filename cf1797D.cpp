// Implementation :skull:

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
      int n, q;
      cin >> n >> q;
      vec <ll> dp(n);
      for (auto &i: dp) cin >> i;
      vec <vec <int>> g(n);
      for (int i = 0; i < n - 1; ++i){
            int u, v;
            cin >> u >> v, --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
      }
      vec <int> ss(n), par(n);
      vec <set <pii>> s(n);
      auto dfs = [&](auto &&dfs, int u, int p) -> void{
            par[u] = p, ss[u] = 1;
            for (auto &v: g[u]) if (v != p){
                  dfs(dfs, v, u);
                  dp[u] += dp[v], ss[u] += ss[v];
                  s[u].insert({-ss[v], v});
            }
      }; dfs(dfs, 0, 0);

      while(q--){
            int tp, u;
            cin >> tp >> u, --u;
            if (tp == 1){
                  cout << dp[u] << "\n";
            }
            else{
                  if (s[u].empty()) continue;
                  int fa = par[u];
                  s[fa].erase({-ss[u], u});
                  auto [_, so] = *s[u].begin();
                  s[u].erase(s[u].begin());
                  ss[u] -= ss[so], dp[u] -= dp[so];
                  ss[so] += ss[u], dp[so] += dp[u];
                  s[so].insert({-ss[u], u});
                  s[fa].insert({-ss[so], so});
                  par[so] = fa, par[u] = so;
            }
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
