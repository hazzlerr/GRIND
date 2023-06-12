/*
  Time: 14:17
  Num of Submissions: 1
  Analysis: When I saw n <= 1e18 I instantly understood that it's matrices
  Rating: 1989
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

int add(int a, int b){
      a += b;
      return a >= mod ? a - mod : a;
}

void inc(int &a, int b){
      a += b;
      a -= a >= mod ? mod : 0;
}

int mul(int a, int b){
      return a * ll(b) % mod;
}

vec <vec <int>> mult(vec <vec <int>> &a, vec <vec <int>> &b){
      int n = sz(a), m = sz(a[0]), l = sz(b[0]);
      vec <vec <int>> res(n, vec <int> (l));
      for (int i = 0; i < n; ++i){
            for (int j = 0; j < l; ++j){
                  for (int k = 0; k < m; ++k){
                        inc(res[i][j], mul(a[i][k], b[k][j]));
                  }
            }
      }
      return res;
}

inline int solve(){
      ll n; cin >> n;
      int m; cin >> m;
      vec <vec <bool>> ban(6, vec <bool> (1 << 6));
      for (int i = 0; i < m; ++i){
            string s; cin >> s;
            int x = 0;
            for (int i = 0; i < sz(s); ++i){
                  x += (s[i] == 'b') << i;
            }
            ban[sz(s) - 1][x] = 1;
      }
      auto good = [&](int msk, int le){
            bool fl = 0;
            for (int i = 1; i <= le; ++i){
                  for (int j = 0; j + i <= le; ++j){
                        int sub = 0;
                        for (int k = 0; k < i; ++k){
                              sub += (msk >> (j + k) & 1) << k;
                        }
                        fl |= ban[i - 1][sub];
                  }
            }
            return !fl;
      };
      if (n < 6){
            int ans = 0;
            for (int msk = 0; msk < (1 << n); ++msk){
                  ans += good(msk, n);
            }
            cout << ans << "\n";
            return 0;
      }
      int ss = 1 << 5;
      vec <vec <int>> res(1, vec <int> (ss)), mu(ss, vec <int> (ss));
      for (int msk = 0; msk < ss; ++msk){
            res[0][msk] = good(msk, 5);
      }
      for (int msk = 0; msk < ss; ++msk){
            for (int b = 0; b < 2; ++b){
                  int nw = msk | (b << 5);
                  mu[msk][nw >> 1] = good(nw, 6);
            }
      }
      ll b = n - 5;
      for (; b; b >>= 1, mu = mult(mu, mu)){
            if (b & 1) res = mult(res, mu);
      }
      int ans = 0;
      for (int i = 0; i < ss; ++i){
            inc(ans, res[0][i]);
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
