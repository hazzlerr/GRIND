// That's a funny random solution (it's based on the fact if the input is randomly generated we will probably get new remainder every time we substract row/column)
// Spent some time debugging it (there was one silly typo)

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

mt19937 rng((uint64_t) new char);

inline int solve(){
      int n, m, p;
      cin >> n >> m >> p;
      vec <vec <ll>> a(n, vec <ll> (m));
      for (int i = 0; i < n; ++i){
            for (int j = 0; j < m; ++j){
                  cin >> a[i][j];
                  if (i) a[i][j] += a[i - 1][j];
                  if (j) a[i][j] += a[i][j - 1];
                  if (i && j) a[i][j] -= a[i - 1][j - 1];
            }
      }
      auto get = [&](int lx, int ly, int rx, int ry){
            ll sum = a[rx][ry];
            if (lx) sum -= a[lx - 1][ry];
            if (ly) sum -= a[rx][ly - 1];
            if (lx && ly) sum += a[lx - 1][ly - 1];
            return sum;
      };

      prq <array <ll, 6>> q;
      q.push({get(0, 0, n - 1, m - 1), 0LL, 0LL, n - 1, m - 1, 0LL});
      while(!q.empty()){
            auto [sum, lx, ly, rx, ry, tp] = q.top(); q.pop();
            if (sum % p == 0){
                  cout << sum << "\n";
                  return 0;
            }
            if (tp == 0 && lx < rx){
                  ll nw = get(lx + 1, ly, rx, ry);
                  q.push({nw, lx + 1, ly, rx, ry, tp});
            }
            if (tp == 1 && lx < rx){
                  ll nw = get(lx, ly, rx - 1, ry);
                  q.push({nw, lx, ly, rx - 1, ry, tp});
            }
            if (tp == 2 && ly < ry){
                  ll nw = get(lx, ly + 1, rx, ry);
                  q.push({nw, lx, ly + 1, rx, ry, tp});
            }
            if (tp == 3 && ly < ry){
                  ll nw = get(lx, ly, rx, ry - 1);
                  q.push({nw, lx, ly, rx, ry - 1, tp});
            }
            if (tp != 3){
                  q.push({sum, lx, ly, rx, ry, tp + 1});
            }
      }
      cout << "0\n";
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
