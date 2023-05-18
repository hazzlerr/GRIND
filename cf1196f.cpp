// We don't need more than k minimum edges, because paths with other edges will contain edges greater than kth edge -> their weight will be greater than kth edge

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

const ll inf = 1e18;

inline int solve(){
      int n, m, k;
      cin >> n >> m >> k;
      vec <array <int, 3>> e(m);
      for (auto &[w, u, v]: e){
            cin >> u >> v >> w, --u, --v;
      }
      sort(all(e));
      while(sz(e) > k) e.pop_back();
      vec <int> ve;
      for (auto [w, u, v]: e){
            ve.push_back(u);
            ve.push_back(v);
      }
      sort(all(ve));
      ve.erase(unique(all(ve)), ve.end());
      int z = sz(ve);
      vec <vec <ll>> d(z, vec <ll> (z, inf));
      for (auto [w, u, v]: e){
            u = lower_bound(all(ve), u) - ve.begin();
            v = lower_bound(all(ve), v) - ve.begin();
            d[u][v] = d[v][u] = w;
      }
      for (int i = 0; i < z; ++i){
            for (int j = 0; j < z; ++j){
                  for (int k = 0; k < z; ++k){
                        umin(d[j][k], d[j][i] + d[i][k]);
                  }
            }
      }
      vec <ll> ds;
      for (int i = 0; i < z; ++i){
            for (int j = i + 1; j < z; ++j){
                  ds.push_back(d[i][j]);
            }
      }
      nth_element(ds.begin(), ds.begin() + k - 1, ds.end());
      cout << ds[k - 1] << "\n";
      return 0;
}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; //cin >> tst;
      while(tst--) solve();
      return 0;
}
