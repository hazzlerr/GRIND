/*
  Time: 1:27:44
  Num of Submissions: 3
  Learned: Funny trick with reversed order
  Analysis: Data structures :skull:
  Rating: 2700
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

const ll inf = 1e18;

struct foo{
      ll k, b;
      foo(ll k = 0, ll b = -inf): k(k), b(b) {}
      ll operator()(ll x){
            return k * x + b;
      }
};

typedef struct node* pnode;
struct node{
      foo f;
      pnode l, r;
      node() { l = r = nullptr; }
      bool app(foo &nf, int x){
            return f(x) < nf(x) ? swap(f, nf), 1 : 0;
      }
};

void upd(foo f, int l, int r, pnode t){
      if (l + 1 == r) return void(t->app(f, l));
      int m = l + r >> 1;
      bool lef = t->f(l) < f(l), mid = t->app(f, m);
      if (lef ^ mid){
            if (!t->l) t->l = new node;
            upd(f, l, m, t->l);
      }
      else{
            if (!t->r) t->r = new node;
            upd(f, m, r, t->r);
      }
}

ll get(int x, int l, int r, pnode t){
      if (!t) return -inf;
      if (l + 1 == r) return t->f(x);
      int m = l + r >> 1;
      if (x < m) return max(get(x, l, m, t->l), t->f(x));
      return max(get(x, m, r, t->r), t->f(x));
}

void clear(pnode t){
      if (!t) return;
      clear(t->l), clear(t->r);
      delete t;
}

const int N = 1.5e5 + 42;

ll a[N];
vec <int> g[N];
int ss[N], us[N];

void siz(int u, int p){
      ss[u] = 1;
      for (auto &v: g[u]) if (v != p && !us[v]){
            siz(v, u), ss[u] += ss[v];
      }
}

int cen(int u, int p, int n){
      for (auto &v: g[u]) if (v != p && !us[v]){
            if (ss[v] > n / 2){
                  return cen(v, u, n);
            }
      }
      return u;
}
int cen(int u){
      siz(u, u);
      return cen(u, u, ss[u]);
}

void pref(int u, int p, int h, ll su, ll pf, vec <pll> &lol){
      lol.push_back({su, pf});
      for (auto &v: g[u]) if (v != p && !us[v]){
            pref(v, u, h + 1, su + a[v], pf + (h + 1) * a[v], lol);
      }
}
void suff(int u, int p, int h, ll su, ll sf, vec <pll> &lol){
      lol.push_back({h, sf});
      for (auto &v: g[u]) if (v != p && !us[v]){
            suff(v, u, h + 1, su + a[v], sf + su + a[v], lol);
      }
}

ll dec(int u){
      us[u] = 1;
      vec <vec <pll>> pfs, sfs;
      pfs.push_back({{a[u], a[u]}});
      sfs.push_back({{0, 0LL}});
      for (auto &v: g[u]) if (!us[v]){
            pfs.emplace_back();
            pref(v, u, 2, a[u] + a[v], a[u] + 2 * a[v], pfs.back());
            sfs.emplace_back();
            suff(v, u, 1, a[v], a[v], sfs.back());
      }
      ll res = -inf;
      for (int it = 0; it < 2; ++it){
            pnode t = new node;
            for (int i = 0; i < sz(pfs); ++i){
                  for (auto [h, sf]: sfs[i]){
                        umax(res, sf + get(h, 0, N, t));
                  }
                  for (auto [su, pf]: pfs[i]){
                        upd({su, pf}, 0, N, t);
                  }
            }
            clear(t);
            reverse(all(sfs));
            reverse(all(pfs));
      }
      for (auto &v: g[u]) if (!us[v]){
            umax(res, dec(cen(v)));
      }
      return res;
}

inline int solve(){
      int n; cin >> n;
      for (int i = 0; i < n - 1; ++i){
            int u, v;
            cin >> u >> v, --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
      }
      for (int i = 0; i < n; ++i){
            cin >> a[i];
      }
      cout << dec(cen(0)) << "\n";
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
