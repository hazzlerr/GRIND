/*
  Time: 13:34
  Num of Submissions: 1
  Analysis: I've learned subtree dp trick
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

const int inf = 1e9 + 42;

inline int solve(){
      int n, k, x;
      cin >> n >> k >> x, --x;
      vec <vec <pii>> g(n);
      for (int i = 0; i < n - 1; ++i){
            int u, v, w;
            cin >> u >> v >> w, --u, --v;
            g[u].push_back({v, w});
            g[v].push_back({u, w});
      }
      vec <vec <array <int, 2>>> dp(n);
      auto mrg = [&](vec <array <int, 2>> a, vec <array <int, 2>> b, int len){
            vec <array <int, 2>> c(sz(a) + sz(b) - 1, {inf, inf});
            for (int i = 0; i < sz(a); ++i){
                  umin(c[i][0], a[i][0]);
                  umin(c[i][1], a[i][1]);
                  for (int j = 0; j < sz(b); ++j){
                        umin(c[i + j][0], a[i][0] + b[j][0] + 2 * len);
                        umin(c[i + j][1], min(a[i][1] + b[j][0] + 2 * len, a[i][0] + b[j][1] + len));
                  }
            }
            return c;
      };
      auto dfs = [&](auto &&dfs, int u, int p) -> void{
            dp[u] = {{0, 0}, {0, 0}};
            for (auto &[v, w]: g[u]) if (v != p){
                  dfs(dfs, v, u);
                  dp[u] = mrg(dp[u], dp[v], w);
            }
      }; dfs(dfs, x, x);
      cout << dp[x][k][1] << "\n";
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
