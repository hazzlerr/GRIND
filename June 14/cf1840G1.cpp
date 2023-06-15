/*
  Time: 13:55
  Num of Submissions: 5
  Analysis: Funny sqrt
  Rating: 2200
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

const int S = 1000;

inline int solve(){
      auto go = [&](int k, int fl){
            cout << (fl ? "+ " : "- ") << k << endl;
            int x; cin >> x;
            return x;
      };
      int st; cin >> st;
      map <int, int> id;
      for (int u = st, i = 0; i < S; ++i){
            if (id.count(u)){
                  cout << "! " << i << endl;
                  return 0;
            }
            id[u] = i;
            if (i + 1 != S) u = go(1, 1);
      }
      int u = go(S - 1, 0);
      int len = 0;
      while(true){
            u = go(S, 1), len += S;
            if (id.count(u)){
                  cout << "! " << len - id[u] << endl;
                  return 0;
            }
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
