// I knew it was a graph + topsort'ish thing, but for some reason I didn't want to think about it and instead spent all of my time working on silly greedy

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

inline int solve(){
      int n; cin >> n;
      vec <int> nxt(n);
      vec <vec <int>> g(n + 1);
      for (int i = 0; i < n; ++i){
            int j; cin >> j, --j;
            if (j == -2) j = i + 1;
            nxt[i] = j;
            g[j].push_back(i);
      }
      vec <int> p(n + 1);
      int pt = n + 1;
      auto dfs = [&](auto &dfs, int u) -> void {
            p[u] = pt--;
            for (auto &v: g[u]) dfs(dfs, v);
      }; dfs(dfs, n);

      vec <int> st = {n};
      for (int i = n - 1; ~i; --i){
            while(!st.empty() && p[st.back()] < p[i]){
                  st.pop_back();
            }
            if (st.back() != nxt[i]){
                  cout << "-1\n";
                  return 0;
            }
            st.push_back(i);
      }
      for (int i = 0; i < n; ++i){
            cout << p[i] << " ";
      }
      cout << "\n";
      return 0;
}

inline void precalc(){}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; cin >> tst;
      precalc();
      while(tst--) solve();
      return 0;
}
