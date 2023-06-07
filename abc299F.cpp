/*
  Time: 7:03
  Num of Submissions: 1
  Analysis: I think I saw this method to calculate dp (when you can count smth multiple times you are only using its first occurence)
  Rating: 2366
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

void inc(int &a, int b){
      a += b;
      a -= a >= mod ? mod : 0;
}

int mul(int a, int b){
      return a * ll(b) % mod;
}

inline int solve(){
      string s; cin >> s;
      int n = sz(s);
      vec <vec <int>> nxt(n, vec <int> (26, n + 1));
      for (int i = n - 1; ~i; --i){
            if (i + 1 < n){
                  nxt[i] = nxt[i + 1];
            }
            nxt[i][s[i] - 'a'] = i;
      }
      int ans = 0;
      for (int st = 0; st + 1 < n; ++st){
            vec <vec <int>> dp(n, vec <int> (n));
            auto upd = [&](int i, int j, int val){
                  if (i >= j || j >= n - 1) return;
                  for (int c = 0; c < 26; ++c){
                        int ni = nxt[i + 1][c], nj = nxt[j + 1][c];
                        if (ni <= st && nj < n){
                              inc(dp[ni][nj], val);
                        }
                  }
            };
            upd(-1, st, 1);
            for (int i = 0; i < st; ++i){
                  for (int j = st + 1; j < n; ++j){
                        upd(i, j, dp[i][j]);
                  }
            }
            for (int i = 0; i < n; ++i){
                  inc(ans, dp[st][i]);
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
