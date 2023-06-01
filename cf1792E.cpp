// We can find all divisors of m1 * m2 by 1) Separately factorizing m1 and m2 2) Getting all divisors using recursion
// Then, for d we need to find maximum mx such that d % mx == 0, and then the answer will be d / mx
// We can do it using dp

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

template <typename T>
using prq = priority_queue <T>;

template <typename T>
using pgq = priority_queue <T, vec <T>, greater <T>>;

template <typename T> bool umin(T &a, T b) { return a > b ? a = b, 1 : 0; }
template <typename T> bool umax(T &a, T b) { return a < b ? a = b, 1 : 0; }

inline int solve(){
      int n, m1, m2;
      cin >> n >> m1 >> m2;
      map <int, int> mp;
      for (int x: {m1, m2}){
            for (int i = 2; i * i <= x; ++i){
                  while(x % i == 0){
                        x /= i, ++mp[i];
                  }
            }
            if (x != 1) ++mp[x];
      }
      vec <pii> pr;
      for (auto [x, y]: mp){
            pr.push_back({x, y});
      }
      vec <int> dv;
      auto get = [&](auto &&get, int pt, int cur) -> void{
            if (pt == sz(pr)){
                  return void(dv.push_back(cur));
            }
            auto [x, y] = pr[pt];
            for (int i = 0; i <= y; ++i){
                  get(get, pt + 1, cur);
                  cur *= x;
            }
      }; get(get, 0, 1);
      sort(all(dv));
      int ss = sz(dv);
      vec <int> dp(ss);
      for (int i = 0; i < ss; ++i){
            dp[i] = dv[i] <= n ? dv[i] : 0LL;
      }
      for (auto [p, _]: pr){
            int pt = 0;
            for (int i = 0; i < ss; ++i){
                  if (dv[i] % p == 0){
                        int k = dv[i] / p;
                        while(dv[pt] < k) ++pt;
                        umax(dp[i], dp[pt]);
                  }
            }
      }
      int cnt = 0, ans = 0;
      for (int i = 0; i < ss; ++i){
            int k = dv[i] / dp[i];
            if (k <= n){
                  ++cnt, ans ^= k;
            }
      }
      cout << cnt << " " << ans << "\n";
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
