/*
  Time: 1:19:15
  Num of Submissions: 3
  Analysis: Data structures :skull:
  Rating: 3100
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
typedef pair <int, int> pii;
typedef tuple <int, int, int> tui;

template <typename T>
using prq = priority_queue <T>;

template <typename T>
using pgq = priority_queue <T, vec <T>, greater <T>>;

template <typename T> bool umin(T &a, T b) { return a > b ? a = b, 1 : 0; }
template <typename T> bool umax(T &a, T b) { return a < b ? a = b, 1 : 0; }

const int N = 6e5 + 42, L = 20;

int dsu[N], rt[N], we[N], pt;
vec <int> g[N];

int get(int u){
      if (dsu[u] < 0) return u;
      return dsu[u] = get(dsu[u]);
}

void unite(int u, int v, int w){
      u = get(u), v = get(v);
      if (u == v) return;
      if (dsu[u] > dsu[v]) swap(u, v);
      dsu[u] += dsu[v], dsu[v] = u;
      g[pt].push_back(rt[u]);
      g[pt].push_back(rt[v]);
      we[pt] = w, rt[u] = pt++;
}

int fi[N], h[N], up[N][L];

void dfs(int u, int p){
      static int tmr = 0;
      up[u][0] = p;
      for (int i = 1; i < L; ++i){
            up[u][i] = up[up[u][i - 1]][i - 1];
      }
      h[u] = h[p] + 1;
      fi[u] = tmr++;
      for (auto &v: g[u]) dfs(v, u);
}

int jump(int u, int k){
      for (int i = 0; i < L; ++i){
            if (k >> i & 1) u = up[u][i];
      }
      return u;
}

int lca(int u, int v){
      if (h[u] > h[v]) swap(u, v);
      v = jump(v, h[v] - h[u]);
      if (u == v) return u;
      for (int i = L - 1; ~i; --i){
            if (up[u][i] != up[v][i]){
                  u = up[u][i], v = up[v][i];
            }
      }
      return up[u][0];
}

int val(int u, int v){
      if (u == v) return -1;
      return we[lca(u, v)];
}

struct node{
      int l, r, cl, cr, p;
      node(int u = -1): l(u), r(u), cl(u), cr(u), p(-1) {}
      node operator+(node o){
            node res;
            if (~l){
                  res.l = l;
                  if (~o.l && fi[o.l] < fi[l]){
                        res.l = o.l;
                  }
            }
            else res.l = o.l;
            if (~r){
                  res.r = r;
                  if (~o.r && fi[o.r] > fi[r]){
                        res.r = o.r;
                  }
            }
            else res.r = o.r;
            res.cl = fi[cl] < fi[o.cl] ? cl : o.cl;
            res.cr = fi[cr] > fi[o.cr] ? cr : o.cr;
            return res;
      }
      void app(int x){
            p = x;
            if (!x) l = r = -1;
            else l = cl, r = cr;
      }
} t[4 * N];

void build(int tl, int tr, int v){
      if (tl + 1 == tr) return void(t[v] = node(tl));
      int tm = tl + tr >> 1;
      build(tl, tm, v * 2 + 1);
      build(tm, tr, v * 2 + 2);
      t[v] = t[v * 2 + 1] + t[v * 2 + 2];
}

void push(int v){
      if (~t[v].p){
            for (int i: {v * 2 + 1, v * 2 + 2}){
                  t[i].app(t[v].p);
            }
            t[v].p = -1;
      }
}

void upd(int l, int r, int x, int tl, int tr, int v){
      if (l >= r) return;
      if (tl == l && tr == r) return t[v].app(x);
      push(v);
      int tm = tl + tr >> 1;
      upd(l, min(tm, r), x, tl, tm, v * 2 + 1);
      upd(max(l, tm), r, x, tm, tr, v * 2 + 2);
      t[v] = t[v * 2 + 1] + t[v * 2 + 2];
}

inline int solve(){
      int n, q;
      cin >> n >> q;
      vec <tui> e(n - 1);
      for (auto &[w, u, v]: e){
            cin >> u >> v >> w, --u, --v;
      }
      sort(all(e));
      fill(dsu, dsu + n, -1);
      iota(rt, rt + n, 0);
      pt = n;
      for (auto &[w, u, v]: e){
            unite(u, v, w);
      }
      dfs(pt - 1, pt - 1);
      build(0, n, 0);
      upd(0, n, 0, 0, n, 0);
      while(q--){
            int tp; cin >> tp;
            if (tp < 3){
                  int l, r;
                  cin >> l >> r, --l;
                  upd(l, r, 2 - tp, 0, n, 0);
            }
            else{
                  int x; cin >> x, --x;
                  int ans = -1;
                  for (auto o: {t[0].l, t[0].r}){
                        if (~o) umax(ans, val(o, x));
                  }
                  cout << ans << "\n";
            }
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
