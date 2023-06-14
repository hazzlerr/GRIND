/*
  Time: 13:23
  Num of Submissions: 1
  Analysis: This is a cool one. It's obvious to think about fixing g = gcd(ai, aj), but how do you find max ai * aj, such that their gcd is equal to g?
            Second obvious idea is to divide every number by g. After that, we need to find max ai' * aj' such that they are coprime
            And now we have the main part of the solution - we go through numbers divisible by g in descending order and keep stack with numbers.
            When we have new number x, we pop numbers from the stack till we have numbers in it that are coprime to x. 
            We can pop numbers that are not coprime with x, because any pair with them will not be better than x with the biggest coprime number.
            
  Rating: 2900
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

const int N = 1e5 + 42;

vec <int> dv[N];
int md[N], mu[N];

int have[N], cnt[N];

inline int solve(){
      int n; cin >> n;
      ll ans = 0;
      for (int i = 0; i < n; ++i){
            int a; cin >> a;
            have[a] = 1;
            umax(ans, (ll) a);
      }
      auto add = [&](int x){
            for (int d: dv[x]) ++cnt[d];
      };
      auto del = [&](int x){
            for (int d: dv[x]) --cnt[d];
      };
      auto get = [&](int x){
            int res = 0;
            for (int d: dv[x]){
                  res += cnt[d] * mu[d];
            }
            return res;
      };
      for (int g = 1; g < N; ++g){
            vec <int> st;
            for (int i = N / g; i; --i){
                  if (!have[i * g]) continue;
                  while(!st.empty() && get(i)){
                        if (__gcd(i, st.back()) == 1){
                              umax(ans, i * ll(st.back()) * ll(g));
                        }
                        del(st.back()), st.pop_back();
                  }
                  add(i);
                  st.push_back(i);
            }
            while(!st.empty()){
                  del(st.back()), st.pop_back();
            }
      }
      cout << ans << "\n";
      return 0;
}

inline void precalc(){
      for (int i = 2; i < N; ++i){
            if (md[i]) continue;
            for (int j = i; j < N; j += i){
                  md[j] = i;
            }
      }
      for (int i = 1; i < N; ++i){
            for (int j = i; j < N; j += i){
                  dv[j].push_back(i);
            }
            if (i == 1) mu[i] = 1;
            else if (md[i / md[i]] == md[i]) mu[i] = 0;
            else mu[i] = -mu[i / md[i]];
      }
}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; //cin >> tst;
      precalc();
      while(tst--) solve();
      return 0;
}
