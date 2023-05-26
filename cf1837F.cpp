// the dumbest problem i've ever seen

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

const ll inf = 1e18;

inline int solve(){
      int n, k;
      cin >> n >> k;
      vec <int> a(n);
      for (auto &i: a) cin >> i;
      ll ans = 0;
      for (ll b = inf / 2; b > 0; b >>= 1){
            while(true){
                  ans += b;
//                  system("pause");
//                  cout << "TRY " << ans << "\n";
                  priority_queue <int> s;
                  ll sum = 0;
                  vec <int> lf(n);
                  for (int i = 0; i < n; ++i){
                        s.push(a[i]);
                        sum += a[i];
                        if (sum > ans){
                              sum -= s.top(); s.pop();
                        }
                        lf[i] = sz(s);
                  }
                  s = priority_queue <int> ();
                  sum = 0;
                  vec <int> rt(n + 1);
                  for (int i = n - 1; ~i; --i){
                        s.push(a[i]);
                        sum += a[i];
                        if (sum > ans){
                              sum -= s.top(); s.pop();
                        }
                        rt[i] = sz(s);
                  }
//                  for (int i = 0; i < n; ++i){
//                        cout << i << ": " << lf[i] << " " << rt[i] << "\n";
//                  }
                  bool fl = 0;
                  for (int i = 0; i < n; ++i){
                        if (lf[i] + rt[i + 1] >= k){
                              ans -= b, fl = 1;
                              break;
                        }
                  }
                  if (fl) break;
            }
      }
      cout << ans + 1 << "\n";
      return 0;
}

inline void precalc(){}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; cin >> tst;
      precalc();
      while(tst--) solve();
      return 0;
}
