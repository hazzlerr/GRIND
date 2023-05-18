// Since number of swaps is m <= n / 3, it will not affect at least n - 2 * m = n / 3 elements
// So, there at least n / 3 numbers that are shifted by k positions => there at most n / (n / 3) = 3 possible k's worth checking

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

template <typename T> bool umin(T &a, T b) { return a > b ? a = b, 1 : 0; }
template <typename T> bool umax(T &a, T b) { return a < b ? a = b, 1 : 0; }

inline int solve(){
      int n, m;
      cin >> n >> m;
      vec <int> p(n);
      for (auto &i: p) cin >> i, --i;
      vec <int> shift(n);
      for (int i = 0; i < n; ++i){
            ++shift[(n + i - p[i]) % n];
      }
      vec <int> ans;
      for (int k = 0; k < n; ++k){
            if (n - shift[k] <= 2 * m){
                  vec <int> q;
                  for (int i = k; i < n; ++i){
                        q.push_back(p[i]);
                  }
                  for (int i = 0; i < k; ++i){
                        q.push_back(p[i]);
                  }
                  vec <int> us(n);
                  int res = n;
                  for (int i = 0; i < n; ++i){
                        if (!us[i]){
                              int j = i;
                              while(!us[j]){
                                    us[j] = 1, j = q[j];
                              }
                              --res;
                        }
                  }
                  if (res <= m) ans.push_back(k);
            }
      }
      cout << sz(ans) << " ";
      for (auto &i: ans){
            cout << i << " ";
      }
      cout << "\n";
      return 0;
}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; cin >> tst;
      while(tst--) solve();
      return 0;
}
