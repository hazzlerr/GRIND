/*
  Time: 17:45
  Num of Submissions: 1
  Analysis: If we look at k = 3 we either move from every node at the same time or just go from one => we can do smth like this using bitmask dp
            After that you can just do dp and recalcualte it using dijkstra
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
      int n, k, m;
      cin >> n >> k >> m;
      vec <int> ve(k);
      for (auto &i: ve) cin >> i, --i;
      vec <vec <pii>> g(n);
      for (int i = 0; i < m; ++i){
            int u, v, w;
            cin >> u >> v >> w, --u, --v;
            g[u].push_back({v, w});
            g[v].push_back({u, w});
      }
      vec <vec <ll>> d(n, vec <ll> (1 << k, inf));
      for (int i = 0; i < k; ++i){
            d[ve[i]][1 << i] = 0;
      }
      for (int msk = 1; msk < (1 << k); ++msk){
            pgq <pll> q;
            for (int i = 0; i < n; ++i){
                  for (int sub = msk; sub; sub = (sub - 1) & msk){
                        umin(d[i][msk], d[i][sub] + d[i][msk ^ sub]);
                  }
                  if (d[i][msk] != inf){
                        q.emplace(d[i][msk], i);
                  }
            }
            while(!q.empty()){
                  auto [ds, u] = q.top(); q.pop();
                  if (ds > d[u][msk]) continue;
                  for (auto &[v, w]: g[u]){
                        if (umin(d[v][msk], d[u][msk] + w)){
                              q.emplace(d[v][msk], v);
                        }
                  }
            }
      }
      ll ans = inf;
      for (int i = 0; i < n; ++i){
            umin(ans, d[i][(1 << k) - 1]);
      }
      cout << ans << "\n";
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
