/*
  Time: 20:52
  Num of Submissions: 1
  Analysis: O(n^2) dp can be calculated as dp[i] = max(dp[j - 1] + cost(j..i))
            When we move i -> i + 1 we can recalc new costs and update max using segtree
  Rating: 2100
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

const int N = 3e5 + 42;
const ll inf = 1e18;

struct node{
      ll x, p;
      node(ll x = -inf): x(x), p(0) {}
      node operator+(node o){
            node res;
            res.x = max(x, o.x);
            return res;
      }
} t[4 * N];

void apply(int v, ll x){
      t[v].x += x, t[v].p += x;
}

void push(int v){
      if (!t[v].p) return;
      for (int i: {v * 2 + 1, v * 2 + 2}){
            apply(i, t[v].p);
      }
}

void uset(int p, ll x, int tl, int tr, int v){
      if (tl + 1 == tr) return void(t[v] = x);
      push(v);
      int tm = tl + tr >> 1;
      if (p < tm) uset(p, x, tl, tm, v * 2 + 1);
      else uset(p, x, tm, tr, v * 2 + 2);
      t[v] = t[v * 2 + 1] + t[v * 2 + 2];
}

void uadd(int l, int r, ll x, int tl, int tr, int v){
      if (l >= r) return;
      if (tl == l && tr == r) return apply(v, x);
      push(v);
      int tm = tl + tr >> 1;
      uadd(l, min(tm, r), x, tl, tm, v * 2 + 1);
      uadd(max(l, tm), r, x, tm, tr, v * 2 + 2);
      t[v] = t[v * 2 + 1] + t[v * 2 + 2];
}

inline int solve(){
      int n; cin >> n;
      vec <int> h(n), a(n);
      for (auto &i: h) cin >> i;
      for (auto &i: a) cin >> i;
      vec <ll> dp(n + 1);
      vec <array <int, 4>> st;
      st.push_back({0, 0, 0, 0});
      uset(0, 0, 0, n + 1, 0);
      for (int i = 1; i <= n; ++i){
            while(h[i - 1] < st.back()[0]){
                  auto [hj, l, r, val] = st.back();
                  uadd(l, r, -val, 0, n + 1, 0);
                  st.pop_back();
            }
            int l = st.back()[2], r = i;
            uadd(l, r, +a[i - 1], 0, n + 1, 0);
            uset(i, dp[i] = t[0].x, 0, n + 1, 0);
            st.push_back({h[i - 1], l, r, a[i - 1]});
      }
      cout << dp[n] << "\n";
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
