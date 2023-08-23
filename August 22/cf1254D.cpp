/*
  Time: 41:46
  Num of Submissions: 1
  Analysis: For an update (u, d), for vertex v we need to increase val by d * (n - (size of subtree u that v belongs to)) / n
            It can be done using sqrt, or pretty neat hld'ish idea (update only big subtree and maintain contribution for small subtrees) 
  Rating: 2700
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

//#pragma GCC optimize("Ofast,unroll-loops")
//#pragma GCC target("avx,avx2,fma")

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

const int mod = 998244353;

int add(int a, int b){
      a += b;
      return a >= mod ? a - mod : a;
}

void inc(int &a, int b){
      a += b;
      a -= a >= mod ? mod : 0;
}

int sub(int a, int b){
      a -= b;
      return a < 0 ? a + mod : a;
}

int mul(int a, int b){
      return a * ll(b) % mod;
}

int bpw(int a, int b){
      int r = 1;
      for (; b; b >>= 1, a = mul(a, a)){
            if (b & 1) r = mul(r, a);
      }
      return r;
}

int inv(int a){
      return bpw(a, mod - 2);
}

int dvd(int a, int b){
      return mul(a, inv(b));
}

const int N = 3e5 + 42;

struct node{
      int s, p;
      node(int s = 0): s(s), p(0) {}
      node operator+(node o){
            node res;
            res.s = add(s, o.s);
            return res;
      }
} t[4 * N];

void apply(int v, int x){
      inc(t[v].s, x), inc(t[v].p, x);
}

void push(int v){
      if (!t[v].p) return;
      for (int i: {v * 2 + 1, v * 2 + 2}){
            apply(i, t[v].p);
      }
      t[v].p = 0;
}

void upd(int l, int r, int x, int tl, int tr, int v){
      if (l >= r) return;
      if (tl == l && tr == r) return apply(v, x);
      push(v);
      int tm = tl + tr >> 1;
      upd(l, min(tm, r), x, tl, tm, v * 2 + 1);
      upd(max(l, tm), r, x, tm, tr, v * 2 + 2);
      t[v] = t[v * 2 + 1] + t[v * 2 + 2];
}

int get(int p, int tl, int tr, int v){
      if (tl + 1 == tr) return t[v].s;
      push(v);
      int tm = tl + tr >> 1;
      if (p < tm) return get(p, tl, tm, v * 2 + 1);
      return get(p, tm, tr, v * 2 + 2);
}

inline int solve(){
      int n, q;
      cin >> n >> q;
      vec <vec <int>> g(n);
      for (int i = 0; i < n - 1; ++i){
            int u, v;
            cin >> u >> v, --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);
      }
      vec <int> ss(n), pa(n);
      auto dfs = [&](auto &&dfs, int u, int p) -> void{
            if (u != 0) g[u].erase(find(all(g[u]), p));
            pa[u] = p, ss[u] = 1;
            for (auto &v: g[u]){
                  dfs(dfs, v, u), ss[u] += ss[v];
                  if (ss[v] > ss[g[u][0]]) swap(v, g[u][0]);
            }
      };
      dfs(dfs, 0, 0);
      vec <int> fi(n), fo(n), up(n);
      int z = 0;
      auto hld = [&](auto &&hld, int u) -> void{
            fi[u] = z++;
            for (auto &v: g[u]){
                  up[v] = v == g[u][0] ? up[u] : v;
                  hld(hld, v);
            }
            fo[u] = z++;
      };
      hld(hld, 0);
      vec <int> rem(n);
      int in = inv(n);
      while(q--){
            int tp; cin >> tp;
            if (tp == 1){
                  int u, d;
                  cin >> u >> d, --u;
                  if (!g[u].empty()){
                        int b = g[u][0];
                        upd(fi[b], fo[b], mul(d, sub(n, ss[b])), 0, z, 0);
                  }
                  if (u != 0){
                        upd(0, fi[u], mul(d, ss[u]), 0, z, 0);
                        upd(fo[u], z, mul(d, ss[u]), 0, z, 0);
                  }
                  inc(rem[u], d);
            }
            else{
                  int u; cin >> u, --u;
                  int ans = add(mul(rem[u], n), get(fi[u], 0, z, 0));
                  while(up[u] != 0){
                        inc(ans, mul(rem[pa[up[u]]], sub(n, ss[up[u]])));
                        u = pa[up[u]];
                  }
                  cout << mul(ans, in) << "\n";
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
