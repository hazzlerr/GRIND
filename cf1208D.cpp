// Simple greedy + segtree

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

const int N = 2e5 + 42;

ll t[4 * N], p[4 * N];

void build(int tl, int tr, int v, vec <ll> &a){
      if (tl + 1 == tr) return void(t[v] = a[tl]);
      int tm = tl + tr >> 1;
      build(tl, tm, v * 2 + 1, a);
      build(tm, tr, v * 2 + 2, a);
      t[v] = min(t[v * 2 + 1], t[v * 2 + 2]);
}

void push(int v){
      if (p[v]){
            for (int i: {v * 2 + 1, v * 2 + 2}){
                  t[i] += p[v], p[i] += p[v];
            }
            p[v] = 0;
      }
}

void upd(int l, int r, ll x, int tl, int tr, int v){
      if (l >= r) return;
      if (tl == l && tr == r){
            t[v] += x, p[v] += x;
            return;
      }
      push(v);
      int tm = tl + tr >> 1;
      upd(l, min(tm, r), x, tl, tm, v * 2 + 1);
      upd(max(l, tm), r, x, tm, tr, v * 2 + 2);
      t[v] = min(t[v * 2 + 1], t[v * 2 + 2]);
}

int get(int tl, int tr, int v){
      if (tl + 1 == tr) return tl;
      push(v);
      int tm = tl + tr >> 1;
      if (t[v * 2 + 2] <= t[v * 2 + 1]){
            return get(tm, tr, v * 2 + 2);
      }
      return get(tl, tm, v * 2 + 1);
}

inline int solve(){
      int n; cin >> n;
      vec <ll> a(n);
      for (auto &i: a) cin >> i;
      build(0, n, 0, a);
      vec <int> ans(n);
      for (int i = 1; i <= n; ++i){
            int pos = get(0, n, 0);
            ans[pos] = i;
            upd(pos + 1, n, -i, 0, n, 0);
            upd(pos, pos + 1, 1e16, 0, n, 0);
      }
      for (auto &i: ans){
            cout << i << " ";
      }
      return 0;
}

inline void precalc() {}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; //cin >> tst;
      precalc();
      while(tst--) solve();
      return 0;
}
