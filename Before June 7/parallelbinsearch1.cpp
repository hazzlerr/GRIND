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

const int N = 1e5 + 42;

int dsu[N];

void make(int n){
      fill(dsu, dsu + n, -1);
}

int get(int u){
      if (dsu[u] < 0) return u;
      return dsu[u] = get(dsu[u]);
}

void unite(int u, int v){
      u = get(u), v = get(v);
      if (u == v) return;
      if (dsu[u] > dsu[v]) swap(u, v);
      dsu[u] += dsu[v], dsu[v] = u;
}

inline int solve(){
      int n, m, k;
      cin >> n >> m >> k;
      vec <vec <int>> cmp(k);
      for (int i = 0; i < n; ++i){
            int c; cin >> c, --c;
            cmp[c].push_back(i);
      }
      vec <pii> e(m);
      for (auto &[u, v]: e){
            cin >> u >> v, --u, --v;
      }
      vec <int> ans(k, -1);
      vec <vec <int>> qq(m);
      for (int b = 16; ~b; --b){
            for (int i = 0; i < k; ++i){
                  if (ans[i] + (1 << b) < m){
                        ans[i] += 1 << b;
                        qq[ans[i]].push_back(i);
                  }
            }
            make(n);
            for (int i = 0; i < m; ++i){
                  unite(e[i].fi, e[i].se);
                  for (auto &x: qq[i]){
                        bool fl = 0;
                        for (auto &u: cmp[x]){
                              fl |= get(u) != get(cmp[x][0]);
                        }
                        if (!fl) ans[x] -= 1 << b;
                  }
                  qq[i].clear();
            }
      }
      for (int i = 0; i < k; ++i){
            if (cmp[i].size() <= 1){
                  cout << "0 ";
                  continue;
            }
            ans[i] += 2;
            cout << (ans[i] == m + 1 ? -1 : ans[i]) << " ";
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
