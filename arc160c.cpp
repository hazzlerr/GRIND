// The main idea is that every cnt will contribute to the total size only cnt + cnt / 2 + cnt / 4 + ... = 2cnt
// So, you can do just a sort of knapsack with it (to do mass updates you can use prefix sums)

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
 
const int mod = 998244353;
 
void inc(int &a, int b){
      a += b;
      a -= a >= mod ? mod : 0;
}
 
void dec(int &a, int b){
      a -= b;
      a += a < 0 ? mod : 0;
}
 
const int N = 2e5 + 100;
 
int cnt[N], sum[N], dp[N], sc[N];
 
inline int solve(){
      int n; cin >> n;
      for (int i = 0; i < n; ++i){
            int a; cin >> a;
            ++cnt[a];
      }
      dp[0] = 1;
      for (int i = 1; i < N; ++i){
            sum[i] = sum[i - 1] / 2 + cnt[i];
            fill(sc, sc + sum[i] + 1, 0);
            for (int j = 0; j <= sum[i - 1]; ++j){
                  inc(sc[0], dp[j]);
                  dec(sc[(j + cnt[i]) / 2 + 1], dp[j]);
            }
            int cur = sc[0];
            for (int j = 0; j <= sum[i] + 1; ++j){
                  dp[j] = cur;
                  inc(cur, sc[j + 1]);
            }
      }
      cout << dp[0] << "\n";
      return 0;
}
 
signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; //cin >> tst;
      while(tst--) solve();
      return 0;
}
