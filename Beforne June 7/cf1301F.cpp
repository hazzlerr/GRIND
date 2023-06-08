/*
  Time: 11:03
  Num of Submissions: 1
  Analysis: You can split problem into two cases:
            1) If you are not using teleportation, the distance is just Manhattan distance
            2) If you are using teleportation, than the distance is distance from points to the city with fixed color + 1
            Instead of finding distance from point to the color, we find distance from the color to point, 
            which can be done using bfs (in bfs you make tp only when you step on a color for the first time)
  Rating: 2600
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
typedef pair <int, int> pii;
typedef tuple <int, int, int> tui;

template <typename T>
using prq = priority_queue <T>;

template <typename T>
using pgq = priority_queue <T, vec <T>, greater <T>>;

template <typename T> bool umin(T &a, T b) { return a > b ? a = b, 1 : 0; }
template <typename T> bool umax(T &a, T b) { return a < b ? a = b, 1 : 0; }

const vec <pii> dd = {{0, +1}, {+1, 0}, {0, -1}, {-1, 0}};

inline int solve(){
      int n, m, k;
      cin >> n >> m >> k;
      vec <vec <int>> a(n, vec <int> (m));
      vec <vec <pii>> cmp(k);
      for (int i = 0; i < n; ++i){
            for (int j = 0; j < m; ++j){
                  cin >> a[i][j], --a[i][j];
                  cmp[a[i][j]].emplace_back(i, j);
            }
      }
      vec <vec <vec <int>>> d(k, vec <vec <int>> (n, vec <int> (m, -1)));
      for (int c = 0; c < k; ++c){
            vec <int> us(k);
            vec <pii> bfs;
            us[c] = 1;
            auto upd = [&](int i, int j, int ds){
                  if (!~d[c][i][j]){
                        d[c][i][j] = ds;
                        bfs.emplace_back(i, j);
                  }
            };
            for (auto &[i, j]: cmp[c]){
                  upd(i, j, 0);
            }
            for (int pt = 0; pt < sz(bfs); ++pt){
                  auto [i, j] = bfs[pt];
                  if (!us[a[i][j]]){
                        us[a[i][j]] = 1;
                        for (auto [ni, nj]: cmp[a[i][j]]){
                              upd(ni, nj, d[c][i][j] + 1);
                        }
                  }
                  for (auto [di, dj]: dd){
                        int ni = i + di, nj = j + dj;
                        if (0 <= ni && ni < n && 0 <= nj && nj < m){
                              upd(ni, nj, d[c][i][j] + 1);
                        }
                  }
            }
      }
      int q; cin >> q;
      while(q--){
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            --x1, --y1, --x2, --y2;
            int ans = abs(x1 - x2) + abs(y1 - y2);
            for (auto &ds: d){
                  umin(ans, ds[x1][y1] + ds[x2][y2] + 1);
            }
            cout << ans << "\n";
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
