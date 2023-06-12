/*
  Time: 6:34
  Num of Submissions: 1
  Analysis: After a couple of simple obesrbations, this tasks boils down to merging scc's on vertical path (which can be done beatifully using dsu)
  Rating: 2094
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

typedef vec <vec <int>> mat;

template <typename T>
using prq = priority_queue <T>;

template <typename T>
using pgq = priority_queue <T, vec <T>, greater <T>>;

template <typename T> bool umin(T &a, T b) { return a > b ? a = b, 1 : 0; }
template <typename T> bool umax(T &a, T b) { return a < b ? a = b, 1 : 0; }

inline int solve(){
      int n; cin >> n;
      vec <int> p(n);
      for (int i = 1; i < n; ++i){
            cin >> p[i], --p[i];
      }
      vec <int> uf(n, -1), mn(n);
      iota(all(mn), 0);
      auto get = [&](int u){
            while(uf[u] >= 0) u = uf[u];
            return u;
      };
      auto unite = [&](int u, int v){
            u = get(u), v = get(v);
            if (u == v) return 0;
            if (uf[u] > uf[v]) swap(u, v);
            uf[u] += uf[v], uf[v] = u;
            umin(mn[u], mn[v]);
            return 1;
      };
      int q; cin >> q;
      while(q--){
            int tp; cin >> tp;
            if (tp == 1){
                  int u, v;
                  cin >> u >> v, --u, --v;
                  while(get(u) != get(v)){
                        unite(mn[get(u)], p[mn[get(u)]]);
                  }
            }
            else{
                  int x; cin >> x, --x;
                  cout << mn[get(x)] + 1 << "\n";
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
