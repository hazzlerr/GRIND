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

const int N = 1e5 + 42;

struct node{
      bool ini, full;
      int sf, pf, ans;
      node(int x = 0, bool ini = 0): sf(x), pf(x), ans(x), ini(ini), full(x) {}
      node operator+(node o){
            if (!ini || !o.ini){
                  node res = ini ? *this : o;
                  res.full = 0;
                  res.ini = 1;
                  return res;
            }
            node res;
            res.ini = 1;
            res.ans = max({ans, o.ans, sf + o.pf});
            res.pf = full ? pf + o.pf : pf;
            res.sf = o.full ? sf + o.sf : o.sf;
            res.full = full && o.full;
            return res;
      }
} t[4 * N];

void upd(int p, int x, int tl, int tr, int v){
      if (tl + 1 == tr) return void(t[v] = node(x, 1));
      int tm = tl + tr >> 1;
      if (p < tm) upd(p, x, tl, tm, v * 2 + 1);
      else upd(p, x, tm, tr, v * 2 + 2);
      t[v] = t[v * 2 + 1] + t[v * 2 + 2];
}

node get(int l, int r, int tl, int tr, int v){
      if (l >= r) return node();
      if (tl == l && tr == r) return t[v];
      int tm = tl + tr >> 1;
      return get(l, min(tm, r), tl, tm, v * 2 + 1) +
             get(max(l, tm), r, tm, tr, v * 2 + 2);
}

inline int solve(){
      int n; cin >> n;
      vec <int> h(n);
      for (auto &i: h) cin >> i;
      vec <int> ii = h;
      sort(all(ii));
      ii.erase(unique(all(ii)), ii.end());
      int z = sz(ii);
      vec <vec <int>> ev(z);
      for (int i = 0; i < n; ++i){
            ev[lower_bound(all(ii), h[i]) - ii.begin()].push_back(i);
      }
      int m; cin >> m;
      vec <array <int, 3>> qq(m);
      for (auto &[l, r, w]: qq){
            cin >> l >> r >> w, --l;
      }
      vec <int> ans(m);
      vec <vec <int>> qr(z);
      for (int b = 16; ~b; --b){
            for (int i = 0; i < m; ++i){
                  if (ans[i] + (1 << b) < z){
                        ans[i] += 1 << b;
                        qr[ans[i]].push_back(i);
                  }
            }
            for (int i = 0; i < n; ++i){
                  upd(i, 0, 0, n, 0);
            }
            for (int i = z - 1; ~i; --i){
                  for (auto &p: ev[i]){
                        upd(p, 1, 0, n, 0);
                  }
                  for (auto &id: qr[i]){
                        auto [l, r, w] = qq[id];
                        int mx = get(l, r, 0, n, 0).ans;
                        if (mx < w) ans[id] -= 1 << b;
                  }
                  qr[i].clear();
            }
      }
      for (int i = 0; i < m; ++i){
            cout << ii[ans[i]] << "\n";
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
