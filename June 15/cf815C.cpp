/*
  Time: 9:30
  Num of Submissions: 1
  Analysis: I totally have learned subtree dp trick
  Rating: 2400
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

const ll inf = 1e18;

inline int solve(){
      int n, b;
      cin >> n >> b;
      vec <vec <int>> g(n);
      vec <ll> c(n), d(n);
      for (int i = 0; i < n; ++i){
            cin >> c[i] >> d[i];
            if (i){
                  int p; cin >> p, --p;
                  g[p].push_back(i);
            }
      }
      auto mrg = [&](vec <array <ll, 2>> a, vec <array <ll, 2>> b){
            vec <array <ll, 2>> c(sz(a) + sz(b) - 1, {inf, inf});
            for (int i = 0; i < sz(a); ++i){
                  for (int j = 0; j < sz(b); ++j){
                        umin(c[i + j][0], a[i][0] + b[j][0]);
                        umin(c[i + j][1], a[i][1] + b[j][1]);
                  }
            }
            return c;
      };
      vec <vec <array <ll, 2>>> dp(n);
      auto dfs = [&](auto &&dfs, int u, int p) -> void{
            dp[u] = {{0, inf}, {c[u], c[u] - d[u]}};
            for (auto &v: g[u]) if (v != p){
                  dfs(dfs, v, u);
                  dp[u] = mrg(dp[u], dp[v]);
            }
            for (int i = 0; i < sz(dp[u]); ++i){
                  umin(dp[u][i][1], dp[u][i][0]);
            }
      }; dfs(dfs, 0, 0);
      for (int i = n; ~i; --i){
            if (dp[0][i][1] <= b){
                  cout << i << "\n";
                  return 0;
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
