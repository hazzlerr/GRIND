// I just observed the pattern with prefix sums, but you can do dp solution 
// if you substitute C(n, k) = C(n - 1, k) + C(n - 1, k - 1)

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

#define int long long

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef tuple <int, int, int> tui;

template <typename T> bool umin(T &a, T b) { return a > b ? a = b, 1 : 0; }
template <typename T> bool umax(T &a, T b) { return a < b ? a = b, 1 : 0; }

const int mod = 998244353;

void inc(int &a, int b){
      a += b;
      a -= a >= mod ? mod : 0;
}

int mul(int a, int b){
      return a * ll(b) % mod;
}

int fa(int n){
      int r = 1;
      for (int i = 1; i <= n; ++i){
            r = mul(r, i);
      }
      return r;
}

int C(int n, int k){
      if (n < k || k < 0) return 0;
      return fa(n) / fa(k) / fa(n - k);
}

inline int solve(){
      int n, a0, x, y, m, k;
      cin >> n >> a0 >> x >> y >> m >> k;
      vec <int> a(n);
      a[0] = a0;
      for (int i = 1; i < n; ++i){
            a[i] = (a[i - 1] * x + y) % m;
      }
      for (int it = 0; it <= k; ++it){
            for (int i = 1; i < n; ++i){
                  inc(a[i], a[i - 1]);
            }
      }
      int res = 0;
      for (int i = 0; i + k <= n; ++i){
            res ^= a[i] * (i + k);
      }

      cout << res << "\n";
      return 0;
}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; //cin >> tst;
      while(tst--) solve();
      return 0;
}
