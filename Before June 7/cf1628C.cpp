// Somehow it works...

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

const vec <pii> dd = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

inline int solve(){
      int n; cin >> n;
      vec <vec <int>> a(n, vec <int> (n));
      for (auto &i: a) for (auto &j: i) cin >> j;
      vec <vec <int>> cnt(n, vec <int> (n));
      auto take = [&](int i, int j){
            for (auto [di, dj]: dd){
                  int ci = i + di, cj = j + dj;
                  if (0 <= ci && ci < n && 0 <= cj && cj < n){
                        ++cnt[ci][cj];
                  }
            }
      };
      int ans = 0;
      for (int i = 1; i < n; ++i){
            for (int j = 0; j < n; ++j){
                  if (cnt[i - 1][j] % 2 == 0){
                        ans ^= a[i][j], take(i, j);
                  }
            }
      }
      cout << ans << "\n";
      return 0;
}

inline void precalc(){}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; cin >> tst;
      precalc();
      while(tst--) solve();
      return 0;
}
