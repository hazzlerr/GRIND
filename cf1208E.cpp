// It's just a slightly tricky implementation

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

const int inf = 1e9 + 42;

inline int solve(){
      int n, w;
      cin >> n >> w;
      vec <ll> ans(w);
      auto upd = [&](int l, int r, ll x){
            ans[l] += x;
            if (r + 1 < w) ans[r + 1] -= x;
      };
      for (int it = 0; it < n; ++it){
            int k; cin >> k;
            vec <ll> a(k);
            for (auto &i: a) cin >> i;
            if (k == w){
                  for (int i = 0; i < k; ++i){
                        upd(i, i, a[i]);
                  }
            }
            else if (2 * k > w){
                  vec <int> lg(k + 1);
                  for (int i = 2; i <= k; ++i){
                        lg[i] = lg[i >> 1] + 1;
                  }
                  int z = lg[k] + 1;
                  vec <vec <ll>> sp(z, vec <ll> (k));
                  sp[0] = a;
                  for (int b = 1; b < z; ++b){
                        for (int i = 0; i + (1 << b) <= k; ++i){
                              sp[b][i] = max(sp[b - 1][i], sp[b - 1][i + (1 << b - 1)]);
                        }
                  }
                  auto get = [&](int l, int r){
                        int b = lg[r - l + 1];
                        return max(sp[b][l], sp[b][r - (1 << b) + 1]);
                  };
                  for (int i = 0; i < w; ++i){
                        int l = k - 1 - min(k - 1, w - 1 - i);
                        int len = min({k - 1, i - l, k - 1 - l});
                        ll mx = get(l, l + len);
                        if (i >= k || i + k < w){
                              umax(mx, 0LL);
                        }
                        upd(i, i, mx);
                  }
            }
            else{
                  ll mx = 0;
                  for (int i = 0; i < k; ++i){
                        umax(mx, a[i]);
                        upd(i, i, mx);
                  }
                  mx = 0;
                  for (int i = 0; i < k; ++i){
                        umax(mx, a[k - 1 - i]);
                        upd(w - 1 - i, w - 1 - i, mx);
                  }
                  if (k <= w - 1 - k){
                        upd(k, w - 1 - k, mx);
                  }
            }
      }
      partial_sum(all(ans), ans.begin());
      for (auto &i: ans){
            cout << i << " ";
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
