// We need to buy at least one color from {c[i], c[i + 1]} for every i in [0..n-2]
// Constraints on m (m <= 40) suggest to think about meet-in-the-middle
// If we divide colors into two subsets, we can consider two types of edges:
// 1) In one mask
// 2) Between to masks
// Cheking first conditions is trivial, getting all vertices that we need from second half can be done using dp

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

inline int solve(){
      int n, m;
      cin >> n >> m;
      vec <int> c(n), x(m);
      for (auto &i: c) cin >> i, --i;
      for (auto &i: x) cin >> i;
      if (m == 1){
            cout << x[0] << "\n";
            return 0;
      }
      vec <ll> g(m);
      ll need = (1LL << c[0]) | (1LL << c[n - 1]);
      for (int i = 0; i + 1 < n; ++i){
            if (c[i] == c[i + 1]){
                  need |= 1LL << c[i];
            }
            else{
                  g[c[i]] |= 1LL << c[i + 1];
                  g[c[i + 1]] |= 1LL << c[i];
            }
      }
      int s1 = m / 2, s2 = m - s1;
      int F = (1 << s1) - 1;
      vec <ll> dp(1 << s1, 1e9);
      for (int msk = 0; msk < (1 << s2); ++msk){
            ll cur = need;
            ll sum = 0;
            for (int i = 0; i < s2; ++i){
                  int j = s1 + i;
                  if (msk >> i & 1) sum += x[j];
                  else cur |= g[j];
            }
            if (((cur >> s1) | msk) == msk){
                  umin(dp[cur & F], sum);
            }
      }
      for (int msk = 0; msk < (1 << s1); ++msk){
            for (int i = 0; i < s1; ++i){
                  umin(dp[msk | (1 << i)], dp[msk]);
            }
      }
      ll ans = 1e9;
      for (int msk = 0; msk < (1 << s1); ++msk){
            ll cur = need;
            ll sum = 0;
            for (int i = 0; i < s1; ++i){
                  if (msk >> i & 1) sum += x[i];
                  else cur |= g[i];
            }
            if (((cur & F) | msk) == msk){
                  umin(ans, sum + dp[msk]);
            }
      }
      cout << ans << "\n";
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
