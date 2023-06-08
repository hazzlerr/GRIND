// Main greedy idea - we don't want to use basic scrolls on montster that will be hit with special scroll
// Second idea - last scroll that will be used is special
// Since we will kill the monster with special scroll, we can solve for left and right parts independently 
// To calculate ans for ith monster, we need to find first monster j that will be killed by explosion without using basic scrolls
// Then we can calc dp[i] using dp[j], prefsums, and a little bit of math

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

template <typename T> bool umin(T &a, T b) { return a > b ? a = b, 1 : 0; }
template <typename T> bool umax(T &a, T b) { return a < b ? a = b, 1 : 0; }

inline int solve(){
      int n; cin >> n;
      vec <ll> a(n);
      for (auto &i: a) cin >> i;
      
      vec <ll> pf = a;
      partial_sum(all(pf), pf.begin());
      auto get = [&](int l, int r){
            if (r < l || l < 0) return 0LL;
            return pf[r] - (l ? pf[l - 1] : 0LL);
      };

      auto ari = [&](ll x, ll len){
            ll l = max(0LL, x - len + 1);
            return (l + x) * (x - l + 1) / 2;
      };

      vec <ll> dpl(n);
      vec <int> st;
      for (int i = 0; i < n; ++i){
            while(!st.empty() && a[st.back()] - st.back() > a[i] - i - 1){
                  st.pop_back();
            }
            if (st.empty()){
                  dpl[i] = get(0, i - 1) - ari(a[i] - 1, i);
            }
            else{
                  int pr = st.back();
                  dpl[i] = get(pr + 1, i - 1) - ari(a[i] - 1, i - pr - 1) + dpl[pr];
            }
            st.push_back(i);
      }
      
      vec <ll> dpr(n);
      st.clear();
      for (int i = n - 1; ~i; --i){
            while(!st.empty() && a[st.back()] + st.back() > a[i] + i - 1){
                  st.pop_back();
            }
            if (st.empty()){
                  dpr[i] = get(i + 1, n - 1) - ari(a[i] - 1, n - i - 1);
            }
            else{
                  int pr = st.back();
                  dpr[i] = get(i + 1, pr - 1) - ari(a[i] - 1, pr - i - 1) + dpr[pr];
            }
            st.push_back(i);
      }
      
      ll ans = 1e18;
      for (int i = 0; i < n; ++i){
            umin(ans, dpl[i] + dpr[i] + a[i]);
      }
      cout << ans << "\n";
      return 0;
}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; cin >> tst;
      while(tst--) solve();
      return 0;
}
