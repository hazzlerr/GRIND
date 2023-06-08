// just basic li-chao

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

const ll inf = 2e18;
const int iinf = 1e9 + 42;

struct foo{
      ll k, b;
      foo(ll k = 0, ll b = inf): k(k), b(b) {}
      ll operator()(ll x){
            return k * x + b;
      }
};

typedef struct node* pnode;

vec <pair <pnode, foo>> st;
vec <int> ss;

struct node{
      pnode l, r;
      foo f;
      node() { l = r = nullptr; }
      bool app(foo &nf, ll x){
            if (nf(x) < f(x)){
                  st.emplace_back(this, f);
                  return swap(f, nf), 1;
            }
            return 0;
      }
};

void upd(foo f, int l, int r, pnode t){
      if (l + 1 == r) return void(t->app(f, l));
      int m = l + r >> 1;
      bool lef = f(l) < t->f(l);
      bool mid = t->app(f, m);
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
      if (!t) return inf;
      if (l + 1 == r) return t->f(x);
      int m = l + r >> 1;
      if (x < m) return min(t->f(x), get(x, l, m, t->l));
      return min(t->f(x), get(x, m, r, t->r));
}

const int N = 1e5 + 42;

vec <pii> g[N];
ll s[N], v[N];

void remember(){
      ss.push_back(sz(st));
}

void rollback(){
      while(st.size() > ss.back()){
            auto [t, f] = st.back();
            st.pop_back();
            t->f = f;
      }
      ss.pop_back();
}

ll h[N], dp[N];
pnode t;

void dfs(int u, int p){
      dp[u] = u ? s[u] + get(v[u], 0, iinf, t) + v[u] * h[u] : 0;
      remember();
      upd({-h[u], dp[u]}, 0, iinf, t);
      for (auto &[v, d]: g[u]) if (v != p){
            h[v] = h[u] + d;
            dfs(v, u);
      }
      rollback();
}

inline int solve(){
      int n; cin >> n;
      for (int i = 0; i < n - 1; ++i){
            int u, v, d;
            cin >> u >> v >> d, --u, --v;
            g[u].push_back({v, d});
            g[v].push_back({u, d});
      }
      for (int i = 1; i < n; ++i){
            cin >> s[i] >> v[i];
      }
      t = new node;
      dfs(0, 0);
      for (int i = 1; i < n; ++i){
            cout << dp[i] << " ";
      }
      return 0;
}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; //cin >> tst;
      while(tst--) solve();
      return 0;
}
