/*
  Time: 1:34:41
  Num of Submissions: 8
  Analysis: Just dnc with 4 cases depending in which halves are max and min.
  For cases when they are in the same half you can calculate sum of L's (we use the fact that max and min are fixed)
  In cases when they are in different halves you need to support sum of mn[i..mid] * l and mn[i..mid]
  (using formula we can get that add = max * (mn * (r - l + 1))) = max * (mn * (r + 1) - mn * l))
  
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

const int mod = 1e9;

void inc(int &a, int b){
      a += b;
      a -= a >= mod ? mod : 0;
}

int mul(int a, int b){
      return a * ll(b) % mod;
}

mt19937 rng(9499);

inline int solve(){
      int n; cin >> n;
      vec <int> a(n);
      for (auto &i: a) cin >> i;
      vec <int> mnl(n), mxl(n), mnr(n), mxr(n);
      int ans = 0;
      auto rec = [&](auto &&rec, int l, int r) -> void{
            if (l == r){
                  inc(ans, mul(a[l], a[l]));
                  return;
            }
            int m = l + r >> 1;
            mnl[m] = mxl[m] = a[m];
            for (int i = m - 1; i >= l; --i){
                  mnl[i] = min(a[i], mnl[i + 1]);
                  mxl[i] = max(a[i], mxl[i + 1]);
            }
            mnr[m + 1] = mxr[m + 1] = a[m + 1];
            for (int i = m + 2; i <= r; ++i){
                  mnr[i] = min(a[i], mnr[i - 1]);
                  mxr[i] = max(a[i], mxr[i - 1]);
            }

            int pmx, pmn;

            // min and max in the left half
            pmx = pmn = m + 1;
            for (int i = m; i >= l; --i){
                  while(pmx <= r && mxr[pmx] <= mxl[i]) ++pmx;
                  while(pmn <= r && mnr[pmn] >= mnl[i]) ++pmn;
                  int st = m - i + 2, le = min(pmx, pmn) - m - 1;
                  ll cnt = (2 * st + le - 1) * ll(le) / 2;
                  inc(ans, mul(mul(mxl[i], mnl[i]), cnt % mod));
//                  cout << "1: " << i + 1 << " -> " << pmx + 1 << ", " << pmn + 1 << " = " << mul(mul(mxl[i], mnl[i]), cnt % mod) << ", " << cnt << ", " << le << "\n";
            }

            // min and max in the right half
            pmx = pmn = m;
            for (int i = m + 1; i <= r; ++i){
                  while(pmx >= l && mxl[pmx] < mxr[i]) --pmx;
                  while(pmn >= l && mnl[pmn] > mnr[i]) --pmn;
                  int st = i - m + 1, le = m - max(pmx, pmn);
                  ll cnt = (2 * st + le - 1) * ll(le) / 2;
                  inc(ans, mul(mul(mxr[i], mnr[i]), cnt % mod));
            }

            ll lol, su;

            // max in the left half and min in the right half
            lol = su = 0;
            pmx = pmn = m + 1;
            for (int i = m; i >= l; --i){
                  while(pmx <= r && mxr[pmx] <= mxl[i]){
                        lol += mnr[pmx] * ll(pmx + 1);
                        su += mnr[pmx];
                        ++pmx;
                  }
                  while(pmn <= r && mnr[pmn] >= mnl[i]){
                        lol -= mnr[pmn] * ll(pmn + 1);
                        su -= mnr[pmn];
                        ++pmn;
                  }
                  if (pmn < pmx){
                        inc(ans, mul((lol - su * ll(i)) % mod, mxl[i]));
                  }
            }

            // max in the right half and min in the left half
            lol = su = 0;
            pmx = pmn = m;
            for (int i = m + 1; i <= r; ++i){
                  while(pmx >= l && mxl[pmx] < mxr[i]){
                        lol += mnl[pmx] * ll(pmx);
                        su += mnl[pmx];
                        --pmx;
                  }
                  while(pmn >= l && mnl[pmn] > mnr[i]){
                        lol -= mnl[pmn] * ll(pmn);
                        su -= mnl[pmn];
                        --pmn;
                  }
                  if (pmx < pmn){
                        inc(ans, mul((su * (i + 1) - lol) % mod, mxr[i]));
                  }
            }

            rec(rec, l, m);
            rec(rec, m + 1, r);
      };

      rec(rec, 0, n - 1);
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
