// dp[i][j] - max number of p[k] == k on prefix i if we did not delete j numbers
// transitions are simple (two cases where you delete a[i] and keep it)

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

inline int solve(){
      int n, k;
      cin >> n >> k;
      vec <int> a(n);
      for (auto &i: a) cin >> i, --i;
      vec <vec <int>> dp(n, vec <int> (n + 1, 0));
      for (int i = 0; i < n; ++i){
            for (int j = 0; j <= i; ++j){
                  umax(dp[i][j + 1], (i ? dp[i - 1][j] : 0) + (j == a[i]));
                  if (i) umax(dp[i][j], dp[i - 1][j]);
            }
      }
      int ans = n + 42;
      for (int i = 0; i <= n; ++i){
            if (dp[n - 1][i] >= k){
                  umin(ans, n - i);
            }
      }
      cout << (ans == n + 42 ? -1 : ans) << "\n";
      return 0;
}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; cin >> tst;
      while(tst--) solve();
      return 0;
}
