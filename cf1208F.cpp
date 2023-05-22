// I've learned sos dp

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

const pii nul = {-1, -1};

pii mrg(pii a, pii b){
      if (a.se < b.se) swap(a.se, b.se);
      if (a.fi < b.se) swap(a.fi, b.se);
      if (a.fi < b.fi) swap(a.fi, b.fi);
      return a;
}

const int L = 21, F = (1 << L) - 1;

pii dp[1 << L];

inline int solve(){
      fill(dp, dp + (1 << L), nul);
      int n; cin >> n;
      vec <int> a(n);
      for (int i = 0; i < n; ++i){
            cin >> a[i];
            dp[a[i]] = mrg(dp[a[i]], {-1, i});
      }
      for (int i = 0; i < L; ++i){
            for (int msk = 0; msk < (1 << L); ++msk){
                  if (~msk >> i & 1){
                        dp[msk] = mrg(dp[msk], dp[msk ^ (1 << i)]);
                  }
            }
      }
      int ans = 0;
      for (int i = 0; i + 2 < n; ++i){
            int need = F ^ a[i];
            int res = 0;
            for (int b = L - 1; ~b; --b){
                  if (need >> b & 1){
                        res ^= 1 << b;
                        if (dp[res].fi <= i){
                              res ^= 1 << b;
                        }
                  }
            }
            umax(ans, a[i] | res);
      }
      cout << ans << "\n";
      return 0;
}

inline void precalc(){
}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; //cin >> tst;
      precalc();
      while(tst--) solve();
      return 0;
}
