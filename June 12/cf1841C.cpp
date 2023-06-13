/*
  Time: 13:06
  Num of Submissions: 2
  Analysis: My implementation skills suck. I go the idea in the first minute and then I was trying to implement it for 40 minutes, got wa3, 
            spent 50 more minutes thinking wtf is happening, added one for, got AC. 
  Rating: ????
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

typedef vec <vec <int>> mat;

template <typename T>
using prq = priority_queue <T>;

template <typename T>
using pgq = priority_queue <T, vec <T>, greater <T>>;

template <typename T> bool umin(T &a, T b) { return a > b ? a = b, 1 : 0; }
template <typename T> bool umax(T &a, T b) { return a < b ? a = b, 1 : 0; }

const vec <int> val = {1, 10, 100, 1000, 10000};

inline int solve(){
      string s; cin >> s;
      int n = sz(s);
      vec <int> a(n);
      for (int i = 0; i < n; ++i){
            a[i] = s[i] - 'A';
      }
      vec <int> cnt(5);
      ll sum = 0;
      for (int i = n - 1; ~i; --i){
            bool fl = 0;
            for (int j = a[i] + 1; j < 5; ++j){
                  fl |= !!cnt[j];
            }
            sum += val[a[i]] * (fl ? -1 : +1);
            ++cnt[a[i]];
      }
      ll ans = sum;
      vec <int> cur(5);

      for (int i = 0; i < n; ++i){
            ll tm = sum;
            int have = 0;
            for (int j = 0; j < 5; ++j){
                  have += !!cnt[j];
            }
            for (int j = 0; j < 5; ++j){
                  have -= !!cnt[j];
                  tm -= cur[j] * val[j] * (have ? -1 : +1);
            }
            --cnt[a[i]];
            have = 0;
            for (int j = a[i] + 1; j < 5; ++j){
                  have += !!cnt[j];
            }
            tm -= val[a[i]] * (have ? -1 : +1);
            for (int x = 0; x < 5; ++x){
                  ll rem = tm;
                  have = 0;
                  for (int j = x + 1; j < 5; ++j){
                        have += !!cnt[j];
                  }
                  tm += val[x] * (have ? -1 : +1);
                  have = 0;
                  ++cnt[x];
                  for (int j = 0; j < 5; ++j){
                        have += !!cnt[j];
                  }
                  for (int j = 0; j < 5; ++j){
                        have -= !!cnt[j];
                        tm += cur[j] * val[j] * (have ? -1 : +1);
                  }
                  umax(ans, tm);
                  --cnt[x], tm = rem;
            }
            ++cur[a[i]];
            for (int j = 0; j < a[i]; ++j){
                  cur[j] = 0;
            }
      }
      cout << ans << "\n";
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
