// Main idea is to calculate dp[i][j] = E C(3k + j, i) for j = 0..2
// Using this dp, you can derive that:
// 1) dp[i][0] + dp[i][1] = dp[i][2] = E C(k, i) = C(k, i + 1)
// 2) You can derive dp[i][j] using C(n, k) = C(n - 1, k - 1) + C(n - 1, k)

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

const int mod = 1e9 + 7;

int add(int a, int b){
      a += b;
      return a >= mod ? a - mod : a;
}

int sub(int a, int b){
      a -= b;
      return a < 0 ? a + mod : a;
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

const int N = 3e6 + 42;

int fa[N], af[N];

int C(int n, int k){
      if (n < k || k < 0) return 0;
      return mul(fa[n], mul(af[n - k], af[k]));
}

inline int solve(){
      int n, q;
      cin >> n >> q;
      int z = 3 * n + 5;
      vec <int> f(z), ans(z);
      f[0] = n;
      int i3 = inv(3);
      for (int i = 1; i < z; ++i){
            f[i] = C(3 * n, i + 1);
            f[i] = sub(f[i], mul(3, f[i - 1]));
            if (i >= 2){
                  f[i] = sub(f[i], f[i - 2]);
            }
            f[i] = mul(f[i], i3);
            ans[i] = add(C(3 * n, i), f[i]);
      }
      while(q--){
            int x; cin >> x;
            cout << ans[x] << "\n";
      }
      return 0;
}

inline void precalc(){
      fa[0] = 1;
      for (int i = 1; i < N; ++i){
            fa[i] = mul(fa[i - 1], i);
      }
      af[N - 1] = inv(fa[N - 1]);
      for (int i = N - 2; ~i; --i){
            af[i] = mul(af[i + 1], i + 1);
      }
}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; //cin >> tst;
      precalc();
      while(tst--) solve();
      return 0;
}
