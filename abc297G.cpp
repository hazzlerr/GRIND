// Data structures :skull:

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

struct bit{
      int n;
      vec <ll> t;
      bit(int z): n(z + 5), t(z + 5) {}
      void upd(int p, ll x){
            for (p += 5; p < n; p += p & -p){
                  t[p] += x;
            }
      }
      ll get(int r){
            ll res = 0;
            for (r += 5; r > 0; r -= r & -r){
                  res += t[r];
            }
            return res;
      }
      int kth(ll x){
            int res = 0;
            ll sum = 0;
            for (int b = 18; ~b; --b){
                  if (res + (1 << b) < n && sum + t[res + (1 << b)] < x){
                        res += 1 << b, sum += t[res];
                  }
            }
            return res - 5;
      }
};

inline int solve(){
      int n; cin >> n;
      vec <int> a(n), b(n), ii;
      for (int i = 0; i < n; ++i){
            cin >> a[i] >> b[i];
            ii.push_back(a[i]);
      }
      int q; cin >> q;
      vec <array <int, 3>> qq(q);
      for (int i = 0; i < q; ++i){
            int tp; cin >> tp;
            if (tp <= 2){
                  int x, y;
                  cin >> x >> y, --x;
                  qq[i] = {tp, x, y};
                  if (tp == 1){
                        ii.push_back(y);
                  }
            }
            else{
                  int x; cin >> x;
                  qq[i] = {tp, x, -1};
            }
      }
      ii.push_back(0);
      sort(all(ii));
      ii.erase(unique(all(ii)), ii.end());
      int ss = sz(ii);
      auto pos = [&](int x){
            return ss - 1 - (lower_bound(all(ii), x) - ii.begin());
      };

      bit cnt(ss), sum(ss);
      ll cur = 0;
      for (int i = 0; i < n; ++i){
            cnt.upd(pos(a[i]), +b[i]);
            sum.upd(pos(a[i]), +a[i] * ll(b[i]));
            cur += b[i];
      }
      for (auto [tp, x, y]: qq){
            if (tp == 1){
                  sum.upd(pos(a[x]), -a[x] * ll(b[x]));
                  cnt.upd(pos(a[x]), -b[x]);
                  a[x] = y;
                  cnt.upd(pos(a[x]), +b[x]);
                  sum.upd(pos(a[x]), +a[x] * ll(b[x]));
            }
            if (tp == 2){
                  sum.upd(pos(a[x]), -a[x] * ll(b[x]));
                  cnt.upd(pos(a[x]), -b[x]);
                  cur -= b[x];
                  b[x] = y;
                  cur += b[x];
                  sum.upd(pos(a[x]), +a[x] * ll(b[x]));
                  cnt.upd(pos(a[x]), +b[x]);
            }
            if (tp == 3){
                  if (cur < x){
                        cout << "-1\n";
                        continue;
                  }
                  int id = cnt.kth(x);
                  int take = cnt.get(id);
                  int i = ss - 1 - id;
                  cout << sum.get(id) + ii[i - 1] * ll(x - take) << "\n";
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
