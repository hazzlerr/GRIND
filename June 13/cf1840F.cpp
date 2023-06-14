/*
  Time: 17:33
  Num of Submissions: 2
  Analysis: Two observations - we don't need to move backwards and the answer will not exceed n * m + r. After that it's just dp
  Rating: 2200
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

const int N = 110;

inline int solve(){
      int n, m;
      cin >> n >> m;
      int z = n * m + N + 2;
      vec <set <int>> h(z), v(z);
      int r; cin >> r;
      for (int i = 0; i < r; ++i){
            int t, tp, c;
            cin >> t >> tp >> c, --tp;
            if (t < z){
                  (tp ? v : h)[t].insert(c);
            }
      }
      vec <vec <array <bool, N>>> dp(n + 1, vec <array <bool, N>> (m + 1));
      dp[0][0][0] = 1;
      for (int k = 0; k < N; ++k){
            for (int i = 0; i <= n; ++i){
                  for (int j = 0; j <= m; ++j){
                        if (!dp[i][j][k]) continue;
                        int nt = i + j + k + 1;
                        assert(nt < z);
                        if (!h[nt].count(i) && !v[nt].count(j) && k + 1 < N){
                              dp[i][j][k + 1] = 1;
                        }
                        if (!h[nt].count(i + 1) && !v[nt].count(j) && i + 1 <= n){
                              dp[i + 1][j][k] = 1;
                        }
                        if (!h[nt].count(i) && !v[nt].count(j + 1) && j + 1 <= m){
                              dp[i][j + 1][k] = 1;
                        }
                  }
            }
      }
      int ans = N;
      for (int i = 0; i < N; ++i){
            if (dp[n][m][i]){
                  cout << n + m + i << "\n";
                  return 0;
            }
      }
      cout << "-1\n";
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
