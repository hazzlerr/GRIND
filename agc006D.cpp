/*
  Time: 20:34
  Num of Submissions: 1
  Analysis: This is a cool adhoc'ish problem, but when you get the idea with binary search 
            it boils down to staring at bruteforce until noticing the pattern (atcoder moment)
  Rating: 3054
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
 
inline int solve(){
      int n; cin >> n;
      n = 2 * n - 1;
      vec <int> p(n);
      for (auto &i: p) cin >> i;
 
      auto work = [&](vec <int> &v){
            vec <int> q(sz(v) - 2);
            for (int i = 0; i < sz(q); ++i){
                  vec <int> a = {v[i], v[i + 1], v[i + 2]};
                  sort(all(a));
                  q[i] = a[1];
            }
            return q;
      };
 
      auto _check = [&](vec <int> &a){
            int l = n / 2, v = a[l];
            while(l >= 0 && a[l] == v) --l, v ^= 1;
            int r = n / 2; v = a[r];
            while(r < n && a[r] == v) ++r, v ^= 1;
            int lf = n / 2 - l, rt = r - n / 2;
            if (lf < rt) return a[l];
            if (lf > rt) return a[r];
            return a[n / 2] ^ (~lf & 1);
      };
 
      auto check = [&](int x){
            vec <int> a(n);
            for (int i = 0; i < n; ++i){
                  a[i] = p[i] >= x;
            }
            return _check(a);
      };
 
      int ans = 1;
      for (int i = n; i; i >>= 1){
            while(true){
                  ans += i;
                  if (i > n || !check(ans)){
                        ans -= i;
                        break;
                  }
            }
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
