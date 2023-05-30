// Obvious xor basis, but I didn't know how to get kth number efficiently (in author's solution they smh managed to get it in O(1))

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
 
const int B = 60;
 
int ss = 0;
ull ba[B];
 
void add(ull x){
      for (int i = B - 1; ~i; --i){
            if (~x >> i & 1) continue;
            if (!ba[i]){
                  ++ss, ba[i] = x;
                  break;
            }
            x ^= ba[i];
      }
}
 
ull get(ull k){
      ull res = 0;
      ull cur = 1ull << ss - 1;
      for (int i = B - 1; ~i; --i){
            if (!ba[i]) continue;
            if ((cur < k && (~res >> i & 1)) || (cur >= k && (res >> i & 1))){
                  res ^= ba[i];
            }
            if (cur < k) k -= cur;
            cur >>= 1;
      }
      return res;
}
 
inline int solve(){
      int n;
      ull l, r;
      cin >> n >> l >> r;
      vec <ull> basis;
      for (int i = 0; i < n; ++i){
            ull a; cin >> a, add(a);
      }
      for (ull i = l; i <= r; ++i){
            cout << get(i) << " ";
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
