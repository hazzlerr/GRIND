// a + b = a | b + a & b
// a ^ b = a | b - a & b

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
      bool dbg = 0;
      int n, k;
      cin >> n >> k;
      vec <int> c(n);
      if (dbg){
            for (auto &i: c) cin >> i;
      }
      auto ask1 = [&](int i, int j){
            cout << "or " << i + 1 << " " << j + 1 << "\n";
            fflush(stdout);
            int x;
            if (dbg) x = c[i] | c[j];
            else cin >> x;
            if (x == -1) exit(0);
            return x;
      };
      auto ask2 = [&](int i, int j){
            cout << "and " << i + 1 << " " << j + 1 << "\n";
            fflush(stdout);
            int x;
            if (dbg) x = c[i] & c[j];
            else cin >> x;
            if (x == -1) exit(0);
            return x;
      };
      array <array <int, 3>, 3> sum;
      for (int i = 0; i < 3; ++i){
            for (int j = i + 1; j < 3; ++j){
                  sum[i][j] = ask1(i, j) + ask2(i, j);
            }
      }
      vec <int> a(n);
      a[0] = (sum[0][1] + sum[0][2] - sum[1][2]) / 2;
      a[1] = (sum[1][2] + sum[0][1] - sum[0][2]) / 2;
      a[2] = (sum[0][2] + sum[1][2] - sum[0][1]) / 2;
      for (int i = 3; i < n; ++i){
            int o = ask1(0, i), an = ask2(0, i);
            int xo = o - an;
            a[i] = xo ^ a[0];
      }
//      for (auto &i: a){
//            cout << i << " ";
//      }
//      cout << "\n";
      sort(all(a));
      cout << "finish " << a[k - 1] << "\n";
      fflush(stdout);
      return 0;
}

inline void precalc(){}

signed main(){
//      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; //cin >> tst;
      precalc();
      while(tst--) solve();
      return 0;
}
