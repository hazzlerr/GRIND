/*
  Time: 58:17
  Num Submissions: 3
  Learned: Relearned CHT
  Analysis: Need to be careful with cross function
  Rating: 2700
*/
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

const int mod = 1e9 + 7;

int nrm(ll a){
      return a % mod;
}

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
      return nrm(a * ll(b));
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

const ll inf = 1e18;

struct line{
      ll k, b;
      line(ll k = 0, ll b = -inf): k(k), b(b) {}
      ll operator()(ll x){
            return k * x + b;
      }
      ll operator^(line o){
            return (o.b - b) / (k - o.k);
      }
      bool operator<(line o){
            return k == o.k ? b < o.b : k > o.k;
      }
};


inline int solve(){
      int n, m, q;
      cin >> n >> m >> q;
      vec <tui> e(m);
      for (auto &[u, v, w]: e){
            cin >> u >> v >> w, --u, --v;
      }
      int ans = 0;
      vec <vec <ll>> d(m + 1, vec <ll> (n, -inf));
      d[0][0] = 0;
      for (int i = 1; i <= m; ++i){
            for (auto &[u, v, w]: e){
                  if (d[i - 1][u] != -inf){
                        umax(d[i][v], d[i - 1][u] + w);
                  }
                  if (d[i - 1][v] != -inf){
                        umax(d[i][u], d[i - 1][v] + w);
                  }
            }
            inc(ans, nrm(*max_element(all(d[i]))));
      }
      vec <line> ln;
      vec <ll> dot;
      auto push = [&](line f){
            while(!ln.empty() && ln.back()(dot.back()) <= f(dot.back())){
                  ln.pop_back(), dot.pop_back();
            }
            if (ln.empty()){
                  dot.push_back(-1);
            }
            else{
                  dot.push_back(ln.back() ^ f);
            }
            ln.push_back(f);
      };

      vec <line> lol(2 * m);
      for (int i = 0; i < m; ++i){
            auto [u, v, w] = e[i];
            lol[2 * i] = {w, d[m][v] - m * ll(w)};
            lol[2 * i + 1] = {w, d[m][u] - m * ll(w)};
      }
      sort(rall(lol));
      for (int i = 0; i < sz(lol); ++i){
            if (!i || lol[i - 1].k != lol[i].k){
                  push(lol[i]);
            }
      }
      dot.push_back(2e9 + 42);
      int i2 = inv(2);
      for (int i = 0, l = m + 1; i < sz(ln) && l <= q; ++i){
            int r = min((ll) q, dot[i + 1]);
            int len = r - l + 1;
            if (len <= 0) continue;
            int st = nrm(ln[i](l));
            int en = nrm(st + (len - 1) * ln[i].k);
            inc(ans, mul(mul(len, add(st, en)), i2));
            l = r + 1;
      }
      cout << ans << "\n";
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
