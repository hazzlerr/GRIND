// you consider two cases: ai < aj and ai > aj
// Then you work with formulas for this two cases using ai mod aj = ai - aj * [ai / aj]

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

const int N = 3e5 + 42;

ll t[4 * N];

void upd1(int l, int r, ll x, int tl, int tr, int v){
      if (l >= r) return;
      if (tl == l && tr == r) return void(t[v] += x);
      int tm = tl + tr >> 1;
      upd1(l, min(tm, r), x, tl, tm, v * 2 + 1);
      upd1(max(l, tm), r, x, tm, tr, v * 2 + 2);
}

ll get1(int p, int tl, int tr, int v){
      if (tl + 1 == tr) return t[v];
      int tm = tl + tr >> 1;
      if (p < tm) return t[v] + get1(p, tl, tm, v * 2 + 1);
      return t[v] + get1(p, tm, tr, v * 2 + 2);
}

void upd2(int p, ll x, int tl, int tr, int v){
      if (tl + 1 == tr) return void(t[v] += x);
      int tm = tl + tr >> 1;
      if (p < tm) upd2(p, x, tl, tm, v * 2 + 1);
      else upd2(p, x, tm, tr, v * 2 + 2);
      t[v] = t[v * 2 + 1] + t[v * 2 + 2];
}

ll get2(int l, int r, int tl, int tr, int v){
      if (l >= r) return 0;
      if (tl == l && tr == r) return t[v];
      int tm = tl + tr >> 1;
      return get2(l, min(tm, r), tl, tm, v * 2 + 1) +
             get2(max(l, tm), r, tm, tr, v * 2 + 2);
}

inline int solve(){
      int n; cin >> n;
      vec <int> a(n);
      for (auto &i: a) cin >> i;
      vec <ll> ans(n), b(n);
      for (int i = 0; i < n; ++i){
            ans[i] += i * 1LL * a[i] - get1(a[i], 0, N, 0);
            for (int j = a[i]; j < N; j += a[i]){
                  upd1(j, min(j + a[i], N), j, 0, N, 0);
            }
      }
      memset(t, 0, sizeof(t));
      ll pf = 0;
      for (int i = 0; i < n; ++i){
//            ans[i] += pf;
            b[i] += pf;
            for (int j = a[i], k = 1; j < N; j += a[i], ++k){
//                  ans[i] -= a[i] * get2(j, min(j + a[i], N), 0, N, 0);
                  b[i] -= a[i] * k * get2(j, min(j + a[i], N), 0, N, 0);
            }
            pf += a[i];
            upd2(a[i], +1, 0, N, 0);
      }
      for (int i = 0; i < n; ++i){
            ans[i] += b[i] + (i ? ans[i - 1] : 0LL);
            cout << ans[i] << " ";
      }
      return 0;
}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; //cin >> tst;
      while(tst--) solve();
      return 0;
}
