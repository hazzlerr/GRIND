// For segment [l, r] you need to sort a[l..r] and then return sum a[l] * 1 + a[l + 1] * 2 + ... a[r] * (r - l + 1)

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

template <typename T>
struct segt{
      int n;
      vec <T> t;
      segt() {}
      segt(int z): n(z + 1), t(2 * z + 42, 0) {}

      void upd(int p, T x){
            for (t[p += n] += x; p >>= 1; ){
                  t[p] = t[p << 1] + t[p << 1 | 1];
            }
      }

      T get(int l, int r){
            T resl = T(), resr = T();
            for (l += n, r += n; l < r; l >>= 1, r >>= 1){
                  if (l & 1) resl = resl + t[l++];
                  if (r & 1) resr = t[--r] + resr;
            }
            return resl + resr;
      }
};

inline int solve(){
      int n, q;
      cin >> n >> q;
      vec <int> a(n);
      for (auto &i: a) cin >> i;
      int z = *max_element(all(a)) + 5;

      const int B = max(1, int(n / sqrt(q)));

      vec <array <int, 3>> qq(q);
      for (int i = 0; i < q; ++i){
            int l, r;
            cin >> l >> r, --l, --r;
            qq[i] = {l, r, i};
      }
      sort(all(qq), [&](auto &x, auto &y){
            int lb = x[0] / B, rb = y[0] / B;
            return lb == rb ? (lb % 2 ? x[1] > y[1] : x[1] < y[1]) : lb < rb;
      });

      segt <int> cnt(z);
      segt <ll> sum(z);
      ll ans = 0;
      auto add = [&](int p){
            int x = a[p];
            ans += sum.get(x, z);
            sum.upd(x, +x);
            ans += (cnt.get(0, x) + 1) * ll(x);
            cnt.upd(x, +1);
      };
      auto del = [&](int p){
            int x = a[p];
            sum.upd(x, -x);
            ans -= sum.get(x, z);
            cnt.upd(x, -1);
            ans -= (cnt.get(0, x) + 1) * ll(x);
      };

      vec <ll> res(q);
      int l = 0, r = -1;
      for (auto [ql, qr, qi]: qq){
            while(r < qr) add(++r);
            while(l > ql) add(--l);
            while(l < ql) del(l++);
            while(r > qr) del(r--);
            res[qi] = ans;
      }
      for (auto &i: res){
            cout << i << "\n";
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
