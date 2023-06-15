/*
  Time: 25:32
  Num of Submissions: 1
  Analysis: Data structures :skull:
            
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

const int N = 4e5 + 42;

int t[4 * N], p[4 * N];

void apply(int v, int x){
      umin(t[v], x), umin(p[v], x);
}

void push(int v){
      if (p[v] != N){
            for (int i: {2 * v + 1, 2 * v + 2}){
                  apply(i, p[v]);
            }
            p[v] = N;
      }
}

void upd(int l, int r, int x, int tl, int tr, int v){
      if (l >= r) return;
      if (tl == l && tr == r) return void(apply(v, x));
      push(v);
      int tm = tl + tr >> 1;
      upd(l, min(tm, r), x, tl, tm, v * 2 + 1);
      upd(max(l, tm), r, x, tm, tr, v * 2 + 2);
      t[v] = min(t[v * 2 + 1], t[v * 2 + 2]);
}

int get(int l, int r, int tl, int tr, int v){
      if (l >= r) return N;
      if (tl == l && tr == r) return t[v];
      push(v);
      int tm = tl + tr >> 1;
      return min(get(l, min(tm, r), tl, tm, v * 2 + 1),
                 get(max(l, tm), r, tm, tr, v * 2 + 2));
}

inline int solve(){
      int n; cin >> n;
      vec <int> l(n), r(n), ii(2 * n);
      for (int i = 0; i < n; ++i){
            cin >> l[i] >> r[i];
            ii[2 * i] = l[i], ii[2 * i + 1] = r[i];
      }
      sort(all(ii));
      ii.erase(unique(all(ii)), ii.end());
      for (int i = 0; i < n; ++i){
            l[i] = lower_bound(all(ii), l[i]) - ii.begin();
            r[i] = lower_bound(all(ii), r[i]) - ii.begin() + 1;
      }
      fill(t, t + 4 * N, N);
      fill(p, p + 4 * N, N);
      vec <int> nxt(n);
      for (int i = n - 1; ~i; --i){
            nxt[i] = min(n, get(l[i], r[i], 0, N, 0));
            upd(l[i], r[i], i, 0, N, 0);
      }
      vec <int> lg(n + 1);
      for (int i = 2; i <= n; ++i){
            lg[i] = lg[i >> 1] + 1;
      }
      int z = lg[n] + 2;
      vec <vec <int>> sp(z, vec <int> (n));
      sp[0] = nxt;
      for (int i = 1; i < z; ++i){
            for (int j = 0; j + (1 << i) <= n; ++j){
                  sp[i][j] = min(sp[i - 1][j], sp[i - 1][j + (1 << i - 1)]);
            }
      }
      auto get = [&](int l, int r){
            int i = lg[r - l + 1];
            return min(sp[i][l], sp[i][r - (1 << i) + 1]);
      };
      vec <vec <int>> up(n + 1, vec <int> (z));
      for (int i = 0; i < n; ++i){
            int res = i;
            for (int j = z - 1; ~j; --j){
                  res += 1 << j;
                  if (res >= n || get(i, res) <= res){
                        res -= 1 << j;
                  }
            }
            up[i][0] = res + 1;
      }
      up[n] = vec <int> (z, n);
      for (int i = 1; i < z; ++i){
            for (int j = 0; j < n; ++j){
                  up[j][i] = up[up[j][i - 1]][i - 1];
            }
      }
      int q; cin >> q;
      while(q--){
            int l, r;
            cin >> l >> r, --l, --r;
            int ans = 0;
            for (int i = z - 1; ~i; --i){
                  if (up[l][i] <= r){
                        ans += 1 << i, l = up[l][i];
                  }
            }
            cout << ans + 1 << "\n";
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
