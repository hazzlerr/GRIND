/*
  Time: 9:04
  Num of Submissions: 2
  Analysis: Easy dp if you know what you're doing
  Rating: ???
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
typedef pair <ll, ll> pll;
typedef pair <int, int> pii;
typedef tuple <int, int, int> tui;

typedef vec <vec <int>> mat;

template <typename T>
using prq = priority_queue <T>;

template <typename T>
using pgq = priority_queue <T, vec <T>, greater <T>>;

template <typename T> bool umin(T &a, T b) { return a > b ? a = b, 1 : 0; }
template <typename T> bool umax(T &a, T b) { return a < b ? a = b, 1 : 0; }

inline int solve(){
      int n; cin >> n;
      vec <pii> a(n);
      vec <int> ii;
      for (auto &[l, r]: a){
            cin >> l >> r;
            ii.push_back(l);
            ii.push_back(r);
      }
      ii.push_back(-1);
      sort(all(ii));
      ii.erase(unique(all(ii)), ii.end());
      int z = sz(ii);
      for (auto &[l, r]: a){
            l = lower_bound(all(ii), l) - ii.begin();
            r = lower_bound(all(ii), r) - ii.begin();
      }
      sort(all(a));

      auto inter = [&](int i, int j){
            return a[i].se >= a[j].fi;
      };

      a.insert(a.begin(), {-1, -1});
      vec <vec <int>> dp(n + 1, vec <int> (z + 1, 0));
      for (int i = 1; i <= n; ++i){
            for (int j = 1; j < i; ++j){
                  if (inter(j, i)){
                        umax(dp[i][max(a[i].se, a[j].se)], 1 + dp[j - 1][a[j].fi - 1]);
                  }
            }
            for (int j = 0; j < z; ++j){
                  umax(dp[i][j], dp[i - 1][j]);
                  umax(dp[i][j + 1], dp[i][j]);
            }
      }
      cout << n - 2 * dp[n][z - 1] << "\n";
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
