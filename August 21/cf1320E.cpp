/*
  Time: 59:37
  Num of Submissions: 3
  Analysis: Virtual tree :skull:
  Difficulty: 3000
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

//#pragma GCC optimize("Ofast,unroll-loops")
//#pragma GCC target("avx,avx2,fma")

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
      int n; cin >> n;
      vec <vec <int>> g(n);
      for (int i = 0; i < n - 1; ++i){
            int u, v;
            cin >> u >> v, --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
      }
      vec <int> h(n), fi(n), fo(n), up(n), pa(n);
      int tmr = 0;
      auto dfs = [&](auto &&dfs, int u, int p) -> void{
            fi[u] = tmr++;
            h[u] = h[p] + 1;
            up[u] = pa[u] = p;
            if (h[p] - h[up[p]] == h[up[p]] - h[up[up[p]]]){
                  up[u] = up[up[p]];
            }
            for (auto &v: g[u]) if (v != p){
                  dfs(dfs, v, u);
            }
            fo[u] = tmr++;
      };
      dfs(dfs, 0, 0);
      auto jump = [&](int u, int k){
            int need = h[u] - k;
            while(h[u] > need){
                  u = h[up[u]] >= need ? up[u] : pa[u];
            }
            return u;
      };
      auto lca = [&](int u, int v){
            if (h[u] > h[v]) swap(u, v);
            v = jump(v, h[v] - h[u]);
            while(u != v){
                  if (up[u] != up[v]){
                        u = up[u], v = up[v];
                  }
                  else{
                        u = pa[u], v = pa[v];
                  }
            }
            return u;
      };
      int q; cin >> q;
      vec <vec <pii>> gg(n);
      vec <int> ans(n, -1), ds(n);
      while(q--){
            int k, m;
            cin >> k >> m;
            vec <int> v(k), s(k);
            for (int i = 0; i < k; ++i){
                  cin >> v[i] >> s[i], --v[i];
            }
            vec <int> u(m);
            for (auto &i: u) cin >> i, --i;
            int z = m + k;
            vec <int> ve;
            ve.insert(ve.begin(), all(v));
            ve.insert(ve.begin(), all(u));
            sort(all(ve), [&](int i, int j) { return fi[i] < fi[j]; });
            for (int i = 0; i < z; ++i){
                  ve.push_back(lca(ve[i], ve[(i + 1) % z]));
            }
            sort(all(ve));
            ve.erase(unique(all(ve)), ve.end());
            for (auto &i: ve){
                  gg[i].clear(), ans[i] = -1, ds[i] = 1e9;
            }
            sort(all(ve), [&](int i, int j) { return fi[i] < fi[j]; });
            vec <int> st;
            for (auto &i: ve){
                  if (st.empty()){
                        st.push_back(i);
                        continue;
                  }
                  while(fi[i] > fo[st.back()]) st.pop_back();
                  gg[st.back()].push_back({i, h[i] - h[st.back()]});
                  gg[i].push_back({st.back(), h[i] - h[st.back()]});
                  st.push_back(i);
            }
            pgq <array <int, 4>> pq;
            for (int i = 0; i < k; ++i){
                  ds[v[i]] = 0;
                  pq.push({0, i, 0, v[i]});
            }
            while(!pq.empty()){
                  auto [d, id, rd, x] = pq.top(); pq.pop();
                  if (~ans[x]) continue;
                  ans[x] = id;
                  int sx = s[id];
                  for (auto &[y, w]: gg[x]){
                        int nd = (rd + w + sx - 1) / sx;
                        if (ds[y] >= nd){
                              pq.push({ds[y] = nd, id, rd + w, y});
                        }
                  }
            }
            for (auto &i: u){
                  cout << ans[i] + 1 << " ";
            }
            cout << "\n";
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
