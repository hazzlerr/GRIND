// Since we only need a matching of size k and maximum number of neighbors that node can have is n, we only need to consider 2 * n * k edges

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

struct edge{
      int u, v, f, w, c;
      edge() {}
      edge(int u, int v, int f, int w, int c): u(u), v(v), f(f), w(w), c(c) {}
};

const int N = 1.6e4 + 42, inf = 1e9 + 42;

vec <int> g[N];
vec <edge> e;

void add(int u, int v, int w, int c){
//      cout << u << " " << v << " " << w << "\n";
      g[u].push_back(sz(e));
      e.push_back({u, v, 0, w, c});
      g[v].push_back(sz(e));
      e.push_back({v, u, 0, -w, 0});
}

pii mcf(int n, int maxf, int s, int t){
      int flow = 0, cost = 0;
      while(flow < maxf){
            vec <int> id(n, 2), d(n, inf), p(n);
            deque <int> q;
            q.push_back(s);
            d[s] = 0;
            while(!q.empty()){
                  int u = q.front();
                  q.pop_front();
                  id[u] = 0;
                  for (auto &i: g[u]){
                        auto [u, v, f, w, c] = e[i];
                        if (f < c && umin(d[v], d[u] + w)){
                              p[v] = i;
                              if (id[v] == 2){
                                    q.push_back(v);
                              }
                              if (id[v] == 0){
                                    q.push_front(v);
                              }
                              id[v] = 1;
                        }
                  }
            }
            if (d[t] == inf) break;
            int f = maxf - flow;
            int u = t;
            while(u != s){
                  int i = p[u];
                  umin(f, e[i].c - e[i].f);
                  u = e[i].u;
            }
            flow += f, cost += f * d[t];
            u = t;
            while(u != s){
                  int i = p[u];
                  e[i].f += f, e[i ^ 1].f -= f;
                  u = e[i].u;
            }
      }
      return {flow, cost};
}

inline int solve(){
      int n, k;
      cin >> n >> k;
      vec <int> a(1 << n);
      for (auto &i: a) cin >> i;
      vec <array <int, 3>> we;
      for (int i = 0; i < (1 << n); ++i){
            for (int j = 0; j < n; ++j){
                  if (~i >> j & 1){
                        we.push_back({-(a[i] + a[i ^ (1 << j)]), i, i ^ (1 << j)});
                  }
            }
      }
      int cut = min(sz(we), 2 * n * k);
      nth_element(we.begin(), we.begin() + cut - 1, we.end());
      while(sz(we) > cut) we.pop_back();
      vec <int> ve;
      for (auto &[w, u, v]: we){
            if (__builtin_parity(u)) swap(u, v);
//            cout << u << " -> " << v << " = " << w << "\n";
            ve.push_back(u);
            ve.push_back(v);
      }
      sort(all(ve));
      ve.erase(unique(all(ve)), ve.end());
      int s = sz(ve), t = sz(ve) + 1;
      for (int i = 0; i < sz(ve); ++i){
//            cout << i << ": " << ve[i] << "\n";
            if (__builtin_parity(ve[i])){
                  add(i, t, 0, 1);
            }
            else{
                  add(s, i, 0, 1);
            }
      }
      for (auto [w, u, v]: we){
            u = lower_bound(all(ve), u) - ve.begin();
            v = lower_bound(all(ve), v) - ve.begin();
            add(u, v, w, 1);
      }
      cout << -mcf(t + 1, k, s, t).se;
      return 0;
}

signed main(){
      ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
      int tst = 1; //cin >> tst;
      while(tst--) solve();
      return 0;
}
