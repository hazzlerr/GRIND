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
      int n; cin >> n;
      vec <vec <int>> ans(n, vec <int> (n, -1));
      for (int i = 0; i < n; ++i){
            int pi; cin >> pi;
            int k = pi;
            int x = i, y = i;
            while(k--){
                  if (x == n || ~ans[x][y]){
                        cout << "-1\n";
                        return 0;
                  }
                  ans[x][y] = pi;
                  if (y >= 0 && !~ans[x][y - 1]) --y;
                  else ++x;
            }
      }
      for (int i = 0; i < n; ++i){
            for (int j = 0; j <= i; ++j){
                  cout << ans[i][j] << " ";
            }
            cout << "\n";
      }
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
