/*
  Time: 12:16
  Num Submissions: 2
  Learnt: Cool dynamics that makes me brain big
  Analysis: This problem is based on only one observation, which is super hard to make. Moslty because statement (and editorial too) are very poorly written
  Rating: 2500
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

const int mod = 998244353;

int add(int a, int b){
      a += b;
      return a >= mod ? a - mod : a;
}

int sub(int a, int b){
      a -= b;
      return a < 0 ? a + mod : a;
}

int mul(int a, int b){
      return a * ll(b) % mod;
}

inline int solve(){
      int n; cin >> n;
      vec <int> a(n);
      for (int i = 1; i <= n - 1; ++i){
            cin >> a[i];
      }
      // f(i) - number of permutations that gives us rooted tree with root = 1
      vec <int> f(n);
      f[0] = 1;
      for (int i = 1; i <= n - 1; ++i){
            // we insert i to any place we want
            f[i] = mul(f[i - 1], i);
            if (a[i]){
                  // we can not insert i to the end, because we will have edge 1 -> i
                  f[i] = sub(f[i], f[i - 1]);
            }
      }
      vec <int> ans(n);
      ans[0] = 0;
      for (int i = 1; i <= n - 1; ++i){
            // we insert i to any place we want
            ans[i] = mul(ans[i - 1], i);
            if (!a[i]){
                  // we can get an edge 1 <- i + 1 only if a[i] = 0 and i is part of some rooted tree
                  ans[i] = add(ans[i], f[i - 1]);
            }
            cout << ans[i] << " ";
      }
      cout << "\n";
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
