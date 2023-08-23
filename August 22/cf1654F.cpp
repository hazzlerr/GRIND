/*
  Time: 15:39
  Num of Submissions: 1
  Analysis: Yay, suffix array
  Rating: 2800
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

//#pragma GCC optimize("Ofast,unroll-loops")
//#pragma GCC target("avx,avx2,fma")

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
      string s; cin >> s;
      int z = sz(s);
      vec <int> p(z), c(z);
      iota(all(p), 0);
      sort(all(p), [&](int i, int j) { return s[i] < s[j]; });
      c[p[0]] = 0;
      for (int i = 1; i < z; ++i){
            c[p[i]] = c[p[i - 1]] + (s[p[i]] != s[p[i - 1]]);
      }
      for (int st = 0; st < n; st++){
            sort(all(p), [&](int i, int j){
                  pii pi = {c[i], c[i ^ (1 << st)]};
                  pii pj = {c[j], c[j ^ (1 << st)]};
                  return pi < pj;
            });
            vec <int> nc(z);
            nc[p[0]] = 0;
            for (int i = 1; i < z; ++i){
                  pii cur = {c[p[i]], c[p[i] ^ (1 << st)]};
                  pii prv = {c[p[i - 1]], c[p[i - 1] ^ (1 << st)]};
                  nc[p[i]] = nc[p[i - 1]] + (cur != prv);
            }
            swap(c, nc);
      }
      for (int i = 0; i < z; ++i){
            cout << s[i ^ p[0]];
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
