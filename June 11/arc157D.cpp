/*
  Time: 17:55
  Num of Submissions: 3
  Analysis: Since we need only 2 Y's in each zone, we have (h + 1) * (w + 1) = (num of Y's) / 2, where h - number of horizontal cuts, and w - vertical.
  Rating: 2435
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

const int mod = 998244353;

void inc(int &a, int b){
      a += b;
      a -= a >= mod ? mod : 0;
}

int mul(int a, int b){
      return a * ll(b) % mod;
}

inline int solve(){
      int n, m;
      cin >> n >> m;
      vec <vec <int>> pf(n, vec <int> (m));
      for (int i = 0; i < n; ++i){
            string s; cin >> s;
            for (int j = 0; j < m; ++j){
                  pf[i][j] = s[j] == 'Y';
                  if (i) pf[i][j] += pf[i - 1][j];
                  if (j) pf[i][j] += pf[i][j - 1];
                  if (i && j) pf[i][j] -= pf[i - 1][j - 1];
            }
      }
      auto get = [&](int li, int lj, int ri, int rj){
            int res = pf[ri][rj];
            if (li) res -= pf[li - 1][rj];
            if (lj) res -= pf[ri][lj - 1];
            if (li && lj) res += pf[li - 1][lj - 1];
            return res;
      };
      int sum = pf[n - 1][m - 1];
      if (sum & 1){
            cout << "0\n";
            return 0;
      }
      int num = pf[n - 1][m - 1] / 2;
      int ans = 0;
      for (int h = 0; h < n; ++h){
            if (num % (h + 1)) continue;
            int w = num / (h + 1) - 1;
            if (w < 0 || w >= m) continue;
            int res = 1;
            vec <int> xs;
            xs.push_back(-1);
            int need = 2 * (w + 1);
            while(sz(xs) <= h){
                  int i = xs.back() + 1, j = xs.back() + 1;
                  while(j < n && get(i, 0, j, m - 1) < need) ++j;
                  if (j == n || get(i, 0, j, m - 1) > need) break;
                  int cnt = 0;
                  xs.push_back(j);
                  while(j < n && get(i, 0, j, m - 1) == need) ++j, ++cnt;
                  res = mul(res, cnt);
            }
            xs.push_back(n - 1);
            if (sz(xs) != h + 2) continue;
            vec <int> ys;
            ys.push_back(-1);
            need = 2 * (h + 1);
            while(sz(ys) <= w){
                  int i = ys.back() + 1, j = ys.back() + 1;
                  while(j < m && get(0, i, n - 1, j) < need) ++j;
                  if (j == m || get(0, i, n - 1, j) > need) break;
                  int cnt = 0;
                  ys.push_back(j);
                  while(j < m && get(0, i, n - 1, j) == need) ++j, ++cnt;
                  res = mul(res, cnt);
            }
            ys.push_back(m - 1);
            if (sz(ys) != w + 2) continue;
            for (int i = 1; i < sz(xs); ++i){
                  for (int j = 1; j < sz(ys); ++j){
                        if (get(xs[i - 1] + 1, ys[j - 1] + 1, xs[i], ys[j]) != 2){
                              res = 0;
                              break;
                        }
                  }
            }
            inc(ans, res);
      }
      cout << ans << "\n";
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
