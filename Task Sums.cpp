/*
  Time: 34:23
  Num of Submissions: 12
  Learned: Cool idea - if you have multiple things combined, you can fix only one of them and solve the problem based on that
  Analysis: If we talk about implemenentaion, I had to use D´Esopo-Pape algo to squeeze, probably, not optimal solution
  Rating: ????
*/

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#pragma GCC optimize("Ofast")
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

mt19937 rng((uint64_t) new char);

inline int solve(){
      int n; cin >> n;
      vec <int> a(n);
      for (auto &i: a) cin >> i;
      int ss = a[0];
      vec <int> mn(ss, 1e9 + 42), id(ss, 2);
      deque <int> q;
      q.push_back(0);
      mn[0] = 0;
      while(!q.empty()){
            int u = q.front(); q.pop_front();
            int o = u % ss;
            if (mn[o] < u) continue;
            id[o] = 0;
            for (int i = 0; i < n; ++i){
                  int v = (o + a[i]) % ss;
                  if (umin(mn[v], u + a[i])){
                        if (id[v] == 2){
                              q.push_back(u + a[i]);
                        }
                        if (id[v] == 0){
                              q.push_front(u + a[i]);
                        }
                        id[v] = 1;
                  }
            }
      }
      int k; cin >> k;
      while(k--){
            int x; cin >> x;
            cout << (x >= mn[x % ss] ? "TAK\n" : "NIE\n");
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
