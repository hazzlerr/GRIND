/*
  Time: 14:03
  Num of Submissions: 1
  Analysis: I found this problem easier than C from the same contest. 
  Rating: ????
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
      vec <vec <int>> pos(n + 1);
      for (int i = 0; i < n; ++i){
            int a; cin >> a;
            pos[a].push_back(i);
      }
      set <pii> s;
      vec <ll> cnt(n + 1);
      cnt[n] = n;
      s.insert({n - 1, 0});
      for (int x = n; x; --x){
            for (auto &i: pos[x]){
                  auto [r, l] = *s.lower_bound({i, -1});
                  cnt[r - l + 1] -= x;
                  s.erase({r, l});
                  if (l < i){
                        s.insert({i - 1, l});
                        cnt[i - l] += x;
                  }
                  if (i < r){
                        s.insert({r, i + 1});
                        cnt[r - i] += x;
                  }
            }
      }
      ll m; cin >> m;
      ll ans = 0;
      for (ll x = n; x && m; --x){
            ll need = min(cnt[x], m / x);
            ans += need * (x - 1);
            m -= need * x, cnt[x] -= need;
            if (cnt[x] > 0 && m > 0){
                  ans += m - 1;
                  break;
            }
      }
      cout << ans << "\n";
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
