// https://codeforces.com/contest/403/problem/D
// It's easy to look at this problem using difference away
// For contribution of b[i] - a[i] we can use dp, for the things between b[i] and a[i + 1] we can use combinatorics (stars and bars)

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

const int mod = 1e9 + 7;

void inc(int &a, int b){
      a += b;
      a -= a >= mod ? mod : 0;
}

int mul(int a, int b){
      return a * ll(b) % mod;
}

int bpw(int a, int b){
      int r = 1;
      for (; b; b >>= 1, a = mul(a, a)){
            if (b & 1) r = mul(r, a);
      }
      return r;
}

int inv(int a){
      return bpw(a, mod - 2);
}

const int N = 1010, K = 55;

int fa[2 * N], af[2 * N];

int dp[K][N];

void precalc(){
      fa[0] = 1;
      for (int i = 1; i < 2 * N; ++i){
            fa[i] = mul(fa[i - 1], i);
      }
      af[2 * N - 1] = inv(fa[2 * N - 1]);
      for (int i = 2 * N - 2; ~i; --i){
            af[i] = mul(af[i + 1], i + 1);
      }

      dp[0][0] = dp[1][0] = 1;
      for (int x = 1; x < N; ++x){
            for (int l = K - 1; l > 0; --l){
                  for (int j = x; j < N; ++j){
                        inc(dp[l][j], dp[l - 1][j - x]);
                  }
            }
      }
      for (int i = 0; i < K; ++i){
            for (int j = 0; j < N; ++j){
                  dp[i][j] = mul(dp[i][j], fa[i]);
            }
      }
}

int C(int n, int k){
      if (n < k || k < 0) return 0;
      return mul(fa[n], mul(af[n - k], af[k]));
}

inline int solve(){
      int n, k;
      cin >> n >> k;
      if (k >= K){
            cout << "0\n";
            return 0;
      }
      n -= k;
      int ans = 0;
      for (int i = 0; i <= n; ++i){
            int left = n - i;
            inc(ans, mul(dp[k][i], C(left + k, k)));
      }
      cout << ans << "\n";
      return 0;
}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; cin >> tst;
      precalc();
      while(tst--) solve();
      return 0;
}
