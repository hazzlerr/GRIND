// Slightly tricky sqrt

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

const int S = 650;

inline int solve(){
      int n; cin >> n;
      vec <int> a(n), b(n);
      for (auto &i: a) cin >> i;
      for (auto &i: b) cin >> i;
      ll ans = 0;
      for (int x = 1; x < S; ++x){
            vec <int> cnt(n + 1);
            for (int i = 0; i < n; ++i){
                  ll cur = x * ll(a[i]) - b[i];
                  if (0 <= cur && cur <= n){
                        cnt[cur] += 1 + (a[i] >= S);
                  }
            }
            for (int i = 0; i < n; ++i){
                  if (a[i] == x){
                        ans += cnt[b[i]];
                  }
            }
      }
      for (int i = 0; i < n; ++i){
            if (a[i] * ll(a[i]) == b[i] + b[i]) --ans;
      }
      cout << ans / 2 << "\n";
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
