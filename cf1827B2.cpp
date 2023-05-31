// This is a cool one
// We can skip index i if max[1..i] < min[i..n] (which is quite intuitive) 
// Then, for range [l, r] we can count how many is satisfy the conditiond above and substract them from r - l + 1
// So, we need to count number of triplets (l, r, k) such that max[l..k] < min[k+1..r]
// If we fix i such that min[k+1..r] = i, it becomes a matter of a technique to count what ls and rs are good 

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
      vec <int> a(n);
      for (auto &i: a) cin >> i;
      vec <int> lg(n + 1);
      for (int i = 2; i <= n; ++i){
            lg[i] = lg[i >> 1] + 1;
      }
      int z = lg[n] + 1;
      vec <vec <int>> mx(z, vec <int> (n)), mn(z, vec <int> (n));
      mx[0] = mn[0] = a;
      for (int b = 1; b < z; ++b){
            for (int i = 0; i + (1 << b) <= n; ++i){
                  mx[b][i] = max(mx[b - 1][i], mx[b - 1][i + (1 << b - 1)]);
                  mn[b][i] = min(mn[b - 1][i], mn[b - 1][i + (1 << b - 1)]);
            }
      }
      auto Max = [&](int l, int r){
            int b = lg[r - l + 1];
            return max(mx[b][l], mx[b][r - (1 << b) + 1]);
      };
      auto Min = [&](int l, int r){
            int b = lg[r - l + 1];
            return min(mn[b][l], mn[b][r - (1 << b) + 1]);
      };
      ll ans = 0;
      for (int i = 0; i < n; ++i){
            ans += i * ll(i + 1) / 2;
            int r = i;
            for (int j = z - 1; ~j; --j){
                  r += 1 << j;
                  if (r >= n || Min(i, r) < a[i]){
                        r -= 1 << j;
                  }
            }
            int l = i;
            for (int j = z - 1; ~j; --j){
                  l -= 1 << j;
                  if (l < 0 || Min(l, i) < a[i]){
                        l += 1 << j;
                  }
            } --l;
            if (l < 0) continue;
            int cl = l;
            for (int j = z - 1; ~j; --j){
                  cl -= 1 << j;
                  if (cl < 0 || Max(cl, l) > a[i]){
                        cl += 1 << j;
                  }
            } --cl;
            ans -= (l - cl) * ll(r - i + 1);
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
