/*
  Time: 8:07
  Num of Submissions: 1
  Learned: Funny way to think about dp
  Analysis: I'm not an expert in combinatorial dp's (idk how to call them), so I'm not used to think about number of something insted of prefix
  Rating: 2200
*/
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

const int mod = 998244353;

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

const int N = 500;

int fa[N], af[N];

int C(int n, int k){
      if (n < k || k < 0) return 0;
      return mul(fa[n], mul(af[n - k], af[k]));
}

inline int solve(){
      int n, k;
      cin >> n >> k;
      vec <vec <int>> dp(n), vec <int> (k + 1));
      dp[0][0] = 1;
      for (int c = 0; c < k; ++c){
            for (int j = 0; j < n; ++j){
                  int between = bpw(k - c, j * (j - 1) / 2);
                  for (int i = 0; i + j < n; ++i){
                        int ways = C(n - 1 - i, j);
                        ways = mul(ways, between);
                        ways = mul(ways, bpw(k - c, j * i));
                        inc(dp[i + j][c + 1], mul(dp[i][c], ways));
                  }
            }
      }
      cout << dp[n - 1][k] << "\n";
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
