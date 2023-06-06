/*
  Time: 18:20
  Num of Submissions: 2
  Analysis: I had a hard time solving it because I misread the problem and thought there are at most 7 PRIME divisiors ;(
            Overall it's a good problem, which strengthened my understanding of algo for finding minimum cycle 
  Rating: 2600
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

const int A = 1e6 + 42;

int md[A];

inline int solve(){
      int n; cin >> n;
      vec <int> a(n);
      for (auto &i: a) cin >> i;
      vec <vec <pii>> g(A);
      for (int i = 0; i < n; ++i){
            if (a[i] == 1){
                  cout << "1\n";
                  return 0;
            }
            vec <pii> dv;
            while(a[i] > 1){
                  int d = md[a[i]];
                  if (dv.empty() || dv.back().fi != d){
                        dv.emplace_back(d, 1);
                  }
                  else ++dv.back().se;
                  a[i] /= d;
            }
            if (sz(dv) == 1){
                  auto [u, su] = dv[0];
                  if (su % 2 == 0){
                        cout << "1\n";
                        return 0;
                  }
                  g[1].push_back({u, i});
                  g[u].push_back({1, i});
            }
            if (sz(dv) == 2){
                  auto [u, su] = dv[0];
                  auto [v, sv] = dv[1];
                  if (su % 2 && sv % 2){
                        g[u].push_back({v, i});
                        g[v].push_back({u, i});
                  }
                  else if (su % 2){
                        g[1].push_back({u, i});
                        g[u].push_back({1, i});
                  }
                  else if (sv % 2){
                        g[1].push_back({v, i});
                        g[v].push_back({1, i});
                  }
                  else{
                        cout << "1\n";
                        return 0;
                  }
            }
      }
      int ans = 1e9;
      vec <int> d(A), p(A);
      for (int i = 1; i * i <= A; ++i){
            if (md[i] != i || g[i].empty()) continue;
            fill(all(d), 1e9), fill(all(p), -1);
            vec <int> bfs = {i};
            d[i] = 0, p[i] = -1;
            for (int pt = 0; pt < sz(bfs); ++pt){
                  int u = bfs[pt];
                  for (auto &[v, id]: g[u]){
                        if (d[v] <= d[u] + 1 && p[u] != id){
                              umin(ans, d[v] + d[u] + 1);
                        }
                        if (umin(d[v], d[u] + 1)){
                              bfs.push_back(v);
                              p[v] = id;
                        }
                  }
            }
      }
      cout << (ans == 1e9 ? -1 : ans) << "\n";
      return 0;
}

inline void precalc(){
      md[1] = 1;
      for (int i = 2; i < A; ++i){
            if (md[i]) continue;
            for (int j = i; j < A; j += i){
                  md[j] = i;
            }
      }
}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; //cin >> tst;
      precalc();
      while(tst--) solve();
      return 0;
}
