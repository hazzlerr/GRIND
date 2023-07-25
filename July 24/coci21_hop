/*
  Time: 3:23
  Num of Submissions: 1
  Analysis: Since xi divides xj, we have 2xi <= xj -> maximum chain length is ~60. 
            Then, we can just assign colors to edges according to log2(x) (we just need to make sure that there are no 4 consecutive edges). 
            11112111211121113111...
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
 
inline int solve(){
      int n; cin >> n;
      vec <ll> a(n);
      for (auto &i: a) cin >> i;
      vec <vec <int>> ans(n, vec <int> (n));
      for (int i = 0; i < n; ++i){
            for (int j = 0; j < i; ++j){
                  ans[i][j] = 3;
                  if (a[i] % a[j] == 0){
                        int li = 63 - __builtin_clzl(a[i]);
                        int lj = 63 - __builtin_clzl(a[j]);
                        for (int s: {2, 4}){
                              if ((li >> s) == (lj >> s)){
                                    ans[i][j] = s / 2;
                                    break;
                              }
                        }
                  }
            }
      }
      for (int i = 1; i < n; ++i){
            for (int j = 0; j < i; ++j){
                  cout << ans[i][j] << " ";
            }
            cout << "\n";
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
