/*
  Time: 6:34
  Num of Submissions: 2
  Analysis: I know mobius function
  Rating: 2300
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("avx2")

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

const int N = 5e5 + 42;

vec <int> dv[N];
int md[N], mu[N];

int cnt[N];

inline int solve(){
      int n, q;
      cin >> n >> q;
      vec <int> a(n), fl(n);
      for (auto &i: a) cin >> i;
      ll ans = 0;
      auto add = [&](int x){
            for (int d: dv[x]){
                  ans += cnt[d]++ * mu[d];
            }
      };
      auto del = [&](int x){
            for (int d: dv[x]){
                  ans -= --cnt[d] * mu[d];
            }
      };
      while(q--){
            int i; cin >> i, --i;
            if (fl[i]) del(a[i]);
            else add(a[i]);
            fl[i] ^= 1;
            cout << ans << "\n";
      }
      return 0;
}

inline void precalc(){
      for (int i = 2; i < N; ++i){
            if (md[i]) continue;
            for (int j = i; j < N; j += i){
                  md[j] = i;
            }
      }
      for (int i = 1; i < N; ++i){
            for (int j = i; j < N; j += i){
                  dv[j].push_back(i);
            }
            if (i == 1) mu[i] = 1;
            else if (md[i / md[i]] == md[i]) mu[i] = 0;
            else mu[i] = -mu[i / md[i]];
      }
}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; //cin >> tst;
      precalc();
      while(tst--) solve();
      return 0;
}
