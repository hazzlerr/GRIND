// C(n, k) = n! / k! / (n - k)!
// C(n, k) = (n * (n - 1) * ... * (n - k + 1)) / k!
// For every prime less than sqrt(n) we can easily find how many times it appears in n!, k!, and (n - k)!
// Primes greater than sqrt(n) appear in every number at most one time
// To factorize big numbers we use the fact that they are consecutive, so we can go through them in the similiar way as in the sieve

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
 
#define int long long
 
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair <int, int> pii;
typedef tuple <int, int, int> tui;
 
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
 
const int N = 1e6 + 42;
 
int md[N];
vec <int> pr;
void precalc(){
      for (int i = 2; i < N; ++i){
            if (md[i]) continue;
            pr.push_back(i);
            for (int j = i; j < N; j += i){
                  md[j] = i;
            }
      }
}
 
int get(int r, int p){
      int ans = 0, st = p;
      while(st <= r){
            ans += r / st, st *= p;
      }
      return ans;
}
 
inline int solve(){
      int n, k;
      cin >> n >> k;
      vec <int> a(k);
      for (int i = 0; i < k; ++i){
            a[i] = n - i;
      }
      int ans = 1;
      for (int p: pr){
            int cnt = get(n, p) - get(k, p) - get(n - k, p) + 1;
            cnt %= mod;
            ans = mul(ans, cnt);
            for (int i = n % p; i < k; i += p){
                  while(a[i] % p == 0) a[i] /= p;
            }
      }
      for (auto &i: a) if (i != 1) {
            ans = mul(ans, 2);
      }
      cout << ans << "\n";
      return 0;
}
 
signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; //cin >> tst;
      precalc();
      while(tst--) solve();
      return 0;
}
