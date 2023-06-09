/*
  Time: 12:30
  Num of Submissions: 5
  Analysis: It looks like a hard problem until you realize that you are working with a tree (this fact is hidden in the constraints)
            Also, I had to be careful with overflow (I thought that __in128 would work, but it didn't)
  Rating: 2300
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

const ll inf = 2e18;

inline int solve(){
      int n; cin >> n;
      vec <__int128> a(n), b(n);
      auto read = [&](vec <__int128> &v){
            for (auto &i: v){
                  ll x; cin >> x; i = x;
            }
      };
      read(b); read(a);
      vec <int> pa(n), deg(n);
      vec <__int128> k(n);
      for (int i = 1; i < n; ++i){
            ll ki;
            cin >> pa[i] >> ki, --pa[i];
            k[i] = ki;
            ++deg[pa[i]];
      }
      vec <int> bfs;
      for (int i = 0; i < n; ++i){
            if (!deg[i]){
                  bfs.push_back(i);
            }
      }
      for (int pt = 0; pt < sz(bfs); ++pt){
            int u = bfs[pt];
            if (u == 0){
                  cout << (b[0] >= a[0] ? "YES" : "NO\n");
                  return 0;
            }
            if (b[u] < -inf){
                  cout << "NO\n";
                  return 0;
            }
            if (a[u] < b[u]){
                  b[pa[u]] += b[u] - a[u];
            }
            else{
                  b[pa[u]] -= k[u] * (a[u] - b[u]);
            }
            if (!--deg[pa[u]]){
                  bfs.push_back(pa[u]);
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
