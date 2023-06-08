/*
  Time: 7:57
  Num of Submissions: 1
  Learned: What q[i] = p[p[i]] looks like
  Analysis: I drew some permutations as a graphs in paint => noticed the pattern => solved
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
      vec <int> p(n);
      for (auto &i: p) cin >> i, --i;
      vec <int> q(n), us(n);
      vec <vec <int>> have(n + 1);
      for (int i = 0; i < n; ++i){
            if (us[i]) continue;
            vec <int> cyc;
            int j = i;
            while(!us[j]){
                  cyc.push_back(j);
                  us[j] = 1, j = p[j];
            }
            int z = sz(cyc);
            if (z % 2){
                  for (int j = 0; j < z; ++j){
                        q[cyc[j]] = cyc[(j + z / 2 + 1) % z];
                  }
            }
            else if (!have[z].empty()){
                  for (int j = 0; j < z; ++j){
                        q[cyc[j]] = have[z][j];
                        q[have[z][j]] = cyc[(j + 1) % z];
                  }
                  have[z].clear();
            }
            else have[z] = cyc;
      }
      bool fl = 1;
      for (auto &i: have) fl &= i.empty();
      if (!fl){
            cout << "-1\n";
            return 0;
      }
      for (auto &i: q){
            cout << i + 1 << " ";
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
