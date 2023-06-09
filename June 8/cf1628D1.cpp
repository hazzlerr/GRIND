/*
  Time: 3:45
  Num of Submissions: 1
  Analysis: I observed that from two different states we will probably get average, because it makes sense
  Rating: 2100
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

const int mod = 1e9 + 7;

int add(int a, int b){
      a += b;
      return a >= mod ? a - mod : a;
}

int mul(int a, int b){
      return a * ll(b) % mod;
}

inline int solve(){
      int n, m, k;
      cin >> n >> m >> k;
      m = n - m;
      vec <vec <int>> dp(n + 1, vec <int> (m + 1));
      for (int i = 1; i <= n; ++i){
            dp[i][0] = mul(i, k);
      }
      int i2 = (mod + 1) / 2;
      for (int i = 1; i <= n; ++i){
            for (int j = 1; j <= m; ++j){
                  dp[i][j] = mul(add(dp[i - 1][j], dp[i - 1][j - 1]), i2);
            }
      }
      cout << dp[n][m] << "\n";
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
