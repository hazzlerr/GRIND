// I've seen 10000000 problems like this, so I basically guessed the solution after some assumptions

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

struct node{
      ll sum, mxpf, mxsf, mnpf, mnsf, mxsu, mnsu;
      node(ll x = 0): sum(x), mxpf(x), mxsf(x), mnpf(x), mnsf(x), mxsu(x), mnsu(x) {}
      node operator+(node o){
            node res;
            res.sum = sum + o.sum;
            res.mnpf = min(mnpf, sum + o.mnpf);
            res.mxpf = max(mxpf, sum + o.mxpf);
            res.mnsf = min(o.mnsf, o.sum + mnsf);
            res.mxsf = max(o.mxsf, o.sum + mxsf);
            res.mnsu = min({mnsu, o.mnsu, mnsf + o.mnpf});
            res.mxsu = max({mxsu, o.mxsu, mxsf + o.mxpf});
            return res;
      }
};

const int N = 1e5 + 42;

node t[4 * N];

void build(int tl, int tr, int v, vec <ll> &a){
      if (tl + 1 == tr) return void(t[v] = a[tl]);
      int tm = tl + tr >> 1;
      build(tl, tm, v * 2 + 1, a);
      build(tm, tr, v * 2 + 2, a);
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
      int n, q;
      cin >> n >> q;
      vec <ll> a(n);
      for (auto &i: a) cin >> i;
      for (int i = 0; i < n; ++i){
            ll b; cin >> b;
            a[i] -= b;
      }
      build(0, n, 0, a);
      while(q--){
            int l, r;
            cin >> l >> r, --l;
            node res = get(l, r, 0, n, 0);
            if (res.sum != 0 || res.mxpf > 0 || res.mnsf < 0){
                  cout << "-1\n";
            }
            else{
                  cout << max(abs(res.mxsu), abs(res.mnsu)) << "\n";
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
