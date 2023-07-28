/*
  Num of Submissions: 1
  Analysis: Easy problem, but I found it satisfying to solve
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

template <typename T>
using prq = priority_queue <T>;

template <typename T>
using pgq = priority_queue <T, vec <T>, greater <T>>;

template <typename T> bool umin(T &a, T b) { return a > b ? a = b, 1 : 0; }
template <typename T> bool umax(T &a, T b) { return a < b ? a = b, 1 : 0; }

inline int solve(){
      int n, k;
      cin >> n >> k;
      vec <int> a(n);
      for (auto &i: a) cin >> i;
      vec <int> ii(n);
      iota(all(ii), 0);
      sort(all(ii), [&](int i, int j){
            return a[i] < a[j];
      });
      int ri = -1, rj = -1, mn = 1 << k;
      for (int i = 0; i + 1 < n; ++i){
            int ci = ii[i], cj = ii[i + 1];
            if (umin(mn, a[ci] ^ a[cj])){
                  ri = ci, rj = cj;
            }
      }
      int x = 0, val = a[ri] & a[rj];
      for (int i = 0; i < k; ++i){
            int cx = x | (1 << i);
            if (umax(val, (a[ri] ^ cx) & (a[rj] ^ cx))){
                  x = cx;
            }
      }
      cout << ri + 1 << " " << rj + 1 << " " << x << "\n";
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
