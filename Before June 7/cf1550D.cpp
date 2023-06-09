/*
  Time: 12:22 
  Num Submissions: 1
  Learnt: Nothing, just practiced combinatorics 
  Something worth remembering: I already knew it, but max sum of k1 * k1 + k2 * k2 + ... of numbers such that 2(k1 + k2 + ...) = n is (n / 2) * (n / 2)  
  Rating: 2300
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

const int N = 5e5 + 42;

int fa[N], af[N];

int C(int n, int k){
      if (n < k || k < 0) return 0;
      return mul(fa[n], mul(af[n - k], af[k]));
}

inline int solve(){
      int n, l, r;
      cin >> n >> l >> r;
      int n2 = n / 2;
      int _k = min(1 - l, r - n);
      int ans = C(n, n2);
      if (n & 1) inc(ans, C(n, n2 + 1));
      ans = mul(ans, _k);
      for (int k = _k + 1; ; ++k){
            int x = max(1, l + k), y = min(n, r - k);
            int len = y - x + 1, have = n2 - x + 1;
            if (len < 0 || have < -1) break;
            inc(ans, C(len, have));
            if (n & 1) inc(ans, C(len, have + 1));
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
      int tst = 1; //cin >> tst;
      precalc();
      while(tst--) solve();
      return 0;
}
