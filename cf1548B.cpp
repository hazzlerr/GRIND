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
      int n; cin >> n;
      vec <ll> a(n);
      for (auto &i: a) cin >> i;
      a.insert(a.begin(), 0LL);
      n = sz(a);
      for (int i = n - 1; i > 0; --i){
            a[i] = abs(a[i] - a[i - 1]);
      }
      vec <int> lg(n + 1);
      for (int i = 2; i <= n; ++i){
            lg[i] = lg[i >> 1] + 1;
      }
      int z = lg[n] + 1;
      vec <vec <ll>> sp(z, vec <ll> (n));
      sp[0] = a;
      for (int b = 1; b < z; ++b){
            for (int i = 0; i + (1 << b) <= n; ++i){
                  sp[b][i] = __gcd(sp[b - 1][i], sp[b - 1][i + (1 << b - 1)]);
            }
      }
      auto get = [&](int l, int r){
            int b = lg[r - l + 1];
            return __gcd(sp[b][l], sp[b][r - (1 << b) + 1]);
      };
      int ans = 1;
      for (int i = 2; i < n; ++i){
            int j = i + 1;
            for (int b = lg[n]; ~b; --b){
                  j -= 1 << b;
                  if (j <= 1 || get(j, i) == 1){
                        j += 1 << b;
                  }
            }
            umax(ans, i - j + 2);
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
