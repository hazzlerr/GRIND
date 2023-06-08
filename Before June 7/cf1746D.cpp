// Using states that make sense is fast enough, i guess

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
      int n, k;
      cin >> n >> k;
      vec <vec <int>> g(n);
      for (int i = 1; i < n; ++i){
            int p; cin >> p, --p;
            g[p].push_back(i);
      }
      vec <int> s(n);
      for (auto &i: s) cin >> i;
      vec <map <int, ll>> dp(n);
      auto dfs = [&](auto &&dfs, int u, ll k) -> ll {
            if (dp[u].count(k)) return dp[u][k];
            dp[u][k] = s[u] * k;
            int cnt = sz(g[u]);
            if (cnt != 0){
                  if (k % cnt == 0){
                        for (auto &v: g[u]){
                              dp[u][k] += dfs(dfs, v, k / cnt);
                        }
                  }
                  else{
                        vec <ll> bst;
                        for (auto &v: g[u]){
                              ll a = dfs(dfs, v, k / cnt);
                              ll b = dfs(dfs, v, k / cnt + 1);
                              dp[u][k] += a;
                              bst.push_back(b - a);
                        }
                        sort(rall(bst));
                        for (int i = 0; i < k % cnt; ++i){
                              dp[u][k] += bst[i];
                        }
                  }
            }
            return dp[u][k];
      };
      cout << dfs(dfs, 0, k) << "\n";
      return 0;
}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; cin >> tst;
      while(tst--) solve();
      return 0;
}
