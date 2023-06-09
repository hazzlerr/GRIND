/*
  Time: 13:04
  Num of Submissions: 1
  Analysis: Using dp from D1 solution, we can notice that it is possilbe to count contribution of evey dp[i][0] using comb 
  (you need to count paths where you either move right or right + down)
  Rating: 2400
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

int dvd(int a, int b){
      return mul(a, inv(b));
}

const int N = 1e6 + 42;

int fa[N], af[N];

int C(int n, int k){
      if (n < k || k < 0) return 0;
      return mul(fa[n], mul(af[n - k], af[k]));
}

inline int solve(){
      int n, m, k;
      cin >> n >> m >> k;
      m = n - m;
      if (m == 0){
            cout << mul(n, k) << "\n";
            return 0;
      }
      int ans = 0;
      for (int i = 1; i <= n; ++i){
            int val = mul(i, k);
            int left = n - i - 1;
            if (left >= m - 1){
                  inc(ans, dvd(mul(val, C(left, m - 1)), bpw(2, left + 1)));
            }
      }
      cout << ans << "\n";
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
      int tst = 1; cin >> tst;
      precalc();
      while(tst--) solve();
      return 0;
}
