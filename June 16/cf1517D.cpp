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
      int n, m, k;
      cin >> n >> m >> k;
      vec <vec <pii>> g(n * m);
      for (int i = 0; i < n; ++i){
            for (int j = 0; j < m - 1; ++j){
                  int c; cin >> c;
                  g[i * m + j].emplace_back(i * m + j + 1, c);
                  g[i * m + j + 1].emplace_back(i * m + j, c);
            }
      }
      for (int i = 0; i < n - 1; ++i){
            for (int j = 0; j < m; ++j){
                  int c; cin >> c;
                  g[i * m + j].emplace_back((i + 1) * m + j, c);
                  g[(i + 1) * m + j].emplace_back(i * m + j, c);
            }
      }
      if (k % 2){
            for (int i = 0; i < n; ++i){
                  for (int j = 0; j < m; ++j){
                        cout << "-1 ";
                  }
                  cout << "\n";
            }
            return 0;
      }
      k /= 2;
      vec <vec <int>> dp(k + 1, vec <int> (n * m, inf));
      dp[0] = vec <int> (n * m, 0);
      for (int j = 0; j < k; ++j){
            for (int i = 0; i < n * m; ++i){
                  for (auto &[v, c]: g[i]){
                        umin(dp[j + 1][i], dp[j][v] + c);
                  }
            }
      }
      for (int i = 0; i < n; ++i){
            for (int j = 0; j < m; ++j){
                  cout << dp[k][i * m + j] * 2LL << " ";
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
